const pather = './online_judge/base_class/pather.js'
const {execSync} = require("child_process")
const {writeFileSync,readFileSync,readdirSync} = require("fs")
const {join} = require("path")
const base = require("./base.js")
const ejs = require("ejs")
const cheerio = require("cheerio")
class vjudge extends base {

    static instance = null

    constructor() {
        super('vjudge','other_oj/vjudge','/vjudge')
        // this.id = id
        // this.link = `https://www.luogu.com.cn/problem/${id}`
        return vjudge.instance || (vjudge.instance = this)
    }

    //返回此oj默认存题目文件的名字,使用 problem,content
    get problem_file_name() {
        return 'config'
    }

    //默认根据oj目录下文件夹名字来
    all_dirs() {
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

    //用于显示的id,不是真正的id
    show_id(pid) {
        return super.show_id(pid).replace('/','-');
    }

    //根据id来渲染ejs
    render_problem(info) {
        // return renderer(info.file)
    let content  = `<iframe id = "frame-description" src="#"
                        width="100%"
                        height="2048px"
                        frameborder="0"
                        scrolling="no">
        ></iframe>
<script>
vjudge_get_problem("${ info.sid.replace('/','-').toUpperCase()}")
</script>
`
            console.log(content)
        return content

    }

    //连接网络 得到题目数据
    http(id) {
        let a = execSync(`wget -O - https://vjudge.net.cn/problem/${id}`,{encoding:'utf-8'})
        let $ = cheerio.load(a)
        let title = $('#prob-title').find('h2').text().trim()
        console.log(title)
        // console.log(a)
        return {title}
    }

    down(id) {
        let pid = id.replace('/','-').toUpperCase();
        let data = this.http(pid)
        //创建config.json
        let config = `{
    "title": "${data.title}",
    "tags": [
    ],
    "memory": 128,
    "time": 1000,
    "source": "https://vjudge.net.cn/problem/${pid}"
}`
        writeFileSync(this.problem(id).config,config,{encoding:'utf-8'})
    }

}

module.exports = new vjudge()
