const {writeFileSync,statSync,mkdirSync,readFileSync,existsSync} = require('fs')
const fs = require("fs")
const glob = require('glob');

exports.mkdirp = function (path) {
    mkdirSync(path,{recursive:true});
}

//问题所在的路径转成对应的题目的id
exports.problem_path_to_id = function (path) {
}

exports.getLatestFileUnixTime = function (dirPath) {
    const files = glob.sync(`${dirPath}/**/*`, { nodir: true });
    let latestTime = 0;

    files.forEach(file => {
        const stats = fs.statSync(file);
        const fileTime = stats.mtime.getTime();
        if (fileTime > latestTime) {
            latestTime = fileTime;
        }
    });

    return latestTime;
}
