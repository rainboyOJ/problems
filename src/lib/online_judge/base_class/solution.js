//solution 扫描

const {join,resolve,isAbsolute,extname,basename,relative} = require('path')
const {writeFileSync,readdirSync,statSync,readFileSync,existsSync} = require("fs")
const moment = require('moment')
const pather = require("./pather.js")
const {globSync}= require('glob')
const GrayMater = require('gray-matter')
const get_double_link_info = require("./get_double_link_info.js")

class solution {

    constructor(_path_) {
        this._default_name = 'solutions'
        this._path = join(_path_,this._default_name)
    }

    //得到文件的
    file(filename){
        // console.log(join(this._path,filename))
        // console.log(__filename,'20',this._path)
        return pather.relative( join(this._path,filename) )
    }

    //绝对路径
    absolute_file(filename){
        return join(this._path,filename);
    }

    //得到信息
    info() {
        //读取所有的md文件
        let solution_names = globSync('*.md',{
            cwd:this._path
        })
        // console.log(this._path)
        // console.log(solution_names)
        let infos = []

        //得到每个solution的信息
        for(let filename of solution_names) {
            let file_path = join(this._path,filename)
            let raw_md = readFileSync(file_path,{encoding:'utf-8'})
            let grayed = GrayMater(raw_md)
            let info = {
                'author' :'未知',
                title:filename.split('.')[0],
                update: moment(statSync(file_path).mtime).format('YYYY-MM-DD hh:mm'),
                top:false
            }
            let double_link_info = get_double_link_info(raw_md);
            // console.log('double_link_info',double_link_info)
            info = {
                ...info,
                file:this.file(filename),
                ...double_link_info
            }

            if(!grayed.isEmpty)
            info = {
                ...info,
                ...grayed.data
            }

            info.unixstamp = moment(info.update).unix()
            infos.push(info)
        }
        return infos
    }
}

module.exports = solution
