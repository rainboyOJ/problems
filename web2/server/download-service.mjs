import fs from 'node:fs';
import path from 'node:path';
import { ZipArchive } from 'archiver';

export const PUBLIC_DATA_EXTENSIONS = Object.freeze(new Set(['.in', '.out', '.ans', '.txt', '.dat']));

export function isPublicDataPath(relativePath) {
  if (typeof relativePath !== 'string' || !relativePath || relativePath.startsWith('/') || relativePath.includes('\\')) return false;
  const parts = relativePath.split('/');
  if (parts.some((part) => !part || part === '.' || part === '..' || part.startsWith('.'))) return false;
  return PUBLIC_DATA_EXTENSIONS.has(path.posix.extname(relativePath).toLocaleLowerCase());
}

export function scanPublicData(dataDir) {
  const root = path.resolve(dataDir);
  try {
    const rootStat = fs.lstatSync(root);
    if (!rootStat.isDirectory() || rootStat.isSymbolicLink()) return [];
  } catch {
    return [];
  }
  const files = [];
  const pending = [root];
  while (pending.length) {
    const current = pending.pop();
    let entries;
    try {
      entries = fs.readdirSync(current, { withFileTypes: true });
    } catch {
      continue;
    }
    for (const entry of entries) {
      if (entry.name.startsWith('.') || entry.isSymbolicLink()) continue;
      const absolute = path.join(current, entry.name);
      if (entry.isDirectory()) {
        pending.push(absolute);
        continue;
      }
      if (!entry.isFile()) continue;
      const relativePath = path.relative(root, absolute).split(path.sep).join('/');
      if (!isPublicDataPath(relativePath)) continue;
      try {
        const stat = fs.statSync(absolute);
        if (!stat.isFile()) continue;
        files.push({
          path: relativePath,
          absolutePath: absolute,
          size: stat.size,
          mtimeMs: stat.mtimeMs
        });
      } catch {
        // A file removed while scanning is not part of the manifest.
      }
    }
  }
  files.sort((a, b) => a.path.localeCompare(b.path));
  return files;
}

export function resolvePublicDataFile(entry, rawPath) {
  if (!entry || typeof rawPath !== 'string' || rawPath.includes('\0')) return null;
  let decoded;
  try {
    decoded = decodeURIComponent(rawPath);
  } catch {
    return null;
  }
  if (!isPublicDataPath(decoded)) return null;
  const manifestFile = entry.publicData?.find((file) => file.path === decoded);
  if (!manifestFile) return null;
  try {
    const stat = fs.lstatSync(manifestFile.absolutePath);
    if (!stat.isFile()) return null;
    return { ...manifestFile, size: stat.size, mtimeMs: stat.mtimeMs };
  } catch {
    return null;
  }
}

export function etagFor(stat) {
  return `"${stat.size.toString(16)}-${Math.floor(stat.mtimeMs).toString(16)}"`;
}

function parseRange(value, size) {
  if (typeof value !== 'string' || !value.startsWith('bytes=') || value.includes(',')) return null;
  const match = /^bytes=(\d*)-(\d*)$/.exec(value.trim());
  if (!match) return null;
  const startValue = match[1];
  const endValue = match[2];
  if (!startValue && !endValue) return null;
  let start;
  let end;
  if (!startValue) {
    const suffix = Number(endValue);
    if (!Number.isInteger(suffix) || suffix <= 0) return null;
    start = Math.max(size - suffix, 0);
    end = size - 1;
  } else {
    start = Number(startValue);
    end = endValue ? Number(endValue) : size - 1;
    if (!Number.isSafeInteger(start) || !Number.isSafeInteger(end) || start > end || start >= size) return { invalid: true };
    end = Math.min(end, size - 1);
  }
  return { start, end };
}

export function sendPublicFile(request, reply, file) {
  const stat = { size: file.size, mtimeMs: file.mtimeMs };
  const etag = etagFor(stat);
  const lastModified = new Date(stat.mtimeMs).toUTCString();
  reply.header('Accept-Ranges', 'bytes');
  reply.header('ETag', etag);
  reply.header('Last-Modified', lastModified);
  reply.header('Cache-Control', 'public, max-age=3600, must-revalidate');
  reply.header('X-Content-Type-Options', 'nosniff');
  const filename = path.basename(file.path).replace(/[\r\n"\\]/g, '_') || 'download';
  const asciiFilename = filename.replace(/[^\x20-\x7E]/g, '_');
  reply.header('Content-Disposition', `attachment; filename="${asciiFilename}"; filename*=UTF-8''${encodeURIComponent(filename)}`);
  reply.type('application/octet-stream');

  const ifNoneMatch = request.headers['if-none-match'];
  const ifModifiedSince = Date.parse(request.headers['if-modified-since'] || '');
  const modifiedAtSecond = Math.floor(stat.mtimeMs / 1000) * 1000;
  const notModified = ifNoneMatch
    ? ifNoneMatch === etag
    : Number.isFinite(ifModifiedSince) && modifiedAtSecond <= ifModifiedSince;
  if (notModified) {
    return reply.code(304).send();
  }

  const range = parseRange(request.headers.range, stat.size);
  if (range?.invalid) {
    reply.header('Content-Range', `bytes */${stat.size}`);
    return reply.code(416).send();
  }
  if (range) {
    const length = range.end - range.start + 1;
    reply.code(206);
    reply.header('Content-Range', `bytes ${range.start}-${range.end}/${stat.size}`);
    reply.header('Content-Length', length);
    return reply.send(fs.createReadStream(file.absolutePath, { start: range.start, end: range.end }));
  }
  reply.header('Content-Length', stat.size);
  return reply.send(fs.createReadStream(file.absolutePath));
}

export class ZipJobQueue {
  constructor({ activeJobs = 1, queueSize = 3, perClient = 1 } = {}) {
    this.activeJobs = activeJobs;
    this.queueSize = queueSize;
    this.perClient = perClient;
    this.active = 0;
    this.queue = [];
    this.clients = new Map();
  }

  submit(clientKey, task) {
    const current = this.clients.get(clientKey) || 0;
    if (current >= this.perClient) return { accepted: false, reason: 'client' };
    if (this.active >= this.activeJobs && this.queue.length >= this.queueSize) return { accepted: false, reason: 'queue' };
    this.clients.set(clientKey, current + 1);
    let cancel;
    const promise = new Promise((resolve, reject) => {
      const job = { clientKey, task, resolve, reject, cancelled: false, started: false };
      cancel = () => {
        if (job.cancelled || job.started) return;
        job.cancelled = true;
        const index = this.queue.indexOf(job);
        if (index >= 0) this.queue.splice(index, 1);
        this.releaseClient(clientKey);
        reject(Object.assign(new Error('ZIP request cancelled'), { code: 'CLIENT_ABORTED' }));
      };
      this.queue.push(job);
      this.pump();
    });
    return { accepted: true, promise, cancel: () => cancel?.() };
  }

  releaseClient(clientKey) {
    const current = this.clients.get(clientKey) || 0;
    if (current <= 1) this.clients.delete(clientKey);
    else this.clients.set(clientKey, current - 1);
  }

  pump() {
    while (this.active < this.activeJobs && this.queue.length) {
      const job = this.queue.shift();
      if (job.cancelled) continue;
      job.started = true;
      this.active += 1;
      Promise.resolve().then(job.task).then(job.resolve, job.reject).finally(() => {
        this.active -= 1;
        this.releaseClient(job.clientKey);
        this.pump();
      });
    }
  }
}

export function zipError(reply, statusCode, error, message, retryable = false, extra = {}) {
  return reply.code(statusCode).type('application/json').send({ error, message, retryable, ...extra });
}

export async function streamZip(reply, request, files, { problemId, compressionLevel = 1, timeoutMs = 15 * 60 * 1000 } = {}) {
  const archive = new ZipArchive({ zlib: { level: compressionLevel } });
  let settled = false;
  let timer;
  const finish = (error) => {
    if (settled) return;
    settled = true;
    clearTimeout(timer);
    request.raw.off('close', onClose);
    if (error) rejectPromise(error);
    else resolvePromise();
  };
  let resolvePromise;
  let rejectPromise;
  const result = new Promise((resolve, reject) => { resolvePromise = resolve; rejectPromise = reject; });
  const onClose = () => {
    if (settled || reply.raw.writableEnded) return;
    archive.abort();
    finish(Object.assign(new Error('Client disconnected'), { code: 'CLIENT_ABORTED' }));
  };

  reply.hijack();
  reply.raw.statusCode = 200;
  reply.raw.setHeader('Content-Type', 'application/zip');
  reply.raw.setHeader('Content-Disposition', `attachment; filename="roj-${problemId}-data.zip"`);
  reply.raw.setHeader('Cache-Control', 'no-store');
  reply.raw.setHeader('X-Content-Type-Options', 'nosniff');
  request.raw.once('close', onClose);
  reply.raw.once('finish', () => finish());
  archive.on('error', (error) => {
    archive.abort();
    if (!reply.raw.writableEnded) reply.raw.destroy(error);
    finish(error);
  });
  timer = setTimeout(() => {
    archive.abort();
    const error = Object.assign(new Error('ZIP generation timed out'), { code: 'ZIP_TIMEOUT' });
    if (!reply.raw.writableEnded) reply.raw.destroy(error);
    finish(error);
  }, timeoutMs);
  timer.unref?.();

  archive.pipe(reply.raw);
  for (const file of files) {
    const stream = fs.createReadStream(file.absolutePath);
    stream.once('error', (error) => archive.emit('error', Object.assign(error, { failedPath: file.path })));
    archive.append(stream, { name: file.path });
  }
  await archive.finalize();
  return result;
}
