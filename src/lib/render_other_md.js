//渲染其它的md文件
const MDRender = require('markdown-r')
const GrayMater = require('gray-matter')
const viewer = require("./viewer.js") //渲染ejs

const {join,resolve,isAbsolute,extname,basename,relative} = require('path')
const {writeFileSync,readdirSync,statSync,readFileSync,existsSync} = require("fs")
const project_dir = resolve(__dirname,'../../')
const web_output_root = join(project_dir,'dist') // 输出路径的地址 dist/
const __dir = (p) => resolve(project_dir,p)

//比如 about.md


//渲染函数
//1. ejs_compiled : 编译后的ejs 
// md_file_path : md文件的绝对路径
// config 渲染需要的数据
function Render(ejs_compiled,md_file_path,config = {}) {

}

const files = [
    [ 'about.md','about.html']
]

for ( let [file,out_file] of files) {

    file = join(project_dir,file)
    let article = MDRender.render( readFileSync(file,{encoding:'utf8'}) ,{
        ejs : {
            options: {
                filename : file
            }
        }
    } )
    // console.log(article)
    let config = {content: article.content,...article.header}
    // console.log(config)
    let index_path = join(web_output_root,out_file)
    let index_html = viewer('article',index_path,config)
}
