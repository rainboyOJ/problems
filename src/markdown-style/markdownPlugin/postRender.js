// 在所有的内容都渲染后做的事件
export default (md) => {
  const origRendered = md.renderer.render

  md.renderer.render = function (...args) {
    const result = origRendered.apply(this, args)
    // console.log(result.slice(0, 200))
    // return result
    const reg = /<nav class="table-of-contents">(.*)?<\/nav>/
    const matchStr = reg.exec(result)
    // console.log(matchStr[0])
    // return result
    if (matchStr && matchStr.length)
      return `<div class="table-of-contents">${matchStr[0]}</div><div class="markdown-content">${result}</div>`

    else
      return `<div class="table-of-contents"></div><div  class="markdown-content">${result}</div>`
  }
}
