//对题目的的数据库进行管理

const {join} = require("path")
const fs = require("fs")
const lokijs = require('lokijs')
//创建数据库

class ProblemDB {
    constructor() {
        this.db = new lokijs(join(__dirname,'problem.db'));
        this.problems = this.db.addCollection('problem');
        this.out_json_path = join(__dirname,'../../roj.json')
        this.out_oj_name_path = join(__dirname,'../../oj_name.json')
    }


    // 添加问题
    addProblem(problem) {
        return this.problems.insert(problem);
    }

    // 获取所有问题
    getAllProblems() {
        return this.problems.find();
    }

    // 根据 ID 获取问题
    getProblemById(id) {
        return this.problems.findOne({ id });
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
    saveDatabase() {
        this.db.saveDatabase();
    }

    //需要使用await
    loadDatabase() {
        return new Promise( (res,rej)=> {
            this.db.loadDatabase({},(err)=>{
                if (err) {
                    rej("error : " + err);
                }
                this.problems = this.db.getCollection('problem')
                res()
            })
        })
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
