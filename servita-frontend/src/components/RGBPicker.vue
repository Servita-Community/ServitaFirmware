<template>
  <div id="rgbPicker" class="appPage">
    <div id="titleControls" class="aPageTitle">
      <h2>Change LED Color</h2>
    </div>
    <div id="rbgPage" class="pourItems">
      <div class="settingsItems">
        <div id="rgbDisplayContainer" class="settingsSubItemsCol">
          <div id="display"></div>
        </div>
      </div>
      <div id="rgbSliders" class="settingsItems">
        <div class="settingsSubItemsCol">
          <label id="rLabel" for="red">Red</label>
          <input type="range" class="slider" id="red" name="red" min="0" max="255" value="0" />
        </div>
        <div class="settingsSubItemsCol">
          <label id="gLabel" for="green">Green</label>
          <input type="range" class="slider" id="green" name="green" min="0" max="255" value="0" />
        </div>
        <div class="settingsSubItemsCol">
          <label id="bLabel" for="blue">Blue</label>
          <input type="range" class="slider" id="blue" name="blue" min="0" max="255" value="0" />
          <button type="button" class="controlsButtons" id="rgbSend" @click="confirmColor">Confirm Color</button>
        </div>
        <div class="settingsSubItemsCol">
          <label id="brightValDisplay" name="brightness">Brightness Level:</label>
          <input name="brightness" type="range" min="0" max="255" value="127" class="slider" id="brightness" />
          <button type="button" class="controlsButtons" id="brightSend" @click="confirmBrightness">Confirm Brightness</button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'RGBPicker',
  methods: {
    confirmColor() {
      const red = document.getElementById('red').value;
      const green = document.getElementById('green').value;
      const blue = document.getElementById('blue').value;
      this.$emit('send-message', 'led', { value: `${red},${green},${blue}` });
    },
    confirmBrightness() {
      const brightness = document.getElementById('brightness').value;
      this.$emit('send-message', 'brightness', { value: brightness });
    }
  }
};
</script>

<style scoped>
#display {
  width: 50%;
  height: 50%;
  flex: 1;
  align-self: center;
}
</style>