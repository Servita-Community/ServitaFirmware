const char main_html[] PROGMEM = R"rawliteral(
<html>

<head>
    <title>Servita</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" type="image/svg+xml" href="data:image/svg+xml;base64,PHN2ZyB2aWV3Qm94PSIwIDAgMTgxIDE4MSIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+CiAgPGRlZnM+CiAgICA8c3R5bGU+CiAgICAgIC5jbHMtMSB7CiAgICAgICAgZmlsbDogdXJsKCNsaW5lYXItZ3JhZGllbnQpOwogICAgICAgIHN0cm9rZTogIzIzMWYyMDsKICAgICAgICBzdHJva2UtbWl0ZXJsaW1pdDogMTA7CiAgICAgIH0KCiAgICAgIC5jbHMtMiB7CiAgICAgICAgZmlsbDogI2ZkZmVmZjsKICAgICAgfQoKICAgICAgLmNscy0yLCAuY2xzLTMgewogICAgICAgIHN0cm9rZS13aWR0aDogMHB4OwogICAgICB9CgogICAgICAuY2xzLTMgewogICAgICAgIGZpbGw6ICNmZmY7CiAgICAgIH0KICAgIDwvc3R5bGU+CiAgICA8bGluZWFyR3JhZGllbnQgZ3JhZGllbnRVbml0cz0idXNlclNwYWNlT25Vc2UiIHkyPSIxMTguMzQiIHgyPSIxMTkuNTMiIHkxPSIxOS42OCIgeDE9IjE2LjY2IiBpZD0ibGluZWFyLWdyYWRpZW50Ij4KICAgICAgPHN0b3Agc3RvcC1jb2xvcj0iIzI2MjYyNiIgb2Zmc2V0PSIwIj48L3N0b3A+CiAgICAgIDxzdG9wIHN0b3AtY29sb3I9IiMyMzFmMjAiIG9mZnNldD0iMSI+PC9zdG9wPgogICAgPC9saW5lYXJHcmFkaWVudD4KICA8L2RlZnM+CiAgPGcgZGF0YS1zYW5pdGl6ZWQtZGF0YS1uYW1lPSJMYXllciAyIiBkYXRhLW5hbWU9IkxheWVyIDIiIGlkPSJMYXllcl8yIj4KICAgIDxyZWN0IGhlaWdodD0iMTgwIiB3aWR0aD0iMTgwIiB5PSIuNSIgeD0iLjUiIGNsYXNzPSJjbHMtMSI+PC9yZWN0PgogIDwvZz4KICA8ZyBkYXRhLXNhbml0aXplZC1kYXRhLW5hbWU9IkxheWVyIDEiIGRhdGEtbmFtZT0iTGF5ZXIgMSIgaWQ9IkxheWVyXzEiPgogICAgPHBhdGggZD0iTTM2LjI5LDU2LjE0YzE0LjI1LTQuMDMsMjguNzItNi4wMyw0My4zNi02Ljg0LDExLjI3LS42MiwyMi41My0uMjQsMzMuNzYuOTMsMTEuMTIsMS4xNiwyMi4xNiwyLjg0LDMyLjg2LDYuMTksNC4wMiwxLjI2LDcuODcsMy4wOCwxMS43Myw0LjgyLDEuMjIuNTUsMi4zLDEuNTUsMy4yNywyLjUxLDIuMDQsMi4wMywyLjEyLDQuNjMuMDYsNi42Mi0xLjIzLDEuMTktMi43NiwyLjE4LTQuMzIsMi45Mi00LjksMi4zMS0xMC4xOSwzLjE4LTE1LjUxLDMuODYtMy40Ny40NC02Ljk3LjY1LTEwLjcuOTguNjUtMy4wMSwxLjI1LTUuNzgsMS44NS04LjU0LjI3LTEuMjYuNTctMi41Mi44Mi0zLjc5LjM2LTEuNzktLjcyLTMuMzUtMi41LTMuNjQtMTEuMzItMS44MS0yMi43Mi0yLjk0LTM0LjE4LTMuMDItOC44Ni0uMDYtMTcuNzMuMS0yNi41Ny42My02Ljc1LjQxLTEzLjQ2LDEuNTEtMjAuMTgsMi4zOC0yLjMuMy0zLjE3LDEuNzQtMi42Nyw0LjA3Ljg5LDQuMTUsMS44Miw4LjI5LDIuNzksMTIuNjktMS45MS0uMjEtMy43MS0uMzktNS41LS42Mi02LjE0LS44LTEyLjI2LTEuNzYtMTguMDgtMy45NC0yLjIyLS44My00LjQxLTEuOTQtNi4zMS0zLjMzLTIuODQtMi4wOS0yLjgzLTQuODQtLjI1LTcuMjgsMi40Mi0yLjMsNS40LTMuNjksOC40Ni00Ljg4LDIuNTMtLjk5LDUuMTMtMS44MSw3LjgtMi43M1oiIGNsYXNzPSJjbHMtMyI+PC9wYXRoPgogICAgPHBhdGggZD0iTTEwMy42NCw4NS41MWMtMTcuMjctLjg1LTM0LjI4LjA4LTUxLjMsMy4yOSwxLjMzLDUuOTUsMi42NSwxMS44Myw0LjAyLDE3Ljk2LTIuMzgtLjI1LTQuNjEtLjQ0LTYuODMtLjcxLTYuNjQtLjgzLTEzLjI4LTEuOC0xOS41Ni00LjIyLTEuOS0uNzMtMy43NS0xLjgxLTUuMzQtMy4wOC0xLjktMS41Mi0xLjkxLTMuNDctLjMzLTUuMzUsMi4xNS0yLjU2LDUuMTItMy44OCw4LjExLTUuMTIsOC4wNi0zLjM0LDE2LjU0LTUuMTUsMjUuMS02LjU5LDExLjUtMS45MywyMy4xLTIuOTUsMzQuNzYtMi43NiwxNi45NS4yOCwzMy43MywyLjAxLDUwLjA1LDYuODksMy42LDEuMDcsNy4wNywyLjY0LDEwLjQ5LDQuMjIsMS40Ni42OCwyLjc3LDEuODUsMy44OCwzLjA1LDEuNTksMS43MSwxLjU2LDMuOS0uMTksNS40My0xLjUzLDEuMzQtMy4zMiwyLjUxLTUuMTksMy4zMi01LjIxLDIuMjQtMTAuNzgsMy4yLTE2LjM3LDMuOTItMy4zNy40My02Ljc3LjctMTAuMzgsMS4wNiwxLjM3LTYuMzMsMi42Ny0xMi4zNSw0LjAxLTE4LjU3LTguMjctMS41Mi0xNi41MS0yLjI3LTI0LjkzLTIuNzNaIiBjbGFzcz0iY2xzLTMiPjwvcGF0aD4KICAgIDxwYXRoIGQ9Ik0zNC4wMiwxMjMuMThjLS4wNC0xLjYyLjgtMi43NywxLjk1LTMuNDIsMi43NS0xLjU2LDUuNTMtMy4xNiw4LjQ3LTQuMjcsNy4zMy0yLjc2LDE1LTQuMzEsMjIuNzUtNS4xNiw3Ljc5LS44NiwxNS42NC0xLjYyLDIzLjQ2LTEuNjQsMTQuNjgtLjA1LDI5LjIzLDEuNTEsNDMuMzUsNS43NSwzLjM3LDEuMDEsNi43MSwyLjQsOS43NSw0LjE2LDQuNSwyLjU5LDQuMjYsNS45OS0uMzMsOC40Ni0zLjY2LDEuOTctNy42OCwyLjktMTEuNzIsMy41Ni0zLjg3LjYzLTcuNzguOTQtMTEuNjgsMS4zOS0uMjYuMDMtLjU0LS4wNC0uOTYtLjA4LDEuMTItNS4xNSwyLjIyLTEwLjIyLDMuMzYtMTUuNS0yMS40LTMuNzItNDIuNjYtMy44OC02NC4wNS4wMywxLjEyLDUuMTYsMi4yMiwxMC4yLDMuMzYsMTUuNDUtMi43MS0uMy01LjM0LS40MS03LjktLjktNC43LS45LTkuMzgtMS45NC0xNC4wMy0zLjA4LTEuMzUtLjMzLTIuNjgtMS4wNy0zLjc5LTEuOTItLjg1LS42NS0xLjM0LTEuNzctMi0yLjhaIiBjbGFzcz0iY2xzLTIiPjwvcGF0aD4KICA8L2c+Cjwvc3ZnPg==" />
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
            <img id="logo" src="data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4KPCFET0NUWVBFIHN2ZyBQVUJMSUMgIi0vL1czQy8vRFREIFNWRyAxLjEvL0VOIiAiaHR0cDovL3d3dy53My5vcmcvR3JhcGhpY3MvU1ZHLzEuMS9EVEQvc3ZnMTEuZHRkIj4KPHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZlcnNpb249IjEuMSIgd2lkdGg9Ijc4NDZweCIgaGVpZ2h0PSIxNTUxcHgiIHN0eWxlPSJzaGFwZS1yZW5kZXJpbmc6Z2VvbWV0cmljUHJlY2lzaW9uOyB0ZXh0LXJlbmRlcmluZzpnZW9tZXRyaWNQcmVjaXNpb247IGltYWdlLXJlbmRlcmluZzpvcHRpbWl6ZVF1YWxpdHk7IGZpbGwtcnVsZTpldmVub2RkOyBjbGlwLXJ1bGU6ZXZlbm9kZCIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiPgo8Zz48cGF0aCBzdHlsZT0ib3BhY2l0eTowLjk5OSIgZmlsbD0iIzBjMGMwYyIgZD0iTSAtMC41LC0wLjUgQyAyNjE0LjgzLC0wLjUgNTIzMC4xNywtMC41IDc4NDUuNSwtMC41QyA3ODQ1LjUsNTE2LjUgNzg0NS41LDEwMzMuNSA3ODQ1LjUsMTU1MC41QyA1MjMwLjE3LDE1NTAuNSAyNjE0LjgzLDE1NTAuNSAtMC41LDE1NTAuNUMgLTAuNSwxMDMzLjUgLTAuNSw1MTYuNSAtMC41LC0wLjUgWiIvPjwvZz4KPGc+PHBhdGggc3R5bGU9Im9wYWNpdHk6MSIgZmlsbD0iI2ZjZmNmYyIgZD0iTSAxMjgwLjUsMTA5LjUgQyAxNDkzLjAxLDEwOC4xODIgMTcwNC4wMSwxMjUuMzQ4IDE5MTMuNSwxNjFDIDIwMTEuNywxNzcuOTY2IDIxMDguMDMsMjAyLjI5OSAyMjAyLjUsMjM0QyAyMjUwLjQxLDI1Mi45NyAyMjk3Ljc0LDI3My4zMDQgMjM0NC41LDI5NUMgMjM2OC4wNywzMDguNTYxIDIzODcuOSwzMjYuMzk0IDI0MDQsMzQ4LjVDIDI0MTcuOTMsMzc0LjI1OCAyNDE2LjI3LDM5OC45MjUgMjM5OSw0MjIuNUMgMjM3NC4wNCw0NDguOTExIDIzNDQuNTQsNDY4Ljc0NCAyMzEwLjUsNDgyQyAyMjY3Ljg3LDQ5OS4zMjYgMjIyMy44Nyw1MTEuOTkzIDIxNzguNSw1MjBDIDIxNTIuMjYsNTI0LjU3MiAyMTI1LjkzLDUyOC41NzIgMjA5OS41LDUzMkMgMjA0My45LDUzNy45OTUgMTk4OC4yMyw1NDMuMTYxIDE5MzIuNSw1NDcuNUMgMTk0Ni40LDQ4Mi4zODMgMTk2MC4wNyw0MTcuMjE3IDE5NzMuNSwzNTJDIDE5NzEuNzEsMzI4LjM5IDE5NTkuMzcsMzEzLjcyNCAxOTM2LjUsMzA4QyAxNzExLjk4LDI3MS4wOTggMTQ4NS45OCwyNTYuMDk4IDEyNTguNSwyNjNDIDExNjEuMzYsMjY0LjI2NyAxMDY0LjM2LDI2OC42IDk2Ny41LDI3NkMgODgxLjkzNiwyODUuMjIzIDc5Ni42MDMsMjk2LjIyMyA3MTEuNSwzMDlDIDY4Ni42MTEsMzE1LjU3NCA2NzUuNDQ0LDMzMS43NCA2NzgsMzU3LjVDIDY5Mi41MDUsNDI0Ljg1IDcwNy4wMDUsNDkyLjE4MyA3MjEuNSw1NTkuNUMgNjM2LjA3Miw1NTEuNTU4IDU1MS40MDUsNTM4LjcyNSA0NjcuNSw1MjFDIDQxMi4wMDIsNTA4LjcyNSAzNTkuMDAyLDQ4OS43MjUgMzA4LjUsNDY0QyAyODcuNzM5LDQ1My4yNDYgMjY5LjIzOSw0MzkuNDEzIDI1Myw0MjIuNUMgMjM3LjQ3LDQwMC4yMTkgMjM2LjQ3LDM3Ny4yMTkgMjUwLDM1My41QyAyNjUuOTk2LDMzMS44MzcgMjg1LjQ5NiwzMTQuMDA0IDMwOC41LDMwMEMgMzQzLjM2NCwyNzkuMjM2IDM4MC4wMzEsMjYyLjIzNiA0MTguNSwyNDlDIDUwMi45NTEsMjE3Ljk3MSA1ODkuMjg1LDE5My42MzcgNjc3LjUsMTc2QyA4MjcuMzQ3LDE0NS4wMTkgOTc4LjY4LDEyNS4wMTkgMTEzMS41LDExNkMgMTE4MS4yOSwxMTIuOTczIDEyMzAuOTYsMTEwLjgwNiAxMjgwLjUsMTA5LjUgWiIvPjwvZz4KPGc+PHBhdGggc3R5bGU9Im9wYWNpdHk6MSIgZmlsbD0iI2ZiZmJmYiIgZD0iTSA1ODY0LjUsMjkzLjUgQyA1OTIyLjE4LDI5MC4zOTQgNTk2MS42OCwzMTUuMzk0IDU5ODMsMzY4LjVDIDU5OTMuOTQsNDA2LjY5NiA1OTg4LjYsNDQyLjM2MyA1OTY3LDQ3NS41QyA1OTM1LjI0LDUxMy4xOTkgNTg5NS4wNyw1MjcuMDMyIDU4NDYuNSw1MTdDIDU3OTkuMzEsNTAyLjE0NSA1NzcxLjgxLDQ3MC4zMTEgNTc2NCw0MjEuNUMgNTc1OS4wNiwzNjEuODQ3IDU3ODQuMjMsMzIxLjAxNCA1ODM5LjUsMjk5QyA1ODQ3Ljk3LDI5Ny4xNTEgNTg1Ni4zLDI5NS4zMTggNTg2NC41LDI5My41IFoiLz48L2c+CjxnPjxwYXRoIHN0eWxlPSJvcGFjaXR5OjEiIGZpbGw9IiNmY2ZjZmMiIGQ9Ik0gMjk2NS41LDM1Ny41IEMgMzA0NC42NiwzNTIuNzkyIDMxMTgsMzcwLjk1OCAzMTg1LjUsNDEyQyAzMjU4LjM5LDQ2MC4zMTQgMzMwMC4yMiw1MjguMTQ4IDMzMTEsNjE1LjVDIDMzMTIuMiw2MjUuMTMgMzMxMi43LDYzNC43OTYgMzMxMi41LDY0NC41QyAzMjU1LjgzLDY0NC42NjcgMzE5OS4xNyw2NDQuNSAzMTQyLjUsNjQ0QyAzMTM5Ljc3LDYwOS40NCAzMTI2LjEsNTgwLjEwNyAzMTAxLjUsNTU2QyAzMDg4LjA2LDU0NS40NDcgMzA3My4wNiw1MzcuNzgxIDMwNTYuNSw1MzNDIDI5OTcuMjcsNTEzLjYyNCAyOTQwLjI3LDUxOC42MjQgMjg4NS41LDU0OEMgMjg0MS4yOSw1ODAuMjU0IDI4MjYuNDYsNjIyLjc1NCAyODQxLDY3NS41QyAyODUwLjM0LDY5NS44MzYgMjg2NC44NCw3MTEuMzM2IDI4ODQuNSw3MjJDIDI5MTIuODksNzM2LjU5OCAyOTQyLjg5LDc0Ni4yNjUgMjk3NC41LDc1MUMgMzAzNy4yOSw3NjEuNTMgMzA5OS4yOSw3NzUuNTMgMzE2MC41LDc5M0MgMzI2Mi40LDgyMi45MDMgMzMxOC4yNCw4OTAuNzM2IDMzMjgsOTk2LjVDIDMzMzQuMjYsMTA2MS4wNCAzMzIxLjkzLDExMjEuNyAzMjkxLDExNzguNUMgMzI1OC4wOSwxMjMxLjc0IDMyMTIuNTksMTI3MC4yNCAzMTU0LjUsMTI5NEMgMzExMC4wMiwxMzEwLjcgMzA2NC4wMiwxMzIwLjM2IDMwMTYuNSwxMzIzQyAyOTI5LjQ2LDEzMzEuMTUgMjg0Ny43OSwxMzE0LjE1IDI3NzEuNSwxMjcyQyAyNjk5LjE1LDEyMjkuMjQgMjY1Ni4zMiwxMTY2LjA3IDI2NDMsMTA4Mi41QyAyNjQwLjk3LDEwNjcuNTQgMjYzOS40NywxMDUyLjU0IDI2MzguNSwxMDM3LjVDIDI2OTcuNSwxMDM3LjMzIDI3NTYuNSwxMDM3LjUgMjgxNS41LDEwMzhDIDI4MTkuOTUsMTA1OC4wMSAyODI2Ljc4LDEwNzcuMTcgMjgzNiwxMDk1LjVDIDI4NTQuNzYsMTEyNi4zMiAyODgxLjkyLDExNDUuNDkgMjkxNy41LDExNTNDIDI5NTguNzQsMTE2MC40MyAzMDAwLjA3LDExNjEuMSAzMDQxLjUsMTE1NUMgMzA3MC4yMiwxMTQ4LjMxIDMwOTUuNTUsMTEzNS4zMSAzMTE3LjUsMTExNkMgMzE0NS4wMiwxMDg5LjQ1IDMxNTUuODYsMTA1Ny4yOSAzMTUwLDEwMTkuNUMgMzE0MS4zLDk4OS45MjQgMzEyMi44LDk2OS4wOSAzMDk0LjUsOTU3QyAzMDcyLjYsOTQ4LjkyMyAzMDUwLjI3LDk0Mi4yNTYgMzAyNy41LDkzN0MgMjk2NS41OSw5MjQuMTA2IDI5MDMuOTIsOTEwLjEwNiAyODQyLjUsODk1QyAyODAyLjY0LDg4NC40MDIgMjc2Ni42NCw4NjYuNDAyIDI3MzQuNSw4NDFDIDI2OTcuNTgsODA5LjY4OCAyNjc0LjA4LDc3MC4xODggMjY2NCw3MjIuNUMgMjY1MC4wNyw2NTQuNjc3IDI2NTYuNzQsNTg5LjAxIDI2ODQsNTI1LjVDIDI3MjIuMDgsNDQ4LjM0NSAyNzgyLjU4LDM5Ny44NDUgMjg2NS41LDM3NEMgMjg5OC40OSwzNjUuNTU4IDI5MzEuODIsMzYwLjA1OCAyOTY1LjUsMzU3LjUgWiIvPjwvZz4KPGc+PHBhdGggc3R5bGU9Im9wYWNpdHk6MSIgZmlsbD0iI2ZjZmNmYyIgZD0iTSA2NjUzLjUsNzU2LjUgQyA2NTMzLjUsNzU2LjUgNjQxMy41LDc1Ni41IDYyOTMuNSw3NTYuNUMgNjI5My41LDc4My4xNjcgNjI5My41LDgwOS44MzMgNjI5My41LDgzNi41QyA2MjkzLjMzLDg5NS44MzQgNjI5My41LDk1NS4xNjggNjI5NCwxMDE0LjVDIDYyOTMuMDUsMTA0NS41MSA2Mjk3LjA1LDEwNzUuODQgNjMwNiwxMTA1LjVDIDYzMjAuMDgsMTEzMy4yMyA2MzQyLjI0LDExNTEuMDYgNjM3Mi41LDExNTlDIDY0MTEuMjYsMTE2OC44MSA2NDQ3LjkyLDExNjMuODEgNjQ4Mi41LDExNDRDIDY1MDQuMTIsMTEyOC42NCA2NTE3LjYyLDExMDcuODEgNjUyMywxMDgxLjVDIDY1MjUuODIsMTA1OS45MSA2NTI3LjY2LDEwMzguMjUgNjUyOC41LDEwMTYuNUMgNjU4NC4xNywxMDE2LjUgNjYzOS44MywxMDE2LjUgNjY5NS41LDEwMTYuNUMgNjY5OS44NiwxMDY5LjkzIDY2OTIuMzYsMTEyMS42IDY2NzMsMTE3MS41QyA2NjQ0LjYsMTIzNy4yMyA2NTk2LjQ0LDEyODEuNCA2NTI4LjUsMTMwNEMgNjQ3My4zMiwxMzIxLjA5IDY0MTYuOTksMTMyNi40MiA2MzU5LjUsMTMyMEMgNjMwMi43NiwxMzEzLjc3IDYyNTIuNDMsMTI5Mi43NyA2MjA4LjUsMTI1N0MgNjE2Ny41MiwxMjE5LjU1IDYxNDEuNjgsMTE3My4zOSA2MTMxLDExMTguNUMgNjEyOC4yNywxMTA0LjYxIDYxMjYuMjcsMTA5MC42MSA2MTI1LDEwNzYuNUMgNjEyMy41Miw4NDAuODQzIDYxMjMuMDIsNjA1LjE3NyA2MTIzLjUsMzY5LjVDIDYxODAuMTcsMzY5LjUgNjIzNi44MywzNjkuNSA2MjkzLjUsMzY5LjVDIDYyOTMuNSw0NDYuODMzIDYyOTMuNSw1MjQuMTY3IDYyOTMuNSw2MDEuNUMgNjQxMy41LDYwMS41IDY1MzMuNSw2MDEuNSA2NjUzLjUsNjAxLjVDIDY2NTMuNSw2NTMuMTY3IDY2NTMuNSw3MDQuODMzIDY2NTMuNSw3NTYuNSBaIi8+PC9nPgo8Zz48cGF0aCBzdHlsZT0ib3BhY2l0eToxIiBmaWxsPSIjZmNmY2ZjIiBkPSJNIDEyNjIuNSw1NTguNSBDIDE0MzUuMyw1NTYuODUxIDE2MDcuMyw1NjcuNjg0IDE3NzguNSw1OTFDIDE5MDMuNjYsNjA4LjYzNiAyMDI2LjMzLDYzNi45NyAyMTQ2LjUsNjc2QyAyMTg1LjQxLDY5MC45NTYgMjIyMy43NSw3MDcuMjg5IDIyNjEuNSw3MjVDIDIyODkuMjgsNzM5LjMyNyAyMzEyLjQ1LDc1OS4xNjEgMjMzMSw3ODQuNUMgMjM0NC4zNyw4MTIuODc2IDIzMzguODcsODM3LjA0MyAyMzE0LjUsODU3QyAyMjgyLjI1LDg4My45NjggMjI0NS45Miw5MDMuOTY4IDIyMDUuNSw5MTdDIDIxNTMuMyw5MzQuMzgzIDIwOTkuOTcsOTQ3LjA1IDIwNDUuNSw5NTVDIDE5NzYuNzIsOTY0LjYxMSAxOTA3LjcyLDk3Mi4xMTEgMTgzOC41LDk3Ny41QyAxODU4LjI0LDg4NC40NDggMTg3OC4yNCw3OTEuNDQ4IDE4OTguNSw2OTguNUMgMTcxNS4yNSw2NjguNTE1IDE1MzAuNzUsNjUzLjUxNSAxMzQ1LDY1My41QyAxMTQ3LjE0LDY1Mi45NDIgOTUwLjk2OSw2NzAuNzc2IDc1Ni41LDcwN0MgNzU1LjU3Miw3MDcuMzg4IDc1NC45MDUsNzA4LjA1NSA3NTQuNSw3MDlDIDc3NC42NjQsNzk4LjQ5IDc5NC42NjQsODg3Ljk5IDgxNC41LDk3Ny41QyA3MzMuMzU3LDk3MC41NCA2NTIuNjkxLDk2MC4wNCA1NzIuNSw5NDZDIDUxNC4wOSw5MzUuNTI4IDQ1Ny40MjQsOTE5LjE5NSA0MDIuNSw4OTdDIDM3NC4wMTksODg0LjE3MiAzNDguNTE5LDg2Ny4wMDUgMzI2LDg0NS41QyAzMTIuMTI5LDgyNS4yNzEgMzEyLjEyOSw4MDQuOTM3IDMyNiw3ODQuNUMgMzQzLjgwOSw3NjEuNjg0IDM2NS4zMDksNzQzLjE4NCAzOTAuNSw3MjlDIDQ1My43NDUsNjk3LjU4MiA1MTkuNDEyLDY3Mi4yNDggNTg3LjUsNjUzQyA2NzguMDQzLDYyOC40MjQgNzY5LjcxLDYwOS4wOTEgODYyLjUsNTk1QyA5OTUuMTgxLDU3My45ODggMTEyOC41MSw1NjEuODIyIDEyNjIuNSw1NTguNSBaIi8+PC9nPgo8Zz48cGF0aCBzdHlsZT0ib3BhY2l0eToxIiBmaWxsPSIjZmNmY2ZjIiBkPSJNIDQxNjkuNSw5NDEuNSBDIDQxNjkuNSw5NjQuODMzIDQxNjkuNSw5ODguMTY3IDQxNjkuNSwxMDExLjVDIDM5NzguNjcsMTAxMS4xNyAzNzg4LDEwMTEuNSAzNTk3LjUsMTAxMi41QyAzNjAyLjM1LDEwNDYuMiAzNjE1Ljg1LDEwNzUuODcgMzYzOCwxMTAxLjVDIDM2NzQuODIsMTE0MS45OSAzNzIwLjY1LDExNjMuODIgMzc3NS41LDExNjdDIDM4MjQuMSwxMTcxLjY4IDM4NzAuMSwxMTYzLjAxIDM5MTMuNSwxMTQxQyAzOTIwLjUxLDExMzcuMTYgMzkyNy4xNywxMTMyLjgzIDM5MzMuNSwxMTI4QyAzOTQzLjQyLDExMTMuNTMgMzk1Ny4wOSwxMTA0Ljg3IDM5NzQuNSwxMTAyQyA0MDI5LjgzLDExMDEuNSA0MDg1LjE3LDExMDEuMzMgNDE0MC41LDExMDEuNUMgNDEyNS44NywxMTQzLjEyIDQxMDMuMzcsMTE3OS43OCA0MDczLDEyMTEuNUMgMzk5Ny42MSwxMjg3LjI0IDM5MDYuMTEsMTMyMy45MSAzNzk4LjUsMTMyMS41QyAzNzYzLjk2LDEzMjIuMzEgMzcyOS45NiwxMzE4LjQ4IDM2OTYuNSwxMzEwQyAzNjc2LjE3LDEzMDMuNjcgMzY1NS44MywxMjk3LjMzIDM2MzUuNSwxMjkxQyAzNTM4LjYyLDEyNTAuNzkgMzQ3Mi40NiwxMTgxLjI5IDM0MzcsMTA4Mi41QyAzNDA0LjY3LDk3Ny4xNTEgMzQxMS42Nyw4NzQuNDg0IDM0NTgsNzc0LjVDIDM1MDEuODQsNjkwLjQ2NiAzNTY5LjAxLDYzMy45NjYgMzY1OS41LDYwNUMgMzc0MS40MSw1NzkuODIxIDM4MjQuMDgsNTc2LjgyMSAzOTA3LjUsNTk2QyAzOTczLjY0LDYxNC41MDggNDAyOS44LDY0OS4wMDggNDA3Niw2OTkuNUMgNDEzNy42OCw3NjcuOTgxIDQxNjguODQsODQ4LjY0OCA0MTY5LjUsOTQxLjUgWiIvPjwvZz4KPGc+PHBhdGggc3R5bGU9Im9wYWNpdHk6MSIgZmlsbD0iI2ZjZmNmYyIgZD0iTSA0ODk0LjUsOTAyLjUgQyA0ODM4LjUsOTAyLjUgNDc4Mi41LDkwMi41IDQ3MjYuNSw5MDIuNUMgNDcyNi43Nyw5MDAuOTAxIDQ3MjYuNDMsODk5LjU2OCA0NzI1LjUsODk4LjVDIDQ3MjcuNTgsODYzLjc0OSA0NzIwLjQyLDgzMS4wODIgNDcwNCw4MDAuNUMgNDY4MC40NCw3NjQuMzQ1IDQ2NDYuOTQsNzQ0Ljg0NSA0NjAzLjUsNzQyQyA0NTY4Ljg1LDczOS45MjkgNDUzNi4xOSw3NDYuOTI5IDQ1MDUuNSw3NjNDIDQ0ODEuNTYsNzc3LjY3MiA0NDY1LjM5LDc5OC41MDUgNDQ1Nyw4MjUuNUMgNDQ1My45Nyw4MzUuOTc1IDQ0NTEuOTcsODQ2LjY0MiA0NDUxLDg1Ny41QyA0NDQ5LjU1LDEwMDUuODMgNDQ0OS4wNSwxMTU0LjE2IDQ0NDkuNSwxMzAyLjVDIDQzOTMuMTcsMTMwMi42NyA0MzM2LjgzLDEzMDIuNSA0MjgwLjUsMTMwMkMgNDI3OS44NywxMzAxLjI1IDQyNzkuMzcsMTMwMC40MiA0Mjc5LDEyOTkuNUMgNDI3OC4yOSwxMTUyLjgzIDQyNzguNjMsMTAwNi4xNiA0MjgwLDg1OS41QyA0MjgzLjUxLDc3OC42NzIgNDMxNC4wMSw3MTAuMTcyIDQzNzEuNSw2NTRDIDQ0MDQuMDIsNjI1Ljc0IDQ0NDEuMzUsNjA2LjQwNiA0NDgzLjUsNTk2QyA0NTUzLjIsNTc5LjQwNSA0NjIyLjg2LDU3OS40MDUgNDY5Mi41LDU5NkMgNDgwMS41OCw2MjguNDExIDQ4NjYuNDEsNzAwLjU3NyA0ODg3LDgxMi41QyA0ODkyLjAyLDg0Mi4zMDIgNDg5NC41Miw4NzIuMzAyIDQ4OTQuNSw5MDIuNSBaIi8+PC9nPgo8Zz48cGF0aCBzdHlsZT0ib3BhY2l0eToxIiBmaWxsPSIjZmNmY2ZjIiBkPSJNIDc1MjguNSwxMzAyLjUgQyA3NDc2LjgzLDEzMDIuNSA3NDI1LjE3LDEzMDIuNSA3MzczLjUsMTMwMi41QyA3MzczLjgzLDEyNjIuNDMgNzM3My41LDEyMjMuMDkgNzM3Mi41LDExODQuNUMgNzM1Ni4yLDEyMDMuNjQgNzM0MC4wMywxMjIyLjk4IDczMjQsMTI0Mi41QyA3MjcwLjY0LDEyOTYuMjUgNzIwNS44MSwxMzIzLjI1IDcxMjkuNSwxMzIzLjVDIDcwNTkuNDQsMTMyMi45MSA2OTk0LjQ0LDEzMDQuNzQgNjkzNC41LDEyNjlDIDY4NTUuOSwxMjE3LjA1IDY4MDYuMDcsMTE0NC44OCA2Nzg1LDEwNTIuNUMgNjc3My4xNyw5OTEuOTUzIDY3NzIuNSw5MzEuMjg3IDY3ODMsODcwLjVDIDY4MDIuNzYsNzc4Ljc0NCA2ODUwLjI2LDcwNS4yNDQgNjkyNS41LDY1MEMgNjk4Ni45NSw2MDkuNDczIDcwNTQuNjEsNTg3LjQ3MyA3MTI4LjUsNTg0QyA3MjM2LjI0LDU3Ni40NzMgNzMzMS4yNCw2MDcuMTQgNzQxMy41LDY3NkMgNzQ2OC42Niw3MjYuNDY5IDc1MDMuNSw3ODguNjM2IDc1MTgsODYyLjVDIDc1MjQuNjksODk4LjE3MiA3NTI4LjAyLDkzNC4xNzIgNzUyOCw5NzAuNUMgNzUyOC41LDEwODEuMTcgNzUyOC42NywxMTkxLjgzIDc1MjguNSwxMzAyLjUgWiIvPjwvZz4KPGc+PHBhdGggc3R5bGU9Im9wYWNpdHk6MSIgZmlsbD0iI2ZkZmRmZCIgZD0iTSA0OTIxLjUsNjAzLjUgQyA0OTgxLjE3LDYwMy4zMzMgNTA0MC44Myw2MDMuNSA1MTAwLjUsNjA0QyA1MTA0LjYxLDYwNS43NzkgNTEwNy43OCw2MDguNjEyIDUxMTAsNjEyLjVDIDUxNzIuNzMsNzg2LjcwMyA1MjM1LjA3LDk2MS4wMzcgNTI5NywxMTM1LjVDIDUyOTcuOTcsMTEzNy42NCA1Mjk5LjQ3LDExMzkuMzEgNTMwMS41LDExNDAuNUMgNTM2NS41OSw5NjEuOTcgNTQyOS40Myw3ODMuMzA0IDU0OTMsNjA0LjVDIDU1NTMuNDMsNjAzLjUwMiA1NjEzLjkzLDYwMy4xNjkgNTY3NC41LDYwMy41QyA1NTg3Ljk3LDgyNS45MTYgNTUwMS4xNCwxMDQ4LjI1IDU0MTQsMTI3MC41QyA1NDEwLjc3LDEyNzkuNTQgNTQwNi43NywxMjg4LjIxIDU0MDIsMTI5Ni41QyA1Mzk0LjA2LDEzMDMuNjUgNTM4NC43MywxMzA2LjMyIDUzNzQsMTMwNC41QyA1MzE0LjUsMTMwMy41NiA1MjU1LDEzMDMuMjMgNTE5NS41LDEzMDMuNUMgNTEwNC4zNywxMDcwLjEgNTAxMy4wMyw4MzYuNzY2IDQ5MjEuNSw2MDMuNSBaIi8+PC9nPgo8Zz48cGF0aCBzdHlsZT0ib3BhY2l0eToxIiBmaWxsPSIjZmRmZGZkIiBkPSJNIDU3OTIuNSw2MDIuNSBDIDU4NDguNSw2MDIuNSA1OTA0LjUsNjAyLjUgNTk2MC41LDYwMi41QyA1OTYwLjUsODM1LjgzMyA1OTYwLjUsMTA2OS4xNyA1OTYwLjUsMTMwMi41QyA1OTA0LjE3LDEzMDIuNSA1ODQ3LjgzLDEzMDIuNSA1NzkxLjUsMTMwMi41QyA1NzkxLjE3LDEwNjkuMSA1NzkxLjUsODM1Ljc2NCA1NzkyLjUsNjAyLjUgWiIvPjwvZz4KPGc+PHBhdGggc3R5bGU9Im9wYWNpdHk6MSIgZmlsbD0iIzEwMTAxMCIgZD0iTSAzNzg5LjUsNzM2LjUgQyAzODM2Ljk0LDczNi4wMiAzODgwLjI3LDc0OC44NTMgMzkxOS41LDc3NUMgMzk1NC44Nyw4MDAuODg1IDM5NzguMjEsODM1LjA1MSAzOTg5LjUsODc3LjVDIDM4NTkuNSw4NzcuODMzIDM3MjkuNSw4NzcuNSAzNTk5LjUsODc2LjVDIDM2MTcuNTMsODE1LjYzNyAzNjU2LjIsNzczLjgwMyAzNzE1LjUsNzUxQyAzNzM5LjU3LDc0Mi40MDIgMzc2NC4yNCw3MzcuNTY4IDM3ODkuNSw3MzYuNSBaIi8+PC9nPgo8Zz48cGF0aCBzdHlsZT0ib3BhY2l0eToxIiBmaWxsPSIjMGQwZDBkIiBkPSJNIDcxMzQuNSw3NDEuNSBDIDcxOTMuNTQsNzM3LjQ5NyA3MjQ1Ljg4LDc1My45OTcgNzI5MS41LDc5MUMgNzMzMy41NCw4MzAuNTg1IDczNTYuMDQsODc5LjQxOSA3MzU5LDkzNy41QyA3MzYyLjE3LDk5Ni4xODcgNzM0Ni4xNywxMDQ4Ljg1IDczMTEsMTA5NS41QyA3MjkwLjQsMTExOS4wOCA3MjY1LjU2LDExMzYuOTIgNzIzNi41LDExNDlDIDcxNzEsMTE3NS4yNCA3MTA3LjMzLDExNzEuMjQgNzA0NS41LDExMzdDIDY5OTYuOTYsMTExMC4xMSA2OTY2LjEzLDEwNjkuNjEgNjk1MywxMDE1LjVDIDY5NDMuODIsOTcxLjY3NSA2OTQ0LjQ5LDkyOC4wMDggNjk1NSw4ODQuNUMgNjk3Ni41OCw4MTUuOTIyIDcwMjEuNzUsNzcxLjA4OCA3MDkwLjUsNzUwQyA3MTA1LjE3LDc0Ni40MzIgNzExOS44Myw3NDMuNTk5IDcxMzQuNSw3NDEuNSBaIi8+PC9nPgo8Zz48cGF0aCBzdHlsZT0ib3BhY2l0eToxIiBmaWxsPSIjNjk2OTY5IiBkPSJNIDY2NTMuNSw3NTYuNSBDIDY1MzQsNzU3LjUgNjQxNC4zMyw3NTcuODMzIDYyOTQuNSw3NTcuNUMgNjI5NC44Myw3ODQuMDA1IDYyOTQuNSw4MTAuMzM5IDYyOTMuNSw4MzYuNUMgNjI5My41LDgwOS44MzMgNjI5My41LDc4My4xNjcgNjI5My41LDc1Ni41QyA2NDEzLjUsNzU2LjUgNjUzMy41LDc1Ni41IDY2NTMuNSw3NTYuNSBaIi8+PC9nPgo8Zz48cGF0aCBzdHlsZT0ib3BhY2l0eToxIiBmaWxsPSIjNDk0OTQ5IiBkPSJNIDQ3MjUuNSw4OTguNSBDIDQ3MjYuNDMsODk5LjU2OCA0NzI2Ljc3LDkwMC45MDEgNDcyNi41LDkwMi41QyA0NzgyLjUsOTAyLjUgNDgzOC41LDkwMi41IDQ4OTQuNSw5MDIuNUMgNDgzOC4zNCw5MDMuNDk5IDQ3ODIsOTAzLjgzMiA0NzI1LjUsOTAzLjVDIDQ3MjUuNSw5MDEuODMzIDQ3MjUuNSw5MDAuMTY3IDQ3MjUuNSw4OTguNSBaIi8+PC9nPgo8Zz48cGF0aCBzdHlsZT0ib3BhY2l0eToxIiBmaWxsPSIjZmJmYmZiIiBkPSJNIDEyOTguNSwxMDA1LjUgQyAxNDY4LjMsMTAwMi43MyAxNjM2LjYzLDEwMTYuOSAxODAzLjUsMTA0OEMgMTg3NC44NSwxMDYyLjQyIDE5NDUuMTgsMTA4MC43NSAyMDE0LjUsMTEwM0MgMjA2MS42OSwxMTE5LjEgMjEwNi4wMiwxMTQwLjc2IDIxNDcuNSwxMTY4QyAyMTU5LjYxLDExNzcuMzggMjE2OC40NCwxMTg5LjIxIDIxNzQsMTIwMy41QyAyMTc3Ljk3LDEyMTkuNjMgMjE3NC45NywxMjM0LjI5IDIxNjUsMTI0Ny41QyAyMTU0LjMxLDEyNjAuMiAyMTQxLjgxLDEyNzAuNyAyMTI3LjUsMTI3OUMgMjA3Ni40NSwxMzA1LjYgMjAyMi40NSwxMzIzLjI2IDE5NjUuNSwxMzMyQyAxOTM0Ljk3LDEzMzcuMjggMTkwNC4zLDEzNDEuNjEgMTg3My41LDEzNDVDIDE4MzguMjksMTM0OC40NyAxODAzLjEzLDEzNTIuMyAxNzY4LDEzNTYuNUMgMTc2NC4xNywxMzU1Ljk2IDE3NjAuMzQsMTM1NS40NiAxNzU2LjUsMTM1NUMgMTc1Ni4wNCwxMzU0LjU5IDE3NTUuNzEsMTM1NC4wOSAxNzU1LjUsMTM1My41QyAxNzcyLjgxLDEyNzYuMyAxNzg5LjQ4LDExOTguOTcgMTgwNS41LDExMjEuNUMgMTY2My44NywxMDk3LjIxIDE1MjEuMiwxMDgzLjM3IDEzNzcuNSwxMDgwQyAxMTk5LjA2LDEwNzYuMDEgMTAyMi4wNiwxMDkwLjAxIDg0Ni41LDExMjJDIDg0NS45NDEsMTEyMi43MiA4NDUuNjA4LDExMjMuNTYgODQ1LjUsMTEyNC41QyA4NjIuMDA4LDEyMDAuODYgODc4LjY3NCwxMjc3LjIgODk1LjUsMTM1My41QyA4NjEuMTUzLDEzNTEuNTcgODI2LjgxOSwxMzQ4LjQxIDc5Mi41LDEzNDRDIDcxNS4zNjQsMTMyOS40OCA2MzguNjk3LDEzMTIuODEgNTYyLjUsMTI5NEMgNTM4Ljc5MSwxMjg2LjU3IDUxNy45NTcsMTI3NC40IDUwMCwxMjU3LjVDIDQ5Mi43NSwxMjQ2LjY3IDQ4NS43NSwxMjM1LjY3IDQ3OSwxMjI0LjVDIDQ3OC4zNDIsMTIwMi45OCA0ODYuODQyLDExODYuMTUgNTA0LjUsMTE3NEMgNTQ4LjU0OCwxMTQ3LjMxIDU5NC41NDgsMTEyNC4zMSA2NDIuNSwxMTA1QyA3NDAuNDcxLDEwNzAuMDEgODQxLjEzOCwxMDQ2LjM0IDk0NC41LDEwMzRDIDEwNjIuMjUsMTAxOS4zIDExODAuMjUsMTAwOS44IDEyOTguNSwxMDA1LjUgWiIvPjwvZz4KPGc+PHBhdGggc3R5bGU9Im9wYWNpdHk6MC44NzgiIGZpbGw9IiNkOGQ4ZDgiIGQ9Ik0gNDE2OS41LDk0MS41IEMgNDE3MC41LDk2NC45OTQgNDE3MC44Myw5ODguNjYxIDQxNzAuNSwxMDEyLjVDIDM5NzkuNSwxMDEyLjUgMzc4OC41LDEwMTIuNSAzNTk3LjUsMTAxMi41QyAzNzg4LDEwMTEuNSAzOTc4LjY3LDEwMTEuMTcgNDE2OS41LDEwMTEuNUMgNDE2OS41LDk4OC4xNjcgNDE2OS41LDk2NC44MzMgNDE2OS41LDk0MS41IFoiLz48L2c+CjxnPjxwYXRoIHN0eWxlPSJvcGFjaXR5OjEiIGZpbGw9IiM1ZTVlNWUiIGQ9Ik0gNzUyOC41LDEzMDIuNSBDIDc0NzYuNjcsMTMwMy41IDc0MjQuNjcsMTMwMy44MyA3MzcyLjUsMTMwMy41QyA3MzcyLjUsMTI2My44MyA3MzcyLjUsMTIyNC4xNyA3MzcyLjUsMTE4NC41QyA3MzczLjUsMTIyMy4wOSA3MzczLjgzLDEyNjIuNDMgNzM3My41LDEzMDIuNUMgNzQyNS4xNywxMzAyLjUgNzQ3Ni44MywxMzAyLjUgNzUyOC41LDEzMDIuNSBaIi8+PC9nPgo8L3N2Zz4K" />
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
                let appData;

                function initWebSocket() {
                    function updateAppDataObject(type, receivedData) {
                        function buildAppDataObject(receivedData) { 
                            console.log('Building appData object:', receivedData);
                            //build the app data object
                            appData = {
                                timestamp: Date.now(),
                                liveConnection: true,
                                pourSize: {
                                    p1: receivedData.p1,
                                    p2: receivedData.p2,
                                    m1: receivedData.mixed1,
                                    m2: receivedData.mixed2
                                }
                            }
                            return appData;
                        } 
                        try {
                            if (appData === undefined || appData === null) {
                                buildAppDataObject(receivedData);
                                ensureSliderIsAccurate();
                            } else if (type == 'pourSize') {
                                appData.timestamp = Date.now();
                                appData.pourSize.p1 = receivedData.p1;
                                appData.pourSize.p2 = receivedData.p2;
                                appData.pourSize.m1 = receivedData.m2;
                                appData.pourSize.m2 = receivedData.m2;
                            } else {
                                return console.log('Unknown type:', type);
                            }
                        }
                        catch (error) {
                            console.log('Error updating appData object:', error);
                            //Window.alert('Error updating appData object. Frontend may not work as expected.');

                        }
                    }
                        console.log('Trying to open a WebSocket connection...');
                        websocket = new WebSocket(`ws://${window.location.hostname}/ws`);
                        websocket.onopen = onOpen;
                        websocket.onclose = onClose;
                        websocket.onmessage = onMessage;
                    function onOpen(event) {
                        console.log('Connection opened');
                        initButton();
                        sendMessage('getPourSize', { payload: 'init' });
                    }
                    function onClose(event) {
                        console.log('Connection closed');
                        appData.liveConnection = false;
                    }
                    // message handler function
                    function onMessage(event) {
                        console.log('Message received:', event.data);
                        const message = JSON.parse(event.data);
                        console.log('Message received:', message);
                        updateAppDataObject(message.type, message);
                    }
                }

                
                    
                window.addEventListener('load', onLoad, false);
                function onLoad(event) {
                    initSliders();

                }

                function sendMessage(type, payload) {
                    const message = { type: type, payload: payload };
                    websocket.send(JSON.stringify(message));
                }

                function initButton() {
                    drink1Button.addEventListener('click', function () {
                        sendMessage('pour', { drink: 'drink1', size: p1Range.value });
                    }, false);

                    drink2Button.addEventListener('click', function () {
                        sendMessage('pour', { drink: 'drink2', size: p2Range.value });
                    }, false);

                    drink3Button.addEventListener('click', function () {
                        sendMessage('pour', { drink: 'drink3', size1: p3Range1.value, size2: p3Range2.value });
                    }, false);

                    cancelButton.addEventListener('click', function () {
                        sendMessage('pour', { drink: 'pourCancel' });
                    }, false);

                    rgbButton.addEventListener('click', function () {
                        sendMessage('led', { value: getRgbVal() });
                    }, false);

                    brightSend.addEventListener('click', function () {
                        sendMessage('brightness', { value: getBrightness() });
                    }, false);

                    mCarUp.addEventListener('mousedown', function () {
                        sendMessage('manual', { action: 'mCarUp' });
                        console.log('mousedown event');
                    }, false);
                    mCarUp.addEventListener('mouseup', function () {
                        sendMessage('manual', { action: 'mCarStop' });
                        console.log('mouseup event');
                    }, false);
                    mCarUp.addEventListener('touchstart', function () {
                        sendMessage('manual', { action: 'mCarUp' });
                        console.log('touchstart event');
                    }, false);
                    mCarUp.addEventListener('touchend', function () {
                        sendMessage('manual', { action: 'mCarStop' });
                        console.log('touchend event');
                    }, false);

                    mCarDown.addEventListener('mousedown', function () {
                        sendMessage('manual', { action: 'mCarDown' });
                        console.log('mousedown event');
                    }, false);
                    mCarDown.addEventListener('mouseup', function () {
                        sendMessage('manual', { action: 'mCarStop' });
                        console.log('mouseup event');
                    }, false);
                    mCarDown.addEventListener('touchstart', function () {
                        sendMessage('manual', { action: 'mCarDown' });
                        console.log('touchstart event');
                    }, false);
                    mCarDown.addEventListener('touchend', function () {
                        sendMessage('manual', { action: 'mCarStop' });
                        console.log('touchend event');
                    }, false);

                    rPump1.addEventListener('mousedown', function () {
                        sendMessage('manual', { action: 'rPump1Start' });
                        console.log('mousedown event');
                    }, false);
                    rPump1.addEventListener('mouseup', function () {
                        sendMessage('manual', { action: 'rPump1Stop' });
                        console.log('mouseup event');
                    }, false);
                    rPump1.addEventListener('touchstart', function () {
                        sendMessage('manual', { action: 'rPump1Start' });
                        console.log('touchstart event');
                    }, false);
                    rPump1.addEventListener('touchend', function () {
                        sendMessage('manual', { action: 'rPump1Stop' });
                        console.log('touchend event');
                    }, false);

                    rPump2.addEventListener('mousedown', function () {
                        sendMessage('manual', { action: 'rPump2Start' });
                        console.log('mousedown event');
                    }, false);
                    rPump2.addEventListener('mouseup', function () {
                        sendMessage('manual', { action: 'rPump2Stop' });
                        console.log('mouseup event');
                    }, false);
                    rPump2.addEventListener('touchstart', function () {
                        sendMessage('manual', { action: 'rPump2Start' });
                        console.log('touchstart event');
                    }, false);
                    rPump2.addEventListener('touchend', function () {
                        sendMessage('manual', { action: 'rPump2Stop' });
                        console.log('touchend event');
                    }, false);

                    mCarHome.addEventListener('click', function () {
                        sendMessage('manual', { action: 'mCarHome' });
                    }, false);

                    sendCredentials.addEventListener('click', function () {
                        const ssid = document.getElementById('ssid').value;
                        const pass = document.getElementById('pass').value;
                        sendMessage('net', { ssid: ssid, password: pass });
                    }, false);

                    lButton.addEventListener('click', function () {
                        sendMessage('lock', { action: 'lock' });
                    }, false);

                    uButton.addEventListener('click', function () {
                        sendMessage('lock', { action: 'unlock' });
                    }, false);

                    ledButton.addEventListener('click', function () {
                        const ledNum = document.getElementById('lNum').value;
                        sendMessage('lnum', { value: ledNum });
                    }, false);
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
                    p3Range1.ontouchend = function () {
                        sendMessage('changePourSize', { drink: 'MIXED_POUR_1_SIZE', size: p3Range1.value });
                    }
                    p3Range1.onmouseup = function () {
                        sendMessage('changePourSize', { drink: 'MIXED_POUR_1_SIZE', size: p3Range1.value });
                    }
                    p3Range2.oninput = function () {
                        displaySliderVals();
                        p3ValueSafety(p3Range1, p3Range2);
                    }
                    p3Range2.ontouchend = function () {
                        sendMessage('changePourSize', { drink: 'MIXED_POUR_2_SIZE', size: p3Range2.value });
                    }
                    p3Range2.onmouseup = function () {
                        sendMessage('changePourSize', { drink: 'MIXED_POUR_2_SIZE', size: p3Range2.value });
                    }
                    p1Range.oninput = function () {
                        displaySliderVals();
                    }
                    p1Range.ontouchend = function () {
                        sendMessage('changePourSizee', { drink: 'DRINK1_POUR_SIZE', size: p1Range.value });
                    }
                    p1Range.onmouseup = function () {
                        sendMessage('changePourSize', { drink: 'DRINK1_POUR_SIZE', size: p1Range.value });
                    }
                    p2Range.oninput = function () {
                        setColor();
                        displaySliderVals();
                    }
                    p2Range.ontouchend = function () {
                        sendMessage('changePourSize', { drink: 'DRINK2_POUR_SIZE', size: p2Range.value });   
                    }
                    p2Range.onmouseup = function () {
                        sendMessage('changePourSize', { drink: 'DRINK2_POUR_SIZE', size: p2Range.value });   
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
                function ensureSliderIsAccurate() {
                    p1Range.value = appData.pourSize.p1;
                    p2Range.value = appData.pourSize.p2;
                    p3Range1.value = appData.pourSize.m1;
                    p3Range2.value = appData.pourSize.m2;
                    displaySliderVals(); 
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