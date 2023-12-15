<template>
    <div>
        <div class="row g-2 align-items-center my-3">
            <div class="col-md-1">
                <span> 筛选: </span>
            </div>

            <div class="col-md-3">
                <div class="input-group">
                    <span class="input-group-text" id="basic-addon1">难度</span>
                    <select v-model="level" class="form-select" aria-label="level">
                        <option value="0" selected>题目难度</option>
                        <option value="1">1</option>
                        <option value="2">2</option>
                        <option value="3">3</option>
                        <option value="4">4</option>
                        <option value="5">5</option>
                    </select>
                </div>
            </div>

            <div class="col-md-3">
                <div class="input-group">
                    <span class="input-group-text" id="basic-addon1">标签</span>
                    <input type="text" class="form-control" placeholder="标签" aria-label="title" aria-describedby="basic-addon1" 
                        readonly @click="choose_tags"
                        v-model="tags_str"
                        >
                </div>
            </div>

            <div class="col-md-4">
                <div class="input-group">
                    <span class="input-group-text" id="basic-addon1">标题</span>
                    <input v-model="title" type="text" class="form-control" placeholder="标题" aria-label="title" aria-describedby="basic-addon1">
                </div>
            </div>

            <div class="col-md-1 d-flex justify-content-center">
                <button type="button" class="btn btn-primary" @click="do_search">
                    search
                </button>
            </div>
        </div>
        
        <div class="d-flex justify-content-center">
            <pagenation 
            @prev_page="prev_page" 
            @next_page="next_page" 
            @page="change_page"
            :page_size="total_pages" :now_page="page"/>
        </div>

        <table class="table">
            <thead>
                <tr>
                    <th scope="col">#</th>
                    <th scope="col">标题</th>
                    <th scope="col">标签</th>
                    <th scope="col">难度</th>
                </tr>
            </thead>
            <tbody>
                <tr v-for="p in problem_list">
                    <th scope="row">
                        <a class="plink" target="__blank__" :href="`/problem/${p._id}`">
                            {{p._id}}
                        </a>
                    </th>
                    <td>
                        <a class="plink" target="__blank__" :href="`/problem/${p._id}`">
                            {{p.title}}
                        </a>
                    </td>
                    <td>{{p.tags}}</td>
                    <td>{{p.level || '未知'}}</td>
                </tr>
            </tbody>
        </table>

        <div class="d-flex justify-content-center">
            <pagenation 
            @prev_page="prev_page" 
            @next_page="next_page" 
            @page="change_page"
            :page_size="total_pages" :now_page="page"/>
        </div>

    </div>
</template>

<script>
    import {ref, reactive, computed } from "vue";
    import lokijs from 'lokijs'
    import roj_json from './roj.json'
    import pagenation from './pagination.vue'

    const db = new lokijs('roj.json')
    db.loadJSONObject(roj_json)

    const problems = db.getCollection('problems')
    const problems_size = problems.chain().find({_id: { '$exists':true} }).filteredrows.length;
    //var a = problems.findOne({_id:1000})
    console.log(problems_size)


    export default {
        components:{pagenation},
        setup() {
            var skip = ref(0)
            var limit = ref(100)
            var problem_list = ref([])

            // 分页
            var page = ref(1)
            var total_size = ref(0)
            var total_pages = ref(0)

            var level = ref(0)
            var tags = ref([])
            var title = ref('')

            var tags_str = computed( ()=> { return tags.value.join(','); })

            // 核心函数:
            function alldoc() {

                let query_object = {_id: { '$exists':true} };
                if( level.value ) //等级
                    query_object.level = level.value
                if( title.value && title.length != 0 ) //标题
                    query_object.title = {'$regex': [title.value,'i']}
                //console.log(query_object)

                let query = problems.chain()
                .find(query_object)
                //标签,使用where
                if( tags.value && tags.value.length != 0 ) {
                    query = query.where( function(obj){
                        if( !obj.tags || obj.tags.length == 0 )
                            return false;

                        for( let tag of tags.value) {
                            if( obj.tags.indexOf(tag) == -1  )
                                return false;
                        }
                        return true;
                    })
                }


                skip.value = (page.value - 1) * limit.value
                total_size.value = query.filteredrows.length;
                total_pages.value = Math.ceil(total_size.value / limit.value)

                return query.simplesort('_id')
                .offset( skip.value )
                .limit(limit.value)
                .data()
            }


            function do_search(stay_at_page = 1) {
                //修改默认的page 
                page.value = stay_at_page
                problem_list.value = alldoc()
            }

            do_search()


            function choose_tags() {
                tags.value.push('123');
                console.log("choose_tags")
            }

            function prev_page() {
                change_page(page.value-1);
            }
            function next_page() {
                change_page(page.value+1);
            }
            function change_page(idx) {
                console.log('change_page',idx)
                if(idx == '...') return;
                if(idx == page.value) return; // 没有改变page值
                if( idx > total_pages.value) {
                    alert('最后一页')
                    return;
                }
                if( idx < 1) {
                    alert('最前一页')
                    return;
                }

                page.value = idx;
                do_search(page.value);
            }

            return {
                problem_list,
                page,
                limit,
                do_search,
                total_size,
                total_pages,
                
                level,
                tags,
                tags_str,
                title,

                prev_page,
                next_page,
                change_page,
                choose_tags,
            };
        },
    };
</script>
