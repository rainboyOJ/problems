/**
 * 手动比较 结果
 */

var fs = require('fs');
var path = require('path');//解析需要遍历的文件夹

//根据文件路径读取文件，返回文件列表
function filelist(filePath){
    let fl = fs.readdirSync(filePath)

    let nlf = fl.reduce( (d,f)=>{
        let stat = fs.statSync( path.join(filePath,f))
        
        if( stat.isFile())
            d.push(f)
        return d

    },[])

    return nlf
}

const { input_regs,output_regs} = {
    input_regs:[
        /([\w]*).in$/i,
    ],
    output_regs:[
        /([\w]*).out$/i,
        /([\w]*).ans$/i,
    ]
}

const get_reg = (flist,reg_array)=>{

    for (let reg of reg_array){
        for(let f of flist){  //找到第一个符合的
            if ( reg.test(f)){
                return reg
            }
        }
    }
    return false;
}

/* 输出匹配的文件列表 */
const file_filter = (flist,reg)=>{

    let list =  flist.reduce((d,f)=>{
        if( reg.test(f) )
            d.push(f)
        return d
    },[])
    
    function sortNumber(a,b){
        let na = a.replace(/[^0-9]/ig,"")
        let nb = b.replace(/[^0-9]/ig,"")

        if(na.length == 0 || nb.length == 0)
            return 1;

        return parseInt(na)-parseInt(nb)
    }
    return list.sort(sortNumber)
}

module.exports = (path)=>{
    //得到文件列表
    let fl = filelist(path)
    let input_reg  = get_reg(fl,input_regs)
    if( input_reg == false) throw(`输入文件没有找到:${path}`)
    let output_reg = get_reg(fl,output_regs)
    if( output_reg == false) throw('`输出文件没有找到:${path}`')
    
    let in_list = file_filter(fl,input_reg)
    let out_list = file_filter(fl,output_reg)

    if( in_list.length == 0 ||  out_list.length == 0 )
        throw(`目录:${path} 下数据为空`)

    if( in_list.length !== out_list.length)
        throw(`目录:${path} 下输入输出数据的数目不相等`)

    let both_list = []

    for( let i in in_list)
        both_list.push( [in_list[i] ,out_list[i]])

    return {
        in_list,
        out_list,
        both_list,
        count:in_list.length
    }

}
