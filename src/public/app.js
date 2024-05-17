function init_copy(params) {

    //copy to clipboard
    document.querySelectorAll('.zeroclipboard-container').forEach( function(clipContainer){
        clipContainer.addEventListener('click', function(event) {
            console.log(clipContainer.parentNode.parentNode)
            if( clipContainer.classList.contains('copied')) return;

            let text = clipContainer.parentNode.parentNode.querySelector('pre > code').textContent
            clipContainer.classList.add('copied');
            try {
                navigator.clipboard.writeText(text).then( ()=>{
                    setTimeout( ()=> clipContainer.classList.remove('copied'),1500)
                })
            }
            catch(err) {
                alert('failed to copy!',err)
            }
        })
    })
}

function vjudge_get_problem(pid) {
    const reg = /<iframe\s+id="frame-description"\s+src="(\S*)"/
    fetch('https://vjudge.net.cn/problem/'+pid)
        .then(response => {
            if (!response.ok) {
                alert('Network response was not ok');
            }
            return response.text();
        })
        .then(html => {
            if( reg.test(html) ){
                let url_subfixx = html.match(reg)[1]
                document.getElementById('frame-description').src = 'https://vjudge.net.cn' + url_subfixx
            }
            else {
                alert('不匹配 reg')
            }
        })
        .catch(error => {
            alert('There was a problem with the fetch operation:', error);
        });
}

document.addEventListener("DOMContentLoaded", function() {
    init_copy();
});
