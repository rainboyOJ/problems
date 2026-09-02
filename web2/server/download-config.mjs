import fs from 'node:fs';
import path from 'node:path';
import { parse } from 'yaml';

export const DEFAULT_DOWNLOAD_CONFIG = Object.freeze({
  repository: {
    rawBase: 'https://raw.githubusercontent.com/rainboyOJ/problems/master'
  },
  download: {
    rawMirrors: ['https://gh-proxy.com/']
  }
});

function asObject(value) {
  return value && typeof value === 'object' && !Array.isArray(value) ? value : {};
}

function optionalUrl(value) {
  if (typeof value !== 'string' || !value.trim()) return null;
  try {
    const url = new URL(value.trim());
    return url.protocol === 'http:' || url.protocol === 'https:' ? url.toString().replace(/\/$/, '') : null;
  } catch {
    return null;
  }
}

function normalizeMirror(value) {
  const url = optionalUrl(value);
  return url ? `${url}/` : null;
}

export function normalizeDownloadConfig(value = {}) {
  const root = asObject(value);
  const repository = asObject(root.repository);
  const download = asObject(root.download);
  const rawBase = optionalUrl(repository.rawBase) || DEFAULT_DOWNLOAD_CONFIG.repository.rawBase;
  const rawMirrors = Array.isArray(download.rawMirrors)
    ? download.rawMirrors.map(normalizeMirror).filter(Boolean)
    : DEFAULT_DOWNLOAD_CONFIG.download.rawMirrors;

  return {
    repository: { rawBase },
    download: { rawMirrors }
  };
}

export function loadDownloadConfig(configPath, logger = console) {
  let parsed = {};
  let invalid = false;
  try {
    const source = fs.readFileSync(path.resolve(configPath), 'utf8');
    parsed = parse(source) || {};
  } catch (error) {
    if (error.code !== 'ENOENT') {
      invalid = true;
      logger.warn?.({ err: error, configPath }, 'Download config could not be read; using defaults');
    }
  }
  const config = normalizeDownloadConfig(parsed);
  return { config, invalid, configPath: path.resolve(configPath) };
}

export function rawUrlFor(config, problemId, relativePath) {
  const encodedPath = relativePath.split('/').map((part) => encodeURIComponent(part)).join('/');
  return `${config.repository.rawBase}/roj/${encodeURIComponent(problemId)}/data/${encodedPath}`;
}

export function downloadSources(config, problemId) {
  const directBase = `${config.repository.rawBase}/roj/${encodeURIComponent(problemId)}/data/`;
  const sources = [];
  const seen = new Set();
  for (const mirror of config.download.rawMirrors) {
    const baseUrl = `${mirror}${directBase}`;
    if (seen.has(baseUrl)) continue;
    seen.add(baseUrl);
    let hostname = mirror;
    try { hostname = new URL(mirror).hostname; } catch { /* normalized config should make this unreachable */ }
    sources.push({
      id: `mirror-${sources.length}`,
      label: `GitHub 加速源（${hostname}）`,
      baseUrl
    });
  }
  if (!seen.has(directBase)) {
    sources.push({ id: 'github', label: 'GitHub Raw 直连', baseUrl: directBase });
  }
  return sources;
}
