import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import Fastify from 'fastify';
import fastifyStatic from '@fastify/static';
import fastifyView from '@fastify/view';
import pug from 'pug';
import { ProblemCatalog } from './problem-catalog.mjs';
import { MarkdownRenderer } from './markdown-renderer.mjs';

const projectRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const rojRoot = path.resolve(process.env.ROJ_ROOT || path.join(projectRoot, '..', 'roj'));
const publicRoot = path.join(projectRoot, 'public');
const port = Number.parseInt(process.env.PORT || '3033', 10) || 3033;
const host = process.env.HOST || '0.0.0.0';

const renderer = new MarkdownRenderer();
const catalog = new ProblemCatalog(rojRoot, renderer);
catalog.load();

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
  return { ...entry, resourceLimit: hasResourceLimit ? `${entry.time ?? '-'} ms / ${entry.memory ?? '-'} MB` : null };
}

function baseLocals(activePath, values = {}) {
  return { activePath, ...values };
}

const app = Fastify({ logger: true });

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
    pdfUrl: entry.hasPdf ? `/problem/${encodeURIComponent(entry.id)}/pdf` : null
  }));
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
  app.log.info({ host, port, rojRoot, problems: catalog.entries.length }, 'ROJ is serving');
} catch (error) {
  app.log.error(error);
  process.exit(1);
}
