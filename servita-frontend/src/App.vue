<template>
  <v-app>
    <div id="app">
      <AppTitle />
      <div id="appView" class="appView">
        <PourControls v-show="currentView === 'pour'" />
        <RGBPicker v-show="currentView === 'rgb'" />
        <DeviceSettings v-show="currentView === 'settings'" />
        <ManualControls v-show="currentView === 'manual'" />
      </div>
      <AppMenu @change-view="changeView" />
    </div>
  </v-app>
</template>

<script>
import AppTitle from './components/AppTitle.vue';
import PourControls from './components/PourControls.vue';
import RGBPicker from './components/RGBPicker.vue';
import DeviceSettings from './components/DeviceSettings.vue';
import ManualControls from './components/ManualControls.vue';
import AppMenu from './components/AppMenu.vue';

export default {
  name: 'App',
  components: {
    AppTitle,
    PourControls,
    RGBPicker,
    DeviceSettings,
    ManualControls,
    AppMenu,
  },
  data() {
    return {
      currentView: 'pour',
    };
  },
  methods: {
    changeView(view) {
      this.currentView = view;
    },
  },
};
</script>

<style>
body {
  background-color: #c9c7c7;
  width: 100%;
  padding: 0;
  margin: 0;
  border: 0;
  font-family: Arial, Helvetica, sans-serif;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: flex-start;
  height: 100vh;
}

#app {
  display: flex;
  flex-direction: column;
  width: 100%;
  height: 100%;
}

h1 {
  text-align: left;
  color: white;
}

h2 {
  text-align: center;
}

.appView {
  display: flex;
  flex-direction: column;
  width: 100vw;
  flex-grow: 1;
  align-items: center;
  justify-content: flex-start;
  overflow-y: auto; /* Enable vertical scrolling */
  padding-bottom: 10%; /* Account for the height of the bottom bar */
}

.break {
  width: 100% !important;
  height: 0;
}
</style>