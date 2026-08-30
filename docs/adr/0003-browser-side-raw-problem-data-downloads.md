# Generate problem data packages on demand from the VPS

Status: accepted and implemented in `web2`.

## Decision

ROJ stores the uploaded `roj/` corpus on the bohai VPS and exposes a filtered list
of public data files from each problem's `data/` directory. Individual files are
served by the local download route. A ZIP package is generated on demand by the
server from the same filtered manifest and streamed to the client; it is not kept
as a permanent archive.

The existing `down/` directory is retained for historical compatibility. It is not
part of the new problem download UI, and new imports must treat `data/` as the
source of public download candidates.

## Source URLs and configuration

The local download path is built from the problem ID and the relative path below
`data/`:

```text
/problem/<id>/data/<relative-path>
```

`ROJ_ROOT` points to the uploaded corpus. GitHub Raw may remain as an optional
emergency fallback for single-file downloads, but it is not used to build the
server-generated ZIP. The existing fallback configuration is retained only for
that future use:

```yaml
repository:
  rawBase: https://raw.githubusercontent.com/rainboyOJ/problems/master
download:
  rawMirrors:
    - https://gh-proxy.com/
```

`rawMirrors` contains optional acceleration prefixes. Empty or invalid fallback
configuration must not affect the local download route. The server reads this
configuration at startup; changes take effect after a restart.

The data root and download policy are server-side settings. They must not be
accepted from a page query string or from a user-controlled path.

## Public-file policy

Only regular, non-hidden files below `data/` with one of these extensions are
public download candidates (case-insensitive): `.in`, `.out`, `.ans`, `.txt`, and
`.dat`. The scanner must exclude source code, scripts, executables, compiled
artifacts, caches, hidden files, and symbolic links. Paths must remain inside the
problem's `data/` directory and must use normalized relative paths.

The same filtered manifest drives both single-file downloads and ZIP generation.
There must be no second, less restrictive file enumeration for the archive.

## Problem-page interaction

Under the problem title, render a compact button group:

- `下载数据` is shown only when the public data manifest is non-empty.
- `查看题解 ↗` is shown for every problem and opens
  `https://pcs2.roj.ac.cn/problem/roj/<id>` as an external link.

Clicking `下载数据` opens a modal containing the public file list. Each row shows
the relative filename and a single-file download action. The modal also provides
`打包下载` to request a server-generated `roj-<id>-data.zip`.

The modal must support an explicit close button, backdrop click, `Escape`, focus
restoration, keyboard-accessible controls, and a usable narrow-screen layout. ZIP
progress should show at least the preparing, downloading, completed, and failed
states. When the streamed response has a known length, the browser may show byte
progress; per-file progress is not required for a single streamed archive. A failed
file stops the package operation and identifies that file; the UI does not retry
automatically.

## HTTP API contract

The problem page obtains its data manifest from:

```text
GET /api/problem/<id>/data
```

For an existing problem with no public files, the response is still `200` with an
empty `files` array. A missing problem returns `404`. The response shape is:

```json
{
  "problemId": "1460",
  "totalFiles": 1,
  "totalBytes": 2048,
  "files": [
    {
      "path": "sample/01.in",
      "size": 2048,
      "downloadUrl": "/problem/1460/data/sample/01.in"
    }
  ],
  "zipUrl": "/problem/1460/data.zip"
}
```

`files` is sorted by normalized relative path and is the only source used by the
page to render the download list. The server may add non-breaking metadata fields,
but `path`, `size`, and `downloadUrl` are stable fields for the first version.

Individual files are downloaded with:

```text
GET /problem/<id>/data/<relative-path>
```

The handler validates the catalog ID, decodes and normalizes the path once, rejects
absolute paths, `..` segments, NUL bytes, backslash escapes, directories and
symbolic links, and then re-applies the public-file extension policy. It never
lists a directory or falls back to a file outside the selected problem. Missing or
disallowed files return `404` rather than revealing whether a private path exists.
Responses use a safe attachment filename, an appropriate binary content type,
`X-Content-Type-Options: nosniff`, and stream the file instead of buffering it in
Fastify memory. Single-file responses advertise `Accept-Ranges: bytes` and honor
valid `Range` requests so interrupted downloads can resume. The response includes
an `ETag` and `Last-Modified` value derived from the validated file metadata; a
matching conditional request may return `304 Not Modified`. Cache headers must allow
public reuse while still revalidating when the source file changes. The URL remains
stable, so replacing a data file must also update its metadata and invalidate any
stale cache according to the deployment policy.

At deployment time, Nginx terminates HTTPS and reverse-proxies these requests to
Fastify. Fastify remains the component that validates the problem ID, public-file
manifest, and relative path. The `roj/` directory is not configured as an Nginx
static root or alias; this keeps private maintenance files outside the web server's
direct path resolution.

The ZIP endpoint is:

```text
GET /problem/<id>/data.zip
```

It uses the same manifest and validation rules as the JSON and individual-file
endpoints. An existing problem with no public files returns `404` (the page should
hide the button), while a missing problem also returns `404`.

Because this archive is generated for the request, it does not promise byte-range
resume or a reusable `ETag`. The response should identify itself as an attachment
with `Content-Type: application/zip` and `Content-Disposition: attachment`; if the
connection fails, the client starts a new ZIP request. Adding resumable ZIP
downloads later requires a stable cached artifact and is a separate design.

ZIP failures use a JSON body with a stable `error` code, a Chinese `message`, and a
boolean `retryable` field. The initial status mapping is:

| Status | Error code | Retryable | Meaning |
| --- | --- | --- | --- |
| `404` | `problem_not_found` or `data_not_found` | no | The problem or public data does not exist. |
| `413` | `zip_too_large` | no | The manifest exceeds the configured source-size limit. |
| `429` | `zip_queue_full` | yes | The active job and bounded queue are full. |
| `504` | `zip_timeout` | yes | The active ZIP job exceeded its time limit. |
| `500` | `zip_failed` | sometimes | A source file changed or could not be read, or the archive writer failed; the UI never retries automatically. |

For `zip_failed`, the response may include `failedPath` with the normalized public
relative path that caused the failure. A `429` response should include
`Retry-After` when a useful retry delay is known. The browser displays these errors
in the download modal and never retries automatically.

## Abuse controls and monitoring

The site has no accounts, so download protection is based on the trusted client
address supplied by the Nginx reverse proxy. The ZIP endpoint allows at most one
active or queued request from the same client address; another request from that
address receives `429`. The global active-job and bounded-queue limits still apply
across all clients. Rate-limit keys must use the proxy's validated forwarding
configuration; arbitrary client-supplied `X-Forwarded-For` values are not trusted.

Single-file downloads are cheaper but can still consume the monthly egress quota.
The deployment should apply a moderate per-address request/connection limit at the
proxy layer without requiring login or a CAPTCHA. Limits must not prevent ordinary
parallel browser requests for one problem's small files.

Download logs should record the problem ID, normalized path or ZIP request, response
status, bytes sent, duration, and queue outcome. Operators should monitor disk
capacity, active ZIP jobs, queue length, ZIP failures, and cumulative egress. Logs
must not include source file contents or unvalidated raw paths.

## On-demand ZIP behavior

The server enumerates the filtered manifest once, opens each regular file through a
validated path, and appends it to a streaming ZIP writer. It must not read the
whole problem or the whole archive into a single memory buffer. Archive entries
preserve paths relative to `data/`; they must not contain an absolute filesystem
path or the `data/` prefix. The response filename is `roj-<id>-data.zip`.

The ZIP writer uses a low Deflate compression level (default recommendation: level
1, or the equivalent setting in the selected library). The goal is to reduce
compression CPU on bohai while still shrinking ordinary text data; maximum
compression is deliberately not used. The archive implementation may store a file
without compression when the library identifies it as already compressed, but this
optimization must not change the public-file manifest or entry names.

Because bohai has 2 vCPUs and about 2 GiB of memory, the service runs one active ZIP
job by default. Additional requests enter a small bounded queue; when that queue is
full, the service returns a retryable busy response instead of allowing unbounded
work to accumulate. The active-job and queue limits are deployment settings, not
values supplied by the client. A client disconnect must abort the archive and
release its file handles. If a temporary archive is required by the selected
library, it must be created under a dedicated temporary directory, removed after
success or failure, and bounded by an explicit size limit.

The service performs a manifest preflight before starting a ZIP job. The default
maximum is 1 GiB of combined source data per archive, and the default active-job
timeout is 15 minutes. Both values are deployment settings. A request above the
size limit returns a non-retryable `413` response; a job that exceeds its active
time limit is cancelled and returns a timeout response. The timeout starts when a
job begins generating, not while it is waiting in the queue. These limits protect
the VPS from future unusually large problems without affecting the current corpus,
whose largest problem is about 170 MiB.

The UI warns when the combined candidate size exceeds 100 MB, but the warning does
not by itself block the operation. A single-file download remains available when
ZIP creation fails.

## Deliberate non-goals

- No permanent server-side ZIP cache.
- No browser-side ZIP generation as the default path.
- No upload, authentication, submission, judging, or registration workflow.
- No automatic migration or rewriting of legacy Markdown links to `down/`.

## Rationale and trade-offs

Keeping the files on bohai removes the GitHub Raw dependency for the normal path and
usually improves access for the site's users. Streaming ZIP generation avoids
permanent duplicate archives, at the cost of CPU and file IO for every package
request. Limiting active jobs and aborting disconnected clients keeps that cost
bounded. GitHub Raw can still be retained as a manually enabled fallback, but it is
not a substitute for VPS bandwidth, backups, or monitoring.

## Implementation checklist

The implementation is expected to keep all of the following guarantees:

1. Fastify loads the VPS data root and optional Raw fallback configuration with
   documented defaults and validates the values.
2. Problem discovery scans `roj/<id>/data/`, applies the public-file policy, and
   exposes one deterministic manifest to the Pug view and API.
3. The problem page renders the conditional data button and the external solution
   link, and the API exposes only validated download paths.
4. Single-file downloads use streaming responses with safe content-disposition,
   range handling, and cache headers behind the Nginx reverse proxy; the `roj/`
   directory is not exposed as a static root.
5. ZIP requests use a streaming writer, one active job by default, a bounded wait
   queue with a retryable busy response, client-disconnect cancellation,
   temporary-file cleanup when needed, attachment headers without a resumable-range
   promise, low Deflate compression, a 1 GiB preflight limit, a 15-minute active
   timeout, per-address abuse protection, progress states, and the 100 MB warning.
6. ZIP entries use paths relative to `data/`, and the generated filename is
   `roj-<id>-data.zip`.
7. Tests cover filtering, path traversal and symlink exclusion, empty-data behavior,
   ZIP concurrency and per-address limits, cleanup after failure, the documented
   error statuses, and the optional Raw fallback.
