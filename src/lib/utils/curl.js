const axios = require("axios")

exports.get = function (url) {
    return axios.get(url).then( res => res.data )
}
