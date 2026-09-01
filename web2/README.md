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

服务端不会把 `roj/` 注册为静态目录，只公开 Markdown 题面、PDF 题面、题面实际引用的图片，以及经过筛选的公开数据清单。公开数据文件由 bohai VPS 的下载路由提供，ZIP 按请求由服务端生成；不把标准程序、题解、脚本、编译产物或未列入清单的附件公开。

公开数据候选来自题目的 `data/` 目录，仅包含大小写不敏感的 `.in`、`.out`、`.ans`、`.txt`、`.dat` 普通文件。历史 `down/` 目录不会进入新的下载界面。题目详情页可以在标题下显示“下载数据”和“查看题解”按钮；打包下载由服务端按请求生成 `roj-<id>-data.zip`，具体约定见 [ADR 0003](../docs/adr/0003-browser-side-raw-problem-data-downloads.md)。

## 数据下载配置（设计约定）

部署时通过 `ROJ_ROOT` 指向 bohai 上上传的 `roj/` 目录。GitHub Raw 地址和加速源只作为可选的单文件备用源：

```yaml
repository:
  rawBase: https://raw.githubusercontent.com/rainboyOJ/problems/master
download:
  rawMirrors:
    - https://gh-proxy.com/
```

加速源按配置顺序尝试，最后回退到 `rawBase`；配置由服务启动时读取，修改后需要重启。ZIP 不依赖这些外部源，而是从 VPS 本地文件按请求生成。ZIP 默认只允许一个任务同时运行，其他请求进入有上限的队列，队列满时返回可重试的繁忙状态，并带有 `Retry-After`。数据 API、单文件下载和 ZIP 生成已经在 `web2` 中实现。

数据接口约定如下：

```text
GET /api/problems?q=<query>&page=<number> # 分页返回题目元数据
GET /api/problem/<id>                  # 返回单题元数据
GET /api/problem/<id>/markdown         # 返回原始 Markdown 题面
GET /api/problem/<id>/data       # 返回公开文件清单
GET /problem/<id>/data/<path>    # 流式下载单个文件
GET /problem/<id>/data.zip       # 按请求生成 ZIP
```

题目列表 API 返回 `items`、`total`、`totalPages`、`page` 和 `pageSize`；单题
元数据包含题号、标题、时间/内存限制、标签、来源、题面类型，以及 Markdown、
PDF 和公开数据是否存在。客户端应使用分页接口，不要假设一次响应包含全部题目。

清单按规范化相对路径排序；没有公开数据的题目返回空清单，页面隐藏下载按钮。下载接口只接受公开扩展名下的普通文件，拒绝目录、符号链接、绝对路径和路径穿越。

文件传输由 Fastify 完成路径校验并以文件流返回，Nginx 只负责 HTTPS 和反向代理。单文件下载支持断点续传，并返回 `Content-Disposition`、`Accept-Ranges`、`ETag`、`Last-Modified` 和安全的缓存响应头。不要把整个 `roj/` 配置为 Nginx 的静态目录或 alias；题目数据、标准程序和配置文件必须始终经过应用层的公开文件规则检查。

ZIP 是按请求实时生成的动态归档，初版只保证重新请求下载，不保证断点续传或可复用的 `ETag`。ZIP 响应使用 `application/zip` 和附件下载头；需要稳定断点续传时，必须另行设计持久化归档缓存。

ZIP 使用低级别 Deflate 压缩（建议 level 1），以减少 2 vCPU VPS 的压缩 CPU 占用；不使用最高压缩级别。

服务器在生成前检查清单总大小，默认单个 ZIP 不超过 `1 GiB` 原始数据；活动生成时间默认不超过 `15 分钟`。超过大小返回 `413`，生成超时则取消当前任务。两个值都是部署配置，且不影响当前最大约 `170 MiB` 的题目。

ZIP 接口使用统一的 JSON 错误结构：`error` 表示稳定错误码，`message` 是用户可读的中文提示，`retryable` 表示是否允许用户稍后手动重试。状态码约定为：`404`（题目或公开数据不存在）、`413`（超过 ZIP 大小限制）、`429`（队列已满）、`504`（生成超时）、`500`（读取文件或生成归档失败）。失败时前端显示错误，不自动重试；如果能确定失败文件，响应可附带 `failedPath`。

网站不提供注册功能，下载保护使用 Nginx 传递并经过信任配置验证的客户端 IP。单个 IP 同时最多拥有一个 ZIP 活动或排队请求；全局 ZIP 并发和队列限制仍然有效。单文件下载在代理层设置适度的请求和连接限制，避免耗尽月度流量，但不能影响普通的小文件并行下载。服务需要记录下载字节数、耗时、状态、队列结果和累计出口流量。

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
