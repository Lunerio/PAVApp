<template>
  <div class="hello">
    <div class="box">
      <round-slider
        v-bind:change="handler"
        v-model="sliderValue"
        handleSize="35"
        radius="150"
        circleShape="pie"
        startAngle="-45"
        endAngle="180"
      ></round-slider>
    </div>
  </div>
</template>

<script>
import RoundSlider from "vue-round-slider";
import axios from "axios";

export default {
  name: "SliderComponent",
  components: {
    RoundSlider,
  },
  data() {
    return {
      sliderValue: 0,
    };
  },
  async mounted () {
    const actualtemp = await axios.get("http://localhost:5000/actualTemp");
    this.sliderValue = actualtemp.data
  },
  methods: {
    handler: async function () {
      const actualstatus = await axios.get("http://localhost:5000/actualStatus");
      if (actualstatus.data == 1) { 
        setTimeout (async () => {
          const res = await axios.get("http://localhost:5000/on?temp=" + this.sliderValue);
          alert(JSON.stringify(res.data));
        },500)
      }
    },
  },
};
</script>

<style scoped>
.box {
  padding: 10px;
  display: inline-block;
}
</style>
