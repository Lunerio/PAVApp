<template>
  <div class="hello">
    <h1>{{ msg }}</h1>
    <p> Off
    <label class="switch">
      <input type="checkbox">
      <span class="slider round"></span>
    </label>
	On
    </p>
    <div class="slidecontainer">
      <input type="range" min="1" max="100" value="50" class="slider2" id="myRange">
    </div>
  </div>
</template>

<script>
export default {
  name: 'HelloWorld',
  props: {
    msg: String
  }
}
</script>
