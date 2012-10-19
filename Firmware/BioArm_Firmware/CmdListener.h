/**
 * @file CmdListener.h
 */
#pragma once
#include <SerialCommand.h>
#include "Robot.h"

namespace CmdListener
{
	extern Robot *robot;
	extern SerialCommand serialCommand;

	void grip();
	void unknown(const char *command);
	void init(Robot *_robot);
	void update();
}
