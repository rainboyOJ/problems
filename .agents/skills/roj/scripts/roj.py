#!/usr/bin/env python3
"""Small read-only client for the ROJ problem site.

The client deliberately keeps judging local: the website exposes statements,
metadata, and public data, but never receives source code or runs a submission.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
from pathlib import Path
from typing import Any, Iterable
from urllib.error import HTTPError, URLError
from urllib.parse import quote, urljoin
from urllib.request import Request, urlopen


DEFAULT_BASE_URL = "https://roj.ac.cn"
DEFAULT_DOWNLOAD_ROOT = Path("roj-data")
DEFAULT_TEST_TIMEOUT_SECONDS = 5.0
CHUNK_SIZE = 1024 * 1024


class RojError(Exception):
    """An expected API, network, or local-data error."""

    def __init__(self, message: str, status: int | None = None):
        super().__init__(message)
        self.status = status


def json_requested(args: argparse.Namespace) -> bool:
    return bool(getattr(args, "json", False) or getattr(args, "command_json", False))


def problem_id(value: str) -> str:
    value = str(value).strip()
    if not re.fullmatch(r"\d+", value):
        raise argparse.ArgumentTypeError("题号必须是数字。")
    return value


def safe_relative_path(value: str) -> str:
    """Validate a manifest path before using it on the local filesystem."""
    if not isinstance(value, str) or not value or "\x00" in value:
        raise RojError("服务器返回了无效的数据文件路径。")
    if value.startswith("/") or "\\" in value:
        raise RojError(f"拒绝不安全的数据路径：{value}")
    parts = value.split("/")
    if any(not part or part in (".", "..") or part.startswith(".") for part in parts):
        raise RojError(f"拒绝不安全的数据路径：{value}")
    return value


def natural_key(value: str) -> list[Any]:
    return [(0, int(part)) if part.isdigit() else (1, part.lower()) for part in re.split(r"(\d+)", value)]


class RojClient:
    def __init__(self, base_url: str, timeout: float = 30.0):
        self.base_url = base_url.rstrip("/") + "/"
        self.timeout = timeout

    def make_url(self, path: str) -> str:
        return urljoin(self.base_url, path.lstrip("/"))

    def request(self, path: str, accept: str = "application/json") -> tuple[bytes, Any]:
        url = self.make_url(path)
        request = Request(url, headers={"Accept": accept, "User-Agent": "roj-cli/1.0"})
        try:
            with urlopen(request, timeout=self.timeout) as response:
                return response.read(), response.headers
        except HTTPError as error:
            detail = "请求失败。"
            try:
                payload = json.loads(error.read().decode("utf-8", errors="replace"))
                if isinstance(payload, dict) and payload.get("message"):
                    detail = str(payload["message"])
            except (ValueError, UnicodeError):
                pass
            raise RojError(f"HTTP {error.code}: {detail}", error.code) from error
        except URLError as error:
            raise RojError(f"无法连接 ROJ：{error.reason}") from error
        except TimeoutError as error:
            raise RojError("请求 ROJ 超时。") from error

    def json(self, path: str) -> dict[str, Any]:
        body, _ = self.request(path)
        try:
            value = json.loads(body.decode("utf-8"))
        except (UnicodeDecodeError, json.JSONDecodeError) as error:
            raise RojError("ROJ 返回了无效的 JSON。") from error
        if not isinstance(value, dict):
            raise RojError("ROJ 返回的 JSON 结构无效。")
        return value

    def problem(self, identifier: str) -> dict[str, Any]:
        return self.json(f"/api/problem/{quote(identifier, safe='')}")

    def manifest(self, identifier: str) -> dict[str, Any]:
        result = self.json(f"/api/problem/{quote(identifier, safe='')}/data")
        files = result.get("files")
        if not isinstance(files, list):
            raise RojError("ROJ 返回的数据清单无效。")
        normalized = []
        for item in files:
            if not isinstance(item, dict) or not isinstance(item.get("path"), str):
                raise RojError("ROJ 返回了无效的数据文件项。")
            normalized.append({
                **item,
                "path": safe_relative_path(item["path"]),
            })
        return {**result, "files": normalized}

    def markdown(self, identifier: str) -> str | None:
        try:
            body, _ = self.request(f"/api/problem/{quote(identifier, safe='')}/markdown", "text/markdown")
        except RojError as error:
            if error.status == 404:
                return None
            raise
        return body.decode("utf-8")


def manifest_file(manifest: dict[str, Any], requested: str) -> dict[str, Any]:
    requested = safe_relative_path(requested)
    files = manifest.get("files", [])
    exact = next((item for item in files if item["path"] == requested), None)
    if exact:
        return exact
    # A basename is convenient for the usual flat data/ directory. Only accept
    # it when unambiguous, so a nested manifest can never download the wrong file.
    matches = [item for item in files if Path(item["path"]).name == requested]
    if len(matches) == 1:
        return matches[0]
    raise RojError(f"公开数据中没有唯一匹配的文件：{requested}")


def local_destination(root: Path, relative: str) -> Path:
    relative = safe_relative_path(relative)
    root = root.expanduser().absolute()
    destination = (root / Path(*relative.split("/"))).absolute()
    try:
        destination.relative_to(root)
    except ValueError as error:
        raise RojError(f"数据路径超出目标目录：{relative}") from error
    return destination


def download_to(client: RojClient, url: str, destination: Path, force: bool = False) -> int:
    if destination.exists() and not force:
        raise RojError(f"文件已存在，未覆盖：{destination}（如需覆盖请使用 --force）")
    temporary = None
    total = 0
    try:
        destination.parent.mkdir(parents=True, exist_ok=True)
        with urlopen(Request(url, headers={"Accept": "application/octet-stream", "User-Agent": "roj-cli/1.0"}), timeout=client.timeout) as response:
            with tempfile.NamedTemporaryFile(prefix=".roj-download-", dir=destination.parent, delete=False) as output:
                temporary = Path(output.name)
                while True:
                    chunk = response.read(CHUNK_SIZE)
                    if not chunk:
                        break
                    output.write(chunk)
                    total += len(chunk)
        os.replace(temporary, destination)
        temporary = None
        return total
    except HTTPError as error:
        raise RojError(f"下载失败：HTTP {error.code}") from error
    except URLError as error:
        raise RojError(f"下载失败：{error.reason}") from error
    except OSError as error:
        raise RojError(f"无法写入下载文件：{destination}（{error.strerror or error}）") from error
    finally:
        if temporary:
            temporary.unlink(missing_ok=True)


def file_url(client: RojClient, identifier: str, relative: str) -> str:
    encoded = "/".join(quote(part, safe="") for part in safe_relative_path(relative).split("/"))
    return client.make_url(f"/problem/{quote(identifier, safe='')}/data/{encoded}")


def download_manifest(client: RojClient, identifier: str, manifest: dict[str, Any], destination: Path,
                      force: bool = False, skip_existing: bool = False) -> tuple[list[dict[str, Any]], list[Path]]:
    downloaded: list[dict[str, Any]] = []
    skipped: list[Path] = []
    for item in manifest.get("files", []):
        target = local_destination(destination, item["path"])
        if target.exists() and skip_existing and not force:
            skipped.append(target)
            continue
        size = download_to(client, file_url(client, identifier, item["path"]), target, force=force)
        downloaded.append({"path": item["path"], "size": size})
    return downloaded, skipped


def print_manifest_summary(manifest: dict[str, Any]) -> None:
    files = manifest.get("files", [])
    total_bytes = manifest.get("totalBytes")
    if not isinstance(total_bytes, (int, float)):
        total_bytes = sum(int(item.get("size", 0) or 0) for item in files)
    print(f"公开数据：{len(files)} 个文件，共 {format_bytes(total_bytes)}")


def format_bytes(value: int | float) -> str:
    value = max(0, float(value))
    units = ("B", "KiB", "MiB", "GiB")
    index = 0
    while value >= 1024 and index < len(units) - 1:
        value /= 1024
        index += 1
    return f"{value:.1f} {units[index]}" if index else f"{int(value)} B"


def cmd_list(client: RojClient, args: argparse.Namespace) -> int:
    query = args.query or ""
    if args.page:
        result = client.json(f"/api/problems?q={quote(query)}&page={args.page}")
        items = result.get("items", [])
        payload = result
    else:
        first = client.json(f"/api/problems?q={quote(query)}&page=1")
        items = list(first.get("items", []))
        total_pages = int(first.get("totalPages", 1) or 1)
        for page in range(2, total_pages + 1):
            current = client.json(f"/api/problems?q={quote(query)}&page={page}")
            items.extend(current.get("items", []))
        payload = {**first, "items": items, "page": 1, "totalPages": total_pages}

    if json_requested(args):
        print(json.dumps(payload, ensure_ascii=False, indent=2))
        return 0
    if not items:
        print("没有找到题目。")
        return 0
    print(f"共 {len(items)} 道题目" + (f"（关键词：{query}）" if query else ""))
    print(f"{'ID':<8} {'题目'}")
    print("-" * 72)
    for item in items:
        print(f"{str(item.get('id', '-')):<8} {item.get('title', '未命名题目')}")
    return 0


def cmd_get(client: RojClient, args: argparse.Namespace) -> int:
    metadata = client.problem(args.identifier)
    markdown = None if args.no_markdown else client.markdown(args.identifier)
    if json_requested(args):
        print(json.dumps({**metadata, "markdown": markdown}, ensure_ascii=False, indent=2))
        return 0
    print(f"题目 {metadata.get('id', args.identifier)}：{metadata.get('title', '未命名题目')}")
    if metadata.get("time") is not None:
        print(f"时间限制：{metadata['time']} ms")
    if metadata.get("memory") is not None:
        print(f"内存限制：{metadata['memory']} MB")
    if metadata.get("tags"):
        print(f"标签：{'、'.join(metadata['tags'])}")
    print(f"题面类型：{'Markdown' if metadata.get('hasMarkdown') else 'PDF'}")
    print(f"公开数据：{'有' if metadata.get('hasPublicData') else '无'}")
    if metadata.get("source"):
        print(f"来源：{metadata['source']}")
    if markdown is not None:
        print("\n" + markdown, end="" if markdown.endswith("\n") else "\n")
    elif metadata.get("hasPdf"):
        print(f"\n这道题是 PDF 题面，请在浏览器打开：{client.make_url(metadata.get('urls', {}).get('pdf', f'/problem/{args.identifier}/pdf'))}")
    return 0


def cmd_download(client: RojClient, args: argparse.Namespace) -> int:
    manifest = client.manifest(args.identifier)
    destination = Path(args.output or DEFAULT_DOWNLOAD_ROOT / args.identifier)
    if not manifest.get("files"):
        raise RojError("这道题没有公开数据。")

    if args.zip:
        target = destination / f"roj-{args.identifier}-data.zip"
        zip_path = manifest.get("zipUrl") or f"/problem/{args.identifier}/data.zip"
        size = download_to(client, client.make_url(zip_path), target, force=args.force)
        payload = {"problemId": args.identifier, "kind": "zip", "path": str(target), "size": size}
        if json_requested(args):
            print(json.dumps(payload, ensure_ascii=False, indent=2))
        else:
            print_manifest_summary(manifest)
            print(f"已下载 ZIP：{target}（{format_bytes(size)}）")
        return 0

    files = [manifest_file(manifest, args.file)] if args.file else manifest.get("files", [])
    selected_manifest = {**manifest, "files": files}
    downloaded, skipped = download_manifest(client, args.identifier, selected_manifest, destination, force=args.force)
    payload = {
        "problemId": args.identifier,
        "kind": "files",
        "destination": str(destination),
        "downloaded": [{**item, "localPath": str(local_destination(destination, item["path"]))} for item in downloaded],
        "skipped": [str(target) for target in skipped],
    }
    if json_requested(args):
        print(json.dumps(payload, ensure_ascii=False, indent=2))
    else:
        print_manifest_summary(manifest)
        for item in downloaded:
            print(f"已下载：{local_destination(destination, item['path'])}")
        for target in skipped:
            print(f"已存在，跳过：{target}")
    return 0


def find_data_pairs(data_dir: Path) -> tuple[list[tuple[Path, Path, str]], list[str]]:
    if not data_dir.is_dir():
        raise RojError(f"数据目录不存在：{data_dir}")
    inputs: dict[str, Path] = {}
    outputs: dict[str, Path] = {}
    for path in data_dir.rglob("*"):
        if not path.is_file() or path.is_symlink():
            continue
        suffix = path.suffix.lower()
        relative = path.relative_to(data_dir).as_posix()
        key = str(Path(relative).with_suffix(""))
        if suffix == ".in":
            inputs[key] = path
        elif suffix == ".out" or (suffix == ".ans" and key not in outputs):
            outputs[key] = path
    missing: list[str] = []
    pairs: list[tuple[Path, Path, str]] = []
    for key in sorted(set(inputs) | set(outputs), key=natural_key):
        if key not in inputs:
            missing.append(f"缺少输入：{key}")
        elif key not in outputs:
            missing.append(f"缺少输出：{key}")
        else:
            pairs.append((inputs[key], outputs[key], key))
    if not pairs:
        raise RojError(f"数据目录没有可评测的 .in/.out 或 .in/.ans 数据：{data_dir}")
    return pairs, missing


def run_case(executable: Path, input_path: Path, expected_path: Path, output_path: Path,
             timeout_seconds: float, diff_command: str) -> dict[str, Any]:
    started = time.monotonic()
    try:
        with input_path.open("rb") as source, output_path.open("wb") as actual:
            process = subprocess.run([str(executable)], stdin=source, stdout=actual, stderr=subprocess.PIPE,
                                     timeout=timeout_seconds, check=False)
    except subprocess.TimeoutExpired:
        return {"name": input_path.name, "input": str(input_path), "expected": str(expected_path),
                "status": "TLE", "timeMs": round((time.monotonic() - started) * 1000, 2)}
    except OSError as error:
        raise RojError(f"无法运行测试数据 {input_path}：{error}") from error
    elapsed = round((time.monotonic() - started) * 1000, 2)
    if process.returncode != 0:
        stderr = process.stderr.decode("utf-8", errors="replace")[-4000:]
        return {"name": input_path.name, "input": str(input_path), "expected": str(expected_path),
                "status": "RE", "returnCode": process.returncode, "stderr": stderr, "timeMs": elapsed}
    try:
        diff = subprocess.run([diff_command, "-b", str(expected_path), str(output_path)],
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False)
    except OSError as error:
        raise RojError("系统中找不到 diff，无法按约定比较输出。") from error
    if diff.returncode == 0:
        status = "AC"
    elif diff.returncode == 1:
        status = "WA"
    else:
        raise RojError("diff 比较输出时发生错误：" + diff.stderr.decode("utf-8", errors="replace"))
    return {"name": input_path.name, "input": str(input_path), "expected": str(expected_path),
            "status": status, "timeMs": elapsed}


def cmd_test(client: RojClient, args: argparse.Namespace) -> int:
    metadata = client.problem(args.identifier)
    data_dir = Path(args.data_dir) if args.data_dir else None
    if data_dir is None:
        candidates = [DEFAULT_DOWNLOAD_ROOT / args.identifier, Path("roj") / args.identifier / "data"]
        data_dir = next((candidate for candidate in candidates if candidate.is_dir()), None)
    if args.download:
        manifest = client.manifest(args.identifier)
        data_dir = data_dir or DEFAULT_DOWNLOAD_ROOT / args.identifier
        if not manifest.get("files"):
            raise RojError("这道题没有公开数据，无法评测。")
        download_manifest(client, args.identifier, manifest, data_dir, force=args.force, skip_existing=True)
    if data_dir is None:
        raise RojError("找不到本地数据；请先运行 download，或给 test 加 --download。")

    pairs, missing = find_data_pairs(data_dir)
    compiler = shutil.which(args.compiler)
    if not compiler:
        raise RojError(f"找不到 C++ 编译器：{args.compiler}")
    diff_command = shutil.which("diff")
    if not diff_command:
        raise RojError("找不到系统 diff，无法按 diff -b 比较输出。")

    timeout_seconds = DEFAULT_TEST_TIMEOUT_SECONDS
    if isinstance(metadata.get("time"), (int, float)) and metadata["time"] > 0:
        timeout_seconds = max(0.001, float(metadata["time"]) / 1000)
    source = Path(args.source).expanduser()
    if not source.is_file():
        raise RojError(f"源代码文件不存在：{source}")
    results: list[dict[str, Any]] = []
    compile_error = None
    with tempfile.TemporaryDirectory(prefix=f"roj-test-{args.identifier}-") as temporary_dir:
        executable = Path(temporary_dir) / "main"
        try:
            compile_process = subprocess.run([compiler, "-std=c++17", "-O2", str(source.absolute()), "-o", str(executable)],
                                             stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=False, timeout=60)
        except subprocess.TimeoutExpired:
            compile_error = "编译超时。"
        else:
            if compile_process.returncode != 0:
                compile_error = compile_process.stderr.decode("utf-8", errors="replace")[-6000:]
        if compile_error is None:
            for index, (input_path, expected_path, key) in enumerate(pairs, 1):
                output_path = Path(temporary_dir) / f"output-{index}.txt"
                result = run_case(executable, input_path, expected_path, output_path, timeout_seconds, diff_command)
                result["index"] = index
                result["case"] = key
                results.append(result)

    passed = sum(result["status"] == "AC" for result in results)
    payload = {
        "problem": metadata,
        "source": str(source),
        "dataDir": str(data_dir),
        "timeLimitMs": metadata.get("time"),
        "memoryLimitMb": metadata.get("memory"),
        "comparison": "diff -b",
        "compile": {"compiler": compiler, "standard": "c++17", "error": compile_error},
        "missingData": missing,
        "passed": passed,
        "total": len(pairs),
        "results": results,
    }
    if json_requested(args):
        print(json.dumps(payload, ensure_ascii=False, indent=2))
    else:
        print(f"题目 {args.identifier}：{metadata.get('title', '未命名题目')}")
        print(f"数据目录：{data_dir}；比较方式：diff -b；时间限制：{timeout_seconds:g} 秒/组")
        if compile_error is not None:
            print("编译失败：")
            print(compile_error.rstrip())
            return 1
        for result in results:
            print(f"{result['index']:>3}. {result['case']:<30} {result['status']:<3} {result['timeMs']:>8} ms")
        for warning in missing:
            print(f"警告：{warning}")
        print(f"结果：{passed}/{len(pairs)} AC")
    return 0 if compile_error is None and passed == len(pairs) and not missing else 1


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="ROJ 只读题目客户端：查询题面、下载公开数据并在本地评测。")
    parser.add_argument("--base-url", default=os.environ.get("ROJ_URL", DEFAULT_BASE_URL), help="ROJ 地址，默认读取 ROJ_URL 或 https://roj.ac.cn")
    parser.add_argument("--timeout", type=float, default=30.0, help="网络请求超时秒数")
    parser.add_argument("--json", action="store_true", help="使用 JSON 输出")
    commands = parser.add_subparsers(dest="command", required=True)

    list_parser = commands.add_parser("list", help="列出题目")
    list_parser.add_argument("query", nargs="?", help="按题号或标题搜索")
    list_parser.add_argument("--page", type=int, help="只请求指定页；省略时自动翻页")
    list_parser.add_argument("--json", dest="command_json", action="store_true", help="使用 JSON 输出")
    list_parser.set_defaults(handler=cmd_list)

    get_parser = commands.add_parser("get", help="获取题目信息和题面")
    get_parser.add_argument("identifier", type=problem_id)
    get_parser.add_argument("--no-markdown", action="store_true", help="只获取元数据，不读取 Markdown")
    get_parser.add_argument("--json", dest="command_json", action="store_true", help="使用 JSON 输出")
    get_parser.set_defaults(handler=cmd_get)

    download_parser = commands.add_parser("download", help="下载公开数据")
    download_parser.add_argument("identifier", type=problem_id)
    group = download_parser.add_mutually_exclusive_group()
    group.add_argument("--file", help="只下载指定文件或唯一匹配的文件名")
    group.add_argument("--zip", action="store_true", help="下载服务器按请求生成的 ZIP")
    download_parser.add_argument("--output", help="目标目录，默认 ./roj-data/<id>/")
    download_parser.add_argument("--force", action="store_true", help="允许覆盖已有文件")
    download_parser.add_argument("--json", dest="command_json", action="store_true", help="使用 JSON 输出")
    download_parser.set_defaults(handler=cmd_download)

    test_parser = commands.add_parser("test", help="使用公开数据在本地评测 C++")
    test_parser.add_argument("identifier", type=problem_id)
    test_parser.add_argument("source", help="C++ 源代码文件")
    test_parser.add_argument("--data-dir", help="本地数据目录")
    test_parser.add_argument("--download", action="store_true", help="数据缺失时显式下载到 ./roj-data/<id>/")
    test_parser.add_argument("--force", action="store_true", help="配合 --download 覆盖已有数据")
    test_parser.add_argument("--compiler", default="g++", help="C++ 编译器，默认 g++")
    test_parser.add_argument("--json", dest="command_json", action="store_true", help="使用 JSON 输出")
    test_parser.set_defaults(handler=cmd_test)
    return parser


def main(argv: Iterable[str] | None = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    client = RojClient(args.base_url, args.timeout)
    try:
        return int(args.handler(client, args))
    except RojError as error:
        if json_requested(args):
            print(json.dumps({"error": "roj_error", "message": str(error)}, ensure_ascii=False), file=sys.stderr)
        else:
            print(f"错误：{error}", file=sys.stderr)
        return 2
    except KeyboardInterrupt:
        print("已取消。", file=sys.stderr)
        return 130


if __name__ == "__main__":
    raise SystemExit(main())
