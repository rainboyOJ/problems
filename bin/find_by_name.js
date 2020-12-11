#!/bin/env node
const jsyaml = require("js-yaml")
const fs = require("fs")
const path = require("path")

const searchString = process.argv[2]
if( !searchString){
  console.log(`usage: ./bin/find_by_name.js searchTitleString`)
  process.exit(0)
}

const problems_path = path.join(__dirname,'..','problems')
const read = (id) => fs.readFileSync(path.join(__dirname,'..','problems',id,'reference.yml'),{encoding:'utf8'})
const reference = (id) => jsyaml.load(read(id))
//const Title = (id) => reference(id).title



let problems = fs.readdirSync(problems_path)

for( let id of problems){
  let stat =  fs.statSync(path.join(problems_path,id))
  if( stat.isDirectory() ){
    let {title} = reference(id)
    if( title.includes(searchString) )
      console.log(`[${id}] : ${title}`)
  }
}
