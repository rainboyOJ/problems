// 在 oj的 solutions 里被调用,查找 [[[ ]]]里的信息
function uniqueArr (arr) {
    return arr.reduce((acc, curr) => {
        if (!acc.find(item => JSON.stringify(item) === JSON.stringify(curr))) {
            acc.push(curr);
        }
        return acc;
    }, []);
}

// [{type:rbook,id: id1}, {type:rbook,id2}]
// => { rbook: [id1,id2]}
function arrToObj( arr) {
    return arr.reduce((obj, {type,id}) => {
        if( !obj[type] ) obj[type] = []
        obj[type].push(id)
        return obj;
    }, {});

}

module.exports =  function get_double_link_info(raw_md) {
    const regex = /\[\[\[(.*?)\]\]\]/gm
    const matches = raw_md.match(regex);
    // console.log(matches)
    if( !matches ) {
        return []
    }
    const regex_info = /\[\[\[\s*(.*)\s*:\s*(.*)\s*\]\]\]/i
    let bidir = []
    for( let str of matches ) {
        if( regex_info.test(str) ) {
            let [_,type,id] =  str.match(regex_info)
            bidir.push({type,id})
        }
    }
    return arrToObj( uniqueArr(bidir) )
}

