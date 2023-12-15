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



module.exports =  [
    // {
    //     name:'luogu',
    //     path:__dir('other_oj/luogu'),
    //     output:__dir('dist/luogu'),
    //     collection_name:'luogu',
    //     Class: require("./luogu.js")
    // }
    require("./luogu.js"),
]
