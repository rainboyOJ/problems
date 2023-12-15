//一些用于github proxy 下载数据的链接
exports.mirrors = {
    //https://cdn.jsdelivr.net/gh/rainboyOJ/problems/problems/1000/data/problem1.in
    "jsdelivr" : "https://cdn.jsdelivr.net/gh/rainboyOJ/problems@master/problems/__id__/data/__data_name",
    "ghproxy" : "https://mirror.ghproxy.com/https://raw.githubusercontent.com/rainboyOJ/problems/master/problems/__id__/data/__data_name",
    //raw.gitmirror.com
    // https://raw.gitmirror.com/rainboyOJ/problems/master/problems/1000/data/problem1.in
    "gitmirror": "https://raw.gitmirror.com/rainboyOJ/problems/master/problems/__id__/data/__data_name"
}


exports.real_link = function(name,id,data_name)
{
    let link = mirrors[name]
    return link.replace('__id__',id+'').replace('__data_name',data_name+'')
}
