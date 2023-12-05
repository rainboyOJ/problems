const exReg = /^blackboard/
const class_name = 'blackboard'

module.exports = [
    'blackboard',
    {
        validate: function( params ){
            return ( exReg.test(params.trim()))
        },
        render: function(tokens, idx, _options, env, self){

            if (tokens[idx].nesting === 1) {
                // opening tag
                return `<div class="${class_name}">\n<div class="blackboard-content">`;

            } else {
                // closing tag
                return '</div></div>\n';
            }
        }

    }
]


