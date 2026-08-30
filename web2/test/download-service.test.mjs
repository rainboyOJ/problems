import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import test from 'node:test';
import { normalizeDownloadConfig, rawUrlFor } from '../server/download-config.mjs';
import { isPublicDataPath, resolvePublicDataFile, scanPublicData, ZipJobQueue } from '../server/download-service.mjs';

function temporaryDirectory() {
  return fs.mkdtempSync(path.join(os.tmpdir(), 'roj-download-test-'));
}

test('public data scanner only includes allowlisted regular files', () => {
  const root = temporaryDirectory();
  const dataDir = path.join(root, 'data');
  fs.mkdirSync(path.join(dataDir, 'nested'), { recursive: true });
  fs.writeFileSync(path.join(dataDir, 'nested', '01.IN'), 'input');
  fs.writeFileSync(path.join(dataDir, 'answer.ans'), 'answer');
  fs.writeFileSync(path.join(dataDir, 'notes.md'), 'private');
  fs.writeFileSync(path.join(dataDir, '.hidden.in'), 'private');
  fs.symlinkSync(path.join(dataDir, 'notes.md'), path.join(dataDir, 'link.in'));
  assert.deepEqual(scanPublicData(dataDir).map((file) => file.path), ['answer.ans', 'nested/01.IN']);
  fs.rmSync(root, { recursive: true, force: true });
});

test('public data scanner does not follow a symbolic-link data root', () => {
  const root = temporaryDirectory();
  const external = temporaryDirectory();
  fs.writeFileSync(path.join(external, 'outside.in'), 'private');
  fs.symlinkSync(external, path.join(root, 'data'));
  assert.deepEqual(scanPublicData(path.join(root, 'data')), []);
  fs.rmSync(root, { recursive: true, force: true });
  fs.rmSync(external, { recursive: true, force: true });
});

test('public data paths reject traversal and unsupported names', () => {
  assert.equal(isPublicDataPath('sample/01.in'), true);
  assert.equal(isPublicDataPath('sample/01.OUT'), true);
  assert.equal(isPublicDataPath('../01.in'), false);
  assert.equal(isPublicDataPath('sample/../01.in'), false);
  assert.equal(isPublicDataPath('sample\\01.in'), false);
  assert.equal(isPublicDataPath('.cache/01.in'), false);
  assert.equal(isPublicDataPath('std.cpp'), false);
});

test('file resolver only accepts a current manifest entry', () => {
  const root = temporaryDirectory();
  const dataDir = path.join(root, 'data');
  fs.mkdirSync(dataDir, { recursive: true });
  const absolutePath = path.join(dataDir, '01.in');
  fs.writeFileSync(absolutePath, 'data');
  const entry = { publicData: scanPublicData(dataDir) };
  assert.equal(resolvePublicDataFile(entry, '01.in').absolutePath, absolutePath);
  assert.equal(resolvePublicDataFile(entry, '../01.in'), null);
  assert.equal(resolvePublicDataFile(entry, 'missing.in'), null);
  fs.rmSync(root, { recursive: true, force: true });
});

test('zip queue enforces one request per client and bounded waiting', async () => {
  const queue = new ZipJobQueue({ activeJobs: 1, queueSize: 1, perClient: 1 });
  let release;
  const active = queue.submit('a', () => new Promise((resolve) => { release = resolve; }));
  assert.equal(active.accepted, true);
  await new Promise((resolve) => setImmediate(resolve));
  assert.equal(queue.submit('a', () => Promise.resolve()).reason, 'client');
  const waiting = queue.submit('b', () => Promise.resolve('b'));
  assert.equal(waiting.accepted, true);
  assert.equal(queue.submit('c', () => Promise.resolve()).reason, 'queue');
  release();
  await Promise.all([active.promise, waiting.promise]);
  assert.equal(queue.active, 0);
});

test('invalid YAML values fall back to safe download defaults', () => {
  const config = normalizeDownloadConfig({
    repository: { rawBase: 'file:///private' },
    download: { rawMirrors: ['https://mirror.example/base', 'not-a-url'], zip: { activeJobs: 0, queueSize: -1, compressionLevel: 99 } }
  });
  assert.equal(config.repository.rawBase, 'https://raw.githubusercontent.com/rainboyOJ/problems/master');
  assert.deepEqual(config.download.rawMirrors, ['https://mirror.example/base/']);
  assert.equal(config.download.zip.activeJobs, 1);
  assert.equal(config.download.zip.queueSize, 3);
  assert.equal(config.download.zip.compressionLevel, 1);
});

test('raw fallback URL encodes each path component', () => {
  const config = normalizeDownloadConfig({ repository: { rawBase: 'https://raw.example/repo/' } });
  assert.equal(rawUrlFor(config, '1460', 'nested/a b.in'), 'https://raw.example/repo/roj/1460/data/nested/a%20b.in');
});
