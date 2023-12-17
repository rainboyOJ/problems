// 网站生成器

//注册有哪些网站
// 文件路径：example.mjs
class webSiteGen {

    constructor(project_path) {
        this.project_path = project_path
        this.ojs = [
            require("./online_judges/roj.js"),
        ]
    }

}



new webSiteGen();
