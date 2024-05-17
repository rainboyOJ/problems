const base = require("./base.js")
class roj extends base {

    static instance = null

    constructor() {
        super('roj','roj','/roj')
        return roj.instance || (roj.instance = this)
    }

    /*
    match(path) {
        if(path.startsWith('roj/')) {
            let new_path = path.replace('roj/','' )
            return super.match(new_path)
        }
        else {
            return super.match(path)
        }
    }
    */
}

module.exports = new roj()
