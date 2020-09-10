const fs = require("fs")
const log = console.log
var getARGV = require("./getARGV.js")


function read(p){
    return fs.readFileSync(p,{encoding:'utf-8'})
}


var a  = 1422


let content = read('./一本通提高篇题目列表.md')

let list = content.split('\n')
for (let l of list){
    if(l[0] == '-'){
        let sp = l.split(' ')
        let id = parseInt(sp[1])
        let name = sp.slice(2).join(" ")
        if( id === 10249){
            log(id,name,'     ')
            continue;
        }

        let ref = getARGV.read(a)
        log('- ', a,name)
        //ref.title = name
        //getARGV.dump(ref,a)

        a++
    }
    else if (l != '')
        log( l)
}
