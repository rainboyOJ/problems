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

document.addEventListener('DOMContentLoaded', () => {
  applyTheme();

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
