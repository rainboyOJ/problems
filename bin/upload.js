/* 上传题目 */

global.C =  require("./config.js")
const login_url = C.base_url +'user/login'

const rp = require('request-promise');
const upload_one = require("./upload_one.js")

// 登录
function login(){
    return rp({ method:'POST',
        uri:login_url,
        jar:true,
    }).form({username:C.username,password:C.password})
    .then( ({status,message})=>{
        //j
        console.log("登录状态")
        console.log(status,message)
        //if( status !== 0 )
            //throw("登录失败")
    })
}

async function main(){
    let start_id = process.argv[2]
    
    if( !start_id){
        console.log('必须输入上传的id,参数为: start_id [end_id]')
        console.log('程序退出!!!')
        process.exit(1)
    }

    await login();
    

    let end_id= process.argv[3] || start_id

    start_id = parseInt(start_id)
    end_id = parseInt(end_id)
    console.log(`上传题目的范围是: ${start_id} -- ${end_id}`)
    for(let i = start_id ;i <=end_id;i++){
        console.log('开始上传题目id:'+i)
        await upload_one(i)
    }
}

main()
