<template>
    <div>
        <nav aria-label="Page navigation example">
            <ul class="pagination">
                <li class="page-item">
                    <a class="page-link" href="#" aria-label="Previous" @click="$emit('prev_page')">
                        <span aria-hidden="true">&laquo;</span>
                    </a>
                </li>
                <template v-for="idx in page_arr">
                    <li class="page-item">
                        <a class="page-link" 
                           @click="$emit('page',idx)"
                            :class="{active: now_page == idx}" href="#"
                            >
                            {{idx}}
                        </a>
                    </li>
                </template>
                <li class="page-item">
                    <a class="page-link" href="#" aria-label="Next" @click="$emit('next_page')">
                        <span aria-hidden="true">&raquo;</span>
                    </a>
                </li>
            </ul>
        </nav>
    </div>
</template>
<script>
    import {ref, reactive, computed } from "vue";
    import page_algo from './pagenation.js'
    export default {
        props:['page_size','now_page'],
        setup(props) {

            var page_arr = computed( ()=> { return page_algo(props.now_page,props.page_size); })
            console.log(page_arr)

            function emit_next() {
                this.$emit('next_page')
            }
            const emit_prev = () =>{
                
                //this.$emit('prev_page')
            }
            function emit_page(page) {
                this.$emit('page',page)
            }
            return {
                emit_next,
                emit_prev,
                emit_page,
                page_arr
            };
        },
    };
</script>
