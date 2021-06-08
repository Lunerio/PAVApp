<template>
  <div id="app">
    <img alt="PAVAapp Logo" src="./assets/PAVApp-logo.png" />
    <HelloWorld msg="PAVApp" />
    <input type="button" @click="changeTheme()" :value="'Cambiar '+theme" />
  </div>
</template>

<script>
import "./assets/black-theme.css";
import "./assets/white-theme.css";
import HelloWorld from "./components/HelloWorld.vue";

export default {
  name: "App",
  components: {
    HelloWorld,
  },
  mounted() {
    this.changeBodyClass();
  },
  data() {
    return {
      theme: "white-theme"
    }
  },
  methods: {
    changeTheme() {
      this.theme = (this.theme === "black-theme") ? "white-theme" : "black-theme";
      this.changeBodyClass()
    },

    changeBodyClass () { 
      if (this.theme === "white-theme") {
         document.body.setAttribute("class", "white-theme")
      } else {
        document.body.setAttribute("class", "black-theme")
      }
    }
  }
};
</script>
