import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import test from 'node:test';
import { downloadSources, normalizeDownloadConfig, rawUrlFor } from '../server/download-config.mjs';
import { isPublicDataPath, readDataManifest } from '../server/data-manifest.mjs';

function temporaryDirectory() {
  return fs.mkdtempSync(path.join(os.tmpdir(), 'roj-manifest-test-'));
}

test('public data paths reject traversal and unsupported names', () => {
  assert.equal(isPublicDataPath('sample/01.in'), true);
  assert.equal(isPublicDataPath('sample/01.OUT'), true);
  assert.equal(isPublicDataPath('../01.in'), false);
  assert.equal(isPublicDataPath('sample/../01.in'), false);
  assert.equal(isPublicDataPath('sample\\01.in'), false);
  assert.equal(isPublicDataPath('.cache/01.in'), false);
  assert.equal(isPublicDataPath('std.cpp'), false);
});

test('data manifest reads sorted public files without touching data contents', () => {
  const root = temporaryDirectory();
  try {
    fs.writeFileSync(path.join(root, 'data.json'), JSON.stringify({
      files: [
        { path: '1.ans', size: 8 },
        { path: '1.in', size: 4 }
      ]
    }));
    const manifest = readDataManifest(root, { warn() {} });
    assert.deepEqual(manifest, {
      files: [
        { path: '1.ans', size: 8 },
        { path: '1.in', size: 4 }
      ],
      invalid: false,
      reason: null
    });
  } finally {
    fs.rmSync(root, { recursive: true, force: true });
  }
});

test('missing or invalid data manifests become empty and invalid', () => {
  const root = temporaryDirectory();
  try {
    const missing = readDataManifest(root, { warn() {} });
    assert.equal(missing.invalid, true);
    assert.deepEqual(missing.files, []);

    fs.writeFileSync(path.join(root, 'data.json'), JSON.stringify({ files: [{ path: '../private.in', size: 2 }] }));
    const invalid = readDataManifest(root, { warn() {} });
    assert.equal(invalid.invalid, true);
    assert.deepEqual(invalid.files, []);
  } finally {
    fs.rmSync(root, { recursive: true, force: true });
  }
});

test('download config ignores legacy zip settings and keeps valid mirrors', () => {
  const config = normalizeDownloadConfig({
    repository: { rawBase: 'file:///private' },
    download: { rawMirrors: ['https://mirror.example/base', 'not-a-url'], zip: { activeJobs: 0 } }
  });
  assert.equal(config.repository.rawBase, 'https://raw.githubusercontent.com/rainboyOJ/problems/master');
  assert.deepEqual(config.download.rawMirrors, ['https://mirror.example/base/']);
  assert.equal('zip' in config.download, false);
});

test('source URLs encode each path component and retain raw fallback', () => {
  const config = normalizeDownloadConfig({
    repository: { rawBase: 'https://raw.example/repo/' },
    download: { rawMirrors: ['https://gh-proxy.com/'] }
  });
  assert.equal(rawUrlFor(config, '1460', 'nested/a b.in'), 'https://raw.example/repo/roj/1460/data/nested/a%20b.in');
  assert.deepEqual(downloadSources(config, '1460'), [
    {
      id: 'mirror-0',
      label: 'GitHub 加速源（gh-proxy.com）',
      baseUrl: 'https://gh-proxy.com/https://raw.example/repo/roj/1460/data/'
    },
    {
      id: 'github',
      label: 'GitHub Raw 直连',
      baseUrl: 'https://raw.example/repo/roj/1460/data/'
    }
  ]);
});
