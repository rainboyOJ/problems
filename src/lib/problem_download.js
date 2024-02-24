//执行yarn download 会自动下载题目

const {relative} = require('path')
const pather = require("./online_judge/base_class/pather.js")
const ojs =
[
    require("./online_judge/luogu.js"),
    require("./online_judge/leetcodecn.js")
]

// 得到执行yarn down 的命令的cwd
let cwd = process.argv[2]
// 得到执行yarn down 的命令的相对cwd
let r_cwd = pather.relative(cwd)

//通过路径来检查是哪个oj
function choose_oj(cwd) {
    for( let oj of ojs) {
        console.log(oj.relative,cwd)
        if( cwd.startsWith(oj.relative) ){
            return oj
        }
    }
    return null
}

const oj = choose_oj(r_cwd)
if( !oj) {
    console.log('没有找到对应的oj')
    process.exit(1)
}
console.log('选中oj:',oj.name)
let id = relative(oj.relative,r_cwd)
console.log('oj id:',id)
console.log('开始下载 对应的题目')
oj.down(id)


