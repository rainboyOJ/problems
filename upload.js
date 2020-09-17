#!/bin/env node

const root_name = "root"
const root_password = "password"
const roj_url = 'http://localhost:3000/'

const problem_create = `${roj_url}admin/problem/create`
const problem_update = `${roj_url}admin/problem/update`

const ProgressBar = require('progress');
const { program } = require('commander');
const fs = require("fs")
const {execSync,spawnSync} = require("child_process")
const yaml = require("js-yaml")


if(!fs.existsSync('cookie')){
  console.log("先在网页上登录admin，然后获取 Cookie存入cookie文件")
  process.exit(0)
}
const COOKIE = fs.readFileSync("cookie","utf8")


if(fs.existsSync('log')){
  console.log("删除上次的日志文件: log")
  fs.unlinkSync('log')
}
if(fs.existsSync('data.zip')) fs.unlinkSync(`data.zip`)



program.option("-f --force","强制上传")
        .option("-u --update","更新题目")
        .option("-i --ignore","忽略错误")
        .option("-d --debug","输出 debug 信息")
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
  let args_1 = ["-X","POST"]
  args.map( d => args_1.push(...[`-F`,`${d[0]}=${d[1]}`]) )

  if(program.force) args_1.push(...["-F",'upload_force=1'])

  args_1.push(`-b`,`${COOKIE.trim()}`)

  let url =  program.update ? problem_update :  problem_create
  args_1.push(url)

  if( program.debug) console.log("curl "+ args_1.join(" "))
  return spawnSync("curl",args_1,{encoding:'utf8',cwd:__dirname})
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

          if(ret.error) throw(ret.error)
          if(ret.stderr && program.debug)
            console.log(ret.stderr)

          if( ret.stdout.startsWith('Redirect') ){
            if( ret.stdout.includes('<a href="/404">')){
              console.log(`网址错误！`)
              process.exit(1)
            }
            console.log(`请重新登录！`)
            process.exit(1)

          }
          if( JSON.parse(ret.stdout).status !== 0){
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
          console.error(e)
          fs.writeFileSync("log",`fail at ${i}\n${e}\n\n\n`,{flag:"a+"})
          if( ! program.ignore ){
            console.log("如果想忽略错误,请加上 -i 或 --ignore,具体查看 log 文件")
            process.exit(1);
          }
        }
    }
    else {

          bar.tick({
            "m1":`失败 题目:${i} 不存在`
          })
          console.log("请查看日志文件: log")
          fs.writeFileSync("log",`fail at ${i} 不存在\n\n\n`,{flag:"a+"})
    }
    if(fs.existsSync('data.zip')) fs.unlinkSync(`data.zip`)
  }
}
main()
