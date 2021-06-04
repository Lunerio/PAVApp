<template>
  <div class="hello">
    <h1>{{ msg }}</h1>
    <p>
      Off
      <label class="switch">
        <input v-on:click="greet" type="checkbox" :checked="encendida" />
        <span class="slider round"></span>
      </label>
      On
    </p>
    {{ encendida }}
    <div>
      <span id="rangeValue">0</span>
        <Input class="range" type="range" name value="0" min="0" max="100" onChange="rangeSlide(this.value)" onmousemove="rangeSlide(this.value)"></Input>
    </div>
    <script type="text/javascript">
        function rangeSlide(value) {
            document.getElementById('rangeValue').innerHTML = value;
        }
    </script>
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
    const res = await axios.get("http://192.168.1.100/");
    alert(JSON.stringify(res.data));
    var status = res.data.split("/");
    console.log(status[1]);
    if (status[1] == "1") {
      this.encendida = true;
    }
    if (status[1] == "0") {
      this.encendida = false;
    }
  },
  methods: {
    greet: async function () {
      // `this` inside methods points to the Vue instance
      // alert('Hello ' + this.name + '!')
      // `event` is the native DOM event
      if (!this.encendida) {
        const on = await axios.get("http://192.168.1.100/on");
        alert(JSON.stringify(on.data));
      } else {
        const off = await axios.get("http://192.168.1.100/off");
        alert(JSON.stringify(off.data));
      }
      this.encendida = !this.encendida;
    },
  },
};
</script>
