/**
 * @file Grip.h
 */
#pragma once
#include <Servo.h>
#include "Settings.h"

/**
 * Grip Class
 * Controls the robot's hand
 */
class Grip
{
public:
	Servo servo;

	Grip();
	void open();
	void close();
};
