// 得到数据信息,不需要渲染
const {join,resolve,extname} = require('path')
const {basename,statSync,readFileSync,readdirSync,existsSync} = require("fs")
const getDataList = require("../../utils/getDataList.js")
class Data {
    
    constructor(_path) {
        this._path = _path
        this._default_name = 'data'
    }

    data_path() {
        return join(this._path,this._default_name)
    }

    info() {
        let _path = this.data_path()
        try {
            if( existsSync(_path)) {
                let {both_list}= getDataList(_path)
                return both_list
            }
        }
        catch(e) {
            if( e.indexOf('输入文件没有找到') != -1)
                return []
            throw e;
        }
        return []
    }
}

module.exports = Data
