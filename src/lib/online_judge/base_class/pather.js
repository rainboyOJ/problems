//路径 转换的类

const {join,resolve,isAbsolute,extname,basename,relative} = require('path')

const project_dir = join(__dirname,'../../../../')

exports.project_dir = project_dir

//绝对路径,转成相对 project_dir 的路径
exports.relative = function (p) {
    // console.log('---------------------')
    // console.log(__filename)
    // console.log(project_dir,p)
    // console.log('----',relative(project_dir,p))
    return relative(project_dir,p)
}

//把相对地址 转成 绝对地址
exports.absolute = function (p) {
    return join(project_dir,p)
}
