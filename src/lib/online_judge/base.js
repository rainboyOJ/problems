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
    constructor(name,_path,output_path) {
        this._name = name
        this._relative_path = _path // 基础的相对地址
        this._path = join(project_dir,_path)//基础路径
        this._output_path = output_path
    }

    get name() {
        return this._name
    }

    id_path(id) {
        return join(this._path,id+'')
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

    //输入一个题目的文件地址,返回
    problem_link(_file_) {
        //default
        let link = join(this._output_path,
            this.relative_problem_base_path( dirname(_file_) ),
            'index.html')
        return link
    }

    //
    solution_list_link(problem_path) {
        return join(this._output_path,
            this.relative_problem_base_path( problem_path) ,
            'solutions/index.html')
    }

    solution_link(_file_){
        // console.log(__filename,_file_)
        // console.log(this._output_path)
        return join(this._output_path,
            this.relative_problem_base_path(_file_) ).replace('.md','.html');
    }

    //返回全部题目的信息
    info() {
        let dirs = readdirSync(this._path)
        console.log('dirs',dirs)
        let infos= []
        for(let d of dirs) 
        {
            let problem_path = this.id_path(d)
            if( statSync(problem_path).isDirectory() ) //是文件夹
            {

                let Problem = new problemClass(problem_path)
                let problem_info = Problem.info();

                let Data = new dataClass(problem_path)
                let data_info = Data.info();

                let solutions = new solutionClass(problem_path).info()
                console.log(solutions)

                // 读取数据

                let doc = {
                    _id:d+'',
                    ...problem_info,
                    //输出路径
                    link: this.problem_link(problem_info.file),
                    data: data_info,
                    solution_list_link: this.solution_list_link(pather_relative(problem_path)),
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
            //渲染器 solution_list
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
