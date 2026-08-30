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

  function renderFiles(files) {
    list.replaceChildren();
    if (!files.length) {
      const empty = document.createElement('p');
      empty.className = 'download-empty';
      empty.textContent = '没有可下载的公开数据。';
      list.append(empty);
      return;
    }
    const fragment = document.createDocumentFragment();
    for (const file of files) {
      const row = document.createElement('div');
      row.className = 'download-file-row';
      const name = document.createElement('span');
      name.className = 'download-file-name';
      name.textContent = file.path;
      const meta = document.createElement('span');
      meta.className = 'download-file-size';
      meta.textContent = formatBytes(file.size);
      const link = document.createElement('a');
      link.className = 'download-file-link';
      link.href = file.downloadUrl;
      link.download = file.path.split('/').pop() || 'download';
      link.textContent = '下载';
      link.setAttribute('aria-label', `下载 ${file.path}`);
      row.append(name, meta, link);
      fragment.append(row);
    }
    list.append(fragment);
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
