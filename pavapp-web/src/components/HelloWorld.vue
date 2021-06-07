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
    <div class="box">
      <round-slider
        v-bind:change="handler"
        v-model="sliderValue"
        v-bind:tooltipFormat="degrees"
        handleSize="35"
        radius="150"
        circleShape="pie"
        startAngle="-45"
        endAngle="180"
        tooltipColor="#204376"
        rangeColor="#33E995"
        pathColor="#204376"
      ></round-slider>
    </div>
  </div>
</template>

<script>
import axios from "axios";
import RoundSlider from "vue-round-slider";

export default {
  name: "HelloWorld",
  components: {
    RoundSlider,
  },
  data() {
    return {
      encendida: false,
      sliderValue: 0,
    };
  },
  props: {
    msg: String,
  },
  async mounted() {
    const actualtemp = await axios.get("http://localhost:5000/actualTemp");
    this.sliderValue = actualtemp.data;
    const actualstatus = await axios.get("http://localhost:5000/actualStatus");
    if (actualstatus.data == "1") {
      this.encendida = true;
    }
    if (actualstatus.data == "0") {
      this.encendida = false;
    }
  },
  methods: {
    degrees: function (args) {
      return args.value + "°C";
    },
    handler: async function () {
      // const actualstatus = await axios.get("http://localhost:5000/actualStatus");
      if (!this.encendida) {
        this.encendida = true;
        setTimeout(async () => {
          const res = await axios.get(
            "192.168.1.100/on?temp=" + this.sliderValue
          );
          alert(JSON.stringify(res.data));
        }, 500);
      }
    },
    greet: async function () {
      if (!this.encendida) {
        const on = await axios.get("http://localhost:5000/on");
        alert(JSON.stringify(on.data));
      } else {
        const off = await axios.get("http://localhost:5000/off");
        alert(JSON.stringify(off.data));
      }
      this.encendida = !this.encendida;
    },
  },
};
</script>
