import './app.scss';
import Prism from 'prismjs';
import 'prismjs/components/prism-markup';
import 'prismjs/components/prism-css';
import 'prismjs/components/prism-javascript';
import 'prismjs/components/prism-typescript';
import 'prismjs/components/prism-python';
import 'prismjs/components/prism-bash';
import 'prismjs/components/prism-c';
import 'prismjs/components/prism-cpp';
import 'prismjs/components/prism-java';
import 'prismjs/components/prism-json';

const THEME_KEY = 'roj.theme';
const root = document.documentElement;
const mediaQuery = window.matchMedia('(prefers-color-scheme: dark)');

function storedTheme() {
  try {
    const value = window.localStorage.getItem(THEME_KEY);
    return value === 'light' || value === 'dark' ? value : 'system';
  } catch {
    return 'system';
  }
}

function resolvedTheme(mode) {
  return mode === 'system' ? (mediaQuery.matches ? 'dark' : 'light') : mode;
}

function applyTheme(mode = storedTheme()) {
  root.dataset.theme = resolvedTheme(mode);
  root.dataset.themeMode = mode;
  const button = document.querySelector('[data-theme-toggle]');
  if (!button) return;

  const next = root.dataset.theme === 'dark' ? 'light' : 'dark';
  button.setAttribute('aria-label', `切换到${next === 'dark' ? '深色' : '浅色'}主题`);
  button.setAttribute('title', `切换到${next === 'dark' ? '深色' : '浅色'}主题`);
  button.querySelector('[data-theme-icon]').textContent = root.dataset.theme === 'dark' ? '☀' : '☾';
}

function setTheme(mode) {
  try {
    window.localStorage.setItem(THEME_KEY, mode);
  } catch {
    // Theme still applies for the current page when storage is unavailable.
  }
  applyTheme(mode);
}

function formatBytes(bytes) {
  if (!Number.isFinite(bytes) || bytes < 0) return '-';
  if (bytes < 1024) return `${bytes} B`;
  const units = ['KiB', 'MiB', 'GiB'];
  let value = bytes;
  let unit = -1;
  do {
    value /= 1024;
    unit += 1;
  } while (value >= 1024 && unit < units.length - 1);
  return `${value.toFixed(value >= 10 || unit === 0 ? 0 : 1)} ${units[unit]}`;
}

function downloadErrorMessage(payload, fallback) {
  return typeof payload?.message === 'string' && payload.message ? payload.message : fallback;
}

async function copyText(text) {
  if (navigator.clipboard?.writeText) {
    try {
      await navigator.clipboard.writeText(text);
      return;
    } catch {
      // Fall through to the textarea fallback when clipboard permission is unavailable.
    }
  }

  const textarea = document.createElement('textarea');
  textarea.value = text;
  textarea.setAttribute('readonly', '');
  textarea.style.position = 'fixed';
  textarea.style.top = '0';
  textarea.style.left = '-9999px';
  document.body.append(textarea);
  textarea.select();
  textarea.setSelectionRange(0, textarea.value.length);
  const copied = typeof document.execCommand === 'function' && document.execCommand('copy');
  textarea.remove();
  if (!copied) throw new Error('clipboard_unavailable');
}

function initCopyStatement() {
  const trigger = document.querySelector('[data-copy-statement]');
  const status = document.querySelector('[data-copy-statement-status]');
  if (!trigger || !status) return;

  const problemId = trigger.dataset.problemId;
  const defaultLabel = trigger.textContent;
  let resetTimer = null;

  function setStatus(message, kind = '') {
    status.textContent = message;
    status.dataset.state = kind;
  }

  function scheduleReset(delay = 1600) {
    window.clearTimeout(resetTimer);
    resetTimer = window.setTimeout(() => {
      trigger.textContent = defaultLabel;
      setStatus('');
    }, delay);
  }

  trigger.addEventListener('click', async () => {
    if (trigger.disabled) return;
    window.clearTimeout(resetTimer);
    trigger.disabled = true;
    trigger.setAttribute('aria-busy', 'true');
    setStatus('正在读取题面…', 'working');

    try {
      const response = await fetch(`/api/problem/${encodeURIComponent(problemId)}/markdown`, {
        headers: { Accept: 'text/markdown' }
      });
      if (!response.ok) {
        const payload = await response.json().catch(() => null);
        throw new Error(downloadErrorMessage(payload, '题面暂时无法读取。'));
      }
      const markdown = await response.text();
      await copyText(markdown);
      trigger.textContent = '已复制';
      setStatus('题面已复制。', 'success');
      scheduleReset();
    } catch (error) {
      trigger.textContent = defaultLabel;
      setStatus(error.message === 'clipboard_unavailable' ? '复制失败，请手动复制。' : (error.message || '题面暂时无法读取。'), 'error');
      scheduleReset(4500);
    } finally {
      trigger.disabled = false;
      trigger.removeAttribute('aria-busy');
    }
  });
}

function initDownloadModal() {
  const trigger = document.querySelector('[data-download-trigger]');
  const modal = document.querySelector('[data-download-modal]');
  if (!trigger || !modal) return;

  const problemId = trigger.dataset.problemId;
  const closeButton = modal.querySelector('[data-download-close]');
  const list = modal.querySelector('[data-download-list]');
  const summary = modal.querySelector('[data-download-summary]');
  const warning = modal.querySelector('[data-download-warning]');
  const status = modal.querySelector('[data-download-status]');
  const zipButton = modal.querySelector('[data-zip-download]');
  let manifest = null;
  let lastFocused = null;
  let loading = null;

  function setStatus(message, kind = '') {
    status.textContent = message;
    status.dataset.state = kind;
  }

  function fileStem(filePath) {
    const separator = filePath.lastIndexOf('/');
    const extension = filePath.lastIndexOf('.');
    return extension > separator ? filePath.slice(0, extension) : filePath;
  }

  function fileExtension(filePath) {
    const separator = filePath.lastIndexOf('/');
    const dot = filePath.lastIndexOf('.');
    return dot > separator ? filePath.slice(dot).toLowerCase() : '';
  }

  function pairFiles(files) {
    const groups = new Map();
    for (const file of files) {
      const key = fileStem(file.path);
      let group = groups.get(key);
      if (!group) {
        group = { input: null, outputs: [], extras: [] };
        groups.set(key, group);
      }
      const extension = fileExtension(file.path);
      if (extension === '.in' && !group.input) group.input = file;
      else if (extension === '.out' || extension === '.ans') group.outputs.push(file);
      else group.extras.push(file);
    }

    const rows = [];
    for (const group of groups.values()) {
      const output = group.outputs.find((file) => fileExtension(file.path) === '.out') || group.outputs[0] || null;
      if (group.input || output) rows.push([group.input, output]);
      for (const file of [...group.outputs.filter((item) => item !== output), ...group.extras]) rows.push([file, null]);
    }
    return rows;
  }

  function appendFileSlot(row, file) {
    const cell = document.createElement('td');
    cell.className = 'download-file-cell';
    const action = document.createElement('td');
    action.className = 'download-file-action';

    if (!file) {
      cell.classList.add('is-empty');
      action.classList.add('is-empty');
      cell.textContent = '-';
      action.textContent = '-';
      row.append(cell, action);
      return;
    }

    const name = document.createElement('span');
    name.className = 'download-file-name';
    name.textContent = file.path;
    const meta = document.createElement('span');
    meta.className = 'download-file-size';
    meta.textContent = formatBytes(file.size);
    cell.append(name, meta);

    const link = document.createElement('a');
    link.className = 'download-file-link';
    link.href = file.downloadUrl;
    link.download = file.path.split('/').pop() || 'download';
    link.textContent = '下载';
    link.setAttribute('aria-label', `下载 ${file.path}`);
    action.append(link);
    row.append(cell, action);
  }

  function renderFiles(files) {
    list.replaceChildren();
    if (!files.length) {
      const empty = document.createElement('p');
      empty.className = 'download-empty';
      empty.textContent = '没有可下载的公开数据。';
      list.append(empty);
      return;
    }
    const table = document.createElement('table');
    table.className = 'download-file-table';
    table.setAttribute('aria-label', '公开数据文件');

    const head = document.createElement('thead');
    const headingRow = document.createElement('tr');
    for (const label of ['输入数据', '操作', '输出数据', '操作']) {
      const heading = document.createElement('th');
      heading.scope = 'col';
      heading.textContent = label;
      headingRow.append(heading);
    }
    head.append(headingRow);
    table.append(head);

    const body = document.createElement('tbody');
    for (const [input, output] of pairFiles(files)) {
      const row = document.createElement('tr');
      appendFileSlot(row, input);
      appendFileSlot(row, output);
      body.append(row);
    }
    table.append(body);
    list.append(table);
  }

  async function loadManifest() {
    if (manifest) return manifest;
    if (loading) return loading;
    loading = fetch(`/api/problem/${encodeURIComponent(problemId)}/data`, { headers: { Accept: 'application/json' } })
      .then(async (response) => {
        const payload = await response.json().catch(() => null);
        if (!response.ok) throw new Error(downloadErrorMessage(payload, '文件列表暂时无法读取。'));
        return payload;
      })
      .then((payload) => {
        manifest = payload;
        summary.textContent = `${payload.totalFiles} 个文件，共 ${formatBytes(payload.totalBytes)}`;
        warning.hidden = payload.totalBytes <= 100 * 1024 * 1024;
        renderFiles(payload.files || []);
        zipButton.disabled = !payload.files?.length;
        return payload;
      })
      .catch((error) => {
        summary.textContent = '文件列表读取失败';
        setStatus(error.message || '文件列表暂时无法读取。', 'error');
        list.replaceChildren();
        return null;
      })
      .finally(() => { loading = null; });
    return loading;
  }

  async function downloadZip() {
    if (!manifest || !manifest.files?.length || zipButton.disabled) return;
    zipButton.disabled = true;
    setStatus('正在准备 ZIP…', 'working');
    try {
      const response = await fetch(manifest.zipUrl, { headers: { Accept: 'application/zip, application/json' } });
      const contentType = response.headers.get('content-type') || '';
      if (!response.ok || contentType.includes('application/json')) {
        const payload = await response.json().catch(() => null);
        throw new Error(downloadErrorMessage(payload, 'ZIP 暂时无法生成。'));
      }
      if (!response.body) throw new Error('浏览器不支持流式下载。');
      const reader = response.body.getReader();
      const chunks = [];
      let loaded = 0;
      const total = Number(response.headers.get('content-length')) || 0;
      setStatus('正在下载 ZIP…', 'working');
      while (true) {
        const result = await reader.read();
        if (result.done) break;
        chunks.push(result.value);
        loaded += result.value.byteLength;
        setStatus(total ? `正在下载 ZIP… ${formatBytes(loaded)} / ${formatBytes(total)}` : `正在下载 ZIP… ${formatBytes(loaded)}`, 'working');
      }
      const blob = new Blob(chunks, { type: 'application/zip' });
      const url = URL.createObjectURL(blob);
      const link = document.createElement('a');
      link.href = url;
      link.download = `roj-${problemId}-data.zip`;
      document.body.append(link);
      link.click();
      link.remove();
      window.setTimeout(() => URL.revokeObjectURL(url), 1000);
      setStatus('ZIP 下载已开始。', 'success');
    } catch (error) {
      setStatus(error.message || 'ZIP 暂时无法生成。', 'error');
    } finally {
      zipButton.disabled = false;
    }
  }

  function closeModal() {
    if (modal.open) modal.close();
  }

  trigger.addEventListener('click', async () => {
    lastFocused = document.activeElement;
    if (typeof modal.showModal === 'function') modal.showModal();
    else modal.setAttribute('open', '');
    closeButton.focus();
    await loadManifest();
  });
  closeButton.addEventListener('click', closeModal);
  modal.addEventListener('click', (event) => {
    if (event.target === modal) closeModal();
  });
  modal.addEventListener('close', () => {
    setStatus('');
    lastFocused?.focus?.();
    lastFocused = null;
  });
  zipButton.addEventListener('click', downloadZip);
}

document.addEventListener('DOMContentLoaded', () => {
  applyTheme();
  initDownloadModal();
  initCopyStatement();

  document.querySelectorAll('.code-block code[class*="language-"]').forEach((code) => {
    const language = [...code.classList].find((name) => name.startsWith('language-'))?.slice(9);
    if (language && Prism.languages[language]) Prism.highlightElement(code);
  });

  document.querySelector('[data-theme-toggle]')?.addEventListener('click', () => {
    setTheme(root.dataset.theme === 'dark' ? 'light' : 'dark');
  });

  document.addEventListener('click', async (event) => {
    const button = event.target.closest('[data-copy-code]');
    if (!button) return;

    const code = button.closest('.code-block')?.querySelector('code');
    if (!code) return;

    try {
      await navigator.clipboard.writeText(code.textContent);
      const original = button.textContent;
      button.textContent = '已复制';
      window.setTimeout(() => { button.textContent = original; }, 1400);
    } catch {
      button.textContent = '复制失败';
      window.setTimeout(() => { button.textContent = '复制'; }, 1400);
    }
  });

  const headings = [...document.querySelectorAll('.markdown-body h2[id], .markdown-body h3[id]')];
  const tocLinks = new Map(
    [...document.querySelectorAll('[data-toc-link]')].map((link) => [link.getAttribute('href').slice(1), link])
  );
  if (headings.length && 'IntersectionObserver' in window && tocLinks.size) {
    const observer = new IntersectionObserver((entries) => {
      const visible = entries.filter((entry) => entry.isIntersecting).sort((a, b) => a.boundingClientRect.top - b.boundingClientRect.top)[0];
      if (!visible) return;
      tocLinks.forEach((link) => link.classList.remove('is-active'));
      tocLinks.get(visible.target.id)?.classList.add('is-active');
    }, { rootMargin: '-88px 0px -65% 0px', threshold: 0 });
    headings.forEach((heading) => observer.observe(heading));
  }
});

mediaQuery.addEventListener?.('change', () => {
  if (storedTheme() === 'system') applyTheme('system');
});
