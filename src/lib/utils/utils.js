const {writeFileSync,statSync,mkdirSync,readFileSync,existsSync} = require('fs')

exports.mkdirp = function (path) {
    mkdirSync(path,{recursive:true});
}
