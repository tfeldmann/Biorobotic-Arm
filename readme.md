# Biorobotic Arm

This is a collaborative project for the course "biorobotics and locomotion".
It contains the source files for the firmware, control-software and remote software.

## General structure
- class Robot
	- Base
    - Shoulder
    - Elbow
    - Wrist
    - Grip
        - open()
        - close()

## API
Connect to the robot via a 19200 baud, 8N1 serial connection.
Commands are sent in plain ascii.

The possible arguments ([Option1 | Option2]) can be numbers or plain text.
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
