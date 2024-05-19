//对题目的的数据库进行管理

const {join} = require("path")
const fs = require("fs")
const lokijs = require('lokijs')
const LokiFsSyncAdapter = require('lokijs/src/loki-fs-sync-adapter.js');
//创建数据库

class ProblemDB {
    constructor() {
        this.db = new lokijs(join(__dirname,'problem.db'),{
            adapter: new LokiFsSyncAdapter()
        });
        this.problems = this.db.addCollection('problem');
        this.out_json_path = join(__dirname,'../../roj.json')
        this.out_oj_name_path = join(__dirname,'../../oj_name.json')
    }


    // 添加问题
    addProblem(problem) {
        return this.problems.insert(problem);
    }

    // 更新问题,如果没有,就添加
    reAddProblem(problem) {
        let doc = this.getProblemById(problem._id)
        if( !doc ){
            this.addProblem(problem)
        }
        else{
            this.problems.findAndRemove({_id:problem._id})
            this.addProblem(problem)
        }
    }

    //solutions 数据中含有 type 这个 attr,
    //且attr是一个数组,数组中含有 id 这个值
    // rbook: ['01_seq','subset_enum']
    solutions_bidir_find(type,id) {
        return this.problems.where( function( obj){
            if( obj.solutions ){
                for( let sol of obj.solutions )
                {
                    if( sol[type] && sol[type].indexOf(id) != -1)
                        return true;
                }
            }
            return false;
        })
    }

    //solutions 数据中含有 type 这个 attr,
    //且attr是一个数组,数组中含有 id 这个值
    // practice_rbook: ['01_seq','subset_enum']
    solutions_has_practice_rbook(id) {
        return this.solutions_bidir_find('practice_rbook',id)
    }

    //查找pre_rbook
    find_pre_rbook(rbook_id) {
        return this.problems.find({'pre_rbook':{'$contains': rbook_id}})
    }

    //查找pre 属性含有 id的值
    find_pre_has(p_id) {
        return this.problems.find({'pre':{'$contains':p_id}})
    }

    // 获取所有问题
    getAllProblems() {
        return this.problems.find();
    }

    // 根据 ID 获取问题
    getProblemById(_id) {
        return this.problems.findOne({ _id });
    }

    // 根据 ID 更新问题
    updateProblemById(id, updatedProblem) {
        const problem = this.problems.findOne({ id });
        if (problem) {
            Object.assign(problem, updatedProblem);
            this.problems.update(problem);
            return problem;
        }
        return null;
    }

    // 根据 ID 删除问题
    deleteProblemById(id) {
        const problem = this.problems.findOne({ id });
        if (problem) {
            this.problems.remove(problem);
            return true;
        }
        return false;
    }

    // 根据条件查询问题
    queryProblems(query) {
        return this.problems.find(query);
    }

    // 获取问题数量
    getProblemsCount() {
        return this.problems.count();
    }

    // 清空问题集合
    clearProblems() {
        this.problems.clear();
    }

    // 保存数据库
    saveDatabase(message) {
        return new Promise( (res,rej)=>{
            this.db.saveDatabase( (err) =>{
                if( err) rej(err)
                else {
                    console.info(message)
                    res();
                }
            });
        })
    }

    //需要使用await
    loadDatabase() {
        this.db.loadDatabase()
        this.problems = this.db.getCollection('problem')
    }

    //提到所有的oj的names
    getUniqueOJNames() {
        const ojValues = this.problems.find().map(problem => problem.oj);
        const uniqueOJValues = [...new Set(ojValues)];
        return uniqueOJValues;
    }
    
    saveJson() {
        //写入数据
        let jsonStr = this.db.serialize()
        // const out_db_path = join(__dirname,'../roj.json')
        // const out_oj_name_path = join(__dirname,'../oj_name.json')
        console.log("写入db:", this.out_json_path)
        let oj_names = this.getUniqueOJNames()
        fs.writeFileSync(this.out_json_path,jsonStr,{encoding:'utf8'})
        fs.writeFileSync(this.out_oj_name_path,JSON.stringify(oj_names),{encoding:'utf8'})
    }
}

module.exports = ProblemDB;
