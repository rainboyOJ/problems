# Download problem data from GitHub Raw

Status: accepted and implemented in `web2`.

## Decision

The GitHub repository is the canonical store for public problem data. The bohai VPS
stores only problem statements, metadata, referenced statement assets, and the small
`data.json` manifest for each problem. The VPS must not receive or read
`roj/<id>/data/` or legacy `roj/<id>/down/` files.

Each numeric problem directory contains a generated manifest:

```json
{
  "files": [
    { "path": "1.ans", "size": 2048 },
    { "path": "1.in", "size": 1024 }
  ]
}
```

Only ordinary, non-hidden files below `data/` with `.in`, `.out`, `.ans`, `.txt`, or
`.dat` extensions (case-insensitive) are included. Paths are normalized relative
paths and sorted lexicographically. A problem with no public data has
`{ "files": [] }`. A missing or invalid manifest is a deployment error; the server
treats that problem as having no data and logs a warning.

The manifest generator is
`.agents/skills/add-roj-problem/scripts/generate-data-manifest.py`. It is run by the
problem import workflow and in check-only mode by `push-to-vps.sh`. A single file over
100 MiB stops the import and requires an explicit storage decision because GitHub Raw
cannot reliably serve it as an ordinary repository file.

## Sources and API

`web2/config.yaml` defines the direct repository root and optional mirror prefixes:

```yaml
repository:
  rawBase: https://raw.githubusercontent.com/rainboyOJ/problems/master
download:
  rawMirrors:
    - https://gh-proxy.com/
```

The server validates HTTP(S) source URLs and exposes them in the manifest API. Mirror
entries are ordered as configured; GitHub Raw direct is always appended as a fallback.
Each source is converted into a problem-specific `baseUrl` ending in
`roj/<id>/data/`.

```text
GET /api/problem/<id>/data
```

The response contains `problemId`, `totalFiles`, `totalBytes`, `sources`, and `files`.
Each `source` has `id`, `label`, and `baseUrl`; each file has `path` and `size`. The
API never returns a VPS file URL and never reads a data file. The old local routes
`/problem/<id>/data/<path>` and `/problem/<id>/data.zip` are removed.

## Browser behavior

The problem download modal shows one source `<select>`. It defaults to the first
configured mirror and always offers GitHub Raw direct when no mirror is available.
Changing the select affects all rows immediately and is not persisted between pages.
Each file action uses `fetch` with CORS and creates a Blob download so text fixtures
are saved instead of merely opened in the browser. A failed source is reported and
the user can switch source manually; the browser does not buffer a ZIP because ZIP
generation is no longer supported.

## CLI behavior

`roj.py download <id>` requests the ROJ manifest, then streams every listed file to
`./roj-data/<id>/` by default. It tries configured mirrors in order and falls back to
GitHub Raw direct. `--file` selects one manifest path or an unambiguous basename;
`--zip` is removed. `test` remains offline by default and only downloads from GitHub
when the user explicitly passes `--download`.

## Deployment

`push-to-vps.sh` validates every manifest before synchronization and exits without
uploading or restarting when validation fails. Its rsync rules exclude both
`roj/*/data/` and `roj/*/down/`; because excluded files are protected from rsync
deletion, old remote copies are not removed automatically. The application does not
configure `roj/` as an Nginx static root, so stale remote data cannot become a hidden
download endpoint.

## Non-goals

- No server-side single-file data proxy or ZIP generation.
- No browser-side ZIP packaging.
- No automatic deletion of old remote data during the first migration.
- No Git LFS migration until GitHub repository limits require it.
