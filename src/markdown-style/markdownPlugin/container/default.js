var twemoji = require('twemoji')
const default_container = [
    [/^warning/,'warning','⚠️'],
    [/^error/,'error','✖️'],
    [/^info/,'info','❗']
]
module.exports = [
    'default',
    {
        validate: function( params ){
            for ( let [exReg] of default_container ){
                if( exReg.test(params.trim()))
                    return true;

            }
            return false
        },
        render: function(tokens, idx, _options, env, self){
            let params = tokens[idx].info.trim()
            for ( let [exReg,class_name,title] of default_container ){
                if( exReg.test(params)){

                    if (tokens[idx].nesting === 1) {
                        // opening tag
                        return `<div class="${class_name}">` + 
                            `<div class="title-icon">${twemoji.parse(title) }</div>` +
                            '\n';

                    } else {
                        // closing tag
                        return '</div>\n';
                    }
                }

            }
            
            return '</div>\n';
        }
    }
]


