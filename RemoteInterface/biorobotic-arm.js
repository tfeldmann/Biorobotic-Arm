loadedInterfaceName = "BioRobotic Arm";

interfaceOrientation = "portrait";

whRatio = 2 / 3;

pages = [[
{
    "name": "applicationName",
    "type": "Label",
    "x": 0.01,
    "y": 0.01,
    "width": 1,
    "height": .05,
    "color": "#ffffff",
    "align": "left",
    "value": "BioRobotic Arm",
},
{
    "name": "companyName",
    "type": "Label",
    "x": 0.3,
    "y": 0.01,
    "width": 0.69,
    "height": .05,
    "color": "#ffffff",
    "align": "right",
    "value": "Feldmann & Co. Roboterfabrik",
},

/** Gyro **/
{
    "name": "gyroSliders",
    "type": "MultiSlider",
    "numberOfSliders": 2,
    "min":0, "max":180,
    "x": .01, "y": .1,
    "width": .3,
    "height": .85,
    "isLocal":true,
},

/** GRIP **/
{
    "name":"gripButton",
    "type":"Button",
    "x" : 0.5,
    "y" : 0.1,
    "width" : .25,
    "height": .20 * whRatio,
    "mode": "contact",
    "max":1,
    "address": "/grip",
    "label": "Grip",
},
/** ELBOW SELECT **/
{
    "name":"elbowButton",
    "type":"Button",
    "x" : 0.5,
    "y" : 0.3,
    "width" : .25,
    "height": .20 * whRatio,
    "mode": "contact",
    "max":1,
    "address": "/elbow",
    "label": "Elbow",
},
/** SHOULDER SELECT **/
{
    "name":"shoulderButton",
    "type":"Button",
    "x" : 0.5,
    "y" : 0.5,
    "width" : .25,
    "height": .20 * whRatio,
    "mode": "contact",
    "max":1,
    "address": "/shoulder",
    "label": "Shoulder",
},

{
    "name": "refreshButton",
    "type": "Button",
    "bounds": [.5, .8, .2, .1],
    "mode": "momentary",
    "color": "#0000aa",
    "stroke": "#aaaaaa",
    "isLocal": true,
    "label": "Refresh",
    "ontouchstart": "interfaceManager.refreshInterface()",
},
{
    "name": "tabButton",
    "type": "Button",
    "bounds": [.8, .8, .2, .1],
    "mode": "toggle",
    "stroke": "#aaa",
    "isLocal": true,
    "ontouchstart": "if(this.value == this.max) { control.showToolbar(); } else { control.hideToolbar(); }",
    "label": "Menu",
},

// gyro values
{
    "name": "gyro",
    "type": "Gyro",
    "min":0,
    "max":180,
    "midiNumber": 3,
    "updateRate": 20,
    "isLocal":false,
    "onvaluechange": "gyroSliders.setSequentialValues(this.pitch, this.yaw);",
},
]];
