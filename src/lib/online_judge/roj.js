const base = require("./base.js")
class roj extends base {

    static instance = null

    constructor() {
        super('roj','roj','/roj')
        return roj.instance || (roj.instance = this)
    }
}

module.exports = new roj()
