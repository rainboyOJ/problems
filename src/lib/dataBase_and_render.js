//数据库的创建
//每一个OJ,创建一个collection
//[创建]->每一个文件夹,都是一个id
//[扫描]->创建database
//[读取database] -> 渲染相应网页

const Path = require("path")
const {project_dir,relative:pather_relative,link_to_output_path} = require('./online_judge/base_class/pather.js')
const {join} = require("path")
const fs = require("fs")

// const lokijs = require('lokijs')
//创建数据库
// var db = new lokijs('roj.json')

const problemDB = require("./database/")
var db = new problemDB();

const ojs = [
    require("./online_judge/roj.js"),
    require("./online_judge/luogu.js"),
    require("./online_judge/noi.openjudge.cn.js"),
    require("./online_judge/leetcodecn.js"),
    require("./online_judge/vjudge.js"),
]

//参数,渲染哪个oj
let need_render_oj = process.argv[2]

async function main() {

    //创建collection
    // let collection = db.addCollection('problem')
    // let oj_names = []
    // let collection_oj_name = db.addCollection('oj_name')
    for( let oj of ojs) {
        // oj_names.push(oj.name)

        // 得到信息
        let infos = oj.info();

        //对所的信息进行处理
        for(let info of infos) {
            if( info.pre) {
                console.log(info)
                //遍历前面的地址
                for(let i = 0 ;i < info.pre.length ;i++) {
                    let pre_path  = info.pre[i]
                    // 把相对地址转成对于problem项目的地址
                    let problem_path =  pather_relative(Path.resolve(info.path,pre_path))
                    // console.log(problem_path)
                    for( let _oj of ojs) {
                        if(  _oj.dirInThisOj(problem_path) )
                            info.pre[i] = _oj.dir_to_id(problem_path)
                    }
                }
                console.log(info)
            }
        }

        //插入
        // await collection_oj_name.insert({name:oj.name})
        // await collection.insert(infos)
        db.addProblem(infos)

        oj.render(infos)
    }

    //写入数据;
    // let jsonStr = db.serialize()
    // const out_db_path = join(__dirname,'../roj.json')
    // const out_oj_name_path = join(__dirname,'../oj_name.json')
    // console.log("写入db:", out_db_path)
    // fs.writeFileSync(out_db_path,jsonStr,{encoding:'utf8'})
    // fs.writeFileSync(out_oj_name_path,JSON.stringify(oj_names),{encoding:'utf8'})
    db.saveDatabase()
    db.saveJson()
}

if( need_render_oj )
{
    console.log(need_render_oj,'开始渲染')
    for( let oj of ojs) {
        if( oj.name == need_render_oj)  {
            let infos = oj.info();
            oj.render(infos)
            console.log(need_render_oj,'渲染完毕')
        }
    }
}
else main() // render_all

