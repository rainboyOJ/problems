#!/usr/bin/env node
// roj.js 是本题目库的命令行 使用[tj/commander  命令行参数解析库](https://github.com/tj/commander.js/blob/HEAD/Readme_zh-CN.md)
// usage:
// roj  --render-one <problem-path> 只渲染一个题目,注意不进行更新
//

const glob = require('glob');
const { Command } = require('commander');
const program = new Command();
const database = require("../lib/database/index.js")
const fs = require("fs")
const {join} = require("path")


const {get_info_by_problem_path,render,get_all_raw_infos,deal_pre_attr} =  require("../lib/online_judge/index.js")
const {absolute,link_to_output_path} = require("../lib/online_judge/base_class/pather.js")

const {getLatestFileUnixTime} = require("../lib/utils/utils.js")

program
  .name('roj')
  .description('roj题库的命令行管理工具')
  .version('0.0.1');

program.command('renderAll')
    .description('渲染所有的题目')
    .action((path, options) => {

        // 1. 加载数据库
        let db = new database()
        db.loadDatabase();

        // 2. 一条一条渲染
        let docs = db.getAllProblems()
        for( let doc of docs)
        {
            // console.log(doc.path)
            // break;
            // 这里不好TODO,应该在render 加入force参加来决定是不是渲染
            let ab_path = join(link_to_output_path(doc.link),'..')
            if(
                !fs.existsSync(ab_path) // 不存在
                || 
                getLatestFileUnixTime(ab_path) < doc.last_update
            )
            {
                console.log(doc.path)
                render([doc])
            }
        }
    })

//更新一条信息
function update_oneinfo_by_time(db,info,force = false) {

    if( force)  //强制
        db.reAddProblem(info)
    else {
        //1. 是否比较新
        let old_info = db.getProblemById(info._id)
        if( old_info.last_update < info.last_update)
            db.reAddProblem(info)
    }
}

program.command('db')
    .argument('<argument>',"update,find")
    .argument('[id]',"id")
    .description('渲染所有的题目')
    .option('--force','强制更新',false)
    .action((argument,id,options) => {
        // console.log(argument,id,options)
        if( argument.toLowerCase() == 'update')
        {
            let db = new database()
            if( !options.force ) {
                db.loadDatabase();
            }

            //1. 得到所有的信息
            let all_raw_infos = get_all_raw_infos()
            //2. 处理信息
            all_raw_infos.map((item) => {
                deal_pre_attr(item)
                update_oneinfo_by_time(db,item,options.force)
                // console.log(all_raw_infos[0])
            })

            db.saveJson();
            db.saveDatabase('保存数据库成功!')
        }
        else if(argument.toLowerCase() === 'find')
        {
            if( !id)  {
                console.log('need [id] : npx roj db find roj-1000')
            }
            let db = new database()
            db.loadDatabase();
            console.log(db.getProblemById(id))
        }
    })


program.command('render-one')
  .description('渲染一个题目')
    //一个options的位置参数
  .argument('[path]', '渲染的题目路径,例如roj/1000,luogu/1014')
  .action((path, options) => {
        if( !path) {
            path = process.cwd()
        }
        let one_problem_info = get_info_by_problem_path(path)
        deal_pre_attr(one_problem_info)
        render([one_problem_info])
        // console.log(path,options)
        let db = new database()
        db.loadDatabase()

        // console.log('before',db.getProblemById(one_problem_info._id))
        // db.reAddProblem(one_problem_info);
        update_oneinfo_by_time(db,one_problem_info,true);
        // console.log('after',db.getProblemById(one_problem_info._id))
        // console.log('after',db.getProblemById(one_problem_info._id).solutions[0])
        // console.log('after-- solutions find',db.solutions_bidir_find('rbook','01_seq'))
        console.log('after info: \n',one_problem_info)

        db.saveJson();
        db.saveDatabase('保存数据库成功!')
  });

program.parse();
