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

开发时可以单独运行 `npm run build`，服务端会读取 `public/assets` 中的构建结果。生产部署前请先构建一次静态资源。

## 内容边界

服务端不会把 `roj/` 注册为静态目录，只公开 Markdown 题面、PDF 题面和题面实际引用的图片。测试数据、标准程序、题解和其他附件不会通过页面路由提供。

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
