import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import {resolve} from 'path'
import {ViteEjsPlugin} from "vite-plugin-ejs";

// https://vitejs.dev/config/
// let p = resolve(new URL('.', import.meta.url).pathname,'src')
// console.log(p)
export default defineConfig({
    plugins: [ ViteEjsPlugin(),vue()],
    root: resolve(new URL('.', import.meta.url).pathname,'src'),
    build: {
        outDir:'../dist'
    }
})
