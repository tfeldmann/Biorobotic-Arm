# Biorobotic Arm

This is a collaborative project for the course "biorobotics and locomotion".
It contains the source files for the firmware, control-software and remote software.

## API
Connect to the robot via a 115200 baud, 8N1 serial connection.
Commands are sent in plain ascii.

The possible arguments ([Option1 | Option2]) can be numbers or plain text.
<pre>
?
	? is the identify command. The robot anwers with BIOROBOTIC_ARM_1.0
	"1.0" is the firmware version. Number changes before the decimal point
	change the API.
</pre>
<pre>
GRIP [OPEN | CLOSE | _ANGLE_]
	The grip can be opened/closed using the first two commands.
	_ANGLE_ can be any number between 0 and 180 (degrees).
</pre>

## Contributors
- Fehmer, Manuel
- Feldmann, Marlene
- Feldmann, Thomas
- Hussmann, Carsten
