//把所有的题目渲染成html文件
//1. markdown-it-r 库
//2. 读取roj.json - 得到所有的题目
//3. compile problem.ejs
//4. 渲染

// --------- utils

const force_update = process.argv.indexOf('force') != -1;
console.log('force_update',force_update)



const {join} = require('path')
const {writeFileSync,statSync,mkdirSync,readFileSync,existsSync} = require('fs')

const problems_path = join(__dirname,'../../problems/')
function read_by_pid(pid) {
    let path = join(problems_path,pid+'/content.md')
    return readFileSync(path,{encoding:'utf8'})
}

//file1 是否比file2 更新
function file_time_newer(file1,file2) {
    //file1 不存在就认,file1不比file2新
    if( !existsSync(file1)) return false;

    if( !existsSync(file2)) throw `${file2} not exists!`

    let s1_time = statSync(file1).ctime
    let s2_time = statSync(file2).ctime
    return s1_time > s2_time;
}

function mkdirp(path) {
    mkdirSync(path,{recursive:true});
}
// --------- utils end
//
// 0 load ejs and compile it
const ejs = require("ejs")
let problem_ejs = ejs.compile(readFileSync( join(__dirname,'../ejs/problem.ejs'),{encoding:'utf8'} ),
    {
        filename: join(__dirname,'../ejs/problem.ejs')
    });

//1
const MDRender = require('markdown-r')
const {mirrors,real_link} = require('../github_proxy.js')
//2. 读取roj.json - 得到所有的题目

const roj_json = require("../roj.json")

let problems = []
for( let {name,data} of roj_json.collections)
{
    if( name == 'problems') {
        problems = data
        break;
    }
}
console.log('题目数量',problems.length)

const out_dir = join(__dirname,'../../dist/problem/');
mkdirp(out_dir)
for( let p of problems ) {
    // console.log(p._id,p.content_ext)
    try {
        //得到输出目录
        let out_path = join(out_dir,p._id + '.html');

        //原文件目录
        let org_path = join('../../problems/' + p._id,'content' + p.content_ext)

        if( !force_update && file_time_newer(out_path,org_path)  ) {
            continue;
        }

        //渲染条件
        //1,
        if( p.content_ext.toLowerCase() == '.md') //是md文件
        {
            p.content = MDRender(read_by_pid(p._id),{}).content
        }
        //传递数据,进行渲染
        let html = problem_ejs({...p,mirrors,real_link});
        writeFileSync(out_path,html,{encoding:'utf8'})
        console.log('render ok',p._id)
    }
    catch(e) {
        console.log(p)
        console.log(e)
        break;
    }
}





// git raw 加速
// 1. https://gitmirror.com/raw.html
// 1.1 https://hub.gitmirror.com//https://raw.githubusercontent.com
// 2. https://gh.api.99988866.xyz/https://raw.githubusercontent.com
// https://mirror.ghproxy.com/https://raw.githubusercontent.com/rainboyOJ/problems/master/problems/10000/content.pdf
