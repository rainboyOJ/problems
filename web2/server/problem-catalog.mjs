import fs from 'node:fs';
import path from 'node:path';

class LruCache {
  constructor(limit = 128) {
    this.limit = limit;
    this.items = new Map();
  }

  get(key) {
    if (!this.items.has(key)) return undefined;
    const value = this.items.get(key);
    this.items.delete(key);
    this.items.set(key, value);
    return value;
  }

  set(key, value) {
    this.items.delete(key);
    this.items.set(key, value);
    while (this.items.size > this.limit) this.items.delete(this.items.keys().next().value);
    return value;
  }

  clear() {
    this.items.clear();
  }
}

function readConfig(configPath) {
  try {
    const value = JSON.parse(fs.readFileSync(configPath, 'utf8'));
    // A config file may be valid JSON without being a usable object.
    if (!value || typeof value !== 'object' || Array.isArray(value)) return { config: {}, invalid: true };
    return { config: value, invalid: false };
  } catch {
    return { config: {}, invalid: true };
  }
}

function optionalString(value) {
  return typeof value === 'string' && value.trim() ? value.trim() : null;
}

function optionalNumber(value) {
  return typeof value === 'number' && Number.isFinite(value) ? value : null;
}

function normalizeTags(value) {
  return Array.isArray(value) ? value.filter((tag) => typeof tag === 'string' && tag.trim()).map((tag) => tag.trim()) : [];
}

export class ProblemCatalog {
  constructor(rootDir, renderer, options = {}) {
    this.rootDir = path.resolve(rootDir);
    this.renderer = renderer;
    this.pageSize = options.pageSize || 30;
    this.renderCache = new LruCache(options.cacheSize || 128);
    this.entries = [];
  }

  load() {
    const entries = [];
    const names = fs.readdirSync(this.rootDir, { withFileTypes: true });

    for (const item of names) {
      if (!item.isDirectory() || !/^\d+$/.test(item.name)) continue;
      const id = item.name;
      const dir = path.join(this.rootDir, id);
      const files = new Set(fs.readdirSync(dir));
      const hasMarkdown = files.has('content.md');
      const hasPdf = files.has('content.pdf');
      if (!hasMarkdown && !hasPdf) continue;

      const { config, invalid } = readConfig(path.join(dir, 'config.json'));
      const configuredTitle = optionalString(config.title);
      const title = configuredTitle || `题目 ${id}`;

      entries.push({
        id,
        number: Number(id),
        title,
        time: optionalNumber(config.time),
        memory: optionalNumber(config.memory),
        tags: normalizeTags(config.tags),
        source: optionalString(config.source),
        dir,
        hasMarkdown,
        hasPdf,
        statementKind: hasMarkdown ? 'markdown' : 'pdf',
        metadataIncomplete: invalid || !configuredTitle,
        configInvalid: invalid
      });
    }

    entries.sort((a, b) => a.number - b.number);
    this.entries = entries;
    this.renderCache.clear();
    return entries;
  }

  get(id) {
    return this.entries.find((entry) => entry.id === String(id)) || null;
  }

  search(query = '', page = 1) {
    const normalizedQuery = String(query || '').trim();
    const searchValue = normalizedQuery.toLocaleLowerCase();
    const matched = searchValue
      ? this.entries.filter((entry) => entry.id.includes(searchValue) || entry.title.toLocaleLowerCase().includes(searchValue))
      : this.entries;
    const totalPages = Math.max(1, Math.ceil(matched.length / this.pageSize));
    const currentPage = Math.min(Math.max(Number.parseInt(page, 10) || 1, 1), totalPages);
    const start = (currentPage - 1) * this.pageSize;

    return {
      items: matched.slice(start, start + this.pageSize),
      total: matched.length,
      totalPages,
      page: currentPage,
      pageSize: this.pageSize,
      query: normalizedQuery,
      startItem: matched.length ? start + 1 : 0,
      endItem: Math.min(start + this.pageSize, matched.length)
    };
  }

  render(entry) {
    if (!entry?.hasMarkdown) return null;
    const cached = this.renderCache.get(entry.id);
    if (cached) return cached;

    const result = this.renderer.renderFile(path.join(entry.dir, 'content.md'), {
      problemId: entry.id,
      problemDir: entry.dir
    });
    return this.renderCache.set(entry.id, result);
  }

  assetPath(entry, resourcePath) {
    if (!entry || typeof resourcePath !== 'string' || resourcePath.includes('\0')) return null;
    const decoded = decodeURIComponent(resourcePath).replaceAll('\\', '/');
    if (!decoded || decoded.startsWith('/') || decoded.includes('..')) return null;
    const extension = path.extname(decoded).toLocaleLowerCase();
    if (!['.png', '.jpg', '.jpeg', '.gif', '.webp', '.svg'].includes(extension)) return null;

    const resolved = path.resolve(entry.dir, decoded);
    const relative = path.relative(entry.dir, resolved);
    if (!relative || relative.startsWith('..') || path.isAbsolute(relative)) return null;
    if (!fs.existsSync(resolved) || !fs.statSync(resolved).isFile()) return null;
    return resolved;
  }

  pdfPath(entry) {
    if (!entry?.hasPdf) return null;
    const pdfPath = path.join(entry.dir, 'content.pdf');
    return fs.existsSync(pdfPath) && fs.statSync(pdfPath).isFile() ? pdfPath : null;
  }
}
