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
      sliderValue: 60,
    };
  },
  methods: {
    handler: async function () {
      const res = await axios.get("http://localhost:5000/on");
      alert(JSON.stringify(res.data));
    },
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.box {
  padding: 10px;
  display: inline-block;
}
</style>
