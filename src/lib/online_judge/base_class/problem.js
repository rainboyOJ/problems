//题目扫描

const {join,resolve,isAbsolute,extname,basename,relative} = require('path')
const {writeFileSync,readdirSync,statSync,readFileSync,existsSync} = require("fs")
const pather = require("./pather.js")

class Problem {


    // _path 这个路径下的题目
    constructor(_path_) {
        this._default_name = 'content'
        this._exts = ['.md','.pdf']
        this._path = _path_ //题目所在路径的绝对路径
    }


    file() {
        for( let ext of this._exts)
        {
            let file = join(this._path,this._default_name + ext)
            if( existsSync( file ) )
                return pather.relative(file)
        }
        throw `${this._path}, problem not exists!`;
    }

    //得到默认的路径的绝对地址
    get default_file() {
        return join(this._path,this._default_name+this._exts[0])
    }

    // 得到配置文件的绝对路径
    get config(){
        return join(this._path,'config.json')
    }

    //搜索,得到题目信息
    info(){
        let a = JSON.parse(readFileSync(join(this._path,'config.json'),{encoding:'utf-8'}))
        return {
            ...a,
            file:this.file()
        }
    }

    //渲染器
    //根据info.link 来渲染输出到对应的路径
    render(info) {

    }
}

module.exports = Problem
