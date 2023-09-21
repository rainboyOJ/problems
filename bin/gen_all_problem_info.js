
//生成所有的all_problme_info.txt
const jsyaml = require("js-yaml")
const fs = require("fs")
const path = require("path")

const problem_dir = path.join(__dirname,"../problems/")

//get all pids
const pids = fs.readdirSync(problem_dir)

let infos = []
for( let pid of pids ) {
    let _raw = fs.readFileSync(path.join(problem_dir,pid,'reference.yml'),{encoding:"utf8"})
    let yaml = jsyaml.load(_raw)
    let info = `${pid} "${yaml.title}" ${yaml.time} ${yaml.memory} "${yaml.tags || ""}"`
    // console.log(info)
    infos.push(info)
}
fs.writeFileSync(path.join(problem_dir,'../all_problme_info.txt'),infos.join('\n'),{encoding:"utf8"})
