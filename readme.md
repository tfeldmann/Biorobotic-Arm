# Biorobotic Arm
This is a collaborative project for the course "biorobotics and locomotion".
It contains the source files for the firmware, graphical control software, scripting (automation) software and remote software as well as the driver.
<p align="center">
    <img src="https://raw.github.com/tfeldmann/Biorobotic-Arm/master/Documentation/BioRob.png" alt="BioRoboter">
</p>

- [Documentation](#documentation)
- [Driver](#driver)
- [Firmware](#firmware)
- [RemoteInterface](#remoteinterface)
- [RobControl](#robcontrol)
- [Scripter](#scripter)
- [API](#api)
    - [Receiving data](#receiving-data)
        - [Control characters](#control-characters)
        - [Position monitoring](#position-monitoring)
    - [Commands](#commands)
        - [Base](#base)
        - [Shoulder](#shoulder)
        - [Elbow](#elbow)
        - [Wrist](#wrist)
        - [Grip](#grip)
        - [Autolevel](#autolevel)
        - [Identify](#identify)
- [Contributors](#contributors)


## Documentation
The folder "Documentation" contains the screenshots used in the files you are currently seeing as well as the board layout and schematics.

- [Board layout](https://raw.github.com/tfeldmann/Biorobotic-Arm/master/Documentation/board-layout.pdf)
- [Board schematics](https://raw.github.com/tfeldmann/Biorobotic-Arm/master/Documentation/board-schematic.pdf)


## Driver
This folder contains the driver which is needed on older windows versions ([installation instructions](http://arduino.cc/en/Guide/windows#toc4)). As of Windows Vista the Arduino is recognized automatically.

On Mac OS X everything should work out of the box. It should work on Linux, too (although this is yet untested).


## Firmware
Here you find the robot's firmware. It is written for an Arduino Mega 2560 R3.
To compile and upload use the [Arduino Software](http://arduino.cc/en/Main/Software) unless you know what you are doing.
The [SerialCommand](https://github.com/kroimon/Arduino-SerialCommand) library must be installed. An archive of the SerialCommand library is included in Firmware/libraries.


## RemoteInterface
This folder contains the setup file for the remote interface (iOS / Android).
You will need the software "[Control](http://charlie-roberts.com/Control/)".

Make sure that you are in the same network as the PC running the RobControl-software and enter the given IP-adress as destination. Install and start the RobControl Remote interface (the .js file in the folder "RemoteInterface").
<p align="center">
    <img src="https://raw.github.com/tfeldmann/Biorobotic-Arm/master/Documentation/RemoteInterface.png" alt="RemoteInterface">
</p>

## RobControl
<p align="center">
    <img src="https://raw.github.com/tfeldmann/Biorobotic-Arm/master/Documentation/RobControl.png" alt="RobControl">
</p>
The graphical robot control software. Start it after you connected the robot to the PC, select the right port and you're good to go. You can control the robot by clicking and dragging. Everything should be quite self-explanatory.


## ScriptingSoftware
<p align="center">
    <img src="https://raw.github.com/tfeldmann/Biorobotic-Arm/master/Documentation/ScriptingSoftware.png" alt="ScriptingSoftware">
</p>
The programmatical robot control software. Here you can enter any command from the section "API" as well as the command "WAIT [seconds]". Click on start to run the script. Additionally you can send single commands in the entry field on the bottom.

The ScriptingSoftware is written in Python 2.7.4 and uses no external modules except for PySerial.


## API
Connect to the robot via a ```19200 baud, 8N1``` serial connection. Monitoring data as well as commands must be sent in plain uppercase ASCII.

### Receiving data

#### Control characters
A hash (#) indicates that a output is for logging purposes only and can be dismissed. Examples:

    # Collision sensor found
    # Ready

An exclamation mark (!) indicates an error and should always be shown to the user. Possible errors are:

    !01 Unknown command
    !02 Collision detected [Axis]
    !03 Could not connect to MMA8452Q

The question mark (?) is used for the identifier (see chapter "Identify").

    ? BIOROBOTIC_ARM


#### Position monitoring
Ca. every 50ms (20Hz) the robot sends a ```P``` following five integers separated by ```;``` that describe the robot's position.
For example:

    P130;45;-90;30;1
      |  |   |  |  |
      |  |   |  |  + - grip opened/closed
      |  |   |  +- - - wrist angle
      |  |   + - - - - elbow angle
      |  + - - - - - - shoulder angle
      +- - - - - - - - base angle

The angles for the base (∆), shoulder (α), elbow (β) and wrist (γ) are shown in the picture below. The API automatically constrains sent values to mechanically possible angles.

      -5° ≤ α ≤ 60°
    -165° ≤ β ≤ 40°
     -80° ≤ γ ≤ 90°
     -135 ≤ Δ ≤ 135

<p align="center">
    <img src="https://raw.github.com/tfeldmann/Biorobotic-Arm/master/Documentation/Geometry.png" alt="geometry">
</p>


### Commands
A short introduction to the commands the robot supports.
Please notice that every line beginning with ```>>``` indicates a command you can send. Do not send ```>>```.

#### Base
Controls the angle of the base. Send only the command name to see how it is used.

    >> BASE
    # BASE [ANGLE]

Example usage:

    >> BASE -30  <-- turn base 30 degrees counterclockwise (seen from above)
    >> BASE 0    <-- sets base to center position

#### Shoulder
Controls the DC-Motor for the shoulder joint. ```POSITION``` can be any integer value between 0 and 350
Send only the command name to see how it is used.

    >> SHOULDER
    # SHOULDER [ANGLE]

Example usage:

    >> SHOULDER 0   <-- sets the shoulder perfectly horizontal
    >> SHOULDER 30  <-- turns the shoulder 30 degrees to ground

#### Elbow
Controls the DC-Motor in the base. ```POSITION``` can be any integer value between 55 and 1023
Send only the command name to see how it is used.

    >> ELBOW
    # ELBOW [ANGLE]

Example usage:

    >> ELBOW 0    <-- sets the elbow in line with the shoulder
    >> ELBOW -45

#### Wrist
Controls the robot's wrist. ```ANGLE``` can be any integer value between -80 and 90. Send only the command name to see a overview:

    >> WRIST
    # WRIST [ANGLE]

Example usage:

    >> WRIST 60   <-- sets wrist to 60 degrees up
    >> WRIST 0    <-- sets wrist in line with the underarm
    >> WRIST -50  <-- sets wrist 50 degrees down

#### Grip
Control the robot's grip with the grip command. You can send the command name to see a overview:

    >> GRIP
    # GRIP ["OPEN" | "CLOSE" | "TOGGLE"]

Example usage:

    >> GRIP OPEN
    >> GRIP CLOSE
    >> GRIP TOGGLE

#### Autolevel
The robot is able to automatically maintain a specific wrist angle. To enable this use the autolevel command.

    >> AUTOLEVEL
    # AUTOLEVEL ["ON" | "H" | "V" | "OFF"]

Example usage:

    >> AUTOLEVEL ON   <-- keep the angle the wrist currently has
    >> AUTOLEVEL H    <-- Keep the wrist parallel to the ground (horizontal)
    >> AUTOLEVEL V    <-- Keep the wrist orthogonal to the ground (vertical)
    >> AUTOLEVEL OFF  <-- disables autolevel

The ```H``` and ```V``` options enable autolevel automatically.

#### Identify
A single question mark is the identify command. You can use this to check your connection settings and whether you're talking to the correct device.

    >> ?
    ? BIOROBOTIC_ARM


## Contributors
<p align="center">
    Fehmer, Manuel <br>
    Feldmann, Marlene <br>
    Feldmann, Thomas <br>
    Hussmann, Carsten <br>
    Neuhaus, Alexander
</p>
<p align="center">
    <img src="https://raw.github.com/tfeldmann/Biorobotic-Arm/master/Documentation/Roboterfabrik.png" alt="Logo">
</p>
