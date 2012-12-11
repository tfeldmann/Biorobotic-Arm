# Biorobotic Arm
This is a collaborative project for the course "biorobotics and locomotion".
It contains the source files for the firmware, graphical control software, scripting software and remote software as well as the driver.


## Driver
This folder contains the driver which is needed on windows ([installation instructions](http://arduino.cc/en/Guide/windows#toc4)).

On Mac OS X the device is recognized automatically. It should work on Linux, too - but we did not test that.


## Firmware
Here you find the robot's firmware. It is written for an Arduino Mega 2560 R3.
To compile and upload, simply use the Arduino Software ([link](http://arduino.cc)).
The [SerialCommand](https://github.com/kroimon/Arduino-SerialCommand) library needs to be installed.


## RemoteInterface
This folder contains the setup file for the remote interface (iOS / Android).
You will need the software "[Control](http://charlie-roberts.com/Control/)".

Make sure that you are in the same network as the PC running the RobControl-software and enter the given IP-adress as destination. Install and start the RobControl Remote interface (the website shows how it's done).


## RobControl
The graphical robot control software. Start it after you connected the robot to the PC, select the right port and you're good to go.

You can control the robot by clicking and dragging. Everything should be quite self-explanatory.


## Scripter
The programmatical robot control software. Here you can enter any command from the section "API" as well as the command "PAUSE [seconds]". Click on start to run the script. Additionally you can send single commands in the entry field on the bottom.


## API
### Monitoring data
Connect to the robot via a 115200 baud, 8N1 serial connection.
As the connection is established you will receive monitoring data from the robot in plain ASCII. Every 20ms (50Hz) you will get five integers separated by ';'.
<pre>
1. base          (0..1023)
2. arm->shoulder (0..1023)
3. arm->elbow    (0..1023)
4. hand->wrist   (0..180)
5. hand->grip    (0, 1)
</pre>

### Commands
Use this commands to control the DC-Motors in the base, the shoulders and
the elbow. "POS" can be any integer value from 0 to 1023. Mechanically,
not all positions are possible.
<pre>
BASE [POS]
SHOULDER [POS]
ELBOW [POS]
</pre>

Controls the robot's wrist. You can either set an angle directly or toggle
the hold-flat-automatic.
<pre>
WRIST [ANGLE | "FLAT"]
</pre>

The grip can be opened/closed. Toggle switches between open and closed
state.
<pre>
GRIP ["OPEN" | "CLOSE" | "TOGGLE"]
</pre>

This is the identify command. The robot answers with "BIOROBOTIC_ARM_1.0
where 1.0 is the firmware version.
<pre>
?
</pre>


## Contributors
- Fehmer, Manuel
- Feldmann, Marlene
- Feldmann, Thomas
- Hussmann, Carsten

<p align="center">![Logo](https://raw.github.com/tfeldmann/Biorobotic-Arm/master/Documentation/Roboterfabrik.png)</p>
