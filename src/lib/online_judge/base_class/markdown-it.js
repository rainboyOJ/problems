const MDRender = require('markdown-r')

// const triple_double_bracket = require("../../../../rbook/bin/triple-square-brackets/index.js")
const triple_double_bracket = require("../../../../rbook/bin/triple-square-brackets/index.js")
console.log(triple_double_bracket)

MDRender.md.use(triple_double_bracket)

module.exports = MDRender
