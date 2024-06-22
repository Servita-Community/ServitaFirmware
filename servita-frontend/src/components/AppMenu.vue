<template>
  <div id="appMenu">
    <div id="barContainer">
      <div id="main" class="menuButtonContainer">
        <button id="goPour" class="menuButtons" @click="changeView('pour')">POUR</button>
      </div>
      <div id="ledControl" class="menuButtonContainer">
        <button id="goRGB" class="menuButtons" @click="changeView('rgb')">LED</button>
      </div>
      <div id="wireless" class="menuButtonContainer">
        <button id="goManual" class="menuButtons" @click="changeView('manual')">MANUAL</button>
      </div>
      <div id="deviceSettings" class="menuButtonContainer">
        <button id="goSettings" class="menuButtons" @click="changeView('settings')">SETTINGS</button>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'AppMenu',
  methods: {
    changeView(view) {
      this.$emit('change-view', view);
    }
  }
};
</script>

<style scoped>
#appMenu {
  position: fixed;
  bottom: 10px;
  width: 100%;
  display: flex;
  justify-content: center;
}

#barContainer {
  display: flex;
  flex-direction: row;
  justify-content: center;
  align-content: center;
  background-color: black;
  column-gap: 10px; /* Adjusted gap for better spacing */
  padding: 10px; /* Add padding to ensure buttons stay inside */
  min-width: fit-content; /* Automatically size to minimum required width */
  height: fit-content; /* Automatically size to minimum required height */
  justify-self: center;
  align-self: center;
  box-shadow: 0px 10px 14px -7px gray;
  border-radius: 1rem; /* More rounded corners */
}

.menuButtonContainer {
  background: black;
  color: white;
  border-radius: 1rem; /* More rounded corners */
  justify-self: center;
  align-self: center;
}

.menuButtons {
  background: black;
  border-radius: 1rem; /* More rounded corners */
  height: 2.5rem; /* Smaller fixed height */
  width: 6rem; /* Smaller fixed width */
  border: none; /* Simplified border style */
  color: white;
  font-weight: bold; /* Bold the letters */
  background-position: center;
  transition: background 0.8s;
  display: flex;
  align-items: center;
  justify-content: center;
}

@media (hover: hover) {
  .menuButtons:hover,
  .menuButtons:focus {
    background: #4682B4 radial-gradient(circle, transparent 1%, #4682B4 1%) center/15000% !important;
  }

  .menuButtons:active {
    background-color: #4682B4;
    background-size: 100%;
    transition: background 0s;
  }
}

@media (hover: none) {
  .menuButtons:focus {
    background: #4682B4 radial-gradient(circle, transparent 1%, #4682B4 1%) center/15000% !important;
  }

  .menuButtons:active {
    background-color: #4682B4;
    background-size: 100%;
    transition: background 0.1s;
  }
}
</style>
