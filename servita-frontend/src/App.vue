<template>
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
  align-content: center;
  justify-content: center;
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
  height: 90%;
  width: 100vw;
  margin-top: 100px;
  margin-bottom: auto;
  position: fixed;
}
.break {
  width: 100% !important;
  height: 0;
}
</style>
