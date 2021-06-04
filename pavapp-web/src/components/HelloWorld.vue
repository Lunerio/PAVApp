<template>
  <div class="hello">
    <p>
      Off
      <label class="switch">
        <input v-on:click="greet" type="checkbox" :checked="encendida" />
        <span class="slider round"></span>
      </label>
      On
    </p>
  </div>
</template>

<script>
import axios from "axios";

export default {
  name: "HelloWorld",
  data() {
    return { encendida: false };
  },
  props: {
    msg: String,
  },
  async mounted() {
    const res = await axios.get("192.168.1.100/actualStatus");
    alert(JSON.stringify(res.data));
    console.log(res.data);
    if (res.data == "1") {
      this.encendida = true;
    }
    if (res.data == "0") {
      this.encendida = false;
    }
  },
  methods: {
    greet: async function () {
      if (!this.encendida) {
        const on = await axios.get("192.168.1.100/on");
        alert(JSON.stringify(on.data));
      } else {
        const off = await axios.get("192.168.1.100/off");
        alert(JSON.stringify(off.data));
      }
      this.encendida = !this.encendida;
    },
  },
};
</script>
