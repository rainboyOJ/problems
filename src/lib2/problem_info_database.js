//得到题目的数据
/*
 * 设计:
 * {
 *  _id: 1000,
 *  title: 'a+b问题'
 *  year: 2013
 *  tags: [ '入门' ],
 *  level: 1,
 *  time:1000,
 *  memory:128
 *  content_ext:'md'// or pdf
 *  data: {
 *      name: 'aplusb',
 *      range:[0,9],
 *      ext:['.in','.out']
 *  }
 * }
 *
 * */
const {join,resolve,extname} = require('path')
const {basename,statSync,readFileSync,readdirSync,existsSync} = require("fs")
// const jsyaml = require('js-yaml')
const fs = require("fs")
const getDataList = require("../../bin/lib/getDataList.js")

const lokijs = require('lokijs')

var db = new lokijs('roj.json')
var problems = db.addCollection('problems')


// console.log("create ok")


//得到题目数据的信息
function get_data_info(path) {
    let {both_list}= getDataList(join(path,'data'))
    return both_list
}

//得到题目的后缀
// 1. md 2 pdf
function get_content_ext(problem_path) {
    if( existsSync( join(problem_path,'content.md')))
        return '.md'
    if( existsSync( join(problem_path,'content.pdf')))
        return '.pdf'
    throw `${problem_path},content.md,content.pdf all not exists!`;
}

//得到题目信息
function get_problem_info(path) {
    // let a = jsyaml.load(readFileSync(join(path,'reference.yml'),{encoding:'utf-8'}),{json:true})
    let a = JSON.parse(readFileSync(join(path,'config.json'),{encoding:'utf-8'}))
    return Object.assign(
        a,
        {  content_ext: get_content_ext(path)},
        { data : get_data_info(path)}
    );
}

async function main() {
    // 1. get All pid
    const problem_dir = resolve(__dirname,'../../problems/')
    let pids = readdirSync(problem_dir)
    for(let pid of pids) {
        let problem_path = join(problem_dir,pid)
        if( statSync(problem_path).isDirectory() )
    {
            try{
                let doc = {
                    // _id:pid,
                    _id:parseInt(pid) ,
                    ...get_problem_info(problem_path)
                }
                // console.log(doc)
                await problems.insert(doc);
                // db.put({_id:'1001'})
                // console.log(doc)
            }
            catch(e) {
                console.log(pid,e)
            }
            // break;
        }
    }
    // 下载dump
    let jsonStr = db.serialize()
    // console.log(jsonStr)
    const out_db_path = join(__dirname,'../src/roj.json')
    console("写入db:" out_db_path)
    fs.writeFileSync(out_db_path,jsonStr,{encoding:'utf8'})

}

main();
