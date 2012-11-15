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
    char *arg = serialCommand.next();
    if (arg == NULL)
    {
        Serial.println("# BASE [ANGLE]");
    }
    else
    {
        int16_t desired_pos = atoi(arg);
        base_set_desired_pos(desired_pos);
        Serial.print("# BASE ");
        Serial.println(desired_pos);
    }
}

void scmd_shoulder()
{
    Serial.println("# SHOULDER [ANGLE]");
}

void scmd_wrist()
{
    char *arg = serialCommand.next();
    if (arg == NULL)
    {
        Serial.println("# WRIST [ANGLE]");
    }
    else
    {
        uint8_t angle = atoi(arg);
        wrist_set_angle(angle);
        Serial.print("# WRIST ");
        Serial.println(angle);
    }
}

void scmd_grip()
{
    char *arg = serialCommand.next();
    if (arg == NULL)
    {
        Serial.println("# GRIP [OPEN|CLOSE]");
    }
    else
    {
        if (strcmp(arg, "OPEN") == 0)
        {
            grip_open();
            Serial.println("# GRIP OPEN");
        }
        else if (strcmp(arg, "CLOSE") == 0)
        {
            grip_close();
            Serial.println("# GRIP CLOSE");
        }
        else
        {
            uint8_t angle = atoi(arg);
            grip_set_angle(angle);
            Serial.print("# GRIP ");
            Serial.println(angle);
        }
    }
}
