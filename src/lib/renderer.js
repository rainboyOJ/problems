//渲染器
// 将整个 markdown 渲染成html
//


const force_update = process.argv.indexOf('force') != -1;
console.log('force_update',force_update)

const {mirrors,real_link} = require('./utils/github_proxy.js')

const {join} = require('path')
const {writeFileSync,statSync,mkdirSync,readFileSync,existsSync} = require('fs')
const viewer = require("./viewer.js") //渲染ejs
const lokijs = require("lokijs")
const ojs = require("./online_judge/")
const roj_json = require("../roj.json")
const MDRender = require('markdown-r')


function file_time_newer(file1,file2) {
    //file1 不存在就认,file1不比file2新
    if( !existsSync(file1)) return false;

    if( !existsSync(file2)) throw `${file2} not exists!`

    let s1_time = statSync(file1).ctime
    let s2_time = statSync(file2).ctime
    return s1_time > s2_time;
}


async function main() {
    const db = new lokijs('roj.json')
    db.loadJSONObject(roj_json)

    for( let oj of ojs ) {
        //得到collections的名字
        console.log(oj.name)
        let collections = db.getCollection(oj.name);

        let problems = collections.find({_id: {'$exists':true}})

        for( let p of problems) {

            //渲染条件
            if(p.content_ext.toLowerCase() == '.md') {
                p.content = MDRender( readFileSync(oj.problem_file_path_by_id(p._id),{encoding:'utf8'}) ).content
            }
            //渲染
            viewer('problem',{...p,mirrors,real_link})

            //写入
            //  创建输出目录
            mkdirp(oj.output_dir_by_id(p._id))
            write
        }
    }
}

main()
