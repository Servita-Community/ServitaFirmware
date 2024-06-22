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