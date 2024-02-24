const axios = require("axios")
const TurndownService = require('turndown')

const turndownService = new TurndownService({
    preformattedCode:true,
    emDelimiter: '*',
    bulletListMarker: '-'
})

// turndownService.addRule('strikethrough', {
//     filter: ['pre'],
//     replacement: (content, node) => '\n```txt\n' + node.innerText.trim() + '\n```\n'
// });
turndownService.addRule('strikethrough', {
    filter: ['sup'],
    replacement: content => '^' + content
});


function download_leet_codecn_probem(string_id) {

   axios({
        url:'https://leetcode.cn/graphql',
        method:'post',
        data : {
            "query":"\n    query questionTranslations($titleSlug: String!) {\n  question(titleSlug: $titleSlug) {\n    translatedTitle\n    translatedContent\n  }\n}",
            "variables":{"titleSlug":"two-sum"},
            "operationName":"questionTranslations"
        }
    }).then( ({data})=> {
            // return data
            let md = turndownService.turndown(data.data.question.translatedContent)
            console.log(md)
    })
}

// download_leet_codecn_probem('id')
function test() {

   axios({
        url:'https://leetcode.cn/graphql',
        method:'post',
        data : {
            "query":"\n    query questionTranslations($titleSlug: String!) {\n  question(titleSlug: $titleSlug) {\n    translatedTitle\n    translatedContent\n  }\n}",
            "variables":{"titleSlug":"two-sum"},
            "operationName":"questionTranslations"
        }
    }).then( ({data})=> {
            // return data
            let md = turndownService.turndown(data.data.question.translatedContent)
            console.log(md)
    })
}
