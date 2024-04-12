//读取menu.js的数据创建节点数据
//这些数据应该存在于 文件的config.json里
//需要的数据有
// id, label, title
// group 分组
// href 这个文章的链接
// pre 每个点的前置节点
// 还有edge数据
const mynodes = [
  { id: 1, label: "Node 1" },
  { id: 2, label: "Node 2" },
  { id: 3, label: "Node 3" },
  { id: 4, label: "Node 4" },
  { id: 5, label: "Node 5" ,title:"hello i'man five node !"}
]

export default mynodes