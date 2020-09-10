/*  得到对应题目的参数,写入对应的题目
 * */

const yaml = require("js-yaml")
const fs = require("fs")
const pathFn = require("path")

const base = pathFn.join(__dirname,"../problems")

function read(p){
    return fs.readFileSync(p,{encoding:'utf-8'})
}

exports.read = (id)=>{
    let ref = pathFn.join(base,id+'','reference.yml')

    if( !fs.existsSync(ref)){
        throw(`${ref} 不存在!`)
    }

    let content = read(ref)
    return yaml.load(content)
}


exports.dump = (obj,id)=>{
    let config = yaml.dump(obj)
    let ref = pathFn.join(base,id+'','reference.yml')
    //console.log(ref)
    //fs.writeFileSync(ref,config,{encoding:'utf-8'})
}
