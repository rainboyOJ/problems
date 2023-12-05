import ejs from 'ejs'

// let content = fs.readFileSync('./1.md',{encoding:'utf8'})
// let filename = Path.join(__dirname,'./1.md')
// let html = ejs.render(content,{},{
// filename
// })

// console.log(html)

function create_func(md: MarkdownIt, options_: any) {
  // 根据 vitepress的源码
  // md.__path 代表渲染文件的路径

  return function ejs_render(state: any): boolean {
    state.src = ejs.render(state.src, options_, {
      filename: state.env.id,
      // filename: state.md.__path,
    })
    return true
  }
}

export default function (md: any, options_: any) {
  md.core.ruler.before('normalize', 'ejs_format', create_func(md, options_))
}
