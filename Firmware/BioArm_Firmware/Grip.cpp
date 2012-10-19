/**
 * @file Grip.cpp
 */
#include "Grip.h"
#define GRIP_OPEN_ANGLE  0
#define GRIP_CLOSE_ANGLE 180

Grip::Grip()
{
	servo.attach(GRIP_SERVO);
}

void Grip::open()
{
	servo.write(GRIP_OPEN_ANGLE);
}

void Grip::close()
{
	servo.write(GRIP_CLOSE_ANGLE);
}

void Grip::angle(uint8_t angle)
{
	servo.write(angle);
}
