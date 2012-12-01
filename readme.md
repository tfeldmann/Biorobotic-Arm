# Biorobotic Arm

This is a collaborative project for the course "biorobotics and locomotion".
It contains the source files for the firmware, control-software and remote software.

## API
The robot is controlled by an Arduino Mega 2560 which has an built-in serial->USB converter. To connect the robot, simply plug in a USB-cable.
If Windows doesn't recognize the controller board install the driver from the "Driver" directory.

Connect to the robot via a 115200 baud, 8N1 serial connection.
Commands are sent in plain ASCII.

### Monitoring data
As the connection is established you will receive monitoring data from the robot. Every 20ms (50Hz) you will get five integers separated by ';'.
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


## Building the software

### Desktop-Software "RobControl":
The easiest way to build the software is via Processing (processing.org).
Needed libraries:
 - GiCentreUtils
 - oscP5.

### Robot Firmware "BioArm_Firmware":
Compile and upload via the Arduino Software. You will need the "SerialCommand" library.


## Contributors
- Fehmer, Manuel
- Feldmann, Marlene
- Feldmann, Thomas
- Hussmann, Carsten

![Logo](https://raw.github.com/tfeldmann/Biorobotic-Arm/master/RobControl/Logo.png)
