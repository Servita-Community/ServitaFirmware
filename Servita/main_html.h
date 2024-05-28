const char main_html[] PROGMEM = R"rawliteral(
<html>

<head>
    <title>Servita</title>
    <link rel="icon" type="image/icon+x"
        href="https://cdn.shopify.com/s/files/1/0781/3146/2449/files/servita-Favicon.svg?v=1715474891" />
    <meta name="viewport" content="width=device-width, initial-scale=1">
</head>

<body>
    <script type="text/javascript">
        document.addEventListener("touchstart", function () { }, true);
    </script>
    <style>
        .break {
            width: 100% !important;
            height: 0;
        }

        h1 {
            text-align: left;
            color: white;
        }

        h2 {
            text-align: center;
        }

        #appTitle {
            display: flex;
            width: 100%;
            height: 80px;
            flex-direction: row;
            background-color: black;
            color: white;
            box-shadow: 0px 5px 14px -7px black;
            justify-content: center;
            top: 0px;
            position: fixed;
        }

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
            /* row-gap: 100px; */
        }
        #mCarUp {
            -webkit-user-select: none; /* Safari */
            -moz-user-select: none; /* Firefox */
            -ms-user-select: none; /* IE10+/Edge */
            user-select: none; /* Standard syntax */
        }
        #mCarDown {
            -webkit-user-select: none; /* Safari */
            -moz-user-select: none; /* Firefox */
            -ms-user-select: none; /* IE10+/Edge */
            user-select: none; /* Standard syntax */
        }
        #rPump1 {
            -webkit-user-select: none; /* Safari */
            -moz-user-select: none; /* Firefox */
            -ms-user-select: none; /* IE10+/Edge */
            user-select: none; /* Standard syntax */
        }
        #rPump2 {
            -webkit-user-select: none; /* Safari */
            -moz-user-select: none; /* Firefox */
            -ms-user-select: none; /* IE10+/Edge */
            user-select: none; /* Standard syntax */
        }
        .appPage {
            height: fit-content;
            width: 100vw;
            justify-content: center;
            align-content: center;
            flex-direction: column;
            transition-duration: 300ms;
            flex-grow: 1;
        }

        .appView {
            display: flex;
            height: 90%;
            width: 100vw;
            margin-top: 100px;
            margin-bottom: auto;
            position: fixed;
        }

        .aPageButtons {
            text-align: center;
            width: 100%;
            display: flex;
            flex-direction: row;
            column-gap: 2%;
            align-content: center;
            flex-wrap: wrap;
            justify-content: center;
        }

        .manButtons {
            text-align: center;
            width: 100%;
            display: flex;
            flex-direction: column;
            gap: 2%;
            align-content: center;
            justify-content: center;
            margin-top: .5%;
            margin-bottom: .5%;
        }

        .manButtons div {
            margin-top: 2%;
            margin-bottom: 2%;
            align-self: center;
            justify-self: center;
            width: 80% !important;
        }

        .aPageTitle {
            width: 100%;
        }

        .controlsButtons {
            justify-self: center;
            align-self: center;
        }

        .controlsButtons {
            font-size: 15px;
            font-family: Arial;
            height: 50px;
            width: inherit;
            border-width: 1px;
            color: #fff;
            border-color: #4682B4;
            font-weight: bold;
            border-top-left-radius: 8px;
            border-top-right-radius: 8px;
            border-bottom-left-radius: 8px;
            border-bottom-right-radius: 8px;
            box-shadow: 0px 10px 14px -7px #276873;
            text-shadow: 0px 1px 0px #3d768a;
            background: rgba(74, 74, 74, 1);
            background-position: center;
            transition: background 0.8s;
        }

        #cancel {
            background: #b21111;
            box-shadow: #e33737;
            text-shadow: none;
            background-position: center;
            transition: background 0.8s;
        }

        #appMenu {
            position: fixed;
            bottom: 10px;
            height: 70px;
            width: 100%;
            display: grid;
            justify-self: center;
        }

        #barContainer {
            display: flex;
            flex-direction: row;
            justify-content: center;
            align-content: center;
            background-color: black;
            column-gap: 5%;
            min-width: 90%;
            height: 90%;
            justify-self: center;
            align-self: center;
            box-shadow: 0px 10px 14px -7px gray;
            border-radius: 20px;
        }

        .menuButtonContainer {
            background: black;
            color: white;
            border-radius: 20px;
            justify-self: center;
            align-self: center;
        }

        .menuButtons {
            background: black;
            border-radius: 10px;
            height: 80%;
            width: 100%;
            border-style: hidden;
            border-width: 1px;
            color: white;
            background-position: center;
            transition: background 0.8s;
        }

        #imgContainer {
            width: fit-content;
            height: fit-content;
            align-self: center;
            justify-self: center;
            margin-right: 5px;
        }

        #logo {
            max-width: 400px;
            max-height: 80px;
            align-self: center;
            justify-self: center;
        }

        

        #submitCredentialsContainer {
            align-self: center;
            justify-self: center;
        }

        #submitCredentials {
            width: 100px;
            height: 35px;
            text-align: center;
        }

        .settingsPage {
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-content: center;
            justify-items: center;
            align-items: center;
        }

        #l-u-Image {
            justify-self: center;
            align-self: center;
        }

        .settingsStatusContainer {
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-content: center;
            text-align: center;
        }

        #lockUnlockContainer {
            justify-self: center;
            align-self: center;
        }

        #pourMenu {
            flex-grow: 1;
            justify-self: center;
            align-self: center;
            width: 100vw;
            flex: 1;
        }

        #cancelContainer {
            justify-content: center;
            align-items: center;
        }

        .pourItems {
            display: flex;
            flex-grow: 1;
            flex-direction: column;
            justify-content: center;
            align-content: center;
            justify-items: center;
            align-items: center;
            width: 100%;
            row-gap: 1vh;
            /* position: fixed; */
        }

        .settingsItems {
            display: flex;
            flex-direction: column;
            background-color: rgb(178, 178, 178);
            border-radius: 20px;
            padding-top: 1em;
            padding-bottom: 1em;
            padding-left: .5em;
            padding-right: .5em;
            justify-self: center;
            align-self: center;
            max-width: 400px;
            min-width: 30vw;
            row-gap: 5vw;
        }
        #inputForm {
            justify-self: center;
            align-self: center;
            padding-top: 1em;
            padding-bottom: 1em;
            padding-left: .5em;
            padding-right: .5em;
            max-width: 400px;
            row-gap: 2vw;
            display: grid;
            text-align: right;
            align-content: center;
            justify-content: center;
        }

        .settingsContainer {
            justify-self: center;
            align-self: center;
            flex-grow: 1;
        }

        .settingsSubItemsRow {
            display: flex;
            flex-direction: row;
            justify-content: center;
            align-content: center !important;
            width: 100%;
            flex: 1;
        }

        .settingsSubItemsCol {
            display: flex;
            flex-grow: 1;
            flex-direction: column;
            justify-content: center;
            align-content: center;
            flex: 1;
            row-gap: 2vh;
            min-width: 30vw;
            max-width: 400px;
        }

        .slidecontainer {
            width: 100%;
            justify-self: center;
            align-self: center;
        }

        .slider {
            -webkit-appearance: none;
            width: 100%;
            height: 15px;
            border-radius: 5px;
            background: #d3d3d3;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
        }

        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #4682B4;
            cursor: pointer;
        }

        .slider::-moz-range-thumb {
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #4682B4;
            cursor: pointer;
        }

        /* Mouse-over effects */
        .slider:hover {
            opacity: 1;
            /* Fully shown on mouse-over */
        }

        #luButtonContainer {
            align-self: center;
            justify-self: center;
        }

        .color-picker {
            min-width: 85vw;
            max-width: 80vw;
            min-height: 10vh;
            padding: 20px;
            flex: 1;
        }

        #rgbDisplayContainer {
            min-height: 10vh;
            align-content: center;
        }

        #display {
            width: 50%;
            height: 50%;
            flex: 1;
            align-self: center;
        }

        #rgbPage {
            flex-grow: 1;
            justify-self: center;
            align-self: center;
            width: 100vw;
            flex: 1;
        }


        @media (min-width:320px) {

            /* smartphones, iPhone, portrait 480x320 phones */
            .manButtons {
                column-gap: 5%;
                row-gap: 5%;
            }

            #logo {
                max-width: 200px;
                max-height: 40px;
            }

            .appView {
                margin-bottom: 60px;
            }

            .aPageTitle {
                font-size: 1em;
            }

            #appTitle {
                height: 60px;

            }

            .controlsButtons {
                font-size: 13px;
                height: 40px;
                width: 80%;
            }

            .settingsItems {
                min-width: 300px;
                max-width: 80vw;
            }

            .settingsSubItemsCol {
                min-width: 300px;
                max-width: 80vw;
            }
            h2 {
                font-size: 1em;
            }


        }

        @media (min-width:481px) {
            /* portrait e-readers (Nook/Kindle), smaller tablets @ 600 or @ 640 wide. */
        }

        @media (min-width:641px) {
            /* portrait tablets, portrait iPad, landscape e-readers, landscape 800x480 or 854x480 phones */
        }

        @media (min-width:961px) {
            /* tablet, landscape iPad, lo-res laptops ands desktops */
        }

        @media (min-width:1025px) {

            /* big landscape tablets, laptops, and desktops */
            .settingsItems {
                min-width: 400px;
                max-width: 400px;
            }
            .manButtons {
                column-gap: 5%;
                row-gap: 10px;
            }
            .manButtons div {
                margin-top: 0;
                margin-bottom: 0;
            }
            
            .settingsContainer {
                max-width: 400px;
            }

            #cancelContainer {
                width: 230px;
            }

            #barContainer {
                min-width: 30%;
                margin-bottom: 20px;
            }

            #rgbSliders {
                max-height: fit-content;
                row-gap: 4vh;
            }
        }

        @media (min-width:1281px) {

            /* hi-res laptops and desktops */
            #cancelContainer {
                width: 230px;
            }

            #barContainer {
                min-width: 30%;
                margin-bottom: 20px;
            }

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

            .controlsButtons:hover,
            .controlsButtons:focus {
                background: #4682B4 radial-gradient(circle, transparent 1%, #303030 1%) center/15000% !important;
            }

            .controlsButtons:active {
                background-color: #4682B4;
                background-size: 100%;
                transition: background 0s;
            }

            #cancel:hover,
            #cancel:focus {
                background: #701313 radial-gradient(circle, transparent 1%, #701313 1%) center/15000% !important;
            }

            #cancel:active {
                background-color: #701313;
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
                transition: background .1s;
            }

            .controlsButtons:focus {
                background: #4682B4 radial-gradient(circle, transparent 1%, #303030 1%) center/15000% !important;
            }

            .controlsButtons:active {
                background-color: #4682B4;
                background-size: 100%;
                transition: background .1s;
            }

            #cancel:focus {
                background: #701313 radial-gradient(circle, transparent 1%, #701313 1%) center/15000% !important;
            }

            #cancel:active {
                background-color: #701313;
                background-size: 100%;
                transition: background .1s;
            }
        }
    </style>
    <div id="appTitle">
        <div id="imgContainer">
            <img id="logo" src="https://cdn.shopify.com/s/files/1/0781/3146/2449/files/logoServita.png?v=1715475631" />
        </div>
    </div>
    <div id="appView" class="appView">
        <div id="pControls" class="appPage">
            <div id="titleControls" class="aPageTitle">
                <h2>
                    Pour a Drink
                </h2>
            </div>
            <div id="pourMenu" class="pourItems">
                <div class="settingsItems">
                    <div id="drink1Container" class="settingsSubItemsCol">
                        <button type="button" class="controlsButtons" id="drink1" style="width: 80%!important;">Drink 1
                        </button>
                        <div class="slidecontainer">
                            <label id="p1ValDisplay" for="p1Range">Pour Size: </label>
                            <input name="p1Range" type="range" min="0" max="20" value="10" class="slider" id="p1Range">
                        </div>
                    </div>
                </div>
                <div class="settingsItems">
                    <div id="drink2Container" class="settingsSubItemsCol">
                        <button type="button" class="controlsButtons" id="drink2" style="width: 80%!important;">Drink 2
                        </button>
                        <div class="slidecontainer">
                            <label id="p2ValDisplay" for="p2Range">Pour Size: </label>
                            <input name="p2Range" type="range" min="0" max="20" value="10" class="slider" id="p2Range">
                        </div>
                    </div>
                </div>
                <div class="settingsItems">
                    <div id="drink3Container" class="settingsSubItemsCol">
                        <button type="button" class="controlsButtons" id="drink3" style="width: 80%!important;">Drink 3
                        </button>
                        <div class="slidecontainer">
                            <label id="p3Val1Display" for="p3Range1">Pump 1 Amount: </label>
                            <input name="p3Range1" type="range" min="0" max="20" value="10" class="slider"
                                id="p3Range1">
                        </div>
                        <div class="slidecontainer">
                            <label id="p3Val2Display" for="p3Range2">Pump 2 Amount: </label>
                            <input name="p3Range2" type="range" min="0" max="20" value="10" class="slider"
                                id="p3Range2">
                        </div>
                    </div>
                </div>
                <div id="cancelContainer" class="settingsSubItemsCol">
                    <button type="button" class="controlsButtons" id="cancel">Cancel
                        Pour</button>
                </div>
            </div>
        </div>
        <div id="rgbPicker" class="appPage" style="display:none;">
            <div id="titleControls" class="aPageTitle">
                <h2>
                    Change LED Color
                </h2>
            </div>
            <div id="rbgPage" class="pourItems">

                <div class="settingsItems">
                    <div id="rgbDisplayContainer" class="settingsSubItemsCol">
                        <div id="display">
                        </div>
                    </div>
                </div>


                <div id="rgbSliders" class="settingsItems">
                    <div class="settingsSubItemsCol">
                        <label id="rLabel" for="red">Red</label>
                        <input type="range" class="slider" id="red" name="red" min="0" max="255" value="0">
                    </div>
                    <div class="settingsSubItemsCol">
                        <label id="gLabel" for="green">Green</label>
                        <input type="range" class="slider" id="green" name="green" min="0" max="255" value="0">
                    </div>
                    <div class="settingsSubItemsCol">
                        <label id="bLabel" for="blue">Blue</label>
                        <input type="range" class="slider" id="blue" name="blue" min="0" max="255" value="0">
                        <button type="button" class="controlsButtons" id="rgbSend" onclick="getRgbVal()">Confirm Color</button>
                    </div>
                    <div class="settingsSubItemsCol">
                        <label id="brightValDisplay" name="brightness">Brightness Level:</label>
                        <input name="brightness" type="range" min="0" max="255" value="127" class="slider"
                            id="brightness">
                        <button type="button" class="controlsButtons" id="brightSend" onclick="getBrightness()">Confirm
                            Brightness</button>
                    </div>

                </div>
            </div>


        </div>
        <div id="settings" class="appPage" style="display:none;">
           <div id="titleControls" class="aPageTitle">
                    <div>
                        <h2>Settings</h2>
                    </div>
            </div>
            <div class="settingsPage">
                <div id="lockUnlockContainer" class="settingsContainer">
                    <h3>Lock/Unlock Device</h3>
                    <div class="settingsItems">
                        <div id="luButtonContainer" class="settingsSubItemsRow">
                            <div class="settingsStatusContainer">
                                <p id="luStatus">Status: Unlocked</p>
                            </div>
                            <div style="text-align: center; width: 80%; align-self: center; justify-self: center;">
                                <button style="width: 80%; align-self: center; justify-self: center; position: center;"
                                    type="button" class="controlsButtons" id="uButton"
                                    onclick="unlocked()">Unlock</button>
                            </div>
                            <div style="text-align: center; width: 80%; align-self: center; justify-self: center;">
                                <button style="width: 80%; align-self: center; justify-self: center; position: center;"
                                    type="button" class="controlsButtons" id="lButton" onclick="locked()">Lock</button>
                            </div>
                        </div>
                    </div>
                </div>
                <div id="wifiControlsContainer" class="settingsContainer">
                    <div class="settingsSubTitle">
                        <h3>Change WiFi Credentials</h2>
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
                            <button type="button" class="controlsButtons" id="submitCredentials">Submit</button>
                        </div>
                    </div>
                </div>
                <div id="numLEDContainer" class="settingsContainer">
                    <div class="settingsSubTitle">
                        <h3>
                            Number Of LEDs
                        </h3>
                    </div>
                    <div id="inputForm" class="settingsItems">
                        <div>
                            <label for="lNum">LEDs: </label>
                            <input type="text" id="lNum" type="text" name="lnum" value="0" />
                        </div>
                        <div>
                            <button type="button" class="controlsButtons" id="ledButton">Submit</button>
                        </div>
             
                    </div>
                </div>
            </div>
        </div>
        <div id="manualControls" class="appPage" style="display:none;">

            <div>
                <h2>Manual Controls</h2>
            </div>
            <div class="manButtons">
                <div>
                    <button id="mCarUp" type="button" class="controlsButtons">Move
                        Carriage Up</button>
                </div>
                <div>
                    <button id="mCarDown" type="button" class="controlsButtons">Move
                        Carriage Down</button>
                </div>
                <div>
                    <button id="mCarHome" type="button" class="controlsButtons">Move
                        Carriage To Home Position</button>
                </div>

                <div>
                    <button id="rPump1" type="button" class="controlsButtons">Run Pump
                        1</button>
                </div>
                
                <div>
                    <button id="rPump2" type="button" class="controlsButtons">Run Pump
                        2</button>
                </div>
                
            </div>
        </div>
    </div>
        <div class="break" style="min-height: 5%"></div>
        <div id="appMenu">
            <div id="barContainer">
                <div id="main" class="menuButtonContainer">
                    <button id="goPour" class="menuButtons" onclick="menuController(pControls)">Pour Drink</button>
                </div>
                <div id="ledControl" class="menuButtonContainer">
                    <button id="goRGB" class="menuButtons" onclick="menuController(rgbPicker)">LED Color</button>
                </div>
                <div id="wireless" class="menuButtonContainer">
                    <button id="goManual" class="menuButtons" onclick="menuController(manualControls)">Manual
                        Controls</button>
                </div>
                <div id="deviceSettings" class="menuButtonContainer">
                    <button id="goSettings" class="menuButtons" onclick="menuController(settings)">Settings</button>
                </div>
            </div>
            <script type="text/javascript">
                const drink1Button = document.getElementById('drink1');
                const drink2Button = document.getElementById('drink2');
                const drink3Button = document.getElementById('drink3');
                const cancelButton = document.getElementById('cancel');
                const drink1Label = document.getElementById('d1Label');
                const drink2Label = document.getElementById('d2Label');
                const drink3Label = document.getElementById('d3Label');
                const p1ValDisplay = document.getElementById('p1ValDisplay')
                const p2ValDisplay = document.getElementById('p2ValDisplay')
                const p3Val1Display = document.getElementById('p3Val1Display');
                const p3Val2Display = document.getElementById('p3Val2Display');
                const p1Range = document.getElementById('p1Range');
                const p2Range = document.getElementById('p2Range');
                const p3Range1 = document.getElementById('p3Range1');
                const p3Range2 = document.getElementById('p3Range2')
                const pControls = document.getElementById('pControls');
                const rgbPicker = document.getElementById('rgbPicker');
                const manualControls = document.getElementById('manualControls');
                const settings = document.getElementById('settings');
                const red = document.getElementById('red');
                const green = document.getElementById('green');
                const blue = document.getElementById('blue');
                const display = document.getElementById('display');
                const brightSend = document.getElementById('brightSend');
                const rgbButton = document.getElementById('rgbSend')
                const rDisplay = document.getElementById('rLabel')
                const bDisplay = document.getElementById('bLabel')
                const gDisplay = document.getElementById('gLabel');
                const brightValDisplay = document.getElementById('brightValDisplay');
                const luStatus = document.getElementById('luStatus');
                const lButton = document.getElementById('lButton');
                const uButton = document.getElementById('uButton');
                const ledButton = document.getElementById('ledButton');
                const brightness = document.getElementById('brightness');
                const sendCredentials = document.getElementById('submitCredentials');
                const mCarUp = document.getElementById('mCarUp');
                const mCarDown = document.getElementById('mCarDown');
                const mCarHome = document.getElementById('mCarHome');
                const rPump1 = document.getElementById('rPump1');
                const rPump2 = document.getElementById('rPump2');

              
                var websocket;


                function initWebSocket() {
                        console.log('Trying to open a WebSocket connection...');
                        websocket = new WebSocket(`ws://${window.location.hostname}/ws`);
                        websocket.onopen = onOpen;
                        websocket.onclose = onClose;
                        // websocket.onmessage = onMessage; // <-- add this line
                    function onOpen(event) {
                        console.log('Connection opened');
                        initButton();
                    }
                    
                    function onClose(event) {
                        console.log('Connection closed');
                    }
                }
                

                function sendData(data) {
                    
                }
                    
                    
                    
            

                
                /*
                function initWebSocket(gateway) {
                    console.log('Trying to open a WebSocket connection...');
                    websocket = new WebSocket(gateway);
                    websocket.onopen = onOpen;
                    websocket.onclose = onClose;
                    // websocket.onmessage = onMessage; // <-- add this line
                }
                function onOpen(event) {
                    console.log('Connection opened');
                }
                function onClose(event) {
                    console.log('Connection closed');
                    setTimeout(initWebSocket, 2000);
                }
                */
                window.addEventListener('load', onLoad, false);
                function onLoad(event) {
                    initSliders(); 
                }
                function initButton() {                    
                drink1Button.addEventListener('click', function () { websocket.send('pour,drink1,' + p1Range.value + ',0,end') }, false);
                drink2Button.addEventListener('click', function () { websocket.send('pour,drink2,0,' + p2Range.value + ',end') }, false);
                drink3Button.addEventListener('click', function () { websocket.send('pour,drink3,' + p3Range1.value + ',' + p3Range2.value + ',end') }, false);
                cancelButton.addEventListener('click', function () { websocket.send('pour,pourCancel,0,0,end') }, false);
                rgbButton.addEventListener('click', function () { websocket.send('led,' + getRgbVal() +',end') }, false);
                brightSend.addEventListener('click', function () { websocket.send('brightnness,' + getBrightness() + ',end') }, false);
                mCarUp.addEventListener('mousedown', function () { websocket.send('manual,mCarUp,end'); console.log('mousedown event') }, false);
                mCarUp.addEventListener('mouseup', function () { websocket.send('manual,stop,end'); console.log('mouseup event') }, false);
                mCarUp.addEventListener('touchstart', function () { websocket.send('manual,mCarUp,end'); console.log('touchstart event') }, false);
                mCarUp.addEventListener('touchend', function () { websocket.send('manual,stop,end'); console.log('touchend event') }, false);
                mCarDown.addEventListener('mousedown', function () { websocket.send('manual,mCarDown,end'); console.log('mousedown event') }, false);
                mCarDown.addEventListener('mouseup', function () { websocket.send('manual,stop,end'); console.log('mouseup event') }, false);
                mCarDown.addEventListener('touchstart', function () { websocket.send('manual,mCarDown,end'); console.log('touchstart event') }, false);
                mCarDown.addEventListener('touchend', function () { websocket.send('manual,stop,end'); console.log('touchend event') }, false);
                rPump1.addEventListener('mousedown', function () { websocket.send('manual,start,rPump1,end'); console.log('mousedown event') }, false);
                rPump1.addEventListener('mouseup', function () { websocket.send('manual,stop,rPump1,end'); console.log('mouseup event'); }, false);
                rPump1.addEventListener('touchstart', function () { websocket.send('manual,start,rPump1,end'); console.log('touchstart event'); }, false);
                rPump1.addEventListener('touchend', function () { websocket.send('manual,stop,rPump1,end'); console.log('touchend event'); }, false);
                rPump2.addEventListener('mousedown', function () { websocket.send('manual,start,rPump2,end'); console.log('mousedown event'); }, false);
                rPump2.addEventListener('mouseup', function () { websocket.send('manual,stop,rPump2,end'); console.log('mouseup event') }, false);
                rPump2.addEventListener('touchstart', function () { websocket.send('manual,start,rPump2,end'); console.log('touchstart event'); }, false);
                rPump2.addEventListener('touchend', function () { websocket.send('manual,stop,rPump2,end'); console.log('touchend event'); }, false);
                mCarHome.addEventListener('click', function () { websocket.send('manual,mCarHome,end') }, false);
                sendCredentials.addEventListener('click', function () {
                    const ssid = document.getElementById('ssid')
                    const pass = document.getElementById('pass')
                    websocket.send('net,' + ssid.value + ',' + pass.value + ',end');
                }, false)
                lButton.addEventListener('click', function () { websocket.send('lock,lock,end'), false });
                uButton.addEventListener('click', function () { websocket.send('lock,unlock,end'), false })
                ledButton.addEventListener('click', function () {
                    const ledNum = document.getElementById('lNum');
                    websocket.send('lnum', ledNum.value, + ',end');
                }, false)
                    


                }
                /*
                function sendData(gateway, data) {
                    initWebSocket(gateway, data);
                }
                */
                function p3ValueSafety(pToAdj, pUserAdj) {
                    const sum = parseInt(pUserAdj.value) + parseInt(pToAdj.value);
                    if (sum > 20) {
                        pToAdj.value = 20 - pUserAdj.value;
                    }
                }
                function initSliders() {
                    displaySliderVals();
                    setColor();
                    p3Range1.oninput = function () {
                        displaySliderVals();
                        p3ValueSafety(p3Range2, p3Range1);
                    }
                    p3Range2.oninput = function () {
                        displaySliderVals();
                        p3ValueSafety(p3Range1, p3Range2);
                    }
                    p1Range.oninput = function () {
                        displaySliderVals();
                    }
                    p2Range.oninput = function () {
                        setColor();
                        displaySliderVals()
                    }
                    brightness.oninput = function () {
                        setColor();
                        displaySliderVals()
                    }
                    red.oninput = function () {
                        setColor();
                        displaySliderVals();
                    }
                    green.oninput = function () {
                        setColor();
                        displaySliderVals();
                    }
                    blue.oninput = function () {
                        setColor();
                        displaySliderVals();
                    }
                }
                function displaySliderVals() {
                    p1ValDisplay.innerHTML = "Pour Size: " + p1Range.value;
                    p2ValDisplay.innerHTML = "Pour Size: " + p2Range.value;
                    p3Val1Display.innerHTML = "Pump 1 Amount: " + p3Range1.value;
                    p3Val2Display.innerHTML = "Pump 2 Amount: " + p3Range2.value;
                    brightValDisplay.innerHTML = "Brightness Level: " + brightness.value;
                    rDisplay.innerHTML = "Red Value: " + red.value;
                    gDisplay.innerHTML = "Green Value: " + green.value;
                    bDisplay.innerHTML = "Blue Value: " + blue.value;
                }
                function sendPourSizeVals() {
                }
                function setColor() {
                    display.style.backgroundColor = `rgb(${red.value}, ${green.value}, ${blue.value})`;
                    display.style.boxShadow = `0 0 1.5em rgba(${red.value}, ${green.value}, ${blue.value}, .5)`;
                }
                function getRgbVal() {
                    return red.value + ',' + green.value + ',' + blue.value;
                }
                function getBrightness() {
                    return brightness.value;
                }
                function locked() {
                    luStatus.innerText = "Status: Locked"
                }
                function unlocked() {
                    luStatus.innerText = "Status: Unlocked"
                }
                function currentPage() {
                    const menuItems = [
                        pControls,
                        rgbPicker,
                        manualControls,
                        settings
                    ];
                    let activePage = ""
                    for (i = 0; i < menuItems.length; i++) {
                        if (menuItems[i].getAttribute('style') == null) {
                            return menuItems[i]
                        }
                    }
                    return activePage;
                }
                function menuController(selection) {
                    console.log('button clicked')
                    let cPage = currentPage();
                    console.log(cPage)
                    if (cPage == null) {
                        return console.log('something went wrong');
                        console.log()
                    }
                    if (selection == cPage) {
                        return
                    }
                    else {
                        cPage.setAttribute('style', 'display:none');
                        selection.removeAttribute('style');
                    }
                }
                function changeDrinkName(drink, name) {
                    let drinkNum;
                    if (drink == 'drink1') {
                        drinkNum = "1"
                        drink = drink1Label
                    }
                    if (drink == 'drink2') {
                        drinkNum = "2"
                        drink = drink2Label
                    }
                    if (drink == 'drink3') {
                        drinkNum = "3"
                        drink = drink3Label
                    }
                    drink.innerHTML = name;
                    return console.log('Drink ' + drinkNum + ' name changed to: ', name + '.');
                }
                initWebSocket();
            </script>
</body>

</html>

)rawliteral";