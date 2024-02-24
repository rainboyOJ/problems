//思路,
//下载整个网站
//1. 扫描http://noi.openjudge.cn/ 标题
//2. 根据第1步,得到二级页面的地址
//3. 扫描,二级页面的上的题目,得到所有题目的uurl
//4. 根据题目的url,得到所有的题目的html content
const pather = './online_judge/base_class/pather.js'
const {execSync} = require("child_process")
const {writeFileSync,readFileSync,readdirSync} = require("fs")
const {join} = require("path")

const {mkdirp} = require("../utils/utils.js")


const cheerio = require("cheerio")

const TurndownService = require('turndown')

const turndownService = new TurndownService({preformattedCode:true})

const base = require("./base.js")
const ejs = require("ejs")
// const url = require("../utils/curl.js")

const cookie =  'PHPSESSID=jp251o6glig7rkm4434vuvn5mh; Hm_lvt_cba6845c6d8176f123f81538e1796b8a=1703292137; Hm_lpvt_cba6845c6d8176f123f81538e1796b8a=1704758163'

var axios = require("axios")
const url = {
    get : function(link) {
        // return axios.request({
        //     url: "http://example.com",
        //     method: "get",
        //     headers:{
        //         Cookie: 
        //     } 
        // }).then...
        return axios.get(link,{headers:{Cookie:cookie}}).then( res => res.data )
    }
}

class NoiOpenJudge extends base {

    static instance = null

    constructor() {
        super('noiopenjudge','other_oj/noiopenjudge','/noiopenjudge')
        // this.id = id
        // this.link = `https://www.luogu.com.cn/problem/${id}`
        return NoiOpenJudge.instance || (NoiOpenJudge.instance = this)
    }

    
    id_path(id) {
        return join(this._path,id.replace('-','/'));
    }

    all_dirs(){
        let all_ids = []
        let dirs = readdirSync(this._path)
        for( let d of dirs) {
            let t = readdirSync(this._path + '/' + d)
            // all_ids.push(d + '-' + t)
            // console.log( t.map(item => d +'-' + item ))
            all_ids = all_ids.concat( t.map(item => d +'/' + item ));
        }
        return all_ids
    }

    //下载所有的题目
    async downloadAll() {
        const web = 'http://noi.openjudge.cn/'
        //step 1
        let mainHtml = await url.get(web)
        let $ = cheerio.load(mainHtml)
        // console.log(html)
        //step 2. 根据第1步,得到二级页面的地址
        let level_2_urls = []
        $('#main > div.main-content > ul > li > h3 > a').each( (idx,ele)=>{
            // console.log()
            let href = $(ele).attr('href').slice(1);
            level_2_urls.push(`${web}${href}`);
        })
        // console.log(level_2_urls)

        /*
        //3. 扫描,二级页面的上的题目,得到所有题目的uurl
        for(let l2url of level_2_urls) {
            // console.log(l2url)
            let l2_html = await url.get(l2url)
            $ = cheerio.load(l2_html)
            let problem_urls  = []
            //可以得知,每个题目的id 都是 /xxx/yyy 这种形式
            $('td.title > a').each( (idx,ele) =>{
                let href = $(ele).attr('href')
                let title = $(ele).text()
                // console.log(href,title)
                problem_urls.push({ href,title})
            })

            for( let {href,title} of problem_urls ) {
                let link = `${web}${href}`
                let phtml = await url.get(link)

                let id = href.slice(1).replace('/','-');

                $ = cheerio.load(phtml)
                let content = $('.problem-content').html()
                // console.log(content)
                //依次转换,dt 转成 h2
                //依次转换,dd 转成 markdown
                $ = cheerio.load('<div>' +content +'</div>')
                let items = $('div').contents()
                let problem = ''
                let pre_item = ''
                for( let item of items ) {
                    let t = $(item)[0].name
                    if( !t) continue
                    let html = $(item).text()
                    // console.log(t,html)
                    if(t == 'dt') {
                        problem += `## ${html}`
                        pre_item = html
                    }
                    else {
                        // problem += turndownService.turndown(html)
                        problem += '\n'
                        if( pre_item[0] == '样') {
                            problem += "```\n"
                            problem += html;
                            problem += "\n```\n"
                        }
                        else 
                            problem += html;
                    }
                    problem += '\n\n'
                }
                // console.log(problem)
                console.log(this.id_path(id))
                

                let _path = this.id_path(id)
                mkdirp(_path)
                //写入文件
                let config = {
                    title,
                    memory:128,
                    time:1000,
                    source : `${web}${href.slice(1)}`
                }
                writeFileSync(join(_path,'content.md'),problem,{encoding:'utf8'})
                writeFileSync(join(_path,'config.json'),JSON.stringify(config,null,4),{encoding:'utf8'})
                // break;
            }
            // break;
        }
        */
        //3. 扫描,二级页面的上的题目,得到所有题目的uurl
        for(let l2url of level_2_urls) {
            // console.log(l2url)
            let l2_html = await url.get(l2url)
            $ = cheerio.load(l2_html)
            let problem_urls  = []
            //可以得知,每个题目的id 都是 /xxx/yyy 这种形式
            $('td.title > a').each( (idx,ele) =>{
                let href = $(ele).attr('href')
                let title = $(ele).text()
                // console.log(href,title)
                problem_urls.push({ href,title})
            })

            for( let {href,title} of problem_urls ) {
                let link = `${web}${href}`
                let phtml = await url.get(link)

                let id = href.slice(1).replace('/','-');

                $ = cheerio.load(phtml)
                // console.log(content)
                //依次转换,dt 转成 h2
                //依次转换,dd 转成 markdown
                let problem = ''
                let pre_item = ''
                //得到 第一个解url,
                // let sol_url = $('table.my-solutions > tbody > tr:nth-child(1) > td.result > a').attr('href')
                let sol_url = $('table.my-solutions > tbody > tr:nth-child(1) > td.result > a').attr('href')
                if( !sol_url) continue;
                // 得到code
                // mkdirp(solutions)
                // table.my-solutions > tbody > tr:nth-child(1) > td.result > a
                // 写入code
                // 写入 rainboy.md
                console.log(this.id_path(id))
                let _path = this.id_path(id) + 'solutions'
                let _code_path = _path + '/rainboy.cpp'
                mkdirp(_path)

                // //得到代码
                // let shtml = await url.get(sol_url)
                // // console.log(shtml)
                // let code = cheerio.load(shtml)('pre').text();
                // console.log(code)
                // writeFileSync(_code_path,code,{encoding:"utf8"})
                let temp = 
`---
title: "rainboy的解析"
date: "2024-01-09 09:47"
update: "2024-01-09 09:47"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 代码

\`\`\`cpp
<%- include("./rainboy.cpp") _%>
\`\`\`
`
                writeFileSync(_path+'/rainboy的解析.md',temp,{encoding:"utf8"})
                // break;
                // console.log(sol_url)
            }
            // break;
        }
    }

}

module.exports = new NoiOpenJudge()
