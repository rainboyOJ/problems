
//基类

const {join,resolve,isAbsolute,extname,basename,relative} = require('path')
const {writeFileSync,readdirSync,statSync,readFileSync,existsSync} = require("fs")
const moment = require('moment')
const GrayMater = require('gray-matter')
const viewer = require("../viewer.js") //渲染ejs
const MDRender = require('markdown-r')
const {mkdirp} = require("../utils/utils.js")
const {mirrors,real_link} = require('../utils/github_proxy.js')


const project_dir = resolve(__dirname,'../../../')
const web_output_root = join(project_dir,'dist') // 输出路径的地址 dist/
const __dir = (p) => resolve(project_dir,p)


class base_oj_class {
    constructor(ojName,path,output_path){
        this._name = ojName
        this._path = isAbsolute(path) ? path : __dir(path)
        this._output_path  = isAbsolute(output_path) ? output_path : __dir(output_path)
    }

    get name() {
        return this._name;
    }

    get path() {
        return this._path;
    }

    get output_path() {
        return this._output_path;
    }

    //-------------------- 路径信息
    id_path(id) {
        return join(this.path,id+'')
    }

    output_dir_by_id(id) {
        return join(this.output_path,id+'')
    }

    //题目的输出生成
    output_html_by_id(id) {
        return join(output_dir_by_id(id),'index.html')
    }

    problem_file_path_by_id(id) {
        let file1 = join(this.id_path(id),'content.md')
        if( existsSync(file1))
            return file1;
        let file2 = join(this.id_path(id),'content.pdf')
        if( existsSync(file2))
            return file2;
        throw `not find ${this.name} ${id} problem content\n file1: ${file1}\n file2:${file2}`
    }

    solution_path(id,filename) {
        // console.log('path',id,filename)
        return join(this.id_path(id),'solutions',filename);
    }

    solution_out_path(id,filename) {
        if( !filename)
            return join(this.output_dir_by_id(id),'solutions')
        return join(this.output_dir_by_id(id),'solutions',basename(filename,'.md')+'.html')
    }

    solution_list_out_path(id) {
        return join(this.output_dir_by_id(id),'solutions','index.html')
    }


    //得到一个输出地址的 网页路径
    html_link(output_html_path) {
        return '/' + relative(web_output_root,output_html_path)
    }
    //-------------------- 路径信息 END ----


    get_data_info(id) {
        let {both_list}= getDataList(join(this.id_path(id),'data'))
        return both_list
    }

    get_content_ext(id) {
        if( existsSync( join(this.id_path(id),'content.md')))
            return '.md'
        if( existsSync( join(this.id_path(id),'content.pdf')))
            return '.pdf'
        throw `${id},content.md,content.pdf all not exists!`;
    }

    get_problem_info(id){

        let a = JSON.parse(readFileSync(join(this.id_path(id),'config.json'),{encoding:'utf-8'}))
        return Object.assign(
            a,
            {  content_ext: this.get_content_ext(id)},
            { data : this.get_data_info(id)}
        );
    }


    //得到一个solution 的信息
    get_solution_info(id,filename) {
        let file_path = this.solution_path(id,filename)
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
                ...grayed.data
            }

        info.unixstamp = moment(info.update).unix()
        info.filename = filename
        return info
    }


    //得到题目的解析
    get_solutions(id) {
        let p = join(this.id_path(id),'solutions')
        let files = readdirSync(p).filter( file => statSync(join(p,file)).isFile() && extname(file) == '.md' )
        return files.map( file => this.get_solution_info(id,file) )
    }


    //扫描目录下的所有文件夹
    scan_dir() {
        let dirs = readdirSync(this.path)
        let ret = []
        for(let d of dirs) {
            if( statSync(this.id_path(d)).isDirectory() ) //是文件夹
            {
                ret.push(d)
            }
        }
        return ret
    }

    //得到所有的信息
    all_info() {
        let ret = []
        for(let _id of this.scan_dir()) {
            let doc = {
                _id,
                ...this.get_problem_info(_id),
                solutions : this.get_solutions(_id)
            }
            ret.push(doc)
        }
        return ret;
    }

    // ---------------- 渲染相关
    //传递 info 然后进行渲染
    render_by_id(id,info) {
        let content = ''
        let file = this.problem_file_path_by_id(id)
        if(info.content_ext.toLowerCase() == '.md') {
            content = MDRender( readFileSync(file,{encoding:'utf8'}) ,{
                ejs : {
                    options: {
                        filename : file
                    }
                }
            } ).content
        }

        let index_html = viewer('problem',{...info,content,mirrors,real_link})
        mkdirp(this.output_dir_by_id(id))
        let index_path = join(this.output_dir_by_id(id),'index.html')
        writeFileSync(index_path,index_html,{encoding:'utf8'})

    }

    //渲染id下单个题目解析
    render_solutions(id,info) {
        mkdirp(this.solution_out_path(id))
        let file = this.solution_path(id,info.filename)
        // console.log(file)
        let out_file = ''
        let content = MDRender( readFileSync(file,{encoding:'utf8'}),
            {
                ejs : {
                    options: {
                        filename : file
                    }
                }
            }
        ).content
        let html = viewer('solution',{...info,content})
        writeFileSync(this.solution_out_path(id,info.filename),html,{encoding:'utf8'})
    }

    render_solutions_list(id,info) {
        mkdirp(this.solution_out_path(id))

        //生成所有的html
        let solution_links= []
        for( let d of info.solutions || []) {
            console.log(this.html_link(this.solution_out_path(id,d.filename)))
            solution_links.push( {
                link: this.html_link(this.solution_out_path(id,d.filename)),
                ...d
            })
        }

        let html = viewer('solution_list',{id,...info,solution_links})
        let out_file = this.solution_list_out_path(id,info.filename)
        mkdirp(basename(out_file))
        writeFileSync(out_file,html,{encoding:'utf8'})
    }

    //渲染入口
    render(id,info) {
        this.render_by_id(id,info);
        //渲染所有solution
        if( !info.solutions) return;

        //渲染solution_list.html
        this.render_solutions_list(id,info);

        for(let sol of info.solutions) {
            // console.log('render solutions',id,sol)
            this.render_solutions(id,sol)
        }
    }
    // ---------------- 渲染相关 END
}

module.exports = base_oj_class;
