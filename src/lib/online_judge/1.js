const luogu = require("./luogu.js")

let infos = luogu.info();

for( let i of infos ) {
    console.log(i)
}
luogu.render(infos)
