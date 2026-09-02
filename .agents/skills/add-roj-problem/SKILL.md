---
name: add-roj-problem
description: Import programming problems into this repository's roj/ corpus from local problem directories, local contest roots, or an explicitly supplied OJ problem URL. Use this skill whenever the user asks to add, import, migrate, register, copy, or prepare a problem for roj, especially when they mention a local path, statement.md, 题面.md, down/下发文件, data/, std.cpp, or finding an unused roj problem ID. This skill governs the complete review-first workflow and must be used even when the user asks for only one part of the import.
compatibility: Requires Python 3 for the bundled ID helper and pandoc for HTML/Markdown statement conversion. Network access is only needed when the user explicitly supplies an external source URL.
---

# Add a Problem to ROJ

Use this skill to prepare one or more read-only problem records in the repository's
`roj/` directory. The goal is a complete, reviewable problem record, not an online
judge integration. The website discovers numeric `roj/<id>/` directories at startup.

## Non-negotiable boundaries

- Work only inside the repository's `roj/` directory and the user-supplied local
  source path. Never scan or copy an unrelated broad filesystem path.
- Do not copy or expose registration, judging, or account data.
- Do not expose `std.cpp`, generators, checkers, or other maintenance files. The
  website's download feature treats allowlisted files under `data/` as public download
  candidates listed in `data.json`; the legacy `down/` directory is retained for
  compatibility but is not part of the new download UI.
- Do not overwrite an existing `roj/<id>/` directory. A collision is a stop-and-ask
  condition, not a reason to replace files.
- Do not write anything before producing a preview and receiving explicit user
  confirmation for that import batch.
- Do not run `git add`, `git commit`, or `git push` automatically.
- Do not put local absolute paths, credentials, or private source URLs into
  `config.json` or `content.md`.

## Accepted input

The primary input is a local path, for example:

```text
/home/rainboy/tmp-暑假比赛
/home/rainboy/tmp-暑假比赛/08-25/A
```

Also support an explicitly supplied source platform plus problem ID or URL. If the
user supplies only a title without a source or local path, ask for the missing source
instead of guessing a problem.

Classify a local path as follows:

1. If it contains a recognizable statement file, PDF, or an unambiguous problem
   record, treat it as one problem directory.
2. Otherwise inspect its immediate child directories as candidate problems.
3. Do not recursively treat every directory as a problem. Skip `.git`,
   `rainboy-解析`, `problem-analysis-workspace`, `data`, `down`, `下发文件`,
   `大样例`, and directories without a statement.
4. If one contest-level statement appears to contain multiple problems, do not copy
   the same combined statement into every child. Put those candidates in the preview
   as requiring a manual split and wait for clarification.

## ID allocation

Use the bundled helper instead of reimplementing directory scanning:

```sh
python3 .agents/skills/add-roj-problem/scripts/find-empty-roj-id.py
python3 .agents/skills/add-roj-problem/scripts/find-empty-roj-id.py --mode append
python3 .agents/skills/add-roj-problem/scripts/find-empty-roj-id.py --start 20000
python3 .agents/skills/add-roj-problem/scripts/find-empty-roj-id.py --start 30000
```

The helper is read-only and scans only direct numeric directories under `roj/`.
Its default mode is the first empty ID at or above `1000`; `--mode append` returns
the next ID after the largest existing ID. Successful stdout contains only the
integer. For a batch, sort candidate source paths with a deterministic natural sort
(`A`, `B`, `C`; `T1`, `T2`, `T10`) and reserve IDs in that order. Re-scan immediately
before the first write to detect a concurrent collision.

**Choose the ID range by problem type.** Before allocating IDs, ask the user which
type the candidate problem(s) belong to when it is not obvious from the source (a
contest directory, a single standalone problem, etc.):

- **比赛题目** (contest problem, e.g. problems from 暑假比赛, 模拟赛, or other
  contest/round sources): allocate from the `20000+` range by running
  `find-empty-roj-id.py --start 20000`. This keeps contest imports grouped together
  and away from the legacy `1000+` problems.
- **其他题目** (standalone/ordinary problems, e.g. textbook or OpenJudge-style
  problems): use the default mode (first empty ID at or above `1000`).

Use `--mode append` instead when the intent is to continue after the largest existing
ID regardless of range.

## Review-first workflow

### 1. Discover and classify

Read the source tree and build a manifest before making directories. For every
candidate, record its source path, proposed ID, title, statement carrier, source
program candidate, public download files, official test files, image references,
total bytes, and warnings.

Recognize statement carriers in this order:

- Existing `content.md`
- `statement.md`, `题面.md`, `problem.md`
- Another Markdown file only when it is clearly the sole statement (do not select
  `sol.md`, `题解.md`, analysis notes, or workspace notes)
- `content.pdf` or a clearly identified statement PDF when no Markdown statement is
  available

If both Markdown and PDF statements exist, use Markdown for `content.md` and do not
copy the redundant PDF unless the user explicitly requests both. A PDF-only problem
is valid and should receive `content.pdf`.

If no statement Markdown/PDF can be identified, do not create a partial record. Report
the candidate as missing a statement and continue with other candidates.

### 2. Choose the standard source

Select a source program only from the candidate problem directory's root:

1. `std.cpp`
2. A root-level `.cpp` whose basename clearly matches the problem name
3. The only ordinary root-level `.cpp`

Never select a file named or clearly used as `brute`, `gen`, `checker`, `validator`,
`std2`, a test helper, or a file inside `data/`, `down/`, `下发文件/`, or
`rainboy-解析/`. Copy the selected source as `std.cpp`. If no unambiguous source
exists, do not invent an empty file; import may proceed only with a warning that
`std.cpp` is unavailable.

### 3. Derive metadata

Create a JSON object with no `null` values:

- `title`: use a clear title from the statement; otherwise use the contest name plus
  original label, such as `2026 暑假比赛 - T1`. If still ambiguous, pause for the
  user's choice.
- `time`: parse an explicit per-problem limit, then a clearly stated contest-wide
  limit. Convert seconds to integer milliseconds.
- `memory`: parse an explicit per-problem limit, then a clearly stated contest-wide
  limit. Store the numeric value in MB.
- `tags`: use known string tags only; otherwise use `[]`.
- `source`: use a human-readable contest/source label and original problem label, not
  an absolute local path.

Omit unknown `time`, `memory`, or `source` fields rather than guessing or writing
`null`. Serialize with UTF-8, two-space indentation, and a trailing newline. Validate
that the complete JSON tree contains no `null` values and that all tags are strings.

### 4. Normalize the statement

The ROJ renderer does not allow raw HTML. When a Markdown file contains HTML tags,
convert it to standard Markdown with `pandoc` (choose the input mode that matches the
file, such as Markdown with raw HTML or HTML) and `--wrap=none`. Preserve headings,
paragraphs, lists, tables, code blocks, LaTeX formulas, and links. Do not use a broad
regular-expression rewrite as a substitute for an HTML parser.

After conversion, inspect the output for leftover structural HTML, lost formulas,
collapsed code blocks, or broken entities. If conversion cannot be performed because
`pandoc` is unavailable or the result is ambiguous, stop that candidate and report it.

For local images referenced by the statement, resolve paths relative to the source
statement, copy only the referenced files into the new problem directory, and keep
their relative references. Preserve remote image URLs. Missing local images are a
preview warning and require confirmation before importing that candidate.

### 5. Copy repository files

Build each candidate in a temporary directory outside `roj/`, then validate it before
moving it into the final numeric directory:

```text
roj/<id>/
├── config.json
├── data.json                # generated public-data manifest, even when empty
├── content.md              # or content.pdf for PDF-only problems
├── std.cpp                 # only when a source was selected
├── data/                   # public data candidates; web2 applies an extension filter
└── down/                   # legacy compatibility data, not used by the new UI
```

Copy the source `data/` directory recursively, preserving filenames and subdirectories.
The web2 download feature exposes only ordinary files with case-insensitive `.in`,
`.out`, `.ans`, `.txt`, or `.dat` extensions; source code, scripts, executables,
compiled artifacts, hidden files, caches, and symlinks are never public downloads.
Treat a clearly identified `大样例/` directory as data candidates only when the user
confirms it contains files intended for visitors; otherwise report it as unresolved.

Copy `down/` and `下发文件/` into `down/` only when preserving legacy source material
is part of the requested import, preserving their relative directory structure. This
directory is not linked from new contest/problem download UI. Copy only data-like
regular files such as `.in`, `.out`, `.ans`, `.txt`, or `.dat`; exclude source programs
and helper scripts. If a file has an unfamiliar extension, list it in the preview
instead of silently deciding its visibility.

Do not copy solutions, analysis workspaces, readmes, generators, checkers, or unrelated
attachments. Do not follow symlinks outside the source problem directory.

Reject or pause a candidate when any single file intended for a GitHub Raw link is
over 100 MB. GitHub cannot reliably serve such a file through the agreed link; wait
for an explicit Git LFS or external storage decision.

### 6. Generate the public data manifest

Do not append a managed download-link block to `content.md`. Generate
`roj/<id>/data.json` with the bundled manifest tool after copying the public data:

```sh
python3 .agents/skills/add-roj-problem/scripts/generate-data-manifest.py \
  --root roj --problem <id>
```

The manifest contains only a sorted `files` array of `{ "path", "size" }` objects.
Generate `{ "files": [] }` for a problem with no public data. The web2 API reads this
small manifest from bohai and gives the browser and `roj.py` configured GitHub Raw or
mirror source URLs; no VPS data URL is created. In the preview, report the public
data candidates, their relative paths, sizes, and the generated manifest.

Before finalizing an import, run the validator:

```sh
python3 .agents/skills/add-roj-problem/scripts/generate-data-manifest.py --check
```

The validator rejects missing or stale manifests, unsafe paths, unsupported
extensions, symlinks, and any single public file over 100 MiB. Do not claim a Raw
download URL works until the destination is committed and available on GitHub.

Existing legacy download-link blocks are not rewritten automatically. If the user asks
to migrate one, show a separate before/after preview and remove only links explicitly
covered by that request. Do not copy `data/` or `down/` into the bohai deployment; the
deployment script excludes both directories.

### 7. Preview and confirm

Present a flat preview before writing. Include proposed IDs, titles, statement type,
source selection, data/down file counts and sizes, public data candidate count, and every
warning or unresolved choice. Explicitly call out skipped directories and why.

Do not create final `roj/<id>/` directories until the user confirms the complete
batch. Once confirmed, write each candidate to a temporary directory and atomically
rename it into place only after that candidate passes validation. Never overwrite a
pre-existing destination.

### 8. Validate and report

For every imported problem, verify:

- `config.json` parses and contains no `null` values; tags are strings
- exactly one usable statement carrier exists (`content.md` or `content.pdf`)
- `data.json` exists, parses, and matches the copied public data (including an empty
  `files` array when no public data exists)
- `content.md` has no unapproved structural raw HTML
- all local image references resolve to copied files
- every reported public data candidate maps to a copied `data/` file
- `std.cpp` exists when a source was selected
- `data/` and `down/` contain no unexpected symlink escapes
- no destination ID collided during the write
- `git diff --check` is clean for the new text files

If the ROJ web server is already running, request each imported `/problem/<id>` page
and each PDF URL that the current server supports. Verify the manifest endpoint and,
when public data exists, verify at least one configured GitHub source URL after the
destination is committed. Do not claim a download URL works before deployment.

Report imported IDs, skipped candidates, warnings, file counts, and validation results.
Leave all Git operations to the user.

## Common mistakes to avoid

- Do not use the broken `x.isnumeric` bound method from the old `bin/next.py`; the
  bundled helper calls numeric checks correctly and ignores `install.sh` and other
  non-directory entries.
- Do not infer a title from a generic heading such as `题目描述` when a contest label
  is available.
- Do not mistake `题解.md`, `sol.md`, or analysis notes for the statement.
- Do not expose non-allowlisted `data/` files or `std.cpp` merely because they were copied.
- Do not claim a GitHub Raw download works before the files are committed to the
  repository at the generated paths.
