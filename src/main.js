// Import all plugins
import * as bootstrap from 'bootstrap';

import { createApp } from "vue";
import App from "./App.vue";
console.log('-------------')

const app = createApp(App);
app.mount("#app");
