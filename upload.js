#!/bin/env node

const root_name = "root"
const root_password = "password"
const roj_url = 'http://localhost:3000/'

const ProgressBar = require('progress');
const { program } = require('commander');
const fs = require("fs")
const {execSync} = require("child_process")
const yaml = require("js-yaml")


if(!fs.existsSync('header')){
  console.log("先在网页上登录admin，然后获取 header存入header文件")
  process.exit(0)
}



program.option("-f --force","强制上传")
        .arguments('<start> [end]')
        .action(function(start,end){
          Start = start
          End = end
        })
program.parse(process.argv)

function upload({file,content,pid,title,time=1000,memory=128,stack=128,spj='default',level=1}){
  if( memory > 4096) memory = Math.ceil(memory/1024/1024)
  let args = [
    ["file",`@${file}`],
    ["content",`${content}`],
    ["pid",pid],
    ["title",title],
    ["time",time],
    ["memory",memory],
    ["stack",stack],
    ["spj",spj],
    ["level",level]
  ]
  let args_1 = (args.map( d => `-F "${d[0]}=${d[1]}"`)).join(" ")
  if(program.force)
    args_1 += " -F upload_force=1"
  return execSync(`curl -X POST ${args_1} -H @header ${roj_url}admin/problem/create`,{encoding:'utf8',stdio:['pipe','pipe','/dev/null']})
  //console.log(`curl -X POST ${args_1} -H @header ${roj_url}admin/problem/create`)
}

async function main(){
  if(!End ) End = Start
  var bar = new ProgressBar(':bar :current/:total\n :m1', { total: End-Start+1 });
  console.log(`你要上传的题目范围是：${Start} --> ${End}`)
  for( let i = Start ;i <= End ;i++){
    if( fs.existsSync(`./problems/${i}`) ){
        try {
          let config = yaml.safeLoad(fs.readFileSync(`./problems/${i}/reference.yml`, 'utf8'));
          //let content = fs.readFileSync(`./problems/${i}/content.md`, 'utf8')
          if(!fs.existsSync(`./problems/${i}/content.md`)){
            throw(`${i} content.md 不存在`)
          }
          execSync(`zip -j data.zip -r ./problems/${i}/data`)
          let ret = upload({file:'data.zip',content:`<problems/${i}/content.md`,pid:i,...config})
          if( ret.startsWith('Redirect') ){
            console.log(`请重新登录！`)
            process.exit(1)

          }
          if( JSON.parse(ret).status !== 0){
            throw(ret)
          }
          fs.unlinkSync(`data.zip`)
          bar.tick({
            "m1":`成功 ${i}`
          })
        }
        catch(e){
          bar.tick({
            "m1":`失败 ${i}`
          })
          fs.writeFileSync("log",`fail at ${i}\n${e}\n\n\n`,{flag:"w+"})
        }
    }
    else {

          bar.tick({
            "m1":`失败 ${i} 不存在`
          })
          fs.writeFileSync("log",`fail at ${i} 不存在\n\n\n`,{flag:"w+"})
    }

    if(fs.existsSync('data.zip')) fs.unlinkSync(`data.zip`)
  }
}
main()
