const {join} = require("path")
class ROJ  {
    constructor(project_path) {
        this.project_path = project_path
        this.oj_path = join(project_path,'problems');
    }

    //扫描,得到所有的id
    san() {
    }

    //得到一条记录
    get_one_doc() {

        //得到 config.json
        //得到content md or pdf
        //扫描 solutions
        //扫描 数据目录
        //

    }

}

module.exports = ROJ
