//渲染 传入的md文件为html
const MDRender = require("./markdown-it.js")
const {mirrors,real_link} = require('../../utils/github_proxy.js')
const {extname} =  require("path")
const {writeFileSync,statSync,mkdirSync,readFileSync,existsSync} = require('fs')
const pather  = require("./pather.js")

//加载使用数据库
const rbookDB = require("../../../../rbook/src/lib/database/index.js")
const _problemDB = require("../../database/index.js")

rbookDB.loadDb();

const problemDB = new _problemDB();
problemDB.loadDatabase();

function file_time_newer(file1,file2) {
    //file1 不存在就认,file1不比file2新
    if( !existsSync(file1)) return false;

    if( !existsSync(file2)) throw `${file2} not exists!`

    let s1_time = statSync(file1).ctime
    let s2_time = statSync(file2).ctime
    return s1_time > s2_time;
}

module.exports = function (md_path ,config = {}) {

    const force_update = config.force_update || false

    //TODO check time

    let ejs_config = {}
    if( config && config.ejs )
        ejs_config = { ...config.ejs }

    ejs_config.data = ejs_config.data || {}
    ejs_config.options= ejs_config.options || {}

    let filename = pather.absolute(md_path)
    ejs_config.options.filename = ejs_config.options.filename || filename
    // console.log(ejs_config)

    let content = '';
    //渲染条件
    if(extname(md_path).toLowerCase() == '.md') {
        content = MDRender.render( readFileSync( filename  ,{encoding:'utf8'}) , 
            { //MDRender config
                ejs:ejs_config,
                //TODO:还可以传入本身的INFO
                mdit : {
                    problemDB,
                    rbookDB
                }
            }
        ).content
    }
    return content
}
