const base = require("./base.js")
class luogu extends base {

    static instance = null

    constructor() {
        super('luogu','other_oj/luogu','/luogu')
        // this.id = id
        // this.link = `https://www.luogu.com.cn/problem/${id}`
        return luogu.instance || (luogu.instance = this)
    }


    //连接网络 得到信息
    http() {

        var getInfo = function(id){
            let realId = /^\d/.test(id) ? `P${id}` : id;
            console.log( 'realId',realId )

            // let a = e(`curl https://www.luogu.com.cn/problem/${realId} --cookie "${cookie}"`,{encoding:'utf-8'})
            let a = e(`wget -O - https://www.luogu.com.cn/problem/${realId}`,{encoding:'utf-8'})
            let dataReg = /decodeURIComponent\("([\s\S]+?)"\)/
            //console.log(a)
            //console.log(dataReg.test(a))
            //console.log( a.match(dataReg))
            let data_string = a.match(dataReg)[1]
            var data = JSON.parse(decodeURIComponent(data_string))
            //console.log(JSON.stringify(data,null,4))
            //console.log(data.currentData.lastCode)
            return data
        }
    }

}

module.exports = new luogu()
