const log = console.log
var a = require("./getARGV.js")
for( let i =2000;i<=2096;i++){
    let info = a.read(i)
    log('- ',i+' ',info.title)
}
