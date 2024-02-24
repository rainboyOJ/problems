const pather = './online_judge/base_class/pather.js'
const {execSync} = require("child_process")
const {writeFileSync,readFileSync} = require("fs")
const {join} = require("path")
const base = require("./base.js")
const ejs = require("ejs")

const axios = require("axios")
const TurndownService = require('turndown')

const turndownService = new TurndownService({
    preformattedCode:true,
    emDelimiter: '*',
    bulletListMarker: '-'
})

// turndownService.addRule('strikethrough', {
//     filter: ['pre'],
//     replacement: (content, node) => '\n```txt\n' + node.innerText.trim() + '\n```\n'
// });
turndownService.addRule('strikethrough', {
    filter: ['sup'],
    replacement: content => '^' + content
});


function download_leet_codecn_probem(string_id) {

    return axios({
        url:'https://leetcode.cn/graphql',
        method:'post',
        data : {
            "query":"\n    query questionTranslations($titleSlug: String!) {\n  question(titleSlug: $titleSlug) {\n    translatedTitle\n    translatedContent\n  }\n}",
            "variables":{"titleSlug":string_id},
            "operationName":"questionTranslations"
        }
    }).then( ({data})=> {
            // return data
            let md = turndownService.turndown(data.data.question.translatedContent)
            let title = data.data.question.translatedTitle
            return {md,title}
    })
}


class leetcodecn extends base {

    static instance = null

    constructor() {
        super('leetcodecn','other_oj/leetcodecn','/leetcodecn')
        return leetcodecn.instance || (leetcodecn.instance = this)
    }

    show_id(pid) {
        let old_sid = super.show_id(pid)
        return parseInt(old_sid.split('.')[0])+'';
    }


    //连接网络 得到题目数据
    http(string_id) {
        return download_leet_codecn_probem(string_id)
    }

    async down(id) {
        let string_id = id
        if(id.indexOf('.') !=-1)
            string_id = id.split('.')[1];
            
        let data=  await this.http(string_id)
        console.log(data)

        let template_md_file =  join(__dirname,'./template/leetcodecn.ejs')

        let template_content = readFileSync(template_md_file,{encoding:'utf-8'})

        let md_content = ejs.render(template_content,data)
        let output_path = this.problem(id).default_file
        writeFileSync(output_path,md_content,{encoding:'utf-8'})

        //创建config.json
        let config = `{
    "title": "${data.title}",
    "tags": [
    ],
    "memory": 128,
    "time": 1000,
    "source": "https://www.leetcode.cn/problems/${string_id}"
}`
        writeFileSync(this.problem(id).config,config,{encoding:'utf-8'})
    }

}

module.exports = new leetcodecn()
