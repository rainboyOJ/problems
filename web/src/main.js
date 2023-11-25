// Import our custom CSS
import './scss/styles.scss'
import * as bootstrap from 'bootstrap'

import { createApp } from 'vue'
import router from './router/index'



import App from './App.vue'

// Import all of Bootstrap's JS

const app = createApp(App)
app.use(router)
app.mount("#app")
