import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import Fastify from 'fastify';
import fastifyStatic from '@fastify/static';
import fastifyView from '@fastify/view';
import pug from 'pug';
import { ProblemCatalog } from './problem-catalog.mjs';
import { ContestCatalog } from './contest-catalog.mjs';
import { MarkdownRenderer } from './markdown-renderer.mjs';
import { loadDownloadConfig } from './download-config.mjs';
import { resolvePublicDataFile, sendPublicFile, streamZip, ZipJobQueue, zipError } from './download-service.mjs';

const projectRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const rojRoot = path.resolve(process.env.ROJ_ROOT || path.join(projectRoot, '..', 'roj'));
const contestsRoot = path.resolve(process.env.CONTESTS_ROOT || path.join(projectRoot, '..', 'contests'));
const publicRoot = path.join(projectRoot, 'public');
const favRoot = path.join(projectRoot, 'fav');
const downloadConfigPath = process.env.DOWNLOAD_CONFIG || path.join(projectRoot, 'config.yaml');
const port = Number.parseInt(process.env.PORT || '3033', 10) || 3033;
const host = process.env.HOST || '0.0.0.0';

const app = Fastify({
  logger: true,
  trustProxy: (address) => address === '127.0.0.1' || address === '::1' || address === '::ffff:127.0.0.1'
});
const { config: downloadConfig, invalid: downloadConfigInvalid } = loadDownloadConfig(downloadConfigPath, app.log);
const renderer = new MarkdownRenderer();
const catalog = new ProblemCatalog(rojRoot, renderer);
catalog.load();
const contestCatalog = new ContestCatalog(contestsRoot, renderer, catalog, { logger: app.log });
contestCatalog.load();
const zipQueue = new ZipJobQueue(downloadConfig.download.zip);

function pageUrl(page, query) {
  const params = new URLSearchParams();
  if (query) params.set('q', query);
  if (page > 1) params.set('page', String(page));
  const value = params.toString();
  return value ? `/?${value}` : '/';
}

function paginationItems(page, totalPages) {
  if (totalPages <= 7) return Array.from({ length: totalPages }, (_, index) => index + 1);
  const items = [1];
  const start = Math.max(2, page - 1);
  const end = Math.min(totalPages - 1, page + 1);
  if (start > 2) items.push('ellipsis');
  for (let current = start; current <= end; current += 1) items.push(current);
  if (end < totalPages - 1) items.push('ellipsis');
  items.push(totalPages);
  return items;
}

function problemViewModel(entry) {
  const hasResourceLimit = entry.time !== null || entry.memory !== null;
  return {
    ...entry,
    publicData: entry.publicData.map((file) => ({
      path: file.path,
      size: file.size,
      downloadUrl: `/problem/${encodeURIComponent(entry.id)}/data/${file.path.split('/').map((part) => encodeURIComponent(part)).join('/')}`
    })),
    hasPublicData: entry.publicData.length > 0,
    resourceLimit: hasResourceLimit ? `${entry.time ?? '-'} ms / ${entry.memory ?? '-'} MB` : null
  };
}

function dataManifest(entry) {
  if (!entry) return null;
  return {
    problemId: entry.id,
    totalFiles: entry.publicData.length,
    totalBytes: entry.publicDataBytes,
    files: entry.publicData.map((file) => ({
      path: file.path,
      size: file.size,
      downloadUrl: `/problem/${encodeURIComponent(entry.id)}/data/${file.path.split('/').map((part) => encodeURIComponent(part)).join('/')}`
    })),
    zipUrl: `/problem/${encodeURIComponent(entry.id)}/data.zip`
  };
}

function zipFailure(reply, error) {
  if (reply.raw.headersSent || reply.sent) return reply;
  if (error?.code === 'ZIP_TIMEOUT') return zipError(reply, 504, 'zip_timeout', 'ZIP 生成超时，请稍后重试。', true);
  if (error?.code === 'CLIENT_ABORTED') return reply;
  return zipError(reply, 500, 'zip_failed', '读取数据或生成 ZIP 失败。', false, error?.failedPath ? { failedPath: error.failedPath } : {});
}

function baseLocals(activePath, values = {}) {
  return { activePath, ...values };
}

await app.register(fastifyView, { engine: { pug }, root: path.join(projectRoot, 'views'), production: process.env.NODE_ENV === 'production' });

if (fs.existsSync(publicRoot)) {
  await app.register(fastifyStatic, {
    root: path.join(publicRoot, 'assets'),
    prefix: '/assets/',
    decorateReply: false,
    index: false,
    setHeaders(res) { res.setHeader('Cache-Control', 'public, max-age=31536000, immutable'); }
  });
}

if (fs.existsSync(favRoot)) {
  await app.register(fastifyStatic, {
    root: favRoot,
    prefix: '/fav/',
    decorateReply: false,
    index: false,
    setHeaders(res) { res.setHeader('Cache-Control', 'public, max-age=31536000, immutable'); }
  });
}

app.get('/', async (request, reply) => {
  const result = catalog.search(request.query?.q, request.query?.page);
  return reply.view('index.pug', baseLocals('/', {
    title: '题目列表 - ROJ',
    problems: result.items.map(problemViewModel),
    pagination: result,
    paginationItems: paginationItems(result.page, result.totalPages),
    pageUrl: (page) => pageUrl(page, result.query)
  }));
});

app.get('/about', async (_request, reply) => reply.view('about.pug', baseLocals('/about', { title: '关于 - ROJ', repositoryUrl: 'https://github.com/rainboyOJ/problems' })));

app.get('/api/problem/:id/data', async (request, reply) => {
  const entry = catalog.get(request.params.id);
  if (!entry) return zipError(reply, 404, 'problem_not_found', '题目不存在。');
  return reply.send(dataManifest(entry));
});

app.get('/contests', async (_request, reply) => {
  const contests = contestCatalog.list();
  return reply.view('contests.pug', baseLocals('/contests', {
    title: '比赛 - ROJ',
    contests
  }));
});

app.get('/contest/:slug', async (request, reply) => {
  const contest = contestCatalog.get(request.params.slug);
  if (!contest) return reply.code(404).view('404.pug', { title: '比赛不存在 - ROJ', message: '没有找到这场比赛。' });

  let statement = null;
  let renderError = null;
  try {
    statement = contestCatalog.render(contest);
  } catch (error) {
    request.log.error({ err: error, contest: contest.slug }, 'Contest Markdown render failed');
    renderError = '这场比赛的 Markdown 暂时无法渲染。';
  }

  return reply.view('contest.pug', baseLocals('/contests', {
    title: `${contest.title} - ROJ`,
    contest,
    statement,
    renderError
  }));
});

app.get('/problem/:id', async (request, reply) => {
  const entry = catalog.get(request.params.id);
  if (!entry) return reply.code(404).view('404.pug', { title: '题目不存在 - ROJ', message: `没有找到题目 ${request.params.id}` });

  let statement = null;
  let renderError = null;
  if (entry.hasMarkdown) {
    try {
      statement = catalog.render(entry);
    } catch (error) {
      request.log.error({ err: error, problemId: entry.id }, 'Problem statement render failed');
      renderError = '这道题的 Markdown 题面暂时无法渲染。';
    }
  }

  return reply.view('problem.pug', baseLocals('/problem', {
    title: `${entry.title} - ROJ`,
    problem: problemViewModel(entry),
    statement,
    renderError,
    pdfUrl: entry.hasPdf ? `/problem/${encodeURIComponent(entry.id)}/pdf` : null,
    solutionUrl: `https://pcs2.roj.ac.cn/problem/roj/${encodeURIComponent(entry.id)}`
  }));
});

app.get('/problem/:id/data.zip', async (request, reply) => {
  const entry = catalog.get(request.params.id);
  if (!entry) return zipError(reply, 404, 'problem_not_found', '题目不存在。');
  if (!entry.publicData.length) return zipError(reply, 404, 'data_not_found', '这道题没有公开数据。');
  const files = entry.publicData.map((file) => resolvePublicDataFile(entry, file.path));
  const missingFile = files.findIndex((file) => !file);
  if (missingFile >= 0) {
    return zipError(reply, 500, 'zip_failed', '公开数据在打包前发生变化，请稍后重试。', true, { failedPath: entry.publicData[missingFile].path });
  }
  const totalBytes = files.reduce((total, file) => total + file.size, 0);
  if (totalBytes > downloadConfig.download.zip.maxSourceBytes) {
    return zipError(reply, 413, 'zip_too_large', '数据总量超过 ZIP 打包限制。');
  }

  const clientKey = request.ip || request.socket.remoteAddress || 'unknown';
  const queued = zipQueue.submit(clientKey, () => streamZip(reply, request, files, {
    problemId: entry.id,
    compressionLevel: downloadConfig.download.zip.compressionLevel,
    timeoutMs: downloadConfig.download.zip.timeoutMs
  }));
  if (!queued.accepted) {
    reply.header('Retry-After', '5');
    return zipError(reply, 429, 'zip_queue_full', queued.reason === 'client' ? '你已有一个 ZIP 任务正在处理。' : '当前 ZIP 下载任务较多，请稍后重试。', true);
  }
  const cancelQueued = () => queued.cancel();
  request.raw.once('close', cancelQueued);
  try {
    await queued.promise;
  } catch (error) {
    zipFailure(reply, error);
  } finally {
    request.raw.off('close', cancelQueued);
  }
});

app.get('/problem/:id/data/*', async (request, reply) => {
  const entry = catalog.get(request.params.id);
  const file = resolvePublicDataFile(entry, request.params['*']);
  if (!file) return reply.code(404).send('Not found');
  return sendPublicFile(request, reply, file);
});

app.get('/problem/:id/pdf', async (request, reply) => {
  const entry = catalog.get(request.params.id);
  const pdfPath = catalog.pdfPath(entry);
  if (!pdfPath) return reply.code(404).view('404.pug', { title: '题面不存在 - ROJ', message: '这道题的 PDF 题面不存在。' });
  reply.type('application/pdf');
  return reply.send(fs.createReadStream(pdfPath));
});

app.get('/problem/:id/asset/*', async (request, reply) => {
  const entry = catalog.get(request.params.id);
  let assetPath = null;
  try { assetPath = catalog.assetPath(entry, request.params['*']); } catch { assetPath = null; }
  if (!assetPath) return reply.code(404).send('Not found');
  const contentTypes = {
    '.png': 'image/png',
    '.jpg': 'image/jpeg',
    '.jpeg': 'image/jpeg',
    '.gif': 'image/gif',
    '.webp': 'image/webp',
    '.svg': 'image/svg+xml'
  };
  reply.type(contentTypes[path.extname(assetPath).toLocaleLowerCase()] || 'application/octet-stream');
  return reply.send(fs.createReadStream(assetPath));
});

app.get('/contest/:slug/asset/*', async (request, reply) => {
  const entry = contestCatalog.get(request.params.slug);
  let assetPath = null;
  try { assetPath = contestCatalog.assetPath(entry, request.params['*']); } catch { assetPath = null; }
  if (!assetPath) return reply.code(404).send('Not found');
  const contentTypes = {
    '.png': 'image/png',
    '.jpg': 'image/jpeg',
    '.jpeg': 'image/jpeg',
    '.gif': 'image/gif',
    '.webp': 'image/webp',
    '.svg': 'image/svg+xml'
  };
  reply.type(contentTypes[path.extname(assetPath).toLocaleLowerCase()] || 'application/octet-stream');
  return reply.send(fs.createReadStream(assetPath));
});

app.setNotFoundHandler(async (request, reply) => {
  if (request.raw.url?.startsWith('/assets/')) return reply.code(404).send('Not found');
  return reply.code(404).view('404.pug', { title: '页面不存在 - ROJ', message: '你访问的页面不存在。' });
});

app.setErrorHandler(async (error, request, reply) => {
  request.log.error({ err: error }, 'Unhandled request error');
  if (reply.sent) return;
  return reply.code(500).view('500.pug', { title: '服务错误 - ROJ', message: '页面暂时无法打开，请稍后再试。' });
});

try {
  await app.listen({ port, host });
  app.log.info({ host, port, rojRoot, contestsRoot, problems: catalog.entries.length, contests: contestCatalog.entries.length, downloadConfigPath, downloadConfigInvalid }, 'ROJ is serving');
} catch (error) {
  app.log.error(error);
  process.exit(1);
}
