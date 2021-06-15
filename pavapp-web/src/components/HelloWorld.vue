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
    try {
      const actualtemp = await axios.get("http://192.168.1.111/actualTemp");
      this.sliderValue = actualtemp.data;
      const actualstatus = await axios.get("http://192.168.1.111/actualStatus");
      if (actualstatus.data == "1") {
        this.encendida = true;
        this.status = "Heating up, please hold!";
        let interval = setInterval(async () => {
          const actualstatus2 = await axios.get(
            "http://192.168.1.111/actualStatus"
          );
          if (actualstatus2.data == "0") {
            this.encendida = false;
            this.status = "You can take your kettle now!";
            this.sliderValue = 0;
            clearInterval(interval);
          }
        }, 6000);
      }
      if (actualstatus.data == "0") {
        this.encendida = false;
      }
    } catch (error) {
      console.log(error);
      this.status = "The kettle is disconnected!!";
    }
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
          let interval2 = setInterval(async () => {
            const actualstatus = await axios.get(
              "http://192.168.1.111/actualStatus"
            );
            if (actualstatus.data == "1") {
              this.encendida = true;
              this.status = "Heating up, please hold!";
            }
            if (actualstatus.data == "0") {
              this.encendida = false;
              this.status = "You can take your kettle now!";
              this.sliderValue = 0;
              clearInterval(interval2);
            }
          }, 6000);
        }
        if (this.encendida) {
          setTimeout(async () => {
            await axios.get("http://192.168.1.111/on?temp=" + this.sliderValue);
          }, 500);
          let interval2 = setInterval(async () => {
            const actualstatus = await axios.get(
              "http://192.168.1.111/actualStatus"
            );
            if (actualstatus.data == "1") {
              this.encendida = true;
              this.status = "Heating up, please hold!";
            }
            if (actualstatus.data == "0") {
              this.encendida = false;
              this.status = "You can take your kettle now!";
              this.sliderValue = 0;
              clearInterval(interval2);
            }
          }, 6000);
        }
      } catch (error) {
        console.log(error);
        this.status = "The kettle is disconnected!!";
      }
    },
    onSwitch: async function () {
      try {
        if (!this.encendida) {
          setTimeout(async () => {
            await axios.get("http://192.168.1.111/on?temp=" + this.sliderValue);
            this.encendida = true;
          }, 500);
          let interval2 = setInterval(async () => {
            const actualstatus = await axios.get(
              "http://192.168.1.111/actualStatus"
            );
            if (actualstatus.data == "1") {
              this.encendida = true;
              this.status = "Heating up, please hold!";
            }
            if (actualstatus.data == "0") {
              this.encendida = false;
              this.status = "You can take your kettle now!";
              this.sliderValue = 0;
              clearInterval(interval2);
            }
          }, 6000);
        } else {
          await axios.get("http://192.168.1.111/off");
        }
      } catch (error) {
        console.log(error);
        this.status = "The kettle is disconnected!!";
      }
      this.encendida = !this.encendida;
    },
  },
};
</script>
