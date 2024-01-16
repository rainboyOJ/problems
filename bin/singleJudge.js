#!/bin/env node
const compare = require("./lib/compare")
const jsyaml = require("js-yaml")
const fs = require("fs")
const {join, basename, dirname} = require("path")
const {execSync} = require("child_process")
const asciiTable = require('ascii-table')
const AsciiTable = require("ascii-table/ascii-table")

if(!module.parent){
  console.log( 
`
singleJudge pid cppfile
singleJudge 1000 tmp/1.cpp
  - 编译 tmp/1.cpp -> tmp/1
  - 找到 problems/1000 里的reference.yml 里对应的第一个题目的编号
  - compare tmp/1 problems/pid/data
`
  )
  
  if(process.argv.length != 4) {
    console.log( '参数数目不对，退出!' )
    process.exit()
  }
  let PID = process.argv[2]
  let CPPFILE = process.argv[3]

  let problem_info_raw =  fs.readFileSync(join(__dirname,'../problems/',PID,'reference.yml'),{encoding:'utf8'}) 
  let Probelm_info = jsyaml.load(problem_info_raw)

  console.log("=========== 题目信息 ===========")
  console.log( problem_info_raw )
  console.log("================================")

  doJudge(CPPFILE,PID,Probelm_info.title)

}

function doJudge(cppfile,PID,title){
  let CID_PID = basename(cppfile,'.cpp') // name.cpp --> name
  let exeCWD =dirname( join(process.cwd(),cppfile) )
  try {
    execSync(`g++ -o ${CID_PID} ${CID_PID}.cpp`,{cwd:exeCWD,stdio:[0,1,"ignore"]})
  }
  catch {
    let table = new asciiTable(`JudgeResult ${PID} ${title}`)
    table.addRow(`编译失败 得分0！`)
    table.setJustify()//(AsciiTable.CENTER,'',8)
    console.log( table.toString() )
    return
  }
  let table = new asciiTable(`JudgeResult ${PID} ${title}`)
  let rets = compare(join(exeCWD,CID_PID+'') ,join(__dirname,'../problems/',PID+'','data'))
  table.setHeading( ...( new Array(rets.length).fill(0).map( (val,idx) => idx+1+'' )) )
  table.addRow(...rets)
  table.setJustify()//(AsciiTable.CENTER,'',8)
  console.log( table.toString() )
  console.log( 'TOTAL SCORE: ', (100 / rets.length * rets.filter(name => name =='AC').length).toFixed(2) )
  console.log( '\n\n' )
}


module.exports =  doJudge
