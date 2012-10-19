/**
 * @file Robot.h
 */
#pragma once
#include "Base.h"
#include "Shoulder.h"
#include "Elbow.h"
#include "Wrist.h"
#include "Grip.h"

/**
 * Robot Class
 */
class Robot
{
public:
	Base     *base;
	Shoulder *shoulder;
	Elbow    *elbow;
	Wrist    *wrist;
	Grip     *grip;

	Robot();
	void update();
};
