import fs from 'node:fs';
import path from 'node:path';
import matter from 'gray-matter';

const STATUS_LABELS = {
  upcoming: '即将开始',
  ongoing: '进行中',
  archived: '已结束'
};

const DISPLAY_KEYS = new Set(['title', 'date', 'endDate', 'description', 'organizer', 'status', 'tags', 'draft']);

function optionalString(value) {
  return typeof value === 'string' && value.trim() ? value.trim() : null;
}

function normalizeDate(value) {
  if (value instanceof Date) {
    if (Number.isNaN(value.getTime())) return null;
    return [value.getUTCFullYear(), value.getUTCMonth() + 1, value.getUTCDate()]
      .map((part, index) => index === 0 ? String(part).padStart(4, '0') : String(part).padStart(2, '0'))
      .join('-');
  }
  if (typeof value !== 'string') return null;
  const match = value.trim().match(/^(\d{4})-(\d{2})-(\d{2})$/);
  if (!match) return null;
  const candidate = new Date(`${match[0]}T00:00:00Z`);
  if (Number.isNaN(candidate.getTime()) || candidate.toISOString().slice(0, 10) !== match[0]) return null;
  return match[0];
}

function todayInShanghai() {
  const parts = new Intl.DateTimeFormat('en-US', {
    timeZone: 'Asia/Shanghai',
    year: 'numeric',
    month: '2-digit',
    day: '2-digit'
  }).formatToParts(new Date());
  const values = Object.fromEntries(parts.filter((part) => part.type !== 'literal').map((part) => [part.type, part.value]));
  return `${values.year}-${values.month}-${values.day}`;
}

function inferStatus(date, endDate, today = todayInShanghai()) {
  if (!date && !endDate) return null;
  if (date && today < date) return 'upcoming';
  if (endDate && today > endDate) return 'archived';
  if (date && today >= date) return 'ongoing';
  return null;
}

function normalizeStatus(value, date, endDate) {
  const explicit = optionalString(value)?.toLocaleLowerCase();
  return explicit && Object.hasOwn(STATUS_LABELS, explicit) ? explicit : inferStatus(date, endDate);
}

function hasExplicitStatus(value) {
  const status = optionalString(value)?.toLocaleLowerCase();
  return Boolean(status && Object.hasOwn(STATUS_LABELS, status));
}

function formatValue(value) {
  if (value instanceof Date) return normalizeDate(value) || value.toISOString();
  if (Array.isArray(value)) return value.map((item) => formatValue(item)).join(', ');
  if (value && typeof value === 'object') return JSON.stringify(value);
  return String(value);
}

function metadataEntries(data, entry) {
  const fields = [];
  const add = (label, value) => {
    if (value !== null && value !== undefined && value !== '') fields.push({ label, value: formatValue(value) });
  };

  add('开始日期', entry.date);
  add('结束日期', entry.endDate);
  add('简介', entry.description);
  add('组织者', entry.organizer);
  add('状态', entry.status ? STATUS_LABELS[entry.status] : null);
  add('标签', entry.tags.length ? entry.tags : null);

  for (const [key, value] of Object.entries(data)) {
    if (DISPLAY_KEYS.has(key) || value === null || value === undefined || value === '') continue;
    add(key, value);
  }
  return fields;
}

function fileSignature(rootDir) {
  if (!fs.existsSync(rootDir)) return 'missing';
  const files = fs.readdirSync(rootDir, { withFileTypes: true })
    .filter((item) => item.isFile() && path.extname(item.name).toLocaleLowerCase() === '.md')
    .map((item) => {
      const filePath = path.join(rootDir, item.name);
      try {
        const stat = fs.statSync(filePath);
        return `${item.name}:${stat.mtimeMs}:${stat.size}`;
      } catch {
        return null;
      }
    })
    .filter(Boolean)
    .sort();
  return files.join('|');
}

export class ContestCatalog {
  constructor(rootDir, renderer, problemCatalog, options = {}) {
    this.rootDir = path.resolve(rootDir);
    this.renderer = renderer;
    this.problemCatalog = problemCatalog;
    this.logger = options.logger || console;
    this.entries = [];
    this.signature = null;
    this.renderCache = new Map();
  }

  refreshIfNeeded() {
    const signature = fileSignature(this.rootDir);
    if (signature !== this.signature) this.load(signature);
    for (const entry of this.entries) {
      if (entry.statusExplicit) continue;
      entry.status = inferStatus(entry.date, entry.endDate);
      entry.statusLabel = entry.status ? STATUS_LABELS[entry.status] : null;
      const statusField = entry.metadata.find((field) => field.label === '状态');
      if (statusField) statusField.value = entry.statusLabel || '';
    }
    return this.entries;
  }

  load(signature = fileSignature(this.rootDir)) {
    const entries = [];
    const seen = new Set();
    let names = [];
    try {
      names = fs.readdirSync(this.rootDir, { withFileTypes: true });
    } catch (error) {
      this.logger.warn?.({ err: error, contestsRoot: this.rootDir }, 'Contest directory cannot be read');
    }

    for (const item of names) {
      if (!item.isFile() || path.extname(item.name).toLocaleLowerCase() !== '.md') continue;
      const slug = path.basename(item.name, path.extname(item.name));
      if (!/^[a-z0-9_-]+$/.test(slug)) {
        this.logger.warn?.({ file: item.name }, 'Contest file has an invalid slug');
        continue;
      }
      if (seen.has(slug)) {
        this.logger.warn?.({ slug, file: item.name }, 'Duplicate contest slug');
        continue;
      }

      const filePath = path.join(this.rootDir, item.name);
      let parsed;
      try {
        parsed = matter(fs.readFileSync(filePath, 'utf8'));
      } catch (error) {
        this.logger.warn?.({ err: error, file: item.name }, 'Contest frontmatter cannot be parsed');
        continue;
      }
      if (!parsed.data || typeof parsed.data !== 'object' || Array.isArray(parsed.data)) {
        this.logger.warn?.({ file: item.name }, 'Contest frontmatter must be an object');
        continue;
      }

      const title = optionalString(parsed.data.title);
      if (!title) {
        this.logger.warn?.({ file: item.name }, 'Contest title is missing');
        continue;
      }
      if (parsed.data.draft === true) continue;

      const date = normalizeDate(parsed.data.date);
      const endDate = normalizeDate(parsed.data.endDate);
      const tags = Array.isArray(parsed.data.tags)
        ? parsed.data.tags.filter((tag) => typeof tag === 'string' && tag.trim()).map((tag) => tag.trim())
        : [];
      const status = normalizeStatus(parsed.data.status, date, endDate);
      const entry = {
        slug,
        title,
        date,
        endDate,
        description: optionalString(parsed.data.description),
        organizer: optionalString(parsed.data.organizer),
        status,
        statusExplicit: hasExplicitStatus(parsed.data.status),
        statusLabel: status ? STATUS_LABELS[status] : null,
        tags,
        filePath,
        resourceDir: path.join(this.rootDir, slug),
        metadata: null
      };
      entry.metadata = metadataEntries(parsed.data, entry);
      entries.push(entry);
      seen.add(slug);
    }

    entries.sort((a, b) => {
      if (a.date && b.date && a.date !== b.date) return b.date.localeCompare(a.date);
      if (a.date && !b.date) return -1;
      if (!a.date && b.date) return 1;
      return a.slug.localeCompare(b.slug, 'en', { numeric: true });
    });
    this.entries = entries;
    this.signature = signature;
    this.renderCache.clear();
    return entries;
  }

  list() {
    return this.refreshIfNeeded();
  }

  get(slug) {
    this.refreshIfNeeded();
    return this.entries.find((entry) => entry.slug === String(slug)) || null;
  }

  render(entry) {
    if (!entry) return null;
    this.refreshIfNeeded();
    const cached = this.renderCache.get(entry.slug);
    if (cached) return cached;

    const rendered = this.renderer.renderFile(entry.filePath, {
      resourceDir: this.rootDir,
      assetScope: entry.slug,
      assetBase: `/contest/${encodeURIComponent(entry.slug)}/asset`
    });
    const problemLinks = rendered.problemLinks
      .map((link) => {
        const problem = this.problemCatalog.get(link.id);
        if (!problem) {
          this.logger.warn?.({ contest: entry.slug, problemId: link.id }, 'Contest links to a missing problem');
          return null;
        }
        return { ...link, title: problem.title, href: `/problem/${encodeURIComponent(problem.id)}` };
      })
      .filter(Boolean);
    const result = { ...rendered, problemLinks };
    this.renderCache.set(entry.slug, result);
    return result;
  }

  assetPath(entry, resourcePath) {
    if (!entry || typeof resourcePath !== 'string' || resourcePath.includes('\0')) return null;
    let decoded;
    try {
      decoded = decodeURIComponent(resourcePath).replaceAll('\\', '/');
    } catch {
      return null;
    }
    if (!decoded || decoded.startsWith('/') || decoded.includes('..')) return null;
    const extension = path.extname(decoded).toLocaleLowerCase();
    if (!['.png', '.jpg', '.jpeg', '.gif', '.webp', '.svg'].includes(extension)) return null;
    const resolved = path.resolve(entry.resourceDir, decoded);
    const relative = path.relative(entry.resourceDir, resolved);
    if (!relative || relative.startsWith('..') || path.isAbsolute(relative)) return null;
    if (!fs.existsSync(resolved) || !fs.statSync(resolved).isFile()) return null;
    return resolved;
  }
}

export { STATUS_LABELS };
