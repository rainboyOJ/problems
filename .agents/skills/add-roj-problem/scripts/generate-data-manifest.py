#!/usr/bin/env python3
"""Generate and validate public data manifests for the ROJ corpus."""

from __future__ import annotations

import argparse
import json
import os
import sys
import tempfile
from pathlib import Path


PUBLIC_EXTENSIONS = frozenset((".in", ".out", ".ans", ".txt", ".dat"))
MAX_FILE_BYTES = 100 * 1024 * 1024


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Generate or validate roj/<id>/data.json manifests."
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=Path("roj"),
        help="ROJ directory to scan (default: ./roj)",
    )
    parser.add_argument(
        "--problem",
        action="append",
        dest="problems",
        help="Only process this numeric problem ID; may be repeated",
    )
    parser.add_argument(
        "--check",
        action="store_true",
        help="Validate existing manifests without writing files",
    )
    return parser.parse_args()


def numeric_problem_dirs(root: Path, selected: list[str] | None) -> list[Path]:
    if not root.exists():
        raise ValueError(f"ROJ directory does not exist: {root}")
    if not root.is_dir() or root.is_symlink():
        raise ValueError(f"ROJ path is not a directory: {root}")

    wanted = set(selected or [])
    if any(not value.isdigit() for value in wanted):
        raise ValueError("--problem values must be numeric IDs")

    directories = []
    for entry in root.iterdir():
        if not entry.is_dir() or entry.is_symlink() or not entry.name.isdigit():
            continue
        if wanted and entry.name not in wanted:
            continue
        directories.append(entry)
    missing = sorted(wanted - {entry.name for entry in directories}, key=int)
    if missing:
        raise ValueError(f"problem directory does not exist: {', '.join(missing)}")
    return sorted(directories, key=lambda entry: int(entry.name))


def is_public_data_path(relative_path: str) -> bool:
    if not relative_path or relative_path.startswith("/") or "\\" in relative_path:
        return False
    parts = relative_path.split("/")
    if any(not part or part in (".", "..") or part.startswith(".") for part in parts):
        return False
    return Path(relative_path).suffix.lower() in PUBLIC_EXTENSIONS


def scan_public_data(data_dir: Path) -> list[dict[str, int | str]]:
    if not data_dir.exists():
        return []
    if not data_dir.is_dir() or data_dir.is_symlink():
        raise ValueError(f"data path is not a regular directory: {data_dir}")

    files: list[dict[str, int | str]] = []
    pending = [data_dir]
    while pending:
        current = pending.pop()
        try:
            entries = list(current.iterdir())
        except OSError as error:
            raise ValueError(f"cannot read data directory {current}: {error}") from error
        for entry in entries:
            if entry.name.startswith(".") or entry.is_symlink():
                continue
            relative = entry.relative_to(data_dir).as_posix()
            if entry.is_dir():
                pending.append(entry)
                continue
            if not entry.is_file() or not is_public_data_path(relative):
                continue
            try:
                size = entry.stat().st_size
            except OSError as error:
                raise ValueError(f"cannot stat data file {entry}: {error}") from error
            if size > MAX_FILE_BYTES:
                raise ValueError(
                    f"data file exceeds 100 MiB and needs a separate storage decision: {entry}"
                )
            files.append({"path": relative, "size": size})
    return sorted(files, key=lambda item: str(item["path"]))


def expected_manifest(problem_dir: Path) -> dict[str, list[dict[str, int | str]]]:
    return {"files": scan_public_data(problem_dir / "data")}


def canonical_json(value: object) -> str:
    return json.dumps(value, ensure_ascii=False, indent=2) + "\n"


def validate_manifest(value: object, problem_dir: Path) -> tuple[bool, str]:
    if not isinstance(value, dict) or set(value) != {"files"}:
        return False, "manifest must contain only a files array"
    files = value.get("files")
    if not isinstance(files, list):
        return False, "manifest files must be an array"

    previous = None
    for item in files:
        if not isinstance(item, dict) or set(item) != {"path", "size"}:
            return False, "each manifest file must contain path and size"
        relative = item["path"]
        size = item["size"]
        if not isinstance(relative, str) or not is_public_data_path(relative):
            return False, f"invalid public data path: {relative!r}"
        if not isinstance(size, int) or isinstance(size, bool) or size < 0:
            return False, f"invalid file size for {relative}"
        if previous is not None and relative <= previous:
            return False, "manifest paths must be strictly sorted"
        previous = relative

    expected = expected_manifest(problem_dir)
    if value != expected:
        return False, "manifest does not match the local data directory"
    return True, ""


def read_manifest(manifest_path: Path) -> object:
    if not manifest_path.exists():
        raise ValueError("manifest is missing")
    if manifest_path.is_symlink() or not manifest_path.is_file():
        raise ValueError("manifest is not a regular file")
    try:
        return json.loads(manifest_path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as error:
        raise ValueError(f"manifest is not valid UTF-8 JSON: {error}") from error


def write_manifest(manifest_path: Path, manifest: dict[str, object]) -> None:
    manifest_path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary_name = tempfile.mkstemp(
        prefix=f".{manifest_path.name}.",
        suffix=".tmp",
        dir=manifest_path.parent,
    )
    temporary_path = Path(temporary_name)
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as output:
            output.write(canonical_json(manifest))
            output.flush()
            os.fsync(output.fileno())
        temporary_path.replace(manifest_path)
    finally:
        temporary_path.unlink(missing_ok=True)


def main() -> int:
    args = parse_args()
    try:
        problem_dirs = numeric_problem_dirs(args.root, args.problems)
        if not problem_dirs:
            raise ValueError(f"no numeric problem directories found under {args.root}")
    except (OSError, ValueError) as error:
        print(f"generate-data-manifest: {error}", file=sys.stderr)
        return 2

    failures = 0
    changed = 0
    for problem_dir in problem_dirs:
        manifest_path = problem_dir / "data.json"
        try:
            expected = expected_manifest(problem_dir)
            if args.check:
                current = read_manifest(manifest_path)
                valid, reason = validate_manifest(current, problem_dir)
                if not valid:
                    raise ValueError(reason)
            else:
                current = None
                if manifest_path.exists():
                    try:
                        current = read_manifest(manifest_path)
                    except ValueError:
                        current = None
                if current != expected or not manifest_path.exists():
                    write_manifest(manifest_path, expected)
                    changed += 1
        except (OSError, ValueError) as error:
            failures += 1
            print(f"{problem_dir.name}: {error}", file=sys.stderr)

    action = "validated" if args.check else f"generated {changed}"
    print(f"{action} {len(problem_dirs)} manifest(s)")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
