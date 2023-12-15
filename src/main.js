// Import all plugins
import * as bootstrap from 'bootstrap';


import lokijs from 'lokijs'
import { createApp } from "vue";
import App from "./App.vue";


const app = createApp(App);
app.mount("#app");
