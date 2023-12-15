var {execSync}= require("child_process")

for ( let i = 1 ;i<=10;i++){
  execSync(`./1 < p${i}.in > p${i}.out`)
}
