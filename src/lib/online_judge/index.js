// 输入数据: html raw string
// 得到的数据:
//      content.md
//          luogu能得到原 markdown
//      link: []
//          原地址
//          vjudge 地址
//      memory
//      time
//      tags
//      

const {join,resolve,extname} = require('path')

const ojs = [
    require("./roj.js"),
    require("./luogu.js"),
    require("./noi.openjudge.cn.js"),
    require("./leetcodecn.js"),
    require("./vjudge.js"),
]


//渲染每一个oj,并得到info
exports.render_all_and_render_info = function() {

}

//根据题目的path
// 例如:roj/1000, luogu/1014,hdu/1014..
// 得到这个题目的相应信息
exports.get_info_by_problem_path = function(path) {
    for( let oj of ojs) {
        if( oj.match(path)) {
            return oj.one_info(path)
        }
    }
    throw 'not match problem by this path : ' + path
}

function name(params) {
    
}
