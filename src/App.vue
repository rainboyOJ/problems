<template>
    <div>
        <div class="row g-3 align-items-center">
            <div class="col-md-1">
                <span> 筛选: </span>
            </div>

            <div class="col-md-3">
                <div class="input-group">
                    <span class="input-group-text" id="basic-addon1">难度</span>
                    <select class="form-select" aria-label="level">
                        <option selected>题目难度</option>
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
                    <input type="text" class="form-control" placeholder="标签" aria-label="title" aria-describedby="basic-addon1">
                </div>
            </div>

            <div class="col-md-5">
                <div class="input-group">
                    <span class="input-group-text" id="basic-addon1">标题</span>
                    <input type="text" class="form-control" placeholder="标题" aria-label="title" aria-describedby="basic-addon1">
                </div>
            </div>
        </div>
        <div class="d-flex m-2 justify-content-center">
            <button type="button" class="btn btn-primary" @click="do_search">
                search
            </button>
        </div>
        <pagenation @prev_page="prev_page" :page_size="total_pages" :now_page="1"/>
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
                    <th scope="row">{{p._id}}</th>
                    <td>{{p.title}}</td>
                    <td>{{p.tags}}</td>
                    <td>{{p.level || '未知'}}</td>
                </tr>
            </tbody>
        </table>
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
            var page = ref(0)
            var total_size = ref(0)
            var total_pages = ref(0)
    

            function alldoc() {
                skip.value = page.value * limit.value
                let query = problems.chain()
                .find({_id: { '$exists':true} })

                total_size.value = query.filteredrows.length;
                total_pages = Math.ceil(total_size.value / limit.value)

                return query.simplesort('_id')
                .offset( skip.value )
                .limit(limit.value)
                .data()
            }


            function do_search() {
                problem_list.value = alldoc()
            }

            do_search()

            function prev_page() {
                console.log('prev_page')
            }

            return {
                problem_list,
                page,
                limit,
                do_search,
                total_size,
                total_pages,
                prev_page
            };
        },
    };
</script>
