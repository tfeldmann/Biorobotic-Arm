#include <SerialCommand.h>
SerialCommand serialCommand;

void scmd_init()
{
	serialCommand.addCommand("?",        scmd_identify);
	serialCommand.addCommand("BASE",     scmd_base);
    serialCommand.addCommand("SHOULDER", scmd_shoulder);
    serialCommand.addCommand("WRIST",    scmd_wrist);
    serialCommand.addCommand("GRIP",     scmd_grip);
    serialCommand.setDefaultHandler(scmd_unknown);
}

void scmd_update()
{
    serialCommand.readSerial();
}

void scmd_unknown(const char *command)
{
    Serial.print("# UNKNOWN: ");
    Serial.println(command);
}

void scmd_identify()
{
	Serial.println("BIOROBOTIC_ARM_1.0");
}

void scmd_base()
{
	Serial.println("# BASE [ANGLE]");
}

void scmd_shoulder()
{
	Serial.println("# SHOULDER [ANGLE]");
}

void scmd_wrist()
{
	Serial.println("# WRIST [ANGLE]");
}

void scmd_grip()
{
    Serial.println("# GRIP [OPEN|CLOSE|ANGLE]");
}
