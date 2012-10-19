/**
 * @file CmdListener.h
 */
#import "CmdListener.h"

namespace CmdListener
{
	Robot *robot;
	SerialCommand serialCommand;

	void grip()
	{
		// @todo parse the intention
		robot->grip->open();
		Serial.println("-- opens grip");
	}

	void unknown(const char *command)
	{
		Serial.print("-- Unknown command: ");
		Serial.println(command);
	}

	void init(Robot *_robot)
	{
		robot = _robot;
		serialCommand.addCommand("GRIP", grip);
		serialCommand.setDefaultHandler(unknown);
	}

	void update()
	{
		serialCommand.readSerial();
	}
}
