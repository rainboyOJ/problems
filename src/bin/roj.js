#!/usr/bin/env node
// roj.js 是本题目库的命令行 使用[tj/commander  命令行参数解析库](https://github.com/tj/commander.js/blob/HEAD/Readme_zh-CN.md)
// usage:
// roj  --render-one <problem-path> 只渲染一个题目,注意不进行更新
//

const { Command } = require('commander');
const program = new Command();

program
  .name('roj')
  .description('roj题库的命令行管理工具')
  .version('0.0.1');

program.command('render-one')
  .description('渲染一个题目')
  .argument('<path>', '渲染的题目路径,例如roj/1000,luogu/1014')
  .action((str, options) => {
        console.log(str,options)
  });

program.parse();
