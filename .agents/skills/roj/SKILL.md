---
name: roj
description: Use the ROJ read-only problem website from an AI or terminal. Trigger whenever the user asks to search, fetch, read, download, inspect, or locally test a problem from roj.ac.cn, or asks how to use the ROJ problem data. This skill covers the bundled scripts/roj.py client: public test data is served only as one packed archive per problem (`<id>.tar.zst`), which the download command fetches and unpacks; never treat ROJ as a submission or remote judging service.
compatibility: Requires Python 3.10+, network access for API and data commands, and g++ plus the system diff command for local C++ testing.
---

# ROJ Client

Use `scripts/roj.py` to interact with the read-only ROJ site. The website serves
problem metadata, Markdown/PDF statements, and public test data. It does not accept
accounts, source-code submissions, or remote judging requests.

Run the globally installed script from any directory with Python 3:

```sh
python3 ~/.agents/skills/roj/scripts/roj.py --help
```

Set `ROJ_URL` or pass `--base-url` when using a local or staging server:

```sh
ROJ_URL=https://roj.ac.cn python3 ~/.agents/skills/roj/scripts/roj.py list
python3 ~/.agents/skills/roj/scripts/roj.py --base-url http://127.0.0.1:3033 list
```

## Commands

### Find problems

`list` searches by numeric ID or title. It automatically follows all result pages;
use `--page N` when only one page is needed.

```sh
python3 ~/.agents/skills/roj/scripts/roj.py list
python3 ~/.agents/skills/roj/scripts/roj.py list "最短路"
python3 ~/.agents/skills/roj/scripts/roj.py list --page 2
python3 ~/.agents/skills/roj/scripts/roj.py --json list "二分"
```

Use `--json` for tool or AI consumption. JSON output is also available after a
subcommand, for example `list --json`.

### Read a problem

`get` prints metadata followed by the raw Markdown statement. PDF-only problems
print the browser URL instead; the CLI does not attempt to convert PDFs to text.

```sh
python3 ~/.agents/skills/roj/scripts/roj.py get 1000
python3 ~/.agents/skills/roj/scripts/roj.py get 10000 --no-markdown
python3 ~/.agents/skills/roj/scripts/roj.py --json get 1000
```

### Download public data

ROJ publishes each problem's public data as a **single packed archive**, never as
individually fetchable files: the manifest lists `archive.name` (e.g. `1337.tar.zst`)
plus a `files` index, and any per-file URL built from `files[].path` returns 404.
`download` therefore fetches the archive from the first source that answers, keeps it
beside the data directory, unpacks it, and verifies every manifest path landed.

The default destination is `./roj-data/<id>/data/`. The archive itself is stored next
to that directory (`./roj-data/<id>/<id>.tar.zst`), so re-running `download` reuses it
instead of hitting the network again; pass `--force` to re-fetch. `--output` names a
destination directory (the archive is stored inside it unless it is named `data`).

```sh
python3 ~/.agents/skills/roj/scripts/roj.py download 1000
python3 ~/.agents/skills/roj/scripts/roj.py download 1000 --output ./data/1000
python3 ~/.agents/skills/roj/scripts/roj.py download 1000 --force
```

Sources are tried in the manifest's `sources` order until one returns the archive.
If the archive carries an extra top-level directory (commonly `data/`), it is stripped
during extraction so files land exactly at `destination/<path>`; a missing manifest
file after extraction is an error, not a silent success. Requires `tar` and `zstd`
(`tar --zstd` first, `zstd -dc | tar -x` as fallback).

### Test C++ locally

`test` is local-only. It compiles with `g++ -std=c++17 -O2`, runs each matching
`.in`/`.out` or `.in`/`.ans` pair, applies the problem time limit when present, and
compares output with `diff -b`. A non-zero program exit is `RE`; timeout is `TLE`;
different output is `WA`; all matching cases are `AC`. Memory limits are reported
but are not forcibly imposed by this Python client.

Data lookup is offline by default, in this order:

1. `--data-dir DIR`
2. `./roj-data/<id>/`
3. `./roj/<id>/data/`

If no data exists, add `--download` to explicitly fetch it into
`./roj-data/<id>/`. This is the only `test` mode that uses the network.

```sh
python3 ~/.agents/skills/roj/scripts/roj.py test 1000 main.cpp
python3 ~/.agents/skills/roj/scripts/roj.py test 1000 main.cpp --data-dir ./tests/1000
python3 ~/.agents/skills/roj/scripts/roj.py test 1000 main.cpp --download
python3 ~/.agents/skills/roj/scripts/roj.py --json test 1000 main.cpp
```

The command returns exit status 0 only when compilation succeeds and every data
pair is `AC`. A missing pair, compiler error, network failure, or test failure is
non-zero. JSON test results include the problem metadata, selected data directory,
compiler details, per-case status, elapsed time, and any diagnostics.

## Safe operating rules

- Treat IDs and paths as untrusted input. Never construct a shell command from a
  problem title or a manifest filename.
- Download only the problem's public archive listed by `/api/problem/<id>/data`; the
  bytes come from its configured sources. Do not expose or copy `std.cpp`, solution
  files, generators, checkers, or legacy `down/` files.
- Do not claim that a local `AC` is an official submission result. It only means the
  program matched the public data with this client's comparison rule.
- Keep downloaded data in a user-selected working directory and inspect it before
  running unfamiliar source code.

## API reference

The client uses these read-only endpoints:

```text
GET /api/problems?q=<query>&page=<number>
GET /api/problem/<id>
GET /api/problem/<id>/markdown
GET /api/problem/<id>/data
```

`/api/problem/<id>/data` returns `archive`, `sources` and a `files` array. `archive`
holds the packed file name (`<id>.tar.zst`) — that archive is the only downloadable
artifact; appending a `files[].path` to a source `baseUrl` returns 404. Each source
contains an `id`, a display `label`, and a problem-specific `baseUrl`, and sources are
tried in order as `<baseUrl><archive.name>`. The `files` array is an index of what the
archive contains (path + size), used to verify extraction and to let `test --download`
decide whether data is already present.

The problem metadata response contains `id`, `title`, `time`, `memory`, `tags`,
`source`, `statementKind`, `hasMarkdown`, `hasPdf`, and `hasPublicData`. A missing
Markdown statement on a PDF-only problem is expected, not an API failure.
