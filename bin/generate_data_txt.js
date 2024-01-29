//生成data.txt 文件
//根据 https://www.reddit.com/r/nginx/comments/9jzqa6/trying_to_understand_mod_zip/
const fs = require('fs');
const {join,resolve,relative} = require("path")
const crc = require("crc")
const {globSync}= require("glob")
const getDataList = require("./lib/getDataList.js")

const BaseDir = join(__dirname,'..')

const work_dirs = [
    'roj',
    'other_oj'
]


function isFileNewer(file1, file2) {
  try {
    const stat1 = fs.statSync(file1);
    const stat2 = fs.statSync(file2);

    // 获取文件的修改时间（mtime）
    const mtime1 = stat1.mtime.getTime();
    const mtime2 = stat2.mtime.getTime();

    // 判断文件1是否新于文件2
    return mtime1 > mtime2;
  } catch (err) {
    // 处理可能的错误
    console.error(err);
    return false;
  }
}

function hasFilesNewer(directory1, file2) {
    // 读取文件夹1中的所有文件
    const files1 = fs.readdirSync(directory1);

    // 遍历文件夹1中的每个文件
    for (const file1 of files1) {
        const filePath1 = join(directory1, file1);

        // 并且文件1是否新于文件2
        if (isFileNewer(filePath1,file2)) {
            return true;
        }
    }

    // 所有文件都不新于相应的文件夹2中的文件
    return false;
}


function create_data_txt(directory1,out_path) {
    // 读取文件夹1中的所有文件
    let str = []
    // const files1 = fs.readdirSync(directory1);
    const filelist = getDataList(directory1).both_list.flat(5)

    // 遍历文件夹1中的每个文件
    for (const file1 of filelist) {
        const filePath1 = join(directory1, file1);
        try {
            let crc_data = crc.crc32( fs.readFileSync(filePath1,{encoding:'utf8'}) ).toString(16)
            let filesize = fs.statSync(filePath1).size
            let location =  '/' + relative(BaseDir,filePath1)
            str.push(`${crc_data} ${filesize} ${location} ${file1}`)
        }
        catch(e) {
            console.log('err',e)
            console.log('err at',filePath1)
            process.exit(1)
        }
    }
    // return str.join("\n")
    fs.writeFileSync(out_path,str.join("\n"),{encoding:'utf8'})
    
}

function work(Dir) {
    let work_dir = join(BaseDir,Dir)
    let data_dirs = globSync( '**/data/',{
        cwd:work_dir,
        absolute:true
    })
    
    for( let dir of data_dirs) {
        // console.log(dir)
        let data_txt = join(dir,'..','data.txt')

        if( !fs.existsSync(dir)) {
            console.log(dir,'not exists')
            continue;
        }

        if( !fs.existsSync(data_txt) || hasFilesNewer(dir,data_txt)) {
            try {
                create_data_txt(dir,data_txt)
            }
            catch(e) {
                console.log('err at',dir)
                console.log('err at',e)
                if( e.indexOf('没有找到') != -1)
                    continue;
                process.exit(1)
            }
            console.log(dir,'ok')
        }
        // break;
    }

}


for( let dir of work_dirs)  {
    work(dir)
}
