/**
 * @file Grip.cpp
 */
#include "Grip.h"

Grip::Grip()
{
	servo.attach(GRIP_SERVO);
}

void Grip::open()
{
	servo.write(0);
}

void Grip::close()
{
	servo.write(180);
}
