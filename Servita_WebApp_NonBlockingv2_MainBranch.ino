// Version 1.1.12 - May 27, 2024
//    Created from Dan's Blynk code as a starting point.
//    Removed all Blynk integration.
//    Rewrote most mechanical operations to be non-blocking and controlled by flags.
//    Limit switches now operate primarily via hardware interrupts.
//    Serial commands created for operation and hardware debug.

#include <FastLED.h>
#include <SerialCommand.h>

#include <string.h>
#include <stdlib.h>



// WebApp Libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// #include <ESPmDNS.h> -> testing a different method
#include <DNSServer.h>
#include <Preferences.h>

//Webapp Config
const byte DNS_PORT = 53;
AsyncWebServer server(80);
DNSServer dnsServer;

// AP SSID - for captive
Preferences preferences;
const char *ssid = "Servita";

// Web App
const char index_html[] PROGMEM = R"rawliteral(
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


// Captive Portal
const char captivePage[] PROGMEM = R"rawliteral(
      <html>
        <head>
            <meta name="viewport" content="width=device-width, initial-scale=1">
        </head>
        <body>
            <style>
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
                    align-items: center;
                    justify-items: center;
                    margin-bottom: 80px;
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
                    flex-grow: 1;
                }
              #content {
                display: grid;
                margin-top: 100px;
                    text-align: right;
                    align-content: center;
                    justify-content: center;
                    height: 200px;
                    flex-grow: 1;
                }
            </style>
          <div id="appTitle">
            <div id="imgContainer">
                <svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg"
                    xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" width="100%" viewBox="0 0 1883 372"
                    enable-background="new 0 0 1883 372" xml:space="preserve">
                    <path fill="#0C0C0C" opacity="1.000000" stroke="none" d="
                        M1383.000000,373.000000 
                            C922.050964,373.000000 461.601929,373.000000 1.076456,373.000000 
                            C1.076456,249.064743 1.076456,125.129410 1.076456,1.097044 
                            C628.666687,1.097044 1256.333374,1.097044 1883.971924,1.097044 
                            C1883.971924,125.064957 1883.971924,249.032486 1883.971924,373.000000 
                            C1717.129150,373.000000 1550.314575,373.000000 1383.000000,373.000000 
                        M123.802849,53.269215 
                            C114.552376,56.491917 105.197968,59.448162 96.078156,63.005810 
                            C85.061661,67.303360 74.333710,72.324043 65.605904,80.596039 
                            C56.322807,89.394341 56.272411,99.311203 66.521729,106.832222 
                            C73.370811,111.858124 81.278709,115.853348 89.262497,118.840660 
                            C110.238823,126.689430 132.288986,130.153809 154.410233,133.022659 
                            C160.868607,133.860229 167.353928,134.489792 174.238235,135.260773 
                            C170.746399,119.380135 167.421219,104.460640 164.198059,89.519135 
                            C162.388840,81.132263 165.542358,75.933731 173.821915,74.861534 
                            C198.031662,71.726395 222.215591,67.761681 246.540451,66.301872 
                            C278.394745,64.390221 310.378967,63.818451 342.298553,64.025528 
                            C383.598907,64.293480 424.669250,68.371613 465.470917,74.895493 
                            C471.876770,75.919731 475.746765,81.545258 474.465332,88.002953 
                            C473.559418,92.568306 472.498688,97.102875 471.512390,101.652344 
                            C469.354034,111.608604 467.199097,121.565605 464.846619,132.427979 
                            C478.260468,131.233170 490.880157,130.492035 503.392670,128.905563 
                            C522.540466,126.477829 541.627502,123.312851 559.277161,115.002571 
                            C564.891968,112.358902 570.382935,108.776794 574.832214,104.485382 
                            C582.277588,97.304230 581.974609,87.932365 574.620544,80.614456 
                            C571.118774,77.129898 567.234131,73.537437 562.821838,71.551949 
                            C548.931396,65.301468 535.039307,58.734249 520.550842,54.195049 
                            C482.011292,42.120609 442.229004,36.060295 402.135406,31.869913 
                            C361.661743,27.639809 321.108917,26.281401 280.474487,28.521900 
                            C227.691620,31.432243 175.560684,38.628483 123.802849,53.269215 
                        M732.959351,184.627243 
                            C728.055664,183.739532 723.144897,182.889084 718.249756,181.956497 
                            C707.612061,179.929886 696.775513,178.062256 688.265991,170.779709 
                            C685.343567,168.278641 682.891785,164.291870 681.975403,160.554642 
                            C678.999390,148.417770 686.193726,134.983948 698.236511,130.153564 
                            C711.591797,124.796722 725.275330,124.950584 738.591614,130.390884 
                            C746.214050,133.504974 751.085815,139.643524 753.586609,147.476273 
                            C754.426147,150.105453 754.704346,152.913864 755.231079,155.599243 
                            C768.888794,155.599243 782.328613,155.599243 796.076477,155.599243 
                            C796.076477,154.562317 796.134583,153.760910 796.068054,152.970016 
                            C793.921875,127.467529 781.937988,108.175201 759.124634,96.367699 
                            C739.255005,86.083733 717.964539,84.997627 696.365417,89.149887 
                            C661.804321,95.793961 639.851807,121.439613 638.835205,155.826706 
                            C637.942810,186.014435 651.748596,205.870911 680.606506,214.951340 
                            C690.089844,217.935379 699.960388,219.686096 709.648438,222.023331 
                            C720.765747,224.705383 732.317078,226.278076 742.886475,230.378006 
                            C758.250366,236.337769 762.228333,253.207870 751.866394,266.102112 
                            C748.498535,270.293060 743.397278,273.578339 738.443176,275.900238 
                            C729.632812,280.029449 719.930481,279.490326 710.435608,278.997467 
                            C690.731995,277.974701 680.746521,269.354462 676.815063,250.211624 
                            C662.766968,250.211624 648.718872,250.211624 634.379395,250.211624 
                            C635.467285,276.076477 646.394958,295.697723 669.050842,307.808990 
                            C690.922058,319.500732 714.490417,320.799438 738.509766,316.958008 
                            C778.935547,310.492767 802.535400,281.434601 799.833191,241.673538 
                            C798.248413,218.355316 786.943542,201.671265 764.992371,193.335159 
                            C754.960022,189.525314 744.217590,187.585541 732.959351,184.627243 
                        M367.382568,159.003403 
                            C397.215820,160.655045 426.925018,163.359879 456.730103,168.844284 
                            C451.893158,191.252518 447.207092,212.961853 442.282684,235.775375 
                            C455.280762,234.463989 467.522614,233.506500 479.685883,231.939102 
                            C499.845184,229.341339 519.910156,225.899811 538.698486,217.822937 
                            C545.431946,214.928314 551.895691,210.705322 557.413574,205.868958 
                            C563.722900,200.338837 563.810547,192.454437 558.083374,186.284332 
                            C554.079895,181.971176 549.340759,177.749466 544.084229,175.309418 
                            C531.775391,169.595688 519.261047,163.962219 506.294128,160.090775 
                            C447.490570,142.534134 386.992950,136.297272 325.910858,135.274902 
                            C283.886810,134.571503 242.090363,138.245224 200.640015,145.204376 
                            C169.793167,150.383286 139.240356,156.923096 110.180389,168.946732 
                            C99.414864,173.401016 88.693581,178.158066 80.948219,187.385345 
                            C75.255783,194.166916 75.286530,201.217712 82.150795,206.680984 
                            C87.896339,211.253860 94.546074,215.150909 101.395012,217.792908 
                            C124.050392,226.532288 147.957977,229.997513 171.905655,233.005646 
                            C179.890839,234.008698 187.916580,234.688812 196.508560,235.577011 
                            C191.560516,213.472916 186.823761,192.312683 182.019775,170.852173 
                            C243.342865,159.275024 304.667664,155.924301 367.382568,159.003403 
                        M872.098267,310.425079 
                            C880.712097,312.813416 889.191406,316.356567 897.964417,317.378540 
                            C926.922607,320.751862 953.681274,315.347534 975.679932,294.550262 
                            C984.184143,286.510498 990.561829,277.026764 994.860596,265.488373 
                            C983.351868,265.488373 972.537659,265.737152 961.742310,265.392334 
                            C955.550964,265.194580 950.126587,265.607391 945.830811,270.962006 
                            C944.059265,273.170135 941.063416,274.534332 938.419617,275.880066 
                            C927.492554,281.442200 915.730591,282.002899 903.862305,280.900696 
                            C883.952209,279.051636 866.722473,262.998566 864.310730,244.014801 
                            C910.076904,244.014801 955.786133,244.014801 1001.840576,244.014801 
                            C1001.840576,238.256973 1001.963562,232.952789 1001.818542,227.655960 
                            C1001.280823,208.012161 996.058105,189.751297 983.702026,174.295593 
                            C960.703247,145.527298 929.608826,137.069870 894.768616,142.721619 
                            C852.095520,149.643997 826.025879,178.162872 821.661011,221.070969 
                            C817.970337,257.352264 834.260742,293.533112 872.098267,310.425079 
                        M1807.840454,257.500061 
                            C1807.567505,244.350052 1808.239990,231.097580 1806.828491,218.070953 
                            C1803.699585,189.195663 1790.148926,166.402313 1764.152710,152.225327 
                            C1745.412964,142.005707 1725.084961,139.278305 1704.132935,142.082092 
                            C1675.228760,145.950058 1652.434082,159.644287 1638.008911,185.575806 
                            C1628.033813,203.507217 1625.983276,222.891022 1627.846924,243.095352 
                            C1631.077026,278.110718 1654.992920,307.229279 1689.053955,315.574432 
                            C1711.937866,321.181152 1734.285522,319.815826 1753.416260,304.261139 
                            C1760.021484,298.890594 1764.939087,291.444336 1770.616211,284.959137 
                            C1770.616211,294.172638 1770.616211,304.010193 1770.616211,313.703735 
                            C1783.350220,313.703735 1795.442383,313.703735 1807.840454,313.703735 
                            C1807.840454,295.104156 1807.840454,276.802155 1807.840454,257.500061 
                        M1470.827759,124.499939 
                            C1470.827759,167.164185 1470.778442,209.828522 1470.844116,252.492661 
                            C1470.892456,283.887299 1486.325317,306.505341 1513.401367,314.772034 
                            C1527.516602,319.081573 1542.009888,319.434326 1556.420898,316.926361 
                            C1594.912842,310.227600 1610.384399,280.008270 1607.949585,245.059799 
                            C1594.690186,245.059799 1581.424438,245.059799 1568.110352,245.059799 
                            C1567.729126,249.564545 1567.507202,253.861557 1566.978027,258.120422 
                            C1565.529663,269.778687 1558.832642,276.974030 1547.184692,279.601959 
                            C1534.887817,282.376282 1521.873901,278.209625 1516.215820,269.567932 
                            C1515.136841,267.920135 1514.087891,266.073669 1513.708740,264.181885 
                            C1512.766968,259.481445 1511.662231,254.708008 1511.610474,249.953171 
                            C1511.385742,229.290115 1511.513916,208.623215 1511.513794,187.957703 
                            C1511.513794,186.363144 1511.513794,184.768570 1511.513794,182.731049 
                            C1540.675659,182.731049 1569.256958,182.731049 1597.863770,182.731049 
                            C1597.863770,170.205139 1597.863770,158.137665 1597.863770,145.608521 
                            C1568.988159,145.608521 1540.418823,145.608521 1511.371094,145.608521 
                            C1511.371094,126.725967 1511.371094,108.304108 1511.371094,89.765823 
                            C1497.636230,89.765823 1484.388550,89.765823 1470.827759,89.765823 
                            C1470.827759,101.197365 1470.827759,112.348648 1470.827759,124.499939 
                        M116.021118,295.148956 
                            C118.368813,298.436768 120.140198,302.477386 123.207314,304.825470 
                            C127.211281,307.890717 132.011078,310.549011 136.871628,311.747986 
                            C153.622437,315.880066 170.485962,319.629578 187.432968,322.862061 
                            C196.655701,324.621216 206.133636,325.042419 215.892151,326.110352 
                            C211.776520,307.188751 207.827835,289.034698 203.782425,270.435913 
                            C280.867554,256.367676 357.481018,256.918701 434.613861,270.338898 
                            C430.490662,289.350555 426.523804,307.641266 422.501587,326.187317 
                            C424.036621,326.331085 425.024475,326.593811 425.970490,326.486664 
                            C440.011749,324.896545 454.127289,323.750275 468.062561,321.494293 
                            C482.654602,319.131989 497.117706,315.761353 510.317108,308.665527 
                            C526.856934,299.773895 527.719238,287.529449 511.489044,278.184967 
                            C500.520325,271.869781 488.493073,266.850128 476.352173,263.208405 
                            C425.440399,247.937134 373.004669,242.308243 320.113342,242.495758 
                            C291.912933,242.595749 263.629456,245.310074 235.558060,248.420120 
                            C207.632919,251.513977 179.983780,257.084076 153.573212,267.029175 
                            C142.960480,271.025482 132.953537,276.792908 123.039764,282.405792 
                            C118.885300,284.757935 115.866570,288.904388 116.021118,295.148956 
                        M1235.339844,170.105362 
                            C1232.857544,163.058960 1230.461548,155.979843 1227.813354,148.996338 
                            C1227.336914,147.740158 1225.834473,145.984238 1224.783813,145.968994 
                            C1210.830933,145.766556 1196.874268,145.833862 1182.163574,145.833862 
                            C1204.325317,202.276382 1226.254150,258.125824 1248.193604,314.002106 
                            C1263.031860,314.002106 1277.525513,313.806763 1292.007690,314.126648 
                            C1296.109619,314.217255 1297.684570,312.804382 1299.095215,309.179535 
                            C1315.829102,266.183502 1332.747437,223.259232 1349.604248,180.311066 
                            C1354.057251,168.965622 1358.466187,157.602814 1362.967896,146.061554 
                            C1348.122803,146.061554 1333.834839,146.061554 1319.481567,146.061554 
                            C1304.152588,189.099976 1288.889038,231.954529 1273.560425,274.991486 
                            C1272.890869,274.437592 1272.503540,274.279358 1272.409912,274.016571 
                            C1260.165283,239.615143 1247.942017,205.206116 1235.339844,170.105362 
                        M1035.923706,177.434708 
                            C1030.800293,187.575928 1028.366943,198.490479 1028.261475,209.690277 
                            C1027.937744,244.009903 1028.068359,278.333832 1028.049072,312.656097 
                            C1028.048828,313.084106 1028.400269,313.512329 1028.495117,313.729309 
                            C1041.959595,313.729309 1055.224243,313.729309 1068.839600,313.729309 
                            C1068.839600,311.670868 1068.836792,309.868988 1068.839722,308.067108 
                            C1068.893311,275.576538 1068.640991,243.081451 1069.119141,210.597122 
                            C1069.397095,191.712982 1079.340942,181.587036 1098.041382,179.343811 
                            C1118.008179,176.948685 1132.342529,187.953903 1134.776855,207.650101 
                            C1135.180176,210.912613 1135.161743,214.227264 1135.348633,217.713669 
                            C1148.760620,217.713669 1161.966431,217.713669 1175.657349,217.713669 
                            C1175.424805,212.782822 1175.475830,208.127838 1174.943237,203.540558 
                            C1172.245972,180.303848 1162.923218,161.055893 1141.287109,149.717316 
                            C1127.977417,142.742294 1113.487427,140.623734 1098.681519,141.229172 
                            C1071.846680,142.326508 1049.209595,151.194504 1035.923706,177.434708 
                        M1406.502686,145.829544 
                            C1401.413086,145.829544 1396.323486,145.829544 1391.196045,145.829544 
                            C1391.196045,202.149887 1391.196045,257.871643 1391.196045,313.707397 
                            C1404.770996,313.707397 1418.146240,313.707397 1431.597290,313.707397 
                            C1431.597290,257.700348 1431.597290,201.988342 1431.597290,145.829544 
                            C1423.408447,145.829544 1415.454834,145.829544 1406.502686,145.829544 
                        M1399.618164,73.951416 
                            C1388.690308,79.573708 1383.587036,88.728668 1384.301147,100.787224 
                            C1384.973877,112.147629 1392.779785,121.600410 1403.144287,124.739098 
                            C1413.696167,127.934547 1425.224365,124.594147 1432.096069,116.350143 
                            C1439.762939,107.152252 1440.403564,92.747116 1433.585571,82.862175 
                            C1426.314209,72.320198 1413.788696,68.842079 1399.618164,73.951416 
                        z" />
                    <path fill="#FDFDFD" opacity="1.000000" stroke="none" d="
                        M124.191963,53.166542 
                            C175.560684,38.628483 227.691620,31.432243 280.474487,28.521900 
                            C321.108917,26.281401 361.661743,27.639809 402.135406,31.869913 
                            C442.229004,36.060295 482.011292,42.120609 520.550842,54.195049 
                            C535.039307,58.734249 548.931396,65.301468 562.821838,71.551949 
                            C567.234131,73.537437 571.118774,77.129898 574.620544,80.614456 
                            C581.974609,87.932365 582.277588,97.304230 574.832214,104.485382 
                            C570.382935,108.776794 564.891968,112.358902 559.277161,115.002571 
                            C541.627502,123.312851 522.540466,126.477829 503.392670,128.905563 
                            C490.880157,130.492035 478.260468,131.233170 464.846619,132.427979 
                            C467.199097,121.565605 469.354034,111.608604 471.512390,101.652344 
                            C472.498688,97.102875 473.559418,92.568306 474.465332,88.002953 
                            C475.746765,81.545258 471.876770,75.919731 465.470917,74.895493 
                            C424.669250,68.371613 383.598907,64.293480 342.298553,64.025528 
                            C310.378967,63.818451 278.394745,64.390221 246.540451,66.301872 
                            C222.215591,67.761681 198.031662,71.726395 173.821915,74.861534 
                            C165.542358,75.933731 162.388840,81.132263 164.198059,89.519135 
                            C167.421219,104.460640 170.746399,119.380135 174.238235,135.260773 
                            C167.353928,134.489792 160.868607,133.860229 154.410233,133.022659 
                            C132.288986,130.153809 110.238823,126.689430 89.262497,118.840660 
                            C81.278709,115.853348 73.370811,111.858124 66.521729,106.832222 
                            C56.272411,99.311203 56.322807,89.394341 65.605904,80.596039 
                            C74.333710,72.324043 85.061661,67.303360 96.078156,63.005810 
                            C105.197968,59.448162 114.552376,56.491917 124.191963,53.166542 
                        z" />
                    <path fill="#FDFDFD" opacity="1.000000" stroke="none" d="
                        M733.378296,184.712433 
                            C744.217590,187.585541 754.960022,189.525314 764.992371,193.335159 
                            C786.943542,201.671265 798.248413,218.355316 799.833191,241.673538 
                            C802.535400,281.434601 778.935547,310.492767 738.509766,316.958008 
                            C714.490417,320.799438 690.922058,319.500732 669.050842,307.808990 
                            C646.394958,295.697723 635.467285,276.076477 634.379395,250.211624 
                            C648.718872,250.211624 662.766968,250.211624 676.816772,250.211792 
                            C680.746521,269.354462 690.731995,277.974701 710.435608,278.997467 
                            C719.930481,279.490326 729.632812,280.029449 738.443176,275.900238 
                            C743.397278,273.578339 748.498535,270.293060 751.866394,266.102112 
                            C762.228333,253.207870 758.250366,236.337769 742.886475,230.378006 
                            C732.317078,226.278076 720.765747,224.705383 709.648438,222.023331 
                            C699.960388,219.686096 690.089844,217.935379 680.606506,214.951340 
                            C651.748596,205.870911 637.942810,186.014435 638.835205,155.826706 
                            C639.851807,121.439613 661.804321,95.793961 696.365417,89.149887 
                            C717.964539,84.997627 739.255005,86.083733 759.124634,96.367699 
                            C781.937988,108.175201 793.921875,127.467529 796.068054,152.970016 
                            C796.134583,153.760910 796.076477,154.562317 796.076477,155.599243 
                            C782.328613,155.599243 768.888794,155.599243 755.231079,155.599243 
                            C754.704346,152.913864 754.426147,150.105453 753.586609,147.476273 
                            C751.085815,139.643524 746.214050,133.504974 738.591614,130.390884 
                            C725.275330,124.950584 711.591797,124.796722 698.236511,130.153564 
                            C686.193726,134.983948 678.999390,148.417770 681.975403,160.554642 
                            C682.891785,164.291870 685.343567,168.278641 688.265991,170.779709 
                            C696.775513,178.062256 707.612061,179.929886 718.249756,181.956497 
                            C723.144897,182.889084 728.055664,183.739532 733.378296,184.712433 
                        z" />
                    <path fill="#FDFDFD" opacity="1.000000" stroke="none" d="
                        M366.898132,159.002777 
                            C304.667664,155.924301 243.342865,159.275024 182.019775,170.852173 
                            C186.823761,192.312683 191.560516,213.472916 196.508560,235.577011 
                            C187.916580,234.688812 179.890839,234.008698 171.905655,233.005646 
                            C147.957977,229.997513 124.050392,226.532288 101.395012,217.792908 
                            C94.546074,215.150909 87.896339,211.253860 82.150795,206.680984 
                            C75.286530,201.217712 75.255783,194.166916 80.948219,187.385345 
                            C88.693581,178.158066 99.414864,173.401016 110.180389,168.946732 
                            C139.240356,156.923096 169.793167,150.383286 200.640015,145.204376 
                            C242.090363,138.245224 283.886810,134.571503 325.910858,135.274902 
                            C386.992950,136.297272 447.490570,142.534134 506.294128,160.090775 
                            C519.261047,163.962219 531.775391,169.595688 544.084229,175.309418 
                            C549.340759,177.749466 554.079895,181.971176 558.083374,186.284332 
                            C563.810547,192.454437 563.722900,200.338837 557.413574,205.868958 
                            C551.895691,210.705322 545.431946,214.928314 538.698486,217.822937 
                            C519.910156,225.899811 499.845184,229.341339 479.685883,231.939102 
                            C467.522614,233.506500 455.280762,234.463989 442.282684,235.775375 
                            C447.207092,212.961853 451.893158,191.252518 456.730103,168.844284 
                            C426.925018,163.359879 397.215820,160.655045 366.898132,159.002777 
                        z" />
                    <path fill="#FDFDFD" opacity="1.000000" stroke="none" d="
                        M871.752808,310.265930 
                            C834.260742,293.533112 817.970337,257.352264 821.661011,221.070969 
                            C826.025879,178.162872 852.095520,149.643997 894.768616,142.721619 
                            C929.608826,137.069870 960.703247,145.527298 983.702026,174.295593 
                            C996.058105,189.751297 1001.280823,208.012161 1001.818542,227.655960 
                            C1001.963562,232.952789 1001.840576,238.256973 1001.840576,244.014801 
                            C955.786133,244.014801 910.076904,244.014801 864.310730,244.014801 
                            C866.722473,262.998566 883.952209,279.051636 903.862305,280.900696 
                            C915.730591,282.002899 927.492554,281.442200 938.419617,275.880066 
                            C941.063416,274.534332 944.059265,273.170135 945.830811,270.962006 
                            C950.126587,265.607391 955.550964,265.194580 961.742310,265.392334 
                            C972.537659,265.737152 983.351868,265.488373 994.860596,265.488373 
                            C990.561829,277.026764 984.184143,286.510498 975.679932,294.550262 
                            C953.681274,315.347534 926.922607,320.751862 897.964417,317.378540 
                            C889.191406,316.356567 880.712097,312.813416 871.752808,310.265930 
                        M933.139343,182.182693 
                            C932.514954,181.958664 931.888794,181.739517 931.266479,181.509888 
                            C910.283264,173.767090 886.684937,179.154068 873.712524,194.733322 
                            C869.592346,199.681473 866.632202,205.245117 864.995667,211.671005 
                            C896.419617,211.671005 927.208740,211.671005 958.611694,211.671005 
                            C954.578918,197.973083 946.393677,188.425415 933.139343,182.182693 
                        z" />
                    <path fill="#FDFDFD" opacity="1.000000" stroke="none" d="
                        M1807.840454,258.000092 
                            C1807.840454,276.802155 1807.840454,295.104156 1807.840454,313.703735 
                            C1795.442383,313.703735 1783.350220,313.703735 1770.616211,313.703735 
                            C1770.616211,304.010193 1770.616211,294.172638 1770.616211,284.959137 
                            C1764.939087,291.444336 1760.021484,298.890594 1753.416260,304.261139 
                            C1734.285522,319.815826 1711.937866,321.181152 1689.053955,315.574432 
                            C1654.992920,307.229279 1631.077026,278.110718 1627.846924,243.095352 
                            C1625.983276,222.891022 1628.033813,203.507217 1638.008911,185.575806 
                            C1652.434082,159.644287 1675.228760,145.950058 1704.132935,142.082092 
                            C1725.084961,139.278305 1745.412964,142.005707 1764.152710,152.225327 
                            C1790.148926,166.402313 1803.699585,189.195663 1806.828491,218.070953 
                            C1808.239990,231.097580 1807.567505,244.350052 1807.840454,258.000092 
                        M1688.936646,187.366180 
                            C1675.583496,196.765701 1669.174805,209.997498 1668.388428,225.956146 
                            C1667.396118,246.099228 1673.377808,263.611786 1691.830933,273.753021 
                            C1710.213501,283.855408 1729.442505,283.474152 1747.126709,271.660065 
                            C1768.060547,257.675110 1773.601562,223.224380 1759.330322,200.762894 
                            C1745.153931,178.450684 1713.667480,172.230301 1688.936646,187.366180 
                        z" />
                    <path fill="#FDFDFD" opacity="1.000000" stroke="none" d="
                        M1470.827759,123.999939 
                            C1470.827759,112.348648 1470.827759,101.197365 1470.827759,89.765823 
                            C1484.388550,89.765823 1497.636230,89.765823 1511.371094,89.765823 
                            C1511.371094,108.304108 1511.371094,126.725967 1511.371094,145.608521 
                            C1540.418823,145.608521 1568.988159,145.608521 1597.863770,145.608521 
                            C1597.863770,158.137665 1597.863770,170.205139 1597.863770,182.731049 
                            C1569.256958,182.731049 1540.675659,182.731049 1511.513794,182.731049 
                            C1511.513794,184.768570 1511.513794,186.363144 1511.513794,187.957703 
                            C1511.513916,208.623215 1511.385742,229.290115 1511.610474,249.953171 
                            C1511.662231,254.708008 1512.766968,259.481445 1513.708740,264.181885 
                            C1514.087891,266.073669 1515.136841,267.920135 1516.215820,269.567932 
                            C1521.873901,278.209625 1534.887817,282.376282 1547.184692,279.601959 
                            C1558.832642,276.974030 1565.529663,269.778687 1566.978027,258.120422 
                            C1567.507202,253.861557 1567.729126,249.564545 1568.110352,245.059799 
                            C1581.424438,245.059799 1594.690186,245.059799 1607.949585,245.059799 
                            C1610.384399,280.008270 1594.912842,310.227600 1556.420898,316.926361 
                            C1542.009888,319.434326 1527.516602,319.081573 1513.401367,314.772034 
                            C1486.325317,306.505341 1470.892456,283.887299 1470.844116,252.492661 
                            C1470.778442,209.828522 1470.827759,167.164185 1470.827759,123.999939 
                        z" />
                    <path fill="#FCFCFC" opacity="1.000000" stroke="none" d="
                        M116.009575,294.746460 
                            C115.866570,288.904388 118.885300,284.757935 123.039764,282.405792 
                            C132.953537,276.792908 142.960480,271.025482 153.573212,267.029175 
                            C179.983780,257.084076 207.632919,251.513977 235.558060,248.420120 
                            C263.629456,245.310074 291.912933,242.595749 320.113342,242.495758 
                            C373.004669,242.308243 425.440399,247.937134 476.352173,263.208405 
                            C488.493073,266.850128 500.520325,271.869781 511.489044,278.184967 
                            C527.719238,287.529449 526.856934,299.773895 510.317108,308.665527 
                            C497.117706,315.761353 482.654602,319.131989 468.062561,321.494293 
                            C454.127289,323.750275 440.011749,324.896545 425.970490,326.486664 
                            C425.024475,326.593811 424.036621,326.331085 422.501587,326.187317 
                            C426.523804,307.641266 430.490662,289.350555 434.613861,270.338898 
                            C357.481018,256.918701 280.867554,256.367676 203.782425,270.435913 
                            C207.827835,289.034698 211.776520,307.188751 215.892151,326.110352 
                            C206.133636,325.042419 196.655701,324.621216 187.432968,322.862061 
                            C170.485962,319.629578 153.622437,315.880066 136.871628,311.747986 
                            C132.011078,310.549011 127.211281,307.890717 123.207314,304.825470 
                            C120.140198,302.477386 118.368813,298.436768 116.009575,294.746460 
                        z" />
                    <path fill="#FEFEFE" opacity="1.000000" stroke="none" d="
                        M1235.528809,170.451385 
                            C1247.942017,205.206116 1260.165283,239.615143 1272.409912,274.016571 
                            C1272.503540,274.279358 1272.890869,274.437592 1273.560425,274.991486 
                            C1288.889038,231.954529 1304.152588,189.099976 1319.481567,146.061554 
                            C1333.834839,146.061554 1348.122803,146.061554 1362.967896,146.061554 
                            C1358.466187,157.602814 1354.057251,168.965622 1349.604248,180.311066 
                            C1332.747437,223.259232 1315.829102,266.183502 1299.095215,309.179535 
                            C1297.684570,312.804382 1296.109619,314.217255 1292.007690,314.126648 
                            C1277.525513,313.806763 1263.031860,314.002106 1248.193604,314.002106 
                            C1226.254150,258.125824 1204.325317,202.276382 1182.163574,145.833862 
                            C1196.874268,145.833862 1210.830933,145.766556 1224.783813,145.968994 
                            C1225.834473,145.984238 1227.336914,147.740158 1227.813354,148.996338 
                            C1230.461548,155.979843 1232.857544,163.058960 1235.528809,170.451385 
                        z" />
                    <path fill="#FDFDFD" opacity="1.000000" stroke="none" d="
                        M1036.025513,177.073700 
                            C1049.209595,151.194504 1071.846680,142.326508 1098.681519,141.229172 
                            C1113.487427,140.623734 1127.977417,142.742294 1141.287109,149.717316 
                            C1162.923218,161.055893 1172.245972,180.303848 1174.943237,203.540558 
                            C1175.475830,208.127838 1175.424805,212.782822 1175.657349,217.713669 
                            C1161.966431,217.713669 1148.760620,217.713669 1135.348633,217.713669 
                            C1135.161743,214.227264 1135.180176,210.912613 1134.776855,207.650101 
                            C1132.342529,187.953903 1118.008179,176.948685 1098.041382,179.343811 
                            C1079.340942,181.587036 1069.397095,191.712982 1069.119141,210.597122 
                            C1068.640991,243.081451 1068.893311,275.576538 1068.839722,308.067108 
                            C1068.836792,309.868988 1068.839600,311.670868 1068.839600,313.729309 
                            C1055.224243,313.729309 1041.959595,313.729309 1028.495117,313.729309 
                            C1028.400269,313.512329 1028.048828,313.084106 1028.049072,312.656097 
                            C1028.068359,278.333832 1027.937744,244.009903 1028.261475,209.690277 
                            C1028.366943,198.490479 1030.800293,187.575928 1036.025513,177.073700 
                        z" />
                    <path fill="#FEFEFE" opacity="1.000000" stroke="none" d="
                        M1407.001953,145.829544 
                            C1415.454834,145.829544 1423.408447,145.829544 1431.597290,145.829544 
                            C1431.597290,201.988342 1431.597290,257.700348 1431.597290,313.707397 
                            C1418.146240,313.707397 1404.770996,313.707397 1391.196045,313.707397 
                            C1391.196045,257.871643 1391.196045,202.149887 1391.196045,145.829544 
                            C1396.323486,145.829544 1401.413086,145.829544 1407.001953,145.829544 
                        z" />
                    <path fill="#FCFCFC" opacity="1.000000" stroke="none" d="
                        M1399.967529,73.787659 
                            C1413.788696,68.842079 1426.314209,72.320198 1433.585571,82.862175 
                            C1440.403564,92.747116 1439.762939,107.152252 1432.096069,116.350143 
                            C1425.224365,124.594147 1413.696167,127.934547 1403.144287,124.739098 
                            C1392.779785,121.600410 1384.973877,112.147629 1384.301147,100.787224 
                            C1383.587036,88.728668 1388.690308,79.573708 1399.967529,73.787659 
                        z" />
                    <path fill="#101010" opacity="1.000000" stroke="none" d="
                        M933.475281,182.366882 
                            C946.393677,188.425415 954.578918,197.973083 958.611694,211.671005 
                            C927.208740,211.671005 896.419617,211.671005 864.995667,211.671005 
                            C866.632202,205.245117 869.592346,199.681473 873.712524,194.733322 
                            C886.684937,179.154068 910.283264,173.767090 931.266479,181.509888 
                            C931.888794,181.739517 932.514954,181.958664 933.475281,182.366882 
                        z" />
                    <path fill="#0D0D0D" opacity="1.000000" stroke="none" d="
                        M1689.245605,187.172165 
                            C1713.667480,172.230301 1745.153931,178.450684 1759.330322,200.762894 
                            C1773.601562,223.224380 1768.060547,257.675110 1747.126709,271.660065 
                            C1729.442505,283.474152 1710.213501,283.855408 1691.830933,273.753021 
                            C1673.377808,263.611786 1667.396118,246.099228 1668.388428,225.956146 
                            C1669.174805,209.997498 1675.583496,196.765701 1689.245605,187.172165 
                        z" />
                </svg>
            </div>
        </div>
        <div id="content">
            <h2>Setup WiFi</h2>
            <form action="/setWiFi" method="POST">
                <label for="ssid">SSID: </label>
                <input type="text" name="ssid"><br> <br>
                <label for="password">Password: </label>
                <input type="password" name="password"><br>
                <br>
            
                <input type="submit" value="Connect">
                </form>

        </div>

            </body>

    </html>
    )rawliteral";






#define userButton 32       // Dispense Button
#define limitSwitchHigh 34  // Top Limit Switch
#define limitSwitchLow 35   // Bottom Limit Switch
#define boardLED 2          // User LED

#define LED_PIN 4    // External RGB LED Data Pin
#define NUM_LEDS 48  // Number of LEDs on External LED Array

#define motor1In1 17  // Motor Driver Control Pins
#define motor1In2 5   //
#define motor1En1 16  // \
                      //
#define motor2In3 19  //
#define motor2In4 21  //
#define motor2En2 18  // \
                      //
#define motor3In5 15  //
#define motor3In6 13  //
#define motor3En3 12  // \
                      //
#define duoButton 27  //
#define ExtIO2 26     //
#define ExtIO3 25     //

// Flags & variables used by non-blocking dispense function
bool dispenseInProgress = false;
bool carraigeDownStarted = false;
bool carraigeReachedBottom = false;
bool drinkPouringStarted = false;
bool drinkPouringComplete = false;
bool carraigeUpStarted = false;
bool carraigeReachedTop = false;
bool elevatorMovingDown = false;
bool elevatorMovingUp = false;
bool pump1running = false;
bool pump2running = false;
unsigned long pour_start_time;
unsigned long current_time;
int pourSize[] = { 3000, 3000, 1500, 1500 };
int drinkVariant;
bool deviceLockout = false;

// Flags used by limit switch interrupt
bool endStopHighTrigger = false;
bool endStopLowTrigger = false;

// State variables used for hardware inputs
uint8_t userButtonState;
uint8_t limitSwitchHighState;
uint8_t limitSwitchLowState;
uint8_t duoButtonState;

// Variables used for external LED array control FastLED Library
int ledBrightness = 255;
const int ledMax = 255;
const int ledMin = 75;
int fadeFlag = 0;
CRGB leds[NUM_LEDS];


//Forward definition - Prototyping
void drink1();
void drink2();
void drink3();
void cancelDispense();
void abortDispense();
void motor2down();
void motor2up();
void motor2stop();
void pump1start();
void pump1stop();
void pump2start();
void pump2stop();
void dispenseDrink();
void resetDispenseFlags();
void setPourSize(int pourOption, int time);
void printPourSizes();
void serial_setPourSize();
void serial_setDeviceLockout();
void printButtons();
void readButtons();

SerialCommand sCmd;  // Constructor for serialCommand handler

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("What?");
}

// Functions called by limit switch interrupt. endStopHighTrigger and endStopLowTrigger flags are used in main loop to perform stop action.
void IRAM_ATTR endStopHigh() {
  endStopHighTrigger = true;
}
void IRAM_ATTR endStopLow() {
  endStopLowTrigger = true;
}

// WebApp Integration
// AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// CaptivePortal Function
void startCaptivePortal() {
  Serial.println("Starting Captive Portal");

  // Start the AP with no password
  WiFi.softAP(ssid, "");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(IP);

  dnsServer.start(53, "*", IP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.print("User Connected");
    request->send_P(200, "text/html", captivePage);
  });

  server.on("/setWiFi", HTTP_POST, [](AsyncWebServerRequest *request) {
    String ssid;
    String pass;
    if (request->hasParam("ssid", true) && request->hasParam("password", true)) {
      String ssid = request->getParam("ssid", true)->value();
      String pass = request->getParam("password", true)->value();
      preferences.putString("ssid", ssid);
      preferences.putString("pass", pass);
      request->send(200, "text/plain", "Received SSID: " + ssid + "\nPassword: " + pass);
      delay(3000);
      ESP.restart();  // Restart ESP to connect with new credentials
      // Optionally connect to WiFi or save credentials here
    } else {
      request->send(400, "text/plain", "Invalid Request");
    }
  });

  server.begin();
}

char *trim(char *str) {
  char *end;
  // Trim leading space
  while (isspace((unsigned char)*str)) str++;
  if (*str == 0)  // All spaces?
    return str;
  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end)) end--;
  // Write new null terminator
  end[1] = '\0';
  return str;
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket client disconnected");
  } else if (type == WS_EVT_DATA) {
    Serial.print("Data received: ");
    Serial.println(String((char *)data));
    String receivedData = String((char *)data);


    // Tokenize the data
    std::vector<char *> parts;
    char *token = strtok((char *)data, ",");
    while (token != NULL) {
      token = trim(token);
      parts.push_back(token);
      token = strtok(NULL, ",");
    }

  
    if (parts.size() == 5 && strcmp(parts[0], "pour") == 0) {
      if (strcmp(parts[0], "pour") == 0) {
        // Handle pour-related actions
        int size1Val = atoi(parts[1]);
        int size2Val = atoi(parts[2]);

        int s1Mult = size1Val * 1000;
        int s2Mult = size2Val * 1000;
        if (strcmp(parts[1], "drink1") == 0) {
          Serial.println("Pouring Drink 1");
          setPourSize(1, s1Mult);
          drink1();
        } else if (strcmp(parts[1], "drink2") == 0) {
          Serial.println("Pouring Drink 2");
          setPourSize(2, s2Mult);
          drink2();
        } else if (strcmp(parts[1], "drink3") == 0) {
          Serial.println("Pouring Drink 3");
          setPourSize(1, s1Mult);
          setPourSize(2, s2Mult);
          drink3();
        } else if (strcmp(parts[1], "pourCancel") == 0) {
          Serial.println("User Cancel");
          cancelDispense();
        }
      }
    } else if (parts.size() == 3 && strcmp(parts[0], "manual") == 0) {
      if (strcmp(parts[1], "mCarUp") == 0) {
        motor2up();
      } else if (strcmp(parts[1], "mCarDown") == 0) {
        motor2down();
      } else if (strcmp(parts[1], "stop") == 0) {
        motor2stop();
      } else if (strcmp(parts[1], "mCarHome") == 0) {
        motor2up();
      }
    } else if (parts.size() == 4 && strcmp(parts[1], "start") == 0) {

      if (strcmp(parts[2], "rPump1") == 0) {
        pump1start();
      } else if (strcmp(parts[2], "rPump2")) {
        pump2start();
      }

    } else if (parts.size() == 4 && strcmp(parts[1], "stop") == 0) {
      if (strcmp(parts[2], "rPump1") == 0) {
        pump1stop();
      } else if (strcmp(parts[2], "rPump2") == 0) {
        pump2stop();
      }
    } else if (parts.size() == 3 && strcmp(parts[0], "net") == 0) {

      preferences.putString("ssid", parts[1]);
      preferences.putString("pass", parts[2]);

      ESP.restart();
    } else if (parts.size() == 3 && strcmp(parts[0], "lock") == 0) {
      if (strcmp(parts[1], "lock") == 0) {
        deviceLockout = true;
      } else if (strcmp(parts[1], "unlock")) {
        deviceLockout = false;
      }
    } else if (parts.size() == 3 && strcmp(parts[0], "lnum") == 0) {
      // rgb locgic here | Number of ext LEDS

    } else if (parts.size() == 5 && strcmp(parts[0], "led") == 0) {
      // RGB Logic here | colors for EXT LED
    } else if (parts.size() == 3 && strcmp(parts[0], "brightness") == 0) {
      // brightness logic here (ext lED)
    }

    else {
      Serial.println("Insufficient data received");
    }
  }
  Serial.println();
}


void initWebSocket() {
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
}
void connectToWiFi(const char *ssid, const char *pass) {
  WiFi.setHostname("servita.local");  // Set the desired hostname here
  WiFi.begin(ssid, pass);

  Serial.print("Connecting to WiFi..");
  int maxAttempts = 10;  // Maximum number of attempts to connect to WiFi
  int attempt = 0;

  while (WiFi.status() != WL_CONNECTED && attempt < maxAttempts) {
    delay(500);
    Serial.print(".");
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    // setupmDNS();
    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // Start server to serve HTML page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send_P(200, "text/html", index_html);
    });
    server.begin();
  } else {
    Serial.println("Failed to connect to WiFi. Please check credentials.");
    // Optionally restart the Captive Portal to re-enter credentials
    startCaptivePortal();
  }
}

//mDNS Code - To be resolved
/* 
void setupmDNS() {
  // Set up mDNS responder:
  // - first argument is the domain name, in this example
  //   the fully-qualified domain name is "esp32.local"
  // - second argument is the IP address to advertise
  //   we send our IP address on the WiFi network
  if (!MDNS.begin("servita")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
}
*/

void setup() {
  Serial.begin(115200);
  preferences.begin("wifi", false);
  String ssid = preferences.getString("ssid", "");
  String pass = preferences.getString("pass", "");


  if (ssid == "" || pass == "") {
    startCaptivePortal();
  } else {
    connectToWiFi(ssid.c_str(), pass.c_str());
  }

  delay(100);
  // Create serial commands and limk them to functions
  sCmd.addCommand("drink1", drink1);
  sCmd.addCommand("drink2", drink2);
  sCmd.addCommand("drink3", drink3);
  sCmd.addCommand("poursize", serial_setPourSize);
  sCmd.addCommand("printpoursizes", printPourSizes);
  sCmd.addCommand("lock", serial_setDeviceLockout);
  sCmd.addCommand("down", motor2down);
  sCmd.addCommand("up", motor2up);
  sCmd.addCommand("s", motor2stop);
  sCmd.addCommand("read", printButtons);
  sCmd.addCommand("cancel", cancelDispense);
  sCmd.addCommand("x", abortDispense);
  sCmd.setDefaultHandler(unrecognized);

  // Set all motor control pins to output
  pinMode(motor1In1, OUTPUT);
  pinMode(motor1In2, OUTPUT);
  pinMode(motor1En1, OUTPUT);
  pinMode(motor2In3, OUTPUT);
  pinMode(motor2In4, OUTPUT);
  pinMode(motor2En2, OUTPUT);
  pinMode(motor3In5, OUTPUT);
  pinMode(motor3In6, OUTPUT);
  pinMode(motor3En3, OUTPUT);

  // Set initial off states for motor outputs
  digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor1En1, LOW);
  digitalWrite(motor2In3, LOW);
  digitalWrite(motor2In4, LOW);
  digitalWrite(motor2En2, LOW);
  digitalWrite(motor3In5, LOW);
  digitalWrite(motor3In6, LOW);
  digitalWrite(motor3En3, LOW);

  // Set hardware input pin configurations
  pinMode(limitSwitchLow, INPUT);
  pinMode(limitSwitchHigh, INPUT);
  pinMode(userButton, INPUT_PULLUP);
  pinMode(duoButton, INPUT_PULLUP);

  // Create interrupts for both limit switches
  attachInterrupt(limitSwitchHigh, endStopHigh, FALLING);
  attachInterrupt(limitSwitchLow, endStopLow, FALLING);

  // Send elevator to the top if not already there
  if (digitalRead(limitSwitchHigh) == 1) motor2up();
  // WebApp - Start WebSocket
  initWebSocket();
  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });
  server.begin();
}

void loop() {
  sCmd.readSerial();               // We don't do much, just process serial commands
  dnsServer.processNextRequest();  // wifi related


  // Response to limit switch hardware interrupt
  if (endStopHighTrigger && elevatorMovingUp) {
    motor2stop();
    endStopHighTrigger = false;
    Serial.println("endStopHigh");
  }
  if (endStopLowTrigger && elevatorMovingDown) {
    motor2stop();
    endStopLowTrigger = false;
    Serial.println("endStopLow");
  }

  if (dispenseInProgress) dispenseDrink();  // Dispense routine gets called repeatedly when dispenseInProgress flag is high

  readButtons();  // Read inputs on every loop

  // Clean up socket connections
  ws.cleanupClients();
}

// Serial Command Handler to set pour size
void serial_setPourSize() {
  setPourSize(atoi(sCmd.next()), atoi(sCmd.next()));
  printPourSizes();
}

// Serial Command Handler to set lockout state
void serial_setDeviceLockout() {
  deviceLockout = atoi(sCmd.next());
  Serial.println("Lockout State: " + String(deviceLockout));
}

// Set each pour size in ms.
void setPourSize(int pourOption, int time) {
  pourSize[pourOption] = time;
}

// Function to initiate dispense of drink 1. Requires lockout state to be 0 to operate.
void drink1() {
  if (!deviceLockout) {
    drinkVariant = 1;
    dispenseDrink();
  } else Serial.println("Device Lockout Enabled. Dispense Command Rejected.");
}

// Function to initiate dispense of drink 2. Requires lockout state to be 0 to operate.
void drink2() {
  if (!deviceLockout) {
    drinkVariant = 2;
    dispenseDrink();
  } else Serial.println("Device Lockout Enabled. Dispense Command Rejected.");
}

// Function to initiate dispense of drink 3 (mix from both pumps). Requires lockout state to be 0 to operate.
void drink3() {
  if (!deviceLockout) {
    drinkVariant = 3;
    dispenseDrink();
  } else Serial.println("Device Lockout Enabled. Dispense Command Rejected.");
}

// Soft termination of dispense function. Will stop pumps and return elevator to the top position.
void cancelDispense() {
  resetDispenseFlags();
  pump1stop();
  pump2stop();
  motor2up();
}

// Hard termination of dispense function. Will stop pumps and motors in place.
void abortDispense() {
  resetDispenseFlags();
  pump1stop();
  pump2stop();
  motor2stop();
}

// Reads hardware input pins.
void readButtons() {
  limitSwitchHighState = digitalRead(limitSwitchHigh);
  limitSwitchLowState = digitalRead(limitSwitchLow);
  userButtonState = digitalRead(userButton);
  duoButtonState = digitalRead(duoButton);
}

// Prints state of input pins to serial console.
void printButtons() {
  Serial.println("limitSwitchHighState: " + String(limitSwitchHighState));
  Serial.println("limitSwitchLowState: " + String(limitSwitchLowState));
  Serial.println("userButtonState: " + String(userButtonState));
  Serial.println("duoButtonState: " + String(duoButtonState));
}

// Prints current pour size setting to serial console.
void printPourSizes() {
  Serial.println("pour size 0 = " + String(pourSize[0]));
  Serial.println("pour size 1 = " + String(pourSize[1]));
  Serial.println("pour size 2 = " + String(pourSize[2]));
  Serial.println("pour size 3 = " + String(pourSize[3]));
}

// Non/blocking function responsible for initiating, timing, and stopping drink pour.
void pourDrink() {
  if (drinkPouringStarted == false) {
    switch (drinkVariant) {
      case 1:
        pump1start();
        break;
      case 2:
        pump2start();
        break;
      case 3:
        pump1start();
        pump2start();
        break;
    }
    drinkPouringStarted = true;
    pour_start_time = millis();
  } else if (drinkPouringStarted == true && drinkPouringComplete == false) {
    unsigned long current_time = millis();
    switch (drinkVariant) {
      case 1:
        if (current_time - pour_start_time > pourSize[0]) pump1stop();
        break;
      case 2:
        if (current_time - pour_start_time > pourSize[1]) pump2stop();
        break;
      case 3:
        if (current_time - pour_start_time > pourSize[2]) pump1stop();
        if (current_time - pour_start_time > pourSize[3]) pump2stop();
        break;
    }
    if (pump1running == false && pump2running == false) {
      drinkPouringComplete = true;
    }
  }
}

// Resets flags used in the dispense function. Called at the end of dispense function, and by cancel & abort funcitons.
void resetDispenseFlags() {
  dispenseInProgress = false;
  carraigeDownStarted = false;
  carraigeReachedBottom = false;
  drinkPouringStarted = false;
  drinkPouringComplete = false;
  carraigeUpStarted = false;
  carraigeReachedTop = false;
}

// Non/blocking function responsible for choreographing elevator and pumps for main dispensing feature
void dispenseDrink() {
  dispenseInProgress = true;
  if (carraigeDownStarted == false) {
    motor2down();
    Serial.println("carraige lowering");
    carraigeDownStarted = true;
  }
  if (carraigeDownStarted == true && limitSwitchLowState == 0 && carraigeReachedBottom == false) {
    carraigeReachedBottom = true;
    Serial.println("carraige reached bottom");
  }
  if (carraigeReachedBottom == true && drinkPouringComplete == false) {
    pourDrink();
  }
  if (drinkPouringComplete == true && carraigeUpStarted == false) {
    motor2up();
    carraigeUpStarted = true;
    Serial.println("carraige raising");
  }
  if (carraigeUpStarted == true && limitSwitchHighState == 0 && carraigeReachedTop == false) {
    carraigeReachedTop = true;
    Serial.println("carraige reached top");
  }
  if (carraigeReachedTop == true) {
    resetDispenseFlags();
  }
}

// Sets elevator motor in downward motion
void motor2down() {
  digitalWrite(motor2In3, HIGH);
  digitalWrite(motor2In4, LOW);
  digitalWrite(motor2En2, HIGH);
  elevatorMovingDown = true;
  elevatorMovingUp = false;
  Serial.println("down");
}

// Sets elevator motor in upward motion
void motor2up() {
  digitalWrite(motor2In3, LOW);
  digitalWrite(motor2In4, HIGH);
  digitalWrite(motor2En2, HIGH);
  elevatorMovingDown = false;
  elevatorMovingUp = true;
  Serial.println("up");
}

// Stops elevator motor
void motor2stop() {
  digitalWrite(motor2In3, LOW);
  digitalWrite(motor2In4, LOW);
  digitalWrite(motor2En2, HIGH);
  elevatorMovingDown = false;
  elevatorMovingUp = false;
  Serial.println("stop");
}

// Starts Pump 1
void pump1start() {
  digitalWrite(motor1In1, HIGH);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor1En1, HIGH);
  pump1running = true;
  Serial.println("pump 1 start");
}

// Stops Pump 1
void pump1stop() {
  digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor1En1, HIGH);
  pump1running = false;
  Serial.println("pump 1 stop");
}

// Starts Pump 2
void pump2start() {
  digitalWrite(motor3In5, HIGH);
  digitalWrite(motor3In6, LOW);
  digitalWrite(motor3En3, HIGH);
  pump2running = true;
  Serial.println("pump 2 start");
}

// Stops Pump 2
void pump2stop() {
  digitalWrite(motor3In5, LOW);
  digitalWrite(motor3In6, LOW);
  digitalWrite(motor3En3, HIGH);
  pump2running = false;
  Serial.println("pump 2 stop");
}
