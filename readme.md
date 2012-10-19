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
Connect to the robot via a 19200 baud, 8N1 serial connection. Commands are sent in plain ascii.

Close / Open the grip
<pre>GRIP OPEN / CLOSE</pre>

## Contributors
- Fehmer, Manuel
- Feldmann, Marlene
- Feldmann, Thomas
- Hussmann, Carsten
