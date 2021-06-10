<template>
  <div id="app">
    <label class="switch2">
      <input
        type="checkbox"
        v-on:click="changeTheme"
        :value="'Cambiar ' + theme"
      />
      <span class="slider rounded"></span>
    </label>
    <img alt="PAVAapp Logo" src="./assets/PAVApp-logo.png" />
    <HelloWorld msg="PAVApp" />
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
      theme: "white-theme",
    };
  },
  methods: {
    changeTheme: async function () {
      this.theme = this.theme === "black-theme" ? "white-theme" : "black-theme";
      this.changeBodyClass();
    },

    changeBodyClass() {
      if (this.theme === "white-theme") {
        document.body.setAttribute("class", "white-theme");
      } else {
        document.body.setAttribute("class", "black-theme");
      }
    },
  },
};
</script>
