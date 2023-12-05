const class_container = [
    [/^center/,'center'],
    [/^oneline/,'oneline'], // 一条线
    [/^lb/,'lb-box']
];

export default [
    'class',
    {
        validate: function( params ){
            for ( let [exReg] of class_container ){
                if( exReg.test(params.trim()))
                    return true;

            }
            return false
        },
        render: function(tokens, idx, _options, env, self){
            let params = tokens[idx].info.trim()
            for ( let [exReg,class_name] of class_container ){
                if( exReg.test(params)){

                    if (tokens[idx].nesting === 1) {
                        // opening tag
                        return `<div class="${class_name}">\n`;

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


