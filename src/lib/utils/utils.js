const {writeFileSync,statSync,mkdirSync,readFileSync,existsSync} = require('fs')

exports.mkdirp = function (path) {
    mkdirSync(path,{recursive:true});
}

//问题所在的路径转成对应的题目的id
exports.problem_path_to_id = function (path) {
}
