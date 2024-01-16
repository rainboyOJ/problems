#!/usr/bin/env node

//const root_name = "root"
//const root_password = "password"
//const roj_url = 'http://192.168.20.251:3000/'

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



program.arguments('<start> [end]')
        .action(function(start,end){
          Start = start
          End = end
        })

program.parse(process.argv)


async function main(){
  if(!End ) End = Start
  var bar = new ProgressBar(':bar :current/:total\n :m1', { total: End-Start+1 });
  console.log(`你要检查的题目范围是：${Start} --> ${End}`)
  for( let i = Start ;i <= End ;i++){
    if( fs.existsSync(`./problems/${i}`) ){
        try {
          let config = yaml.safeLoad(fs.readFileSync(`./problems/${i}/reference.yml`, 'utf8'));
          if( config.time < 1000)
            console.error(`${i} time ${config.time}`)
          if( config.memory< 64)
            console.error(`${i} memory ${config.memory}`)
          //config.memory = 128
          //config.time = 1000
          //let res = yaml.safeDump(config)
          //fs.writeFileSync(`./problems/${i}/reference.yml`,res, 'utf8')
          bar.tick()
        }
        catch(e){
          bar.tick({
            "m1":`失败 ${i}`
          })
          console.error(e)
        }
    }
    else {

          bar.tick({
            "m1":`失败 题目:${i} 不存在`
          })
          console.log("请查看日志文件: log")
    }
  }
}
main()
