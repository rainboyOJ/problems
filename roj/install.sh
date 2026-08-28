#!/usr/bin/env bash

set -euo pipefail

# 脚本所在目录。当前脚本可能从任意目录执行，所以先定位 install.sh 自己的位置。
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# 默认把当前执行目录作为部署目录。用户可以在一个空目录中执行 install.sh，
# 脚本会把仓库、compose 文件、.env、judge 配置和测试数据目录都准备在这里。
DEPLOY_DIR="${DEPLOY_DIR:-$PWD}"
WORKSPACE_DIR="${WORKSPACE_DIR:-$DEPLOY_DIR}"

# GitHub 访问较慢时使用代理。设置 GITHUB_PROXY= 可以关闭代理，直接访问原始 GitHub URL。
GITHUB_PROXY="${GITHUB_PROXY:-https://gh-proxy.com/}"

# GHCR 镜像访问较慢时使用 Docker 镜像代理。设置 DOCKER_IMAGE_PROXY= 可以关闭代理。
DOCKER_IMAGE_PROXY="${DOCKER_IMAGE_PROXY:-gh-proxy.org/docker}"

# 两个需要拉取的仓库地址：judge_server 负责实际评测，roj2 是本 OJ Web/API 项目。
JUDGE_SERVER_REPO_URL="${JUDGE_SERVER_REPO_URL:-https://github.com/rainboyOJ/judge_server_cpp.git}"
ROJ_REPO_URL="${ROJ_REPO_URL:-https://github.com/rainboyOJ/roj2.git}"

# 两个仓库的本地目录，以及容器运行时使用的镜像名。
JUDGE_SERVER_DIR="${JUDGE_SERVER_DIR:-$WORKSPACE_DIR/judge_server_cpp}"
ROJ_DIR="${ROJ_DIR:-$WORKSPACE_DIR/roj2}"
IMAGE_NAME="${IMAGE_NAME:-ghcr.io/rainboyoj/roj2:latest}"
JUDGE_SERVER_IMAGE_NAME="${JUDGE_SERVER_IMAGE_NAME:-ghcr.io/rainboyoj/judge-server-cpp:latest}"
API_HOST_PORT="${API_HOST_PORT:-3300}"

# UPDATE_REPOS=1 时会 git fetch/pull。
UPDATE_REPOS="${UPDATE_REPOS:-0}"
FORCE_JUDGE_CONFIG_COPY="${FORCE_JUDGE_CONFIG_COPY:-0}"

# judge_server 容器运行时挂载的配置和测试数据目录。
COMPOSE_FILE_PATH="${COMPOSE_FILE_PATH:-$DEPLOY_DIR/docker-compose.yaml}"
ENV_FILE_PATH="${ENV_FILE_PATH:-$DEPLOY_DIR/.env}"
JUDGE_SERVER_CONFIG_PATH="${JUDGE_SERVER_CONFIG_PATH:-$DEPLOY_DIR/judge_server_config.json}"
JUDGE_SERVER_TESTDATA_DIR="${JUDGE_SERVER_TESTDATA_DIR:-$DEPLOY_DIR/judge_server_testData}"

# 这两个数组会在 setup_docker_commands 中根据当前用户权限被改成 docker 或 sudo docker。
DOCKER_CMD=(docker)
COMPOSE_CMD=(docker compose)

# 支持 ./install.sh install 和 ./install.sh update，默认 install。
COMMAND="${1:-install}"
STEP_INDEX=0
STEP_TOTAL=0

if [[ -t 1 && -z "${NO_COLOR:-}" ]]; then
  C_RESET=$'\033[0m'
  C_BOLD=$'\033[1m'
  C_CYAN=$'\033[36m'
  C_GREEN=$'\033[32m'
  C_YELLOW=$'\033[33m'
  C_RED=$'\033[31m'
else
  C_RESET=""
  C_BOLD=""
  C_CYAN=""
  C_GREEN=""
  C_YELLOW=""
  C_RED=""
fi

log() {
  printf '%s[install]%s %s\n' "$C_CYAN" "$C_RESET" "$*"
}

step() {
  STEP_INDEX=$((STEP_INDEX + 1))
  printf '%s[install]%s %s[%2d/%2d]%s %s%s%s\n' \
    "$C_CYAN" "$C_RESET" \
    "$C_GREEN" "$STEP_INDEX" "$STEP_TOTAL" "$C_RESET" \
    "$C_BOLD$C_CYAN" "$*" "$C_RESET"
}

warn() {
  printf '%s[install]%s %sWARN:%s %s\n' "$C_CYAN" "$C_RESET" "$C_YELLOW" "$C_RESET" "$*" >&2
}

fail() {
  printf '%s[install]%s %sERROR:%s %s\n' "$C_CYAN" "$C_RESET" "$C_RED" "$C_RESET" "$*" >&2
  exit 1
}

usage() {
  cat <<EOF
Usage:
  ./install.sh          Install and start services.
  ./install.sh update   Update repositories, pull fresh images, and restart services.
  ./install.sh clear    Remove related containers and pulled images.

Environment:
  DEPLOY_DIR=           Directory for docker-compose.yaml, .env, judge config, and test data.
  WORKSPACE_DIR=        Directory where judge_server_cpp and roj2 are cloned.
  UPDATE_REPOS=1        Update existing local git repositories.
  IMAGE_NAME=           OJ image, defaults to ${IMAGE_NAME}.
  JUDGE_SERVER_IMAGE_NAME=
                         judge_server image, defaults to ${JUDGE_SERVER_IMAGE_NAME}.
  GITHUB_PROXY=         Disable the GitHub proxy and use repository URLs directly.
  DOCKER_IMAGE_PROXY=   Disable the Docker image proxy and pull image names directly.
  FORCE_JUDGE_CONFIG_COPY=1
                         Overwrite judge_server_config.json from judge_server repo.
EOF
}

require_command() {
  command -v "$1" >/dev/null 2>&1 || fail "missing required command: $1"
}

# 判断仓库地址是否还是占位值。占位地址不会尝试 clone。
is_placeholder_url() {
  [[ -z "$1" || "$1" == TODO* || "$1" == "placeholder" ]]
}

# 如果启用了 GitHub 代理，并且 URL 是 https://github.com/...，则拼出代理后的下载地址。
# 例如：https://github.com/a/b.git -> https://gh-proxy.com/https://github.com/a/b.git
proxied_git_url() {
  local url=$1
  local proxy=${GITHUB_PROXY%/}

  if [[ -z "$proxy" || "$url" != https://github.com/* ]]; then
    printf '%s\n' "$url"
    return
  fi

  printf '%s/%s\n' "$proxy" "$url"
}

# 如果启用了 Docker 镜像代理，并且镜像名是 ghcr.io/...，则通过代理拉取。
# 拉取后会重新 tag 回原始镜像名，这样 docker-compose.yaml 可以继续使用 ghcr.io/...。
proxied_docker_image() {
  local image=$1
  local proxy=${DOCKER_IMAGE_PROXY%/}

  if [[ -z "$proxy" || "$image" != ghcr.io/* ]]; then
    printf '%s\n' "$image"
    return
  fi

  printf '%s/%s\n' "$proxy" "$image"
}

# 选择可用的 Docker / Compose 命令。
# 如果当前用户不能直接访问 Docker daemon，就使用 sudo docker。
setup_docker_commands() {
  require_command docker

  if docker info >/dev/null 2>&1; then
    DOCKER_CMD=(docker)
  else
    warn "Docker needs sudo permission on this machine."
    log "Requesting sudo now so Docker commands can run."
    sudo -v
    DOCKER_CMD=(sudo docker)
    "${DOCKER_CMD[@]}" info >/dev/null
  fi

  if "${DOCKER_CMD[@]}" compose version >/dev/null 2>&1; then
    COMPOSE_CMD=("${DOCKER_CMD[@]}" compose)
    return
  fi

  if command -v docker-compose >/dev/null 2>&1; then
    if [[ "${DOCKER_CMD[0]}" == "sudo" ]]; then
      COMPOSE_CMD=(sudo docker-compose)
    else
      COMPOSE_CMD=(docker-compose)
    fi
    return
  fi

  fail "missing Docker Compose plugin or docker-compose binary"
}

# 拉取或更新指定仓库：
# - 目录不存在：git clone
# - 目录存在且是 git 仓库：install 模式复用，update 模式 fast-forward 更新
# - 目录存在但不是 git 仓库：只警告，不覆盖用户文件
pull_or_update_repo() {
  local name=$1
  local url=$2
  local dir=$3
  local network_url

  network_url="$(proxied_git_url "$url")"

  if [[ -d "$dir/.git" ]]; then
    if [[ "$UPDATE_REPOS" != "1" ]]; then
      log "using existing $name repo at $dir"
      return
    fi

    log "updating $name at $dir"
    if is_placeholder_url "$url"; then
      git -C "$dir" pull --ff-only
    else
      git -C "$dir" fetch "$network_url"
      git -C "$dir" merge --ff-only FETCH_HEAD
    fi
    return
  fi

  if [[ -d "$dir" ]]; then
    warn "$name directory exists but is not a git repo: $dir"
    return
  fi

  if is_placeholder_url "$url"; then
    warn "$name repo URL is not configured; skipping clone for $dir"
    return
  fi

  if [[ "$network_url" != "$url" ]]; then
    log "cloning $name through GitHub proxy into $dir"
  else
    log "cloning $name into $dir"
  fi
  git clone "$network_url" "$dir"
}

# 启动前检查 roj2 仓库里必须存在 Dockerfile 和 docker-compose.yaml。
ensure_files() {
  [[ -f "$ROJ_DIR/Dockerfile" ]] || fail "missing Dockerfile in $ROJ_DIR"
  [[ -f "$ROJ_DIR/docker-compose.yaml" ]] || fail "missing docker-compose.yaml in $ROJ_DIR"
}

prepare_deploy_workspace() {
  mkdir -p "$DEPLOY_DIR"
  cp "$ROJ_DIR/docker-compose.yaml" "$COMPOSE_FILE_PATH"
  [[ -f "$ROJ_DIR/.env.example" ]] || fail "missing .env.example in $ROJ_DIR"
  cp "$ROJ_DIR/.env.example" "$ENV_FILE_PATH"

  log "prepared compose file: $COMPOSE_FILE_PATH"
  log "prepared env file: $ENV_FILE_PATH"
}

pull_and_tag_image() {
  local label=$1
  local image=$2
  local pull_image

  pull_image="$(proxied_docker_image "$image")"

  if [[ "$pull_image" == "$image" ]]; then
    log "pulling $label image: $image"
    "${DOCKER_CMD[@]}" pull "$image"
    return
  fi

  log "pulling $label image through Docker image proxy: $pull_image"
  if "${DOCKER_CMD[@]}" pull "$pull_image"; then
    log "tagging $pull_image as $image"
    "${DOCKER_CMD[@]}" tag "$pull_image" "$image"
    return
  fi

  warn "failed to pull $pull_image through Docker image proxy; falling back to $image"
  "${DOCKER_CMD[@]}" pull "$image"
}

pull_runtime_images() {
  pull_and_tag_image "application" "$IMAGE_NAME"
  pull_and_tag_image "judge_server" "$JUDGE_SERVER_IMAGE_NAME"
}

prepare_judge_runtime_files() {
  local source_config="$JUDGE_SERVER_DIR/config/config.json"
  local source_default_testdata="$JUDGE_SERVER_DIR/testData/1000"
  local target_default_testdata="$JUDGE_SERVER_TESTDATA_DIR/1000"

  [[ -f "$source_config" ]] || fail "missing judge_server config: $source_config"

  mkdir -p "$(dirname "$JUDGE_SERVER_CONFIG_PATH")"
  mkdir -p "$JUDGE_SERVER_TESTDATA_DIR"

  if [[ -d "$JUDGE_SERVER_CONFIG_PATH" ]]; then
    fail "$JUDGE_SERVER_CONFIG_PATH is a directory; remove it and rerun install.sh so it can be created as a file"
  fi

  if [[ -e "$JUDGE_SERVER_TESTDATA_DIR" && ! -d "$JUDGE_SERVER_TESTDATA_DIR" ]]; then
    fail "$JUDGE_SERVER_TESTDATA_DIR exists but is not a directory"
  fi

  if [[ ! -f "$JUDGE_SERVER_CONFIG_PATH" || "$FORCE_JUDGE_CONFIG_COPY" == "1" ]]; then
    cp "$source_config" "$JUDGE_SERVER_CONFIG_PATH"
    sed -i -E 's#"test_data_path"[[:space:]]*:[[:space:]]*"[^"]*"#"test_data_path": "/opt/boxtest/testData"#' "$JUDGE_SERVER_CONFIG_PATH"
    log "copied judge config to $JUDGE_SERVER_CONFIG_PATH"
  else
    log "using existing judge config: $JUDGE_SERVER_CONFIG_PATH"
  fi

  if [[ -d "$source_default_testdata" && ! -e "$target_default_testdata" ]]; then
    cp -R "$source_default_testdata" "$target_default_testdata"
    log "copied default judge test data to $target_default_testdata"
  elif [[ -d "$target_default_testdata" ]]; then
    log "using existing default judge test data: $target_default_testdata"
  else
    warn "default judge test data not found in $source_default_testdata"
  fi

  log "using judge test data directory: $JUDGE_SERVER_TESTDATA_DIR"
}

clear_docker_resources() {
  log "removing related containers"
  "${DOCKER_CMD[@]}" rm -f \
    roj-api-server \
    roj-judge-dispatcher \
    roj-mongodb \
    roj-judge-server >/dev/null 2>&1 || true

  log "removing pulled images"
  "${DOCKER_CMD[@]}" rmi \
    "$IMAGE_NAME" \
    "$JUDGE_SERVER_IMAGE_NAME" >/dev/null 2>&1 || true
}

main() {
  # update 模式强制更新仓库并重新拉取镜像；install 模式默认复用已有仓库。
  case "$COMMAND" in
    install)
      STEP_TOTAL=11
      ;;
    update)
      STEP_TOTAL=12
      UPDATE_REPOS=1
      ;;
    clear)
      STEP_TOTAL=4
      step "check Docker command"
      require_command docker
      step "setup Docker permissions and Compose command"
      setup_docker_commands
      step "remove related containers and images"
      clear_docker_resources
      step "finish clear"
      return 0
      ;;
    -h|--help|help)
      usage
      return 0
      ;;
    *)
      usage >&2
      fail "unknown command: $COMMAND"
      ;;
  esac

  step "check git command"
  require_command git
  step "setup Docker permissions and Compose command"
  setup_docker_commands

  log "This installer may use sudo for Docker, depending on your local Docker permissions."

  # 先准备两个代码仓库，再检查构建所需文件。
  step "prepare judge_server repository"
  pull_or_update_repo "judge_server" "$JUDGE_SERVER_REPO_URL" "$JUDGE_SERVER_DIR"
  step "prepare roj2 repository"
  pull_or_update_repo "roj2" "$ROJ_REPO_URL" "$ROJ_DIR"

  step "check required project files"
  ensure_files
  step "prepare deploy workspace"
  prepare_deploy_workspace
  step "pull runtime Docker images"
  pull_runtime_images
  step "prepare judge_server runtime files"
  prepare_judge_runtime_files

  step "prepare Docker Compose workspace"
  # docker compose 在部署目录中执行。compose 文件和 .env 都由 install.sh 生成在这里。
  cd "$DEPLOY_DIR"
  export IMAGE_NAME
  export JUDGE_SERVER_IMAGE_NAME
  export JUDGE_SERVER_CONFIG_PATH
  export JUDGE_SERVER_TESTDATA_DIR
  export API_HOST_PORT

  # update 模式先停掉旧容器，避免旧服务或孤儿容器继续占用端口。
  if [[ "$COMMAND" == "update" ]]; then
    step "stop old services when updating"
    "${COMPOSE_CMD[@]}" down --remove-orphans
  else
    log "install mode: skip stopping existing services"
  fi

  step "start services with Docker Compose"
  "${COMPOSE_CMD[@]}" up -d

  step "finish install"
  cat <<EOF
[install] done
[install] API: http://127.0.0.1:$API_HOST_PORT/problems
[install]
[install] judge_server runtime files:
[install]   config:    $JUDGE_SERVER_CONFIG_PATH
[install]   testData:  $JUDGE_SERVER_TESTDATA_DIR
[install]
[install] To change judge_server settings:
[install]   1. stop services:
[install]      cd $DEPLOY_DIR && ${COMPOSE_CMD[*]} down
[install]   2. edit $JUDGE_SERVER_CONFIG_PATH
[install]   3. put problem data under $JUDGE_SERVER_TESTDATA_DIR/<pid>/data
[install]   4. start services:
[install]      cd $DEPLOY_DIR && ${COMPOSE_CMD[*]} up -d
[install]
[install] Logs:
[install]   cd $DEPLOY_DIR && ${COMPOSE_CMD[*]} logs -f judge-server judge-dispatcher api-server
[install] Stop: ${COMPOSE_CMD[*]} down
EOF
}

main "$@"
