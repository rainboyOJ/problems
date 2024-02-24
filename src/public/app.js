//copy to clipboard
document.querySelectorAll('.zeroclipboard-container').forEach( function(clipContainer){
    clipContainer.addEventListener('click', function(event) {
        if( clipContainer.classList.contains('copied')) return;

        let text = clipContainer.parentNode.querySelector('pre > code').textContent
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
