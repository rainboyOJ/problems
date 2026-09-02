import fs from 'node:fs';
import path from 'node:path';

export const PUBLIC_DATA_EXTENSIONS = Object.freeze(new Set(['.in', '.out', '.ans', '.txt', '.dat']));
export const MAX_PUBLIC_DATA_FILE_BYTES = 100 * 1024 * 1024;

export function isPublicDataPath(relativePath) {
  if (typeof relativePath !== 'string' || !relativePath || relativePath.startsWith('/') || relativePath.includes('\\')) return false;
  const parts = relativePath.split('/');
  if (parts.some((part) => !part || part === '.' || part === '..' || part.startsWith('.'))) return false;
  return PUBLIC_DATA_EXTENSIONS.has(path.posix.extname(relativePath).toLocaleLowerCase());
}

function validFileEntry(file, previousPath) {
  if (!file || typeof file !== 'object' || Array.isArray(file)) return { error: 'file entry must be an object' };
  if (Object.keys(file).sort().join(',') !== 'path,size') return { error: 'file entry must contain only path and size' };
  if (!isPublicDataPath(file.path)) return { error: `invalid public data path: ${String(file.path)}` };
  if (!Number.isSafeInteger(file.size) || file.size < 0) return { error: `invalid file size for ${file.path}` };
  if (file.size > MAX_PUBLIC_DATA_FILE_BYTES) return { error: `file exceeds 100 MiB: ${file.path}` };
  if (previousPath !== null && file.path <= previousPath) return { error: 'manifest paths must be strictly sorted' };
  return { value: { path: file.path, size: file.size } };
}

function validateManifest(value) {
  if (!value || typeof value !== 'object' || Array.isArray(value)) return { error: 'manifest must be an object' };
  if (Object.keys(value).sort().join(',') !== 'files') return { error: 'manifest must contain only a files array' };
  if (!Array.isArray(value.files)) return { error: 'manifest files must be an array' };

  const files = [];
  let previousPath = null;
  for (const file of value.files) {
    const result = validFileEntry(file, previousPath);
    if (result.error) return result;
    files.push(result.value);
    previousPath = result.value.path;
  }
  return { value: files };
}

export function readDataManifest(problemDir, logger = console) {
  const manifestPath = path.join(problemDir, 'data.json');
  try {
    const stat = fs.lstatSync(manifestPath);
    if (!stat.isFile() || stat.isSymbolicLink()) throw Object.assign(new Error('manifest is not a regular file'), { code: 'INVALID_MANIFEST_FILE' });
    const source = fs.readFileSync(manifestPath, 'utf8');
    const parsed = JSON.parse(source);
    const result = validateManifest(parsed);
    if (result.error) {
      logger.warn?.({ manifestPath, reason: result.error }, 'Problem data manifest is invalid');
      return { files: [], invalid: true, reason: result.error };
    }
    return { files: result.value, invalid: false, reason: null };
  } catch (error) {
    const reason = error.code === 'ENOENT' ? 'manifest is missing' : `manifest could not be read: ${error.message}`;
    logger.warn?.({ manifestPath, reason }, 'Problem data manifest is unavailable');
    return { files: [], invalid: true, reason };
  }
}
