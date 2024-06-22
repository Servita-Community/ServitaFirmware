<template>
<div id="pControls" class="appPage">
    <div id="titleControls" class="aPageTitle">
    <h2>Pour a Drink</h2>
    </div>
    <div id="pourMenu" class="pourItems">
    <div class="settingsItems" v-for="drink in drinks" :key="drink.id">
        <div :id="drink.containerId" class="settingsSubItemsCol">
        <button type="button" class="controlsButtons" :id="drink.buttonId">{{ drink.name }}</button>
        <div class="slidecontainer" v-for="range in drink.ranges" :key="range.id">
            <label :id="range.labelId" :for="range.inputId">{{ range.labelText }}</label>
            <input :name="range.inputName" type="range" min="0" max="20" value="10" class="slider" :id="range.inputId">
        </div>
        </div>
    </div>
    <div id="cancelContainer" class="settingsSubItemsCol">
        <button type="button" class="controlsButtons" id="cancel">Cancel Pour</button>
    </div>
    </div>
</div>
</template>

<script src="./PourControls.js"></script>
<style scoped src="./PourControls.css"></style>