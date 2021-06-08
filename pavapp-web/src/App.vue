<template>
  <div id="app">
    <img alt="PAVAapp Logo" src="./assets/PAVApp-logo.png" />
    <HelloWorld msg="PAVApp" />
    <input type="button" @click="cambiarTheme()" :value="'Cambiar '+theme" />
  </div>
</template>

<script>
import "./assets/theme-black.css";
import "./assets/theme-white.css";
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
      theme: "black-theme"
    }
  },
  methods: {
    changeTheme: function () {
      this.cambiarBodyClass()
  },
    changeBodyClass: function () { 
      if (this.theme === "black") {
         document.body.setAttribute("class", "black-theme")
      } else {
        document.body.setAttribute("class", "white-theme")
      }
    }
  }
};
</script>

<style>
#app {
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  margin-top: 60px;
}
.box {
  padding: 10px;
  display: inline-block;
}
</style>
