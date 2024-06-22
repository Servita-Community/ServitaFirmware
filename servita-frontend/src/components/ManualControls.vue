<template>
    <div id="manualControls" class="appPage">
      <div>
        <h2>Manual Controls</h2>
      </div>
      <div class="manButtons">
        <div>
          <button id="mCarUp" type="button" class="controlsButtons" @mousedown="sendManualControl('mCarUp')" @mouseup="sendManualControl('mCarStop')">Move Carriage Up</button>
        </div>
        <div>
          <button id="mCarDown" type="button" class="controlsButtons" @mousedown="sendManualControl('mCarDown')" @mouseup="sendManualControl('mCarStop')">Move Carriage Down</button>
        </div>
        <div>
          <button id="mCarHome" type="button" class="controlsButtons" @click="sendManualControl('mCarHome')">Move Carriage To Home Position</button>
        </div>
        <div>
          <button id="rPump1" type="button" class="controlsButtons" @mousedown="sendManualControl('rPump1Start')" @mouseup="sendManualControl('rPump1Stop')">Run Pump 1</button>
        </div>
        <div>
          <button id="rPump2" type="button" class="controlsButtons" @mousedown="sendManualControl('rPump2Start')" @mouseup="sendManualControl('rPump2Stop')">Run Pump 2</button>
        </div>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    name: 'ManualControls',
    methods: {
      sendManualControl(action) {
        this.$emit('send-message', 'manual', { action });
      }
    }
  };
  </script>
  
  <style scoped>
.manButtons {
  text-align: center;
  width: 100%;
  display: flex;
  flex-direction: column;
  gap: 2%;
  align-content: center;
  justify-content: center;
  margin-top: 0.5%;
  margin-bottom: 0.5%;
}

.manButtons div {
  margin-top: 2%;
  margin-bottom: 2%;
  align-self: center;
  justify-self: center;
  width: 80% !important;
}

@media (min-width: 320px) {
  .manButtons {
    column-gap: 5%;
    row-gap: 5%;
  }
}

@media (min-width: 1025px) {
  .manButtons {
    column-gap: 5%;
    row-gap: 10px;
  }

  .manButtons div {
    margin-top: 0;
    margin-bottom: 0;
  }
}
  </style>