/* 上传题目 */
/* 先填写 */


const rp = require('request-promise');
const fs = require("fs")
const {execSync} = require("child_process")
const pathFn = require("path")
const yaml = require("js-yaml")
const fse = require("fs-extra")


//包装
function createProblem(data){
    return rp({
        method:'POST',
        uri:C.base_url+'problem/upload',
        jar:true,
        json:true,
        body:data
    }).then( html => {
        return html
    })
}

async function upload_one(l){
    // 登录
    //let login = await rp({
        //method:'POST',
        //uri:login_url,
        //jar:true,
    //}).form({username,password})

    //创建题目
    //let list = fs.readdirSync(pathFn.join(__dirname,'../problems'))
    ////let list = [1307]
    //for( l of list){

        let base_path = pathFn.join(__dirname,'../problems',l.toString())
        
        if(!fs.existsSync(base_path)){
            console.log(`${l} 不存在`)
            return;
        }


        let content = fs.readFileSync(base_path+'/content.md',{encoding:'utf-8'})

        let data = yaml.load(fs.readFileSync(base_path+'/reference.yml',{encoding:'utf-8'}) )
        data.pid = l
        data.content = content

        let res = await createProblem(data)

        //创建data_zip
        execSync(`zip -ll -j /tmp/problem_data.zip ${base_path}/data/*`)

        let formdata = {
            pid:l,
            file:fs.createReadStream('/tmp/problem_data.zip'),
            force:'true'
        }

        res = await rp.post({url: C.base_url+'problem/dataupload',jar:true, formData:formdata})
        res  = JSON.parse(res)
        if( res.status == 0)
            console.log(`${l} 上传成功`)
        else{
            console.log(`${l} 上传失败`)
            console.log(res)
        }
        //删除
        fse.removeSync('/tmp/problem_data.zip')
        
    //}
    //上传数据
}


module.exports = upload_one
