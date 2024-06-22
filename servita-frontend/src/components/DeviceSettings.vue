<template>
  <div id="settings" class="appPage">
    <div id="titleControls" class="aPageTitle">
      <h2>Settings</h2>
    </div>
    <div class="settingsPage">
      <div id="lockUnlockContainer" class="settingsContainer">
        <h3>Lock/Unlock Device</h3>
        <div class="settingsItems">
          <div id="luButtonContainer" class="settingsSubItemsRow">
            <div class="settingsStatusContainer">
              <p id="luStatus">Status: Unlocked</p>
            </div>
            <div style="text-align: center; width: 80%;">
              <button style="width: 80%;" type="button" class="controlsButtons" @click="lockDevice">Lock</button>
            </div>
            <div style="text-align: center; width: 80%;">
              <button style="width: 80%;" type="button" class="controlsButtons" @click="unlockDevice">Unlock</button>
            </div>
          </div>
        </div>
      </div>
      <div id="wifiControlsContainer" class="settingsContainer">
        <div class="settingsSubTitle">
          <h3>Change WiFi Credentials</h3>
        </div>
        <div id="inputForm" class="settingsItems">
          <div id="sContain">
            <label for="ssid">Network Name: </label>
            <input id="ssid" type="text" />
          </div>
          <div id="pContain">
            <label for="pass">Password: </label>
            <input id="pass" type="text" />
          </div>
          <div id="submitCredentialsContainer">
            <button type="button" class="controlsButtons" @click="submitCredentials">Submit</button>
          </div>
        </div>
      </div>
      <div id="numLEDContainer" class="settingsContainer">
        <div class="settingsSubTitle">
          <h3>Number Of LEDs</h3>
        </div>
        <div id="inputForm" class="settingsItems">
          <div>
            <label for="lNum">LEDs: </label>
            <input type="text" id="lNum" name="lnum" value="0" />
          </div>
          <div>
            <button type="button" class="controlsButtons" @click="submitLEDCount">Submit</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'DeviceSettings',
  methods: {
    lockDevice() {
      this.$emit('send-message', 'lock', { action: 'lock' });
      document.getElementById('luStatus').innerText = "Status: Locked";
    },
    unlockDevice() {
      this.$emit('send-message', 'lock', { action: 'unlock' });
      document.getElementById('luStatus').innerText = "Status: Unlocked";
    },
    submitCredentials() {
      const ssid = document.getElementById('ssid').value;
      const pass = document.getElementById('pass').value;
      this.$emit('send-message', 'net', { ssid, password: pass });
    },
    submitLEDCount() {
      const ledNum = document.getElementById('lNum').value;
      this.$emit('send-message', 'lnum', { value: ledNum });
    }
  }
};
</script>

<style scoped>
.settingsPage {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-content: center;
  justify-items: center;
  align-items: center;
}

.settingsItems {
  display: flex;
  flex-direction: column;
  background-color: rgb(178, 178, 178);
  border-radius: 0.5rem;
  padding: 1em 0.5em;
  justify-self: center;
  align-self: center;
  max-width: 400px;
  min-width: 30vw;
  row-gap: 5vw;
}

.settingsSubItemsRow {
  display: flex;
  flex-direction: row;
  justify-content: center;
  align-content: center !important;
  width: 100%;
  flex: 1;
}

.settingsStatusContainer {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-content: center;
  text-align: center;
}

.settingsContainer {
  justify-self: center;
  align-self: center;
  flex-grow: 1;
}

#inputForm {
  justify-self: center;
  align-self: center;
  padding-top: 1em;
  padding-bottom: 1em;
  padding-left: 0.5em;
  padding-right: 0.5em;
  max-width: 400px;
  row-gap: 2vw;
  display: grid;
  text-align: right;
  align-content: center;
  justify-content: center;
}

#submitCredentialsContainer {
  align-self: center;
  justify-self: center;
}

#submitCredentials {
  width: 6.25rem;
  height: 2.2rem;
  text-align: center;
}
</style>
