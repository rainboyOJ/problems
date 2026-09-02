# ROJ

ROJ 是只读题目展示站。页面由 Fastify + Pug 服务端渲染，Vite 只负责构建浏览器端静态资源。

## 本地运行

在项目根目录下，确保 `roj/` 与 `web2/` 同级：

```sh
cd web2
npm install
npm run build
npm run start
```

默认访问 `http://127.0.0.1:3033/`。

开发时可以使用 `npm run dev`，它会先构建 Vite 资源，再启动同一个 Fastify 页面服务。

可用环境变量：

- `PORT`：监听端口，默认 `3033`
- `HOST`：监听地址，默认 `0.0.0.0`
- `ROJ_ROOT`：题目目录，默认使用 `web2/../roj`
- `CONTESTS_ROOT`：比赛目录，默认使用 `web2/../contests`
- `DOWNLOAD_CONFIG`：下载配置文件，默认使用 `web2/config.yaml`

开发时可以单独运行 `npm run build`，服务端会读取 `public/assets` 中的构建结果。生产部署前请先构建一次静态资源。

## 内容边界

服务端不会把 `roj/` 注册为静态目录，只公开 Markdown 题面、PDF 题面、题面实际引用的图片，以及每题 `data.json` 中的公开数据清单。公开数据文件由 GitHub Raw 或配置的加速源提供，bohai 不托管或读取 `data/`、`down/`；不把标准程序、题解、脚本、编译产物或未列入清单的附件公开。

公开数据由导入工具从题目的 `data/` 目录生成 `data.json`，仅包含大小写不敏感的 `.in`、`.out`、`.ans`、`.txt`、`.dat` 普通文件及其大小。历史 `down/` 目录不会进入新的下载界面。题目详情页可以在标题下显示“下载数据”和“查看题解”按钮；下载源由 `config.yaml` 配置，具体约定见 [ADR 0004](../docs/adr/0004-github-raw-problem-data-downloads.md)。

## 数据下载配置（设计约定）

部署时通过 `ROJ_ROOT` 指向 bohai 上上传的题面和 manifest；GitHub Raw 地址和加速源作为公开数据源：

```yaml
repository:
  rawBase: https://raw.githubusercontent.com/rainboyOJ/problems/master
download:
  rawMirrors:
    - https://gh-proxy.com/
```

加速源按配置顺序展示，最后保留 `rawBase` 直连；配置由服务启动时读取，修改后需要重启。数据 API 只读取每题的 `data.json`，单文件内容由浏览器或 `roj.py` 直接从选定的 GitHub 源下载。

数据接口约定如下：

```text
GET /api/problems?q=<query>&page=<number> # 分页返回题目元数据
GET /api/problem/<id>                  # 返回单题元数据
GET /api/problem/<id>/markdown         # 返回原始 Markdown 题面
GET /api/problem/<id>/data       # 返回公开文件清单
GET /problem/<id>/pdf            # 题面 PDF
```

`/api/problem/<id>/data` 返回 `sources`、`files`、`totalFiles` 和 `totalBytes`。
`sources` 中每项包含源 ID、显示名称和当前题目的 `baseUrl`；将清单中的安全相对
路径编码后拼接到 `baseUrl`，即可从选中的 GitHub 源下载文件。默认配置优先使用
gh-proxy，始终保留 GitHub Raw 直连。

题目列表 API 返回 `items`、`total`、`totalPages`、`page` 和 `pageSize`；单题
元数据包含题号、标题、时间/内存限制、标签、来源、题面类型，以及 Markdown、
PDF 和公开数据是否存在。客户端应使用分页接口，不要假设一次响应包含全部题目。

清单按规范化相对路径排序；没有公开数据的题目返回空清单，页面隐藏下载按钮。
数据文件由浏览器或 CLI 直接从 GitHub 源下载，Fastify 不接受数据文件路径请求。

文件清单由 Fastify 从 `data.json` 读取并校验，Nginx 只负责 HTTPS 和反向代理。实际数据文件不经过 Fastify，不把整个 `roj/` 配置为 Nginx 的静态目录或 alias；题面、标准程序和配置文件仍必须经过应用层路径规则检查。

## 比赛文件

比赛文件放在仓库根目录的 `contests/` 下，每个一级 Markdown 文件的文件名（不含 `.md`）就是详情页 slug。例如 `contests/2026-summer.md` 对应 `/contest/2026-summer`。

```yaml
---
title: 2026 暑假训练赛
date: 2026-07-01
endDate: 2026-07-07
description: 暑假期间的训练赛
organizer: ROJ
status: archived
tags: [训练赛, 暑假]
---

比赛说明，以及指向站内题目的链接：

- [A. 两数之和](/problem/1000)
```

`title` 是必填字段。`status` 可取 `upcoming`、`ongoing`、`archived`；省略时根据日期按中国时区自动推断。编辑中的文件可以设置 `draft: true` 暂不公开。比赛图片可放在同名目录（如 `contests/2026-summer/schedule.png`），正文使用相对路径引用。
