#!/usr/bin/env python3
"""Find an unused numeric problem ID under a ROJ directory.

The default mode returns the first gap at or above --start.  Append mode returns the
next ID after the largest existing numeric directory.  The script never mutates the
filesystem and writes only the selected integer to stdout on success.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Find an unused numeric ID in a ROJ directory."
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=Path("roj"),
        help="ROJ directory to scan (default: ./roj)",
    )
    parser.add_argument(
        "--start",
        type=int,
        default=1000,
        help="Smallest candidate ID (default: 1000)",
    )
    parser.add_argument(
        "--mode",
        choices=("gap", "append"),
        default="gap",
        help="gap: first missing ID; append: ID after the current maximum",
    )
    return parser.parse_args()


def numeric_directories(root: Path) -> set[int]:
    if not root.exists():
        raise ValueError(f"ROJ directory does not exist: {root}")
    if not root.is_dir():
        raise ValueError(f"ROJ path is not a directory: {root}")

    ids: set[int] = set()
    for entry in root.iterdir():
        if (
            not entry.is_dir()
            or entry.is_symlink()
            or not entry.name
            or any(char < "0" or char > "9" for char in entry.name)
        ):
            continue
        ids.add(int(entry.name))
    return ids


def find_id(ids: set[int], start: int, mode: str) -> int:
    if start < 0:
        raise ValueError("--start must be non-negative")
    if mode == "append":
        return max(max(ids, default=start - 1) + 1, start)

    candidate = start
    while candidate in ids:
        candidate += 1
    return candidate


def main() -> int:
    args = parse_args()
    try:
        ids = numeric_directories(args.root)
        selected = find_id(ids, args.start, args.mode)
    except (OSError, ValueError) as error:
        print(f"find-empty-roj-id: {error}", file=sys.stderr)
        return 2

    print(selected)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
