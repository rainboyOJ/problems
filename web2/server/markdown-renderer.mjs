import fs from 'node:fs';
import path from 'node:path';
import matter from 'gray-matter';
import MarkdownIt from 'markdown-it';
import Katex from 'katex';
import TexMath from 'markdown-it-texmath';
import Container from 'markdown-it-container';
import taskCheckbox from 'markdown-it-task-checkbox';
import insDel from 'markdown-it-ins-del';
import sub from 'markdown-it-sub';
import sup from 'markdown-it-sup';
import mark from 'markdown-it-mark';
import abbr from 'markdown-it-abbr';
import { full as emoji } from 'markdown-it-emoji';
import twemoji from 'twemoji';

const ADMONITION_TITLES = { note: '注', info: '信息', tip: '提示', warning: '注意', danger: '警告', example: '示例', quote: '引用' };

function escapeHtml(value) {
  return String(value ?? '').replace(/[&<>"']/g, (char) => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;' }[char]));
}

function slugify(value) {
  const base = String(value || '').trim().toLocaleLowerCase().replace(/[^\p{L}\p{N}]+/gu, '-').replace(/^-+|-+$/g, '');
  return base || 'section';
}

function uniqueHeadingId(base, used) {
  let id = base;
  let count = 2;
  while (used.has(id)) id = `${base}-${count++}`;
  used.add(id);
  return id;
}

function normalizeLanguage(value) {
  const language = String(value || '').trim().toLocaleLowerCase().split(/\s+/, 1)[0] || 'text';
  const map = { cxx: 'cpp', 'c++': 'cpp', cc: 'cpp', h: 'c', py: 'python', js: 'javascript', ts: 'typescript', sh: 'bash', plaintext: 'text', plain: 'text' };
  return map[language] || language.replace(/[^a-z0-9_-]/g, '') || 'text';
}

function encodePath(value) {
  return value.split('/').map((part) => encodeURIComponent(part)).join('/');
}

function localImageUrl(src, env) {
  const cleanSrc = src.split('#', 1)[0].split('?', 1)[0];
  const resourceDir = env.resourceDir || env.problemDir;
  if (!resourceDir || !cleanSrc || cleanSrc.startsWith('/') || cleanSrc.includes('\\') || cleanSrc.includes('..')) return null;
  const fullPath = path.resolve(resourceDir, cleanSrc);
  const relative = path.relative(resourceDir, fullPath);
  const normalizedRelative = relative.split(path.sep).join('/');
  const extension = path.extname(fullPath).toLocaleLowerCase();
  if (!relative || relative.startsWith('..') || path.isAbsolute(relative) || !['.png', '.jpg', '.jpeg', '.gif', '.webp', '.svg'].includes(extension)) return null;
  if (env.assetScope && normalizedRelative !== env.assetScope && !normalizedRelative.startsWith(`${env.assetScope}/`)) return null;
  if (!fs.existsSync(fullPath) || !fs.statSync(fullPath).isFile()) return null;
  const assetBase = env.assetBase || `/problem/${encodeURIComponent(env.problemId)}/asset`;
  const urlRelative = env.assetScope && normalizedRelative.startsWith(`${env.assetScope}/`)
    ? normalizedRelative.slice(env.assetScope.length + 1)
    : normalizedRelative;
  return `${assetBase}/${encodePath(urlRelative)}`;
}

function addHeadingIds(tokens, env) {
  const used = new Set();
  for (let index = 0; index < tokens.length; index += 1) {
    const token = tokens[index];
    if (token.type !== 'heading_open' || !['h2', 'h3'].includes(token.tag)) continue;
    const inline = tokens[index + 1];
    const id = uniqueHeadingId(slugify(inline?.content), used);
    token.attrSet('id', id);
    env.toc.push({ id, level: Number(token.tag.slice(1)), text: inline?.content || '' });
  }
}

function extractProblemLinks(tokens) {
  const links = [];
  const seen = new Set();
  for (const token of tokens) {
    if (token.type !== 'inline' || !token.children) continue;
    for (let index = 0; index < token.children.length; index += 1) {
      const child = token.children[index];
      if (child.type !== 'link_open') continue;
      const href = child.attrGet('href') || '';
      const match = href.match(/^\/problem\/(\d+)(?:[?#].*)?\/?$/);
      if (!match || seen.has(match[1])) continue;
      const labelParts = [];
      for (let labelIndex = index + 1; labelIndex < token.children.length; labelIndex += 1) {
        const labelToken = token.children[labelIndex];
        if (labelToken.type === 'link_close') break;
        if (['text', 'code_inline', 'emoji'].includes(labelToken.type)) labelParts.push(labelToken.content);
      }
      seen.add(match[1]);
      links.push({ id: match[1], label: labelParts.join('').trim() || match[1] });
    }
  }
  return links;
}

export class MarkdownRenderer {
  constructor() {
    this.md = new MarkdownIt({ html: false, linkify: true, typographer: true, breaks: false });
    this.md.use(TexMath, { engine: Katex, delimiters: ['dollars', 'beg_end', 'julia'], katexOptions: { strict: false, throwOnError: false, macros: { '\\R': '\\mathbb{R}' } } });
    this.md.use(taskCheckbox, { disabled: true });
    this.md.use(insDel).use(sub).use(sup).use(mark).use(abbr).use(emoji);

    this.md.use(Container, 'line', {
      validate: (params) => params.trim() === 'line',
      render: (tokens, index) => tokens[index].nesting === 1 ? '<div class="sample-group">\n' : '</div>\n'
    });

    for (const type of Object.keys(ADMONITION_TITLES)) {
      this.md.use(Container, type, {
        validate: (params) => params.trim().split(/\s+/, 1)[0] === type,
        render: (tokens, index) => tokens[index].nesting === 1
          ? `<aside class="admonition admonition-${type}"><div class="admonition-title">${ADMONITION_TITLES[type]}</div>\n`
          : '</aside>\n'
      });
    }

    this.md.renderer.rules.fence = (tokens, index) => {
      const token = tokens[index];
      const language = normalizeLanguage(token.info);
      const content = token.content.replace(/\n$/, '');
      const label = language === 'text' ? '文本' : language;
      return `<div class="code-block"><div class="code-toolbar"><span class="code-language">${escapeHtml(label)}</span><button class="code-copy-button" type="button" data-copy-code>复制</button></div><pre><code class="language-${escapeHtml(language)}">${escapeHtml(content)}</code></pre></div>\n`;
    };

    this.md.renderer.rules.image = (tokens, index, options, env) => {
      const token = tokens[index];
      const source = token.attrGet('src') || '';
      const alt = token.content || '题面图片';
      const remote = /^(?:https?:)?\/\//i.test(source) ? source.replaceAll(' ', '%20') : null;
      const local = remote ? null : localImageUrl(source, env);
      if (!remote && !local) return `<span class="md-image-missing" role="img" aria-label="${escapeHtml(alt)}">图片暂缺：${escapeHtml(alt)}</span>`;
      const title = token.attrGet('title');
      const titleAttr = title ? ` title="${escapeHtml(title)}"` : '';
      return `<img class="md-image" src="${escapeHtml(remote || local)}" alt="${escapeHtml(alt)}" loading="lazy"${titleAttr}>`;
    };

    const defaultLinkOpen = this.md.renderer.rules.link_open || ((tokens, index, opts, env, self) => self.renderToken(tokens, index, opts));
    this.md.renderer.rules.link_open = (tokens, index, options, env, self) => {
      const href = tokens[index].attrGet('href') || '';
      if (/^https?:\/\//i.test(href)) {
        tokens[index].attrSet('target', '_blank');
        tokens[index].attrSet('rel', 'noopener noreferrer');
      }
      return defaultLinkOpen(tokens, index, options, env, self);
    };

    this.md.renderer.rules.emoji = (tokens, index) => twemoji.parse(tokens[index].content);
  }

  renderFile(filePath, env = {}) {
    const parsed = matter(fs.readFileSync(filePath, 'utf8'));
    const renderEnv = { ...env, toc: [] };
    const tokens = this.md.parse(parsed.content, renderEnv);
    addHeadingIds(tokens, renderEnv);
    return {
      html: this.md.renderer.render(tokens, this.md.options, renderEnv),
      toc: renderEnv.toc,
      frontMatter: parsed.data,
      problemLinks: extractProblemLinks(tokens)
    };
  }
}
