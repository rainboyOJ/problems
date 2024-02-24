//数据库的创建
//每一个OJ,创建一个collection
//[创建]->每一个文件夹,都是一个id
//[扫描]->创建database
//[读取database] -> 渲染相应网页

const {join} = require("path")
const fs = require("fs")

const lokijs = require('lokijs')
//创建数据库
var db = new lokijs('roj.json')

const ojs = [
    require("./online_judge/roj.js"),
    require("./online_judge/luogu.js"),
    require("./online_judge/noi.openjudge.cn.js"),
    require("./online_judge/leetcodecn.js")
]

async function main() {

    //创建collection
    let collection = db.addCollection('problem')
    let oj_names = []
    // let collection_oj_name = db.addCollection('oj_name')
    for( let oj of ojs) {
        oj_names.push(oj.name)

        // 得到信息
        let infos = oj.info();
        //插入
        // await collection_oj_name.insert({name:oj.name})
        await collection.insert(infos)

        oj.render(infos)
    }

    //写入数据
    let jsonStr = db.serialize()
    const out_db_path = join(__dirname,'../roj.json')
    const out_oj_name_path = join(__dirname,'../oj_name.json')
    console.log("写入db:", out_db_path)
    fs.writeFileSync(out_db_path,jsonStr,{encoding:'utf8'})
    fs.writeFileSync(out_oj_name_path,JSON.stringify(oj_names),{encoding:'utf8'})
}

main()

