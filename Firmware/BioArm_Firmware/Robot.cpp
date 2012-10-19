/**
 * @file Robot.cpp
 */
#include "Robot.h"

Robot::Robot()
{
	base     = new Base();
	shoulder = new Shoulder();
	elbow    = new Elbow();
	wrist    = new Wrist();
	grip     = new Grip();
}

void Robot::update()
{

}
