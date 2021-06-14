<template>
  <div class="hello">
    <p>
      <label class="switch">
        <input v-on:click="onSwitch" type="checkbox" :checked="encendida" />
        <span class="slider round"></span>
      </label>
    </p>
    <div>{{ status }}</div>
    <div class="box">
      <round-slider
        v-bind:change="onChange"
        v-model="sliderValue"
        v-bind:tooltipFormat="degrees"
        handleSize="35"
        radius="140"
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
      status: "",
    };
  },
  props: {
    msg: String,
  },
  async mounted() {
    setInterval(async () => {
      try {
        await axios.get("http://192.168.1.111/actualStatus");
      } catch (error) {
        console.log(error);
        this.status = "The kettle is disconnected!!";
      }
    }, 4000);
    const actualtemp = await axios.get("http://192.168.1.111/actualTemp");
    this.sliderValue = actualtemp.data;
    setInterval(async () => {
      const actualstatus = await axios.get("http://192.168.1.111/actualStatus");
      if (actualstatus.data == "1") {
        this.encendida = true;
        setInterval(async () => {
          const actualstatus2 = await axios.get(
            "http://192.168.1.111/actualStatus"
          );
          if (actualstatus2.data == "1") {
            this.status = "Heating up, please hold!";
          }
          if (actualstatus2.data == "0") {
            this.encendida = false;
            this.status = "You can take your kettle now!";
            this.sliderValue = 0;
            stop;
          }
        }, 3000);
      }
      if (actualstatus.data == "0") {
        this.encendida = false;
      }
    }, 2000);
  },
  methods: {
    degrees: function (args) {
      return args.value + "°C";
    },
    onChange: async function () {
      try {
        if (!this.encendida) {
          setTimeout(async () => {
            await axios.get("http://192.168.1.111/on?temp=" + this.sliderValue);
            this.encendida = true;
          }, 500);
        } else {
          setTimeout(async () => {
            await axios.get("http://192.168.1.111/on?temp=" + this.sliderValue);
          }, 500);
        }
      } catch (error) {
        console.log(error);
        this.status = "The kettle is disconnected!!";
      }
    },
    onSwitch: async function () {
      try {
        if (!this.encendida) {
          await axios.get("http://192.168.1.111/on?temp=" + this.sliderValue);
        } else {
          await axios.get("http://192.168.1.111/off");
        }
        this.encendida = !this.encendida;
      } catch (error) {
        console.log(error);
        this.status = "The kettle is disconnected!!";
      }
    },
  },
};
</script>
