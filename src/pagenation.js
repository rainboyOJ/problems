//分页算法

//根据 now_page : 当前的页面的数量,从1开始
//total_page 求出页面的分布算法
function page_algo(now_page,total_page) {

    let arr = [now_page]
    const show_half_page_size = 4; //显示的一半的页面数量
    let now = now_page
    //向左拓展
    for( let i = now_page-1 ; i>0 && i >= now_page-show_half_page_size   ;i--) {
        arr.unshift(i)
    }
    if( arr[0] >=3 ) {
        arr.unshift('...');
        arr.unshift(1);
    }
    else if( arr[0] == 2) {
        arr.unshift(1);
    }

    //向右拓展
    for( let i = now_page+1 ; i <= total_page && i <= now_page+show_half_page_size   ;i++) {
        arr.push(i)
    }

    let last = arr[arr.length-1]
    if( last <= total_page -2 ) {
        arr.push('...');
        arr.push(total_page);
    }
    else if( last == total_page-1) {
        arr.push(total_page);
    }

    return arr
}

export default page_algo
