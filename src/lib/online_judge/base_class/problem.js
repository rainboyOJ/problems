//题目扫描

const {join,resolve,isAbsolute,extname,basename,relative} = require('path')
const {writeFileSync,readdirSync,statSync,readFileSync,existsSync} = require("fs")
const pather = require("./pather.js")
const { parse:jsonc_parse } = require('jsonc-parser');
const {project_dir} = require("./pather.js")

class Problem {


    // _path 这个路径下的题目
    constructor(_path_,problem_file_name) {
        this._default_name = problem_file_name ||  'content'
        this._exts = ['.md','.pdf','.json']
        this._path = _path_ //题目所在路径的绝对路径
    }


    //返回方个文件夹下的题目文件名
    //可能为content.md, 或 content.pdf
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

    // 提取md文件里 [[[]]]
    // 得到双链的信息
    get_double_link_info() {
        let problem_path = this.file()
        if( extname(problem_path) !== '.md')
            return {}
        let raw_md = readFileSync(join(project_dir ,this.file()),{encoding:'utf-8'});
        const regex = /\[\[\[(.*?)\]\]\]/gm
        const matches = raw_md.match(regex);
        console.log(matches)
    }

    //得到题目信息
    info(){
        // let a = JSON.parse(readFileSync(join(this._path,'config.json'),{encoding:'utf-8'}))
        let a = jsonc_parse(readFileSync(join(this._path,'config.json'),{encoding:'utf-8'}))
        // this.get_double_link_info();
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
