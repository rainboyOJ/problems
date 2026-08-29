---
name: add-roj-contest
description: Create or update ROJ contest Markdown records under this repository's contests/ directory from user-provided contest information or a local contest source. Use when the user asks to create, add, register, or prepare a contest page for web2. Do not use this skill to import individual problems into roj/; use add-roj-problem instead.
---

# Create a ROJ Contest

Create a reviewable contest record for the read-only ROJ website. The deliverable is a
top-level `contests/<slug>.md` file and, when needed, an adjacent
`contests/<slug>/` resource directory. This is content preparation for the existing
Fastify + Pug site, not an online-judge, registration, submission, or scoring feature.

## When this skill applies

Use it when the user asks to create or maintain a contest page, contest announcement,
contest schedule, or contest overview for this repository, including requests based on
a local contest directory such as `/home/rainboy/tmp-暑假比赛`.

Do not use it for these unrelated tasks:

- Importing a problem, assigning a `roj/<id>`, copying `data/`, `down/`, or `std.cpp`:
  use `add-roj-problem`.
- Changing web2 routes, templates, styling, or the contest data model: treat that as
  an application implementation task and inspect the web2 code directly.
- Publishing files to GitHub, deploying to the VPS, or committing changes: leave those
  actions to the user unless they explicitly request them.

## Read the repository contract first

Before writing anything, inspect the current implementation and working tree:

1. Read `web2/README.md` for the current contest-file contract.
2. Read `web2/server/contest-catalog.mjs` and the contest Pug views when they exist.
3. Inspect `contests/` for existing slugs and resource directories.
4. Inspect `roj/` only to verify problem IDs that the contest will link to. Do not
   recursively scan unrelated paths or infer a missing problem import from this task.
5. Preserve unrelated user changes in the worktree.

The implementation is the source of truth if the instructions below and the code have
drifted. Report a contract mismatch before writing when it would change the resulting
URLs or file format.

## Contest file contract

Only Markdown files directly under `contests/` are discovered. A file's basename is its
URL slug:

```text
contests/2026-summer.md  ->  /contest/2026-summer
```

Use a unique lowercase slug containing only ASCII letters, digits, `_`, and `-`.
Prefer a stable event/date slug such as `2026-summer` or `2026-08-training`; do not
silently transliterate an ambiguous Chinese title. If the appropriate slug is unclear,
ask the user. Never overwrite an existing `contests/<slug>.md` without explicit
permission; a collision is a stop-and-ask condition.

The required frontmatter is `title`. Supported fields are:

```yaml
---
title: 2026 暑假训练赛
date: 2026-07-01
endDate: 2026-07-07
description: 暑假期间的训练赛
organizer: ROJ
status: upcoming
tags: [训练赛, 暑假]
draft: false
---
```

Field rules:

- `title` is a non-empty human-readable string. Do not use the slug as a substitute
  unless the user explicitly wants that title.
- `date` is the start date and `endDate` is the inclusive end date. Use ISO
  `YYYY-MM-DD`; reject impossible dates and do not invent missing dates.
- `status` is optional and, when present, must be `upcoming`, `ongoing`, or `archived`.
  If omitted, the site infers it from the dates using the `Asia/Shanghai` calendar.
- `description`, `organizer`, and `tags` are optional. Keep tags as a list of strings.
- `draft: true` hides the contest from both the list and detail routes. Use it for an
  intentionally unpublished page, not as a way to conceal an unresolved error.
- Unknown frontmatter fields are allowed by the current site and are displayed as
  extra metadata. Preserve meaningful source fields, but do not copy credentials,
  local absolute paths, private URLs, or implementation-only noise.

If a date or status is not known, omit it rather than guessing. If the source contains
times, time zones, or date ranges that cannot be represented by these fields, preserve
the detail in the Markdown body and call out the limitation in the preview.

## Source discovery and problem mapping

The user may provide a complete Markdown draft, a local contest root, or only structured
details. Classify the input before editing:

- For a Markdown draft, parse its frontmatter and body; preserve useful content while
  normalizing links and unsupported raw HTML.
- For a local contest root, inspect only its immediate files and clearly named overview
  material first. Identify the contest title, dates, organizer, schedule, problem
  labels, and explanatory text. Do not treat every child directory as a problem import.
- For a request with no source and no usable contest details, ask for the missing title,
  slug, or source instead of fabricating a contest.

Problem links in the contest body must use standard Markdown links to existing ROJ
  pages:

```markdown
- [A. 两数之和](/problem/1000)
- [B. 统计](/problem/1001)
```

The site extracts `/problem/<number>` links from the rendered body, deduplicates them
in first-appearance order, and displays a generated “比赛题目” section. Before the
preview, verify every proposed ID exists as a usable entry under `roj/` (Markdown or
PDF-only). If a source problem has not been imported yet, do not allocate an ID or
create a partial contest link: tell the user to import it with `add-roj-problem`, or
ask for the correct existing ID. A missing ID may remain in the body only if the user
explicitly wants a placeholder; mark it as unresolved and explain that it will not
appear in the generated list.

Keep external links as ordinary Markdown links. The renderer opens HTTP(S) links in a
new window. Do not turn local absolute paths into links.

## Images and resources

Use the optional adjacent directory for contest images:

```text
contests/
  2026-summer.md
  2026-summer/
    schedule.png
    venue.jpg
```

With the current renderer, a local image in `contests/<slug>/` is referenced from the
Markdown using the slug prefix:

```markdown
![比赛日程](2026-summer/schedule.png)
```

Only existing image files with `.png`, `.jpg`, `.jpeg`, `.gif`, `.webp`, or `.svg`
extensions are served through `/contest/<slug>/asset/...`. Keep paths relative, use
forward slashes, and never use `..`, backslashes, or absolute filesystem paths. The
site does not expose arbitrary contest attachments, source code, test data, or a
general download directory through this feature.

If a local image is missing, report it in the preview and either fix the source path or
leave a clearly marked missing-image warning after the user chooses to proceed. Do not
copy unrelated files merely because they are next to the source Markdown.

## Normalize the Markdown

The web2 renderer supports headings, paragraphs, lists, tables, fenced code, links,
images, LaTeX, and the repository's existing Markdown containers. Keep the contest page
focused on information a reader needs: overview, schedule, rules/notes, problem list,
and references.

Do not copy raw HTML that the renderer will drop. When the source is HTML or contains
structural HTML, use `pandoc` or another appropriate parser to convert it to standard
Markdown, then inspect headings, lists, tables, formulas, code blocks, links, and image
paths. Do not replace a structured conversion with a broad regular-expression rewrite.

Do not duplicate the generated “比赛题目” section in the body solely for the site. The
body should contain the canonical links and surrounding explanation; the page creates
the compact list automatically.

## Review-first workflow

Do not write the final contest file immediately. Follow this sequence:

1. Build a manifest containing the proposed slug, title, dates, status, organizer,
   tags, source path, body sections, problem-link mappings, image paths, and warnings.
2. Check slug collisions, frontmatter validity, date validity, problem existence, local
   image existence, and whether the source contains unsupported or private material.
3. Present a flat preview with the exact destination path, frontmatter, proposed problem
   links, resource files, and every unresolved choice. State whether the page is draft
   or public.
4. Wait for explicit confirmation of the complete preview. A vague “looks fine” about
   only one field is not confirmation for the whole write.
5. Create the Markdown and resource directory only after confirmation. Write through a
   temporary directory when transforming a larger source, then move into place without
   replacing an existing destination.

For an existing contest that the user explicitly asks to update, show a before/after
preview and preserve fields and body sections not covered by the request. If the update
would change the slug or replace existing resources, ask separately before making that
destructive change.

## Validate after writing

Verify all of the following before reporting success:

- `contests/<slug>.md` exists at the exact requested path and parses with `gray-matter`.
- `title` is present and non-empty; dates are valid ISO dates; status and tags follow
  the contract; `draft` has the intended value.
- The Markdown body contains the intended problem links, and each non-placeholder ID
  exists in `roj/`.
- Every local image reference resolves within `contests/<slug>/` and uses an allowed
  image extension; no path escapes the resource directory.
- No raw structural HTML, credentials, local absolute paths, or accidental private
  source material was copied.
- The slug appears at most once, and no unrelated file was overwritten.
- `git diff --check` is clean for the new or changed text files.
- If the web2 server is running, request `/contests` and `/contest/<slug>` and confirm
  the page title, status, generated problem list, and images render as expected. A
  missing problem must remain a logged warning and must not make the page fail.

Do not claim that the page is publicly deployed or that a link is available on GitHub
until the user commits/pushes the files and deploys the repository. Leave Git commands
and VPS operations to the user.

## Minimal template

Use this as a starting point, adapting it to the actual contest information:

```markdown
---
title: 2026 暑假训练赛
date: 2026-07-01
endDate: 2026-07-07
description: 暑假期间的训练赛
organizer: ROJ
tags: [训练赛]
---

## 比赛说明

这里写比赛背景、适用对象和注意事项。

## 时间安排

- 比赛时间：2026-07-01 至 2026-07-07

## 题目

- [A. 两数之和](/problem/1000)
```
