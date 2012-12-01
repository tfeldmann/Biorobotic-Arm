# Biorobotic Arm

This is a collaborative project for the course "biorobotics and locomotion".
It contains the source files for the firmware, control-software and remote software.

## API
The robot is controlled by an Arduino Mega 2560 which has an built-in serial->USB converter. To connect the robot, simply plug in a USB-cable.
If Windows doesn't recognize the controller board install the driver from the "Driver" directory.

Connect to the robot via a 115200 baud, 8N1 serial connection.
Commands are sent in plain ASCII.

### Monitoring data


### Commands
<pre>
BASE [POS]
SHOULDER [POS]
ELBOW [POS]

	Use this commands to control the DC-Motors in the base, the shoulders and
	the elbow. "POS" can be any integer value from 0 to 1023. Mechanically,
	not all positions are possible.
</pre>
<pre>
WRIST [ANGLE | "FLAT"]

	Controls the robot's wrist. You can either set an angle directly or toggle
	the hold-flat-automatic.
</pre>
<pre>
GRIP ["OPEN" | "CLOSE" | "TOGGLE"]

	The grip can be opened/closed. Toggle switches between open and closed
	state.
</pre>
<pre>
?

	This is the identify command. The robot answers with "BIOROBOTIC_ARM_1.0
	where 1.0 is the firmware version.
</pre>

## Building the software
Desktop-Software (RobControl):
The easiest way to build the software is via Processing (processing.org).
You need the libraries GiCentreUtils and oscP5.

Robot Firmware (BioArm_Firmware):
Compile and upload via the Arduino Software. You will need the "SerialCommand" library.


## Contributors
- Fehmer, Manuel
- Feldmann, Marlene
- Feldmann, Thomas
- Hussmann, Carsten

![Logo](https://raw.github.com/tfeldmann/Biorobotic-Arm/master/RobControl/Logo.png)
