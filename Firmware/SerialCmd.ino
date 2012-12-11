/**
 * SerialCmd.ino
 */
#include <SerialCommand.h>
SerialCommand serialCommand;

void scmd_init()
{
    serialCommand.addCommand("?",         scmd_identify);
    serialCommand.addCommand("BASE",      scmd_base);
    serialCommand.addCommand("SHOULDER",  scmd_shoulder);
    serialCommand.addCommand("ELBOW",     scmd_elbow);
    serialCommand.addCommand("WRIST",     scmd_wrist);
    serialCommand.addCommand("GRIP",      scmd_grip);
    serialCommand.addCommand("STOP",      scmd_stop);
    serialCommand.addCommand("AUTOLEVEL", scmd_autolevel);
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
    Serial.println("BIOROBOTIC_ARM");
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
    char *arg = serialCommand.next();
    if (arg == NULL)
    {
        Serial.println("# SHOULDER [ANGLE]");
    }
    else
    {
        int16_t angle = atoi(arg);
        shoulder_set_desired_pos(angle);
        Serial.print("# SHOULDER ");
        Serial.println(angle);
    }
}

void scmd_elbow()
{
    char *arg = serialCommand.next();
    if (arg == NULL)
    {
        Serial.println("# ELBOW [ANGLE]");
    }
    else
    {
        int16_t angle = atoi(arg);
        elbow_set_desired_pos(angle);
        Serial.print("# ELBOW ");
        Serial.println(angle);
    }
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
        Serial.println("# GRIP [OPEN|CLOSE|TOGGLE]");
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
        else if (strcmp(arg, "TOGGLE") == 0)
        {
            grip_is_open() ? grip_close() : grip_open();
            Serial.println("# GRIP TOGGLE");
        }
    }
}

void scmd_stop()
{
    base_set_desired_pos(base_position());
    shoulder_set_desired_pos(shoulder_position());
    elbow_set_desired_pos(elbow_position());
}

void scmd_autolevel()
{
    char *arg = serialCommand.next();
    if (arg == NULL)
    {
        Serial.println("# AUTOLEVEL [ON|OFF|TOGGLE]");
    }
    else
    {
        if (strcmp(arg, "ON") == 0)
        {
            wrist_set_autolevel(true);
            Serial.println("# AUTOLEVEL ON");
        }
        else if (strcmp(arg, "OFF") == 0)
        {
            wrist_set_autolevel(false);
            Serial.println("# AUTOLEVEL OFF");
        }
        else if (strcmp(arg, "TOGGLE") == 0)
        {
            wrist_set_autolevel(!wrist_is_autolevel());
            Serial.println("# AUTOLEVEL TOGGLE");
        }
    }
}
