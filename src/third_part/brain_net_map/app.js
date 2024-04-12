import { DataSet, Network } from "vis-network/standalone";
// import mynodes from "./nodes.js";
// CSS will be automatically injected into the page.

// create an array with nodes
const nodes = new DataSet(Nodes);

// create an array with edges
const edges = new DataSet(Edges);

// create a network
const container = document.getElementById("mynetwork");
const data = {
  nodes: nodes,
  edges: edges
};

const options = {
    autoResize: true,
    height: '100%',
    width: '100%',
    locale: 'en',
    clickToUse: false,
    nodes :{
        shape: 'box',
        shadow:{
            enabled: true,
            color: 'rgba(0,0,0,0.5)',
            size:10,
            x:5,
            y:5
        },
    },
    edges : {
        arrows : {
            to : {
                enabled:true,
                type:'arrow'
            }
        },
        // dashes:true,
        hoverWidth: 1.5,
        shadow:{
            enabled: false,
            color: 'rgba(0,0,0,0.5)',
            size:10,
            x:5,
            y:5
        },
    },
    layout: {
        randomSeed: 100,
        improvedLayout: true,
        clusterThreshold: 150,
        hierarchical: {
            enabled: true,
            levelSeparation: 150,
            nodeSpacing: 100,
            treeSpacing: 200,
            blockShifting: true,
            edgeMinimization: true,
            parentCentralization: true,
            direction: 'UD',        // UD, DU, LR, RL
            sortMethod: 'hubsize',  // hubsize, directed
            shakeTowards: 'leaves'  // roots, leaves
        }
    },
    interaction :{
        hover:true
    }
};
const network = new Network(container, data, options);

network.on('click', function(params) {
  if (params.nodes.length > 0) {
    var clickedNodeId = params.nodes[0];
    var clickedNode = nodes.get(clickedNodeId);
    console.log(clickedNode)
    
    // 检查是否点击的是带有链接的结点
    if (clickedNode.href) {
        window.open(clickedNode.href, '_blank');
    }
  }
});

