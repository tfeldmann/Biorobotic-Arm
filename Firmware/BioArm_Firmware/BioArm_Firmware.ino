/**
 * @file BioArm_Firmware.ino
 *
 *     ____  _       ___                      _______       __
 *    / __ )(_)___  /   |  _________ ___     / ____/ |     / /
 *   / __  / / __ \/ /| | / ___/ __ `__ \   / /_   | | /| / /
 *  / /_/ / / /_/ / ___ |/ /  / / / / / /  / __/   | |/ |/ /
 * /_____/_/\____/_/  |_/_/  /_/ /_/ /_/  /_/      |__/|__/
 *
 * This is the entry point for the biorobotic-arm's firmware.
 * You can find the repository at: https://github.com/tfeldmann/Biorobotic-Arm
 */

#include <SerialCommand.h>
#include <Servo.h>
#include "CmdListener.h"
#include "Robot.h"

Robot *robot;

void setup()
{
	// create the robot
	robot = new Robot();

	// establish serial communication
	Serial.begin(19200);
	CmdListener::init(robot);
}

void loop()
{
	robot->update();
	CmdListener::update();
}
