const pather = './online_judge/base_class/pather.js'
const {execSync} = require("child_process")
const {writeFileSync,readFileSync} = require("fs")
const {join} = require("path")
const base = require("./base.js")
const ejs = require("ejs")
class luogu extends base {

    static instance = null

    constructor() {
        super('luogu','other_oj/luogu','/luogu')
        // this.id = id
        // this.link = `https://www.luogu.com.cn/problem/${id}`
        return luogu.instance || (luogu.instance = this)
    }


    //连接网络 得到题目数据
    http(id) {
        let realId = /^\d/.test(id) ? `P${id}` : id;
        console.log( 'realId',realId )

        // let a = e(`curl https://www.luogu.com.cn/problem/${realId} --cookie "${cookie}"`,{encoding:'utf-8'})
        let a = execSync(`wget -O - https://www.luogu.com.cn/problem/${realId}`,{encoding:'utf-8'})
        let dataReg = /decodeURIComponent\("([\s\S]+?)"\)/
        //console.log(a)
        //console.log(dataReg.test(a))
        //console.log( a.match(dataReg))
        let data_string = a.match(dataReg)[1]
        var data = JSON.parse(decodeURIComponent(data_string))
        //console.log(JSON.stringify(data,null,4))
        //console.log(data.currentData.lastCode)
        return data
    }

    down(id) {
        let data = this.http(id)
        console.log(data)

        let problem = data.currentData.problem
        let template_md_file =  join(__dirname,'./template/luogou.ejs')

        let template_content = readFileSync(template_md_file,{encoding:'utf-8'})

        let md_content = ejs.render(template_content,problem)
        let output_path = this.problem(id).default_file
        writeFileSync(output_path,md_content,{encoding:'utf-8'})
    }

}

module.exports = new luogu()
