
# ROJ Skill 安装说明

这是一份给 OpenCode、Codex 或 Claude Code 使用的安装指令。用户要求安装
ROJ Skill 时，请按下面的流程执行。不要下载或克隆整个
`rainboyOJ/problems` 仓库。

## 目标文件

只从 GitHub Raw 下载以下三个文件：

```text
https://raw.githubusercontent.com/rainboyOJ/problems/master/.agents/skills/roj/SKILL.md
https://raw.githubusercontent.com/rainboyOJ/problems/master/.agents/skills/roj/scripts/roj.py
https://raw.githubusercontent.com/rainboyOJ/problems/master/.agents/skills/roj/agents/openai.yaml
```

安装命令默认先访问 GitHub Raw；直连失败时，自动改用
`https://gh-proxy.com/https://raw.githubusercontent.com/...` 重试。可以通过
`RAW_BASE` 和 `RAW_MIRROR` 环境变量替换默认地址。

## 选择安装目录

先识别当前 Agent 的 Skill 目录和项目级 Skill 目录，遵循当前工具的既有约定：

- 如果用户明确指定了安装目录，使用用户指定的目录。
- 如果当前项目已经有 `.agents/skills/`，优先安装到当前项目的
  `.agents/skills/roj/`，这样项目协作者都能使用。
- 全局安装统一使用 `$AGENT_HOME/skills/roj/`；如果没有设置 `AGENT_HOME`，
  使用默认目录 `~/.agents/skills/roj/`。
- 如果 OpenCode、Codex 或 Claude Code 当前配置了专用的全局 Skill 目录，遵循
  工具的现有配置；如果只需要当前项目可用，使用项目约定的
  `.agents/skills/roj/` 或 `.claude/skills/roj/`。

不要凭猜测覆盖一个已经存在的 `roj` Skill。目标目录存在且内容不是本仓库版本时，
先报告差异并请求用户确认；目录不存在时才创建。

## 安装步骤

将下面的 `<SKILL_DIR>` 替换为上一步选定的目录，然后执行：

```sh
set -eu

RAW_BASE="${RAW_BASE:-https://raw.githubusercontent.com/rainboyOJ/problems/master}"
RAW_MIRROR="${RAW_MIRROR:-https://gh-proxy.com}"
RAW_BASE="${RAW_BASE%/}"
RAW_MIRROR="${RAW_MIRROR%/}"
TMP_DIR="$(mktemp -d)"
trap 'rm -rf "$TMP_DIR"' EXIT

download_raw() {
  path="$1"
  output="$2"
  direct_url="${RAW_BASE}/${path}"
  mirror_url="${RAW_MIRROR}/${direct_url}"
  if curl -fL --retry 2 --connect-timeout 10 "$direct_url" -o "$output"; then
    return 0
  fi
  printf 'GitHub Raw 直连失败，改用加速源：%s\n' "$mirror_url" >&2
  curl -fL --retry 2 --connect-timeout 10 "$mirror_url" -o "$output"
}

download_raw ".agents/skills/roj/SKILL.md" "$TMP_DIR/SKILL.md"
download_raw ".agents/skills/roj/scripts/roj.py" "$TMP_DIR/roj.py"
download_raw ".agents/skills/roj/agents/openai.yaml" "$TMP_DIR/openai.yaml"

mkdir -p "<SKILL_DIR>/scripts" "<SKILL_DIR>/agents"
cp "$TMP_DIR/SKILL.md" "<SKILL_DIR>/SKILL.md"
cp "$TMP_DIR/roj.py" "<SKILL_DIR>/scripts/roj.py"
cp "$TMP_DIR/openai.yaml" "<SKILL_DIR>/agents/openai.yaml"
chmod +x "<SKILL_DIR>/scripts/roj.py"
```

如果系统没有 `curl`，使用等价的 `wget`，但仍然只下载上面列出的文件。不要使用
`git clone`，也不要把 `roj/`、`data/` 或整个仓库复制到 Skill 目录。

## 验证

安装后检查文件存在，并运行：

```sh
python3 "<SKILL_DIR>/scripts/roj.py" --help
```

确认帮助中包含 `list`、`get`、`download` 和 `test` 四个命令。最后告知用户安装
目录和验证结果。ROJ 客户端只查询题目、读取题面、下载公开数据并在本地评测 C++；
它不提交代码，也不调用远程评测服务。
