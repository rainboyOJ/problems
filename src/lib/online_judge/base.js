//题目库的基类

const {join,resolve,isAbsolute,extname,dirname,basename,relative} = require('path')
const {writeFileSync,readdirSync,statSync,readFileSync,existsSync} = require("fs")

const {project_dir,relative:pather_relative,link_to_output_path} = require('./base_class/pather.js')

const {mirrors,real_link} = require('../utils/github_proxy.js')

const problemClass = require("./base_class/problem.js")
const solutionClass = require("./base_class/solution.js")
const dataClass = require("./base_class/data.js")


const renderer = require("./base_class/renderer.js")
const viewer = require('../viewer.js')

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

    get relative() {
        return this._relative_path
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
    dir_to_id(dir_name) {
        return this.pid_prefix +dir_name
    }


    //用于显示的id,不是真正的id
    show_id(pid) {
        return pid.replace(this.pid_prefix,'');
    }

    //根据pid,转成对的路径
    //有些oj可以转,因为pid 就是 所在的文件夹名
    //有些oj不能转,如果不能转,重载这个函数为throw
    id_path(pid) {
        let first_idx = pid.indexOf('-');
        return join(this._path,pid.slice(first_idx))
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

                let Problem = new problemClass(problem_path)
                let problem_info = Problem.info();

                let Data = new dataClass(problem_path)
                let data_info = Data.info();

                let solutions = new solutionClass(problem_path).info()
                // console.log(solutions)

                // 读取数据

                let doc = {
                    _id: pid,
                    sid: this.show_id(pid),
                    oj:this.name,
                    ...problem_info,
                    //输出路径
                    data: data_info,

                    //题目的href
                    link: this.problem_link(pid),
                    //数据的href
                    data_link: this.data_link(pid),
                    //解析的href
                    solution_list_link: this.solution_list_link(pid),

                    solutions : solutions.map( sol => {return { ...sol,link:this.solution_link(sol.file)}} )
                    // solutions : solutions.map( sol => { return {...sol} })
                    // solutions : solutions.map( d => d)
                }
                infos.push(doc)
            }
        }
        return infos
    }

    render(infos) {
        //得到所有的infos
        //然后开始渲染
        for(let info of infos) {
            // problemClass.render(info);
            //渲染器 题目
            let content = renderer(info.file)
            let data = {...info,content, mirrors,real_link}
            viewer('problem',link_to_output_path(info.link),data)

            //渲染data.html
            if(data.data.length)
                viewer('data',link_to_output_path(info.data_link),data)

            //渲染器 solution_list
            if( data.solutions.length)
                viewer('solution_list',link_to_output_path(info.solution_list_link),data)
            //渲染器 solution
            for(let i = 0 ;i< info.solutions.length ;i++){
                data.content = renderer(info.solutions[i].file)
                data.current_solution = i
                viewer('solution',link_to_output_path(info.solutions[i].link),data)
            }
        }
    }

}

module.exports = Base
