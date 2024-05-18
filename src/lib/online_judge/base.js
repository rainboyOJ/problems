//题目库的基类

const {join,resolve,isAbsolute,extname,dirname,basename,relative} = require('path')
const {writeFileSync,readdirSync,statSync,readFileSync,existsSync} = require("fs")

const {project_dir,relative:pather_relative,link_to_output_path} = require('./base_class/pather.js')

const {mirrors,real_link} = require('../utils/github_proxy.js')

const {getLatestFileUnixTime} = require("../utils/utils.js")

const problemClass = require("./base_class/problem.js")
const solutionClass = require("./base_class/solution.js")
const dataClass = require("./base_class/data.js")

const Glob = require("glob")
const fse = require("fs-extra")


const renderer = require("./base_class/renderer.js")
const viewer = require('../viewer.js')

const config_ejs = {

    data : {
        onedrive_video: function(url) {
            return `<video width="100%" height="360" controls> <source src="https://d.roj.ac.cn/d/oneDrive/${url}" type="video/mp4"> Your browser does not support the video tag. </video>`
        }
    }

}

class Base {
    //name oj名字
    //_path oj所有的路径(相对于problems 项目)
    //output_path 输出到dist文件夹下的名字
    constructor(name,_path,output_path) {
        this._name = name
        this._relative_path = _path // 基础的相对地址
        this._path = join(project_dir,_path)//基础路径
        this._output_path = output_path
    }

    get name() {
        return this._name
    }

    //oj相对于 project_dir 所在的位置
    get relative() {
        return this._relative_path
    }

    //路径path : roj/abc 是否在当前路径下面
    //路径path必须是一个相对于project_dir的地址
    dirInThisOj(path){
        // path 例如 : other_oj/luogu/1014
        // this.relative other_oj/luogu
        // tmp -> 1014
        let tmp = relative(this.relative,path)
        // console.log(this.relative,path,tmp)
        return tmp && !tmp.startsWith('..') && !isAbsolute(tmp);
        // return true;
    }

    /*
     * 是对dirInThisOj的补充
     * dirInThisOj的path参数必须是 相对于project_dir 的相对地址
     * 有的时候这个地址可能比较长: 使用vjudge/hdu/1014
     * 但我只想传递 hdu/1014 怎么办呢?
     * 只要 检查 this._relative_path + hud/1014 这文件夹是否在project_dir里存在就行了
     * */
    match(path) {
        //进行交替的比对
        let oj_base_path_split = this.relative.split('/')
        let path_split = path.split('/')
        let common_cnt = 0;
        let _end_cnt = Math.min(oj_base_path_split.length , path_split.length)
        for( let i =  1;i<= _end_cnt;i++) {
            if( oj_base_path_split.slice(-i).join('/')
                ==
                path_split.slice(0,i).join('/')
            )
            common_cnt = i;
        }
        // console.log(common_cnt)
        let _findal_path = join(this.relative, path_split.slice( -(path_split.length - common_cnt)).join('/')) ;
        // console.log("_findal_path",_findal_path)
        let final_path = join(project_dir,_findal_path)
        // console.log(final_path)
        return existsSync(final_path)
    }

    //返回此oj默认存题目文件的名字,使用 problem,content
    get problem_file_name() {
        return 'content'
    }

    //默认根据oj目录下文件夹名字来
    all_dirs() {
        let dirs = readdirSync(this._path)
        return dirs
    }

    get pid_prefix(){
        return this.name+'-';
    }

    //把dir文件名转成id
    // vjudge/poj/1995
    dir_to_id(dir_name) {
        let _id = this.pid_prefix +dir_name
        if( dir_name.startsWith(this.relative)){
            _id = this.pid_prefix + relative(this.relative,dir_name)
        }
        return _id.replace(/\//g,'-');
    }

    //用于显示的id,不是真正的id
    show_id(pid) {
        return pid.replace(this.pid_prefix,'');
    }

    //根据pid,转成相对的路径,相对problems项目的路径
    //有些oj可以转,因为pid 就是 所在的文件夹名
    //有些oj不能转,如果不能转,重载这个函数为throw
    id_path(pid) {
        let first_idx = pid.indexOf('-');
        return join(this._relative_path,pid.slice(first_idx+1).replace(/-/g,'/'))
    }

    //根据文件的名字,得到绝对路径
    dir_to_path(dir) {
        return join(this._path,dir)
    }

    link_remove_first(link){
        return '/' + link.split('/').slice(1).join('/')
    }

    //文件 相对本题目库的 相对地址
    relative_problem_base_path(some_path) {
        // console.log('-->',some_path)
        // console.log('-->',this._relative_path)
        // console.log('--->', relative(this._relative_path,some_path) )
        return relative(this._relative_path,some_path)
    }

    //根据题目的pid的,href 后缀
    //比如这个题目的id是1000
    //那么它的link的后缀 就是 1000/
    link_subffix(pid) {
        // return this.relative_problem_base_path( dirname(_file_) ),
        // return pid.replace(this.pid_prefix,'');
        return this.show_id(pid)
    }

    //输入一个题目的文件地址,返回题目对应的在网站上的link
    problem_link(pid) {
        //default
        let link = join(this._output_path,
                this.link_subffix(pid),
            'index.html')
        return link
    }

    //显示数据列表下载的地址
    data_link(pid) {
        let link = join(this._output_path,
                this.link_subffix(pid),
            'data.html')
        return link
    }

    //
    solution_list_link(pid) {
        return join(this._output_path,
            this.link_subffix(pid),
            'solutions/index.html')
    }

    solution_link(_file_){
        // console.log(__filename,_file_)
        // console.log(this._output_path)
        return join(this._output_path,
            this.relative_problem_base_path(_file_) ).replace('.md','.html');
    }

    //-- 用于创建题目的相关信息
    problem(dir) {
        return new problemClass(this.dir_to_path(dir))
    }
    //-- 用于创建题目的相关信息 end

    //得到一个题目的info
    //dir 相对于 这个题目_relative的dir
    one_info(dir) {

        if( dir.startsWith(this.relative))
            dir = relative(this.relative,dir)

        let pid = this.dir_to_id(dir)
        let problem_path = this.dir_to_path(dir)
        if( !existsSync(problem_path) ) {
            throw `${problem_path} not exists!`
            return {}
        }

        //不是文件夹
        if( !statSync(problem_path).isDirectory() ) {
            throw `${problem_path} is not directory`
            return {}
        }

        let Problem = new problemClass(problem_path,this.problem_file_name)
        let problem_info = Problem.info();

        let Data = new dataClass(problem_path)
        let data_info = Data.info();

        let solutions = new solutionClass(problem_path).info()
        // console.log(solutions)
        let lastUnixTime = getLatestFileUnixTime(problem_path)

        // 读取数据

        let doc = {
            _id: pid,
            sid: this.show_id(pid),
            oj:this.name,
            ...problem_info,
            path: this.id_path(pid),
            //输出路径
            data: data_info,

            //题目的href
            link: this.problem_link(pid),
            //数据的href
            data_link: this.data_link(pid),
            //解析的href
            solution_list_link: this.solution_list_link(pid),

            //最后的更新时间
            last_updte: lastUnixTime,

            solutions : solutions.map( sol => {return { ...sol,link:this.solution_link(sol.file)}} )
            // solutions : solutions.map( sol => { return {...sol} })
            // solutions : solutions.map( d => d)
        }
        return doc
    }

    //返回全部题目的信息
    info() {
        let all_dir = this.all_dirs()
        // console.log('dirs',dirs)
        let infos= []
        for(let dir of all_dir)
        {
            let pid = this.dir_to_id(dir)
            let problem_path = this.dir_to_path(dir)
            if( statSync(problem_path).isDirectory() ) //是文件夹
            {

                try {
                    let doc = this.one_info(dir)
                    infos.push(doc)
                }
                catch(e) {
                    console.error(e)
                    console.error(problem_path)
                    process.exit(1)
                }
            }
        }
        return infos
    }

    //渲染给定绝对路径的 md file 文件
    render_problem(info) {
        let ext = extname(info.file)
        if(  ext == '.md' )
            return renderer(info.file,{ejs : config_ejs})
        else if( ext == '.pdf')
        return `<script>
            const pdfs = [
                "https://mirror.ghproxy.com/https://raw.githubusercontent.com/rainboyOJ/problems/master/problems/<%=_id%>/content.pdf",
            ]
            </script>
            <div id="pdfjs">
                <iframe width="100%" height="100%"
                    src="/pdfJs/generic/web/viewer.html?file=https://mirror.ghproxy.com/https://raw.githubusercontent.com/rainboyOJ/problems/master/problems/<%=_id%>/content.pdf">
                </iframe>
            </div>
`
    }

    render(infos) {
        //得到所有的infos
        //然后开始渲染
        for(let info of infos) {
            // problemClass.render(info);
            //渲染器 题目
            let content = this.render_problem(info)
            let data = {...info,content, mirrors,real_link}
            // For debug
            // console.log(data)
            viewer('problem',link_to_output_path(info.link),data)

            //渲染data.html
            if(data.data.length)
                viewer('data',link_to_output_path(info.data_link),data)

            //渲染器 solution_list
            if( data.solutions.length)
                viewer('solution_list',link_to_output_path(info.solution_list_link),data)
            //渲染器 solution
            for(let i = 0 ;i< info.solutions.length ;i++){
                // console.log(info.solutions[i])
                data.content = renderer(info.solutions[i].file,{ejs : config_ejs})
                data.current_solution = i
                viewer('solution',link_to_output_path(info.solutions[i].link),data)
                //把solutions 目录下的所有的图片文件 png,svg,jpg,jpeg,全部复制到对应的输出文件夹下面
                if( i == 0) {
                    let out_path = dirname(link_to_output_path(info.solutions[i].link))
                    let org_path = dirname(info.solutions[i].file)

                    //得到所有的图片文件
                    let imgs = Glob.globSync("**/*.{png,jpg,jpeg,svg}",{cwd : org_path })
                    
                    function move_to_dist(src) {
                        fse.copySync(join(org_path,src),join(out_path,src))
                    }
                    for(let img of imgs) move_to_dist(img);
                }
            }

        }
    }

}

module.exports = Base
