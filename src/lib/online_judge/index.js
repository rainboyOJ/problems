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

const {join,resolve,extname,isAbsolute} = require('path')
const {relative: project_dir_relative,absolute:project_dir_absolute} = require("./base_class/pather.js")

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
exports.get_info_by_problem_path = function get_info_by_problem_path(path) {
    if( isAbsolute(path) ) path = project_dir_relative(path)
    return get_match_oj(path).one_info(path);
}

//通过path 得到对应的id
function get_match_oj(path) {
    if( isAbsolute(path) ) path = project_dir_relative(path)

    // console.log(path)
    for( let oj of ojs) {
        if( oj.match(path)) {
            return oj
        }
    }
    throw 'not match problem by this path : ' + path
}

function dir_to_id(path) {
    if( isAbsolute(path) ) path = project_dir_relative(path)
    return get_match_oj(path).dir_to_id(path)
}

//通过oj的那么得到oj object
function get_oj_by_name(name) {
    for( let oj of ojs) {
        if( oj.name === name ) {
            return oj
        }
    }
    throw 'not match problem by this path : ' + path
}

// 渲染单个的 infos,可以单个的渲染,也可以一次渲染多个
// 但必须保证所有的info是同一个oj的
// infos type is Array
function render(infos,env = {}) {
    let oj = get_oj_by_name(infos[0].oj)
    oj.render(infos,env)
}


exports.render = render


exports.get_all_raw_infos = function () {
    let all_infos = []
    for( let oj of ojs) {
        all_infos = all_infos.concat(oj.info());
    }
    return all_infos;
}


// 处理problem info 的 pre 信息
exports.deal_pre_attr = function(info) {

    function trans_to_id(str) {
        //1. 得到这个题目的绝对地址
        if( str.startsWith('..')) //这种情况是地址
        {
            const dir = project_dir_absolute(info.path)
            const pre_problem_dir = join(dir,str)
            // console.log(str,dir,pre_problem_dir)
            str = dir_to_id(pre_problem_dir)
        }
        // console.log('pre id',str)
        return str; //本身就是id
    }


    if( info.pre) {

        if( typeof info.pre === 'string')
        {
            // return [trans_to_id(info.pre)]
            info.pre = [trans_to_id(info.pre)]
        }
        else if( Array.isArray(info.pre) )
        {
            let ret = []
            for( let str of info.pre) {
                ret.push(trans_to_id(str))
            }
            // return ret
            info.pre = ret
        }
    }
}
