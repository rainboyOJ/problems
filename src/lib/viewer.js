//ejs 渲染器
// 逻辑很简单,传入 viewName,数据data, 然后返回渲染结果

const ejs = require("ejs")
const {writeFileSync,statSync,mkdirSync,readFileSync,existsSync} = require('fs')
const {resolve,join} = require("path")
const {project_dir } = require("./online_judge/base_class/pather.js")

const viewDir = join(__dirname,'../views/')
var ejs_template = {

}

module.exports = function(viewName,output_path,data,config = {}) {
    if( !ejs_template[viewName] ) {
        let view_path = join(viewDir,`${viewName}.ejs`)
        ejs_template[viewName] = ejs.compile(readFileSync(view_path,{encoding:'utf8'}),
            {
                filename:view_path
            }
        )
    }
    let html = ejs_template[viewName](data,config)
    //写入
    let real_output_path = output_path
    if( isAbsolute(output_path) ) {
        real_output_path = join(project_dir,output_path)
    }
    writeFileSync(real_output_path,html,{encoding:'utf8'})
}
