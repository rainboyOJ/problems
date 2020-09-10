var ch = require("child_process")

for(let i =1;i<=10;i++)
    ch.execSync(`./std < ./data/p${i}.in > ./data/p${i}.out`)
