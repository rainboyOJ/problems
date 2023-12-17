//solution 扫描

const {join,resolve,isAbsolute,extname,basename,relative} = require('path')
const {writeFileSync,readdirSync,statSync,readFileSync,existsSync} = require("fs")
const moment = require('moment')
const pather = require("./pather.js")
const {globSync}= require('glob')
const GrayMater = require('gray-matter')

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
            let grayed = GrayMater(readFileSync(file_path,{encoding:'utf-8'}))
            let info = {
                'author' :'未知',
                title:filename.split('.')[0],
                update: moment(statSync(file_path).mtime).format('YYYY-MM-DD hh:mm'),
                top:false
            }
            if(!grayed.isEmpty)
            info = {
                ...info,
                file:this.file(filename),
                ...grayed.data
            }

            info.unixstamp = moment(info.update).unix()
            infos.push(info)
        }
        return infos
    }
}

module.exports = solution
