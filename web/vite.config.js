const path = require('path')
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'


export default defineConfig({
    plugins: [vue()],
    root: path.resolve(__dirname, 'src'),
    resolve: {
        alias: {
            '~bootstrap': path.resolve(__dirname, 'node_modules/bootstrap'),
            '@': path.join(__dirname,'src'),
        }
    },
    server: {
        port: 8080,
        hot: true
    }
})

