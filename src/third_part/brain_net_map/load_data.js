



//1. 加载loki的数据
// const {flatten_menu_json} = require("../../src/menu.js")

// import roj_json from './roj.json'
const {data}= require('../../roj.json').collections[0]

function get_by_id(pid) {
    for(let d of data) {
        if(d._id == pid)
            return d
    }

    return null
}


//2.加载Nodes数据
//需要的数据有
//
// id, label(显示), title()
// group 分组
// href 这个文章的链接
// pre 每个点的前置节点
//
// 下一节点,通常是题目
// next :[
//
// ]
// 还有edge数据
// console.log(flatten_menu_json)

const nodeSet = new Set();

function load_data(){

    let Nodes = []
    let Edges = []

    function addNode(node) {
        if( !nodeSet.has(node._id))
        {
            nodeSet.add(node._id)
            Nodes.push({
                id: node._id,
                title: node.title,
                label: node.title,
                ...node
            })

        }

    }


    for( let d of data)
    {
        // 没有id,说明这个节点,没有加入
        if( !d.pre) continue;
        for( let pre_id of d.pre) {
            let pre_node = get_by_id(pre_id);
            if( !pre_node ) continue;

            Edges.push({
                from: pre_id,
                to: d._id
            })
            addNode(pre_node);
            addNode(d);
        }

        // if (d.next) {
        //     for( let nxt of d.next) {
        //         Nodes.push({
        //             title:nxt.title || nxt.id,
        //             label: nxt.label || nxt.title || nxt.id,
        //             ...nxt
        //         })
        //
        //         Edges.push({
        //             from:d.id,
        //             to:nxt.id
        //         })
        //     }
        // }
    }
    return {Nodes,Edges}
}

// export const Ns = Nodes
// export const Es = Edges


function nodejsPlugin() {
    return {
        name: 'nodejs-plugin',
        config() {
            // 在 Vite 构建过程中执行 Node.js 代码
            // const data = fs.readFileSync('yourNodeJsFile.js', 'utf-8');

            let{Nodes,Edges} = load_data();
            return {
                define: {
                    // 将计算得到的数据传递给前端
                    // $yourData: JSON.stringify(data)
                    Nodes,Edges
                }
            };
        }
    };
}
// var aaa = nodejsPlugin().config()
module.exports = nodejsPlugin
