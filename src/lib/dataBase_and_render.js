//数据库的创建
//每一个OJ,创建一个collection
//[创建]->每一个文件夹,都是一个id
//[扫描]->创建database
//[读取database] -> 渲染相应网页

const {join,resolve,extname} = require('path')
const fs = require("fs")
const {basename,statSync,readFileSync,readdirSync,existsSync} = require("fs")
const getDataList = require("./utils/getDataList.js")
const lokijs = require('lokijs')

//创建数据库
var db = new lokijs('roj.json')
const ojs = require("./online_judge/")

async function main() {

    for( let oj of ojs) {

        // 得到信息
        let infos = oj.all_info();
        //创建collection
        let collection = db.addCollection(oj.name)
        //插入
        collection.insert(infos)
        for(let info of infos) {
            console.log('info',info)
            oj.render(info._id,info) //渲染数据
        }
    }

    //写入数据
    let jsonStr = db.serialize()
    // console.log(jsonStr)
    const out_db_path = join(__dirname,'../roj.json')
    console.log(out_db_path)
    console.log("写入db:", out_db_path)
    fs.writeFileSync(out_db_path,jsonStr,{encoding:'utf8'})
}

main()
