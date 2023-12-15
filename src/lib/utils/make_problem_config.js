//创建题目的 config.json 数据

class problemConfig = {

    constructor() {
        this.title = undefined
        this.memory = 128
        this.time = 128
        this.tags = []
        this.source = undefined
        this.oj = 'roj'
        this.id = undefined
    }

    toObject() {
        return {...this}
    }

    void set(name,val) {
        this[name] = val
    }

    void set_source(name,val) {
        set(name,val)
    }

    void add_tags(tag) {
        this.tags.push(tag)
    }

    toJSON(){
        return JSON.stringify(this.toObject())
    }

}

module.exports = problemConfig
