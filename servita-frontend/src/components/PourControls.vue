<template>
<div id="pControls" class="appPage">
    <div id="titleControls" class="aPageTitle">
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

<script>
export default {
  name: 'PourControls',
  data() {
    return {
      drinks: [
        {
          id: 1,
          containerId: 'drink1Container',
          buttonId: 'drink1',
          name: 'Drink 1',
          ranges: [
            {
              id: 'p1Range',
              labelId: 'p1ValDisplay',
              labelText: 'Pour Size:',
              inputId: 'p1Range',
              inputName: 'p1Range'
            }
          ]
        },
        {
          id: 2,
          containerId: 'drink2Container',
          buttonId: 'drink2',
          name: 'Drink 2',
          ranges: [
            {
              id: 'p2Range',
              labelId: 'p2ValDisplay',
              labelText: 'Pour Size:',
              inputId: 'p2Range',
              inputName: 'p2Range'
            }
          ]
        },
        {
          id: 3,
          containerId: 'drink3Container',
          buttonId: 'drink3',
          name: 'Drink 3',
          ranges: [
            {
              id: 'p3Range1',
              labelId: 'p3Val1Display',
              labelText: 'Pump 1 Amount:',
              inputId: 'p3Range1',
              inputName: 'p3Range1'
            },
            {
              id: 'p3Range2',
              labelId: 'p3Val2Display',
              labelText: 'Pump 2 Amount:',
              inputId: 'p3Range2',
              inputName: 'p3Range2'
            }
          ]
        }
      ]
    };
  }
};
</script>

<style scoped>
.appPage {
  display: flex;
  flex-direction: column;
  align-items: center;
  padding-top: 2rem; /* Add some padding to the top to avoid sticking to the very top */
  width: 100%;
}

.aPageTitle {
  width: 100%;
  text-align: center;
  margin-bottom: 1rem;
}

.pourItems {
  display: flex;
  flex-direction: column;
  align-items: center;
  width: 100%;
  gap: 1rem;
}

.settingsItems {
  display: flex;
  flex-direction: column;
  background-color: rgb(178, 178, 178);
  border-radius: 0.5rem;
  padding: 1em 0.5em;
  max-width: 400px;
  min-width: 30vw;
  gap: 1rem;
  align-items: center;
}

.settingsSubItemsCol {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 1rem;
  min-width: 30vw;
  max-width: 400px;
}

.controlsButtons {
  font-size: 1rem;
  font-family: Arial;
  height: 3rem;
  width: 100%;
  color: #fff;
  font-weight: bold;
  border-radius: 0.5rem;
  background: rgba(74, 74, 74, 1);
  transition: background 0.8s;
}

#cancel {
  background: #b21111;
  box-shadow: #e33737;
  transition: background 0.8s;
}

#cancelContainer {
  width: 100%;
  display: flex;
  justify-content: center;
}

@media (min-width: 320px) {
  .settingsItems, .settingsSubItemsCol {
    min-width: 300px;
    max-width: 80vw;
  }
}

@media (min-width: 1025px) {
  .settingsItems, .settingsSubItemsCol {
    min-width: 400px;
    max-width: 400px;
  }
  #cancelContainer {
    width: 230px;
  }
}
</style>
