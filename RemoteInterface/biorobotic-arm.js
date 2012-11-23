loadedInterfaceName = "BioRobotic Arm";

interfaceOrientation = "portrait";

whRatio = 2 / 3;

pages = [[
{
    "name": "applicationName",
    "type": "Label",
    "x": 0,
    "y": 0,
    "width": 1,
    "height": .05,
    "color": "#ffffff",
    "align": "left",
    "value": "BIOROBOTIC ARM",
},

/** Gyro **/
{
    "name": "refreshButton",
    "type": "Button",
    "x": 0,
    "y": .85,
    "width": .15,
    "height": .15 * whRatio,
    "mode": "momentary",
    "color": "#0000aa",
    "stroke": "#aaaaaa",
    "isLocal": true,
    "label": "Zero",
    "ontouchstart": "interfaceManager.refreshInterface()",
},

{
    "name": "gyroSliders",
    "type": "MultiSlider",
    "numberOfSliders": 2,
    "min":0, "max":180,
    "x": .0, "y": .05,
    "width": .99,
    "height": .15,
    "isLocal":true,
},

/** GRIP **/
{
    "name":"gripButton",
    "type":"Button",
    "x" : 0.5,
    "y" : 0.5,
    "width" : .25,
    "height": .20 * whRatio,
    "mode": "contact",
    "max":1,
    "address": "/grip",
    "label": "Grip",
},

{
    "name": "tabButton",
    "type": "Button",
    "bounds": [.8, .8, .2, .1],
    "mode": "toggle",
    "stroke": "#aaa",
    "isLocal": true,
    "ontouchstart": "if(this.value == this.max) { control.showToolbar(); } else { control.hideToolbar(); }",
    "label": "menu",
},

// gyro values
{
    "name": "gyro",
    "type": "Gyro",
    "min":0,
    "max":180,
    "midiNumber":3,
    "updateRate":40,
    "isLocal":false,
    "onvaluechange": "gyroSliders.setSequentialValues(this.pitch, this.yaw);",
},
]];
