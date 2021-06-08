<template>
  <div id="app">
    <img alt="PAVAapp Logo" src="./assets/PAVApp-logo.png" />
    <HelloWorld msg="PAVApp" />
  </div>
</template>

<script>
import "./assets/theme.css";
import HelloWorld from "./components/HelloWorld.vue";

export default {
  name: "App",
  components: {
    HelloWorld,
  },
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
