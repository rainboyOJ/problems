<template>
    <div>
        <nav aria-label="Page navigation example">
            <ul class="pagination">
                <li class="page-item">
                    <a class="page-link" href="#" aria-label="Previous" @click="$emit('prev_page')">
                        <span aria-hidden="true">&laquo;</span>
                    </a>
                </li>
                <li class="page-item"><a class="page-link" href="#">1</a></li>
                <li class="page-item"><a class="page-link" href="#">2</a></li>
                <li class="page-item"><a class="page-link" href="#">3</a></li>
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
    export default {
        props:['page_size','now_page'],
        setup(props) {

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

            };
        },
    };
</script>
