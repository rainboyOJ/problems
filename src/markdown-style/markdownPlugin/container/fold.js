//var md = require('markdown-it')();

module.exports = [ 'fold', {

  validate: function(params) {
      return /^fold/.test(params.trim())
  },

  render: function (tokens, idx) {
    //var m = tokens[idx].info.trim().match(/^fold\s+(.*)$/);

    if (tokens[idx].nesting === 1) {
      // opening tag
      return '<details><summary> 点击 </summary>\n<article>';

    } else {
      // closing tag
      return '</article></details>\n';
    }
  }
}
]

// Output:
//
// <details><summary>click me</summary>
// <p><em>content</em></p>
// </details>
