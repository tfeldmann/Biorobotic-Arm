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
[Option1 | Option2] shows the possible arguments.

<pre>
	GRIP [OPEN | CLOSE] : Opens/Closes the grip
</pre>

## Contributors
- Fehmer, Manuel
- Feldmann, Marlene
- Feldmann, Thomas
- Hussmann, Carsten
