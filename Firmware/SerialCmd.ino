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
    serialCommand.addCommand("RESET",     scmd_reset);
    serialCommand.addCommand("STANDBY",   scmd_standby);
    serialCommand.addCommand("BEEP",      scmd_beep);
    serialCommand.addCommand("VENT",      scmd_ventilator);
    serialCommand.setDefaultHandler(scmd_unknown);
}

void scmd_update()
{
    serialCommand.readSerial();
}

void scmd_unknown(const char *command)
{
    Serial.print("!01 Unknown command: ");
    Serial.println(command);
}

void scmd_identify()
{
    Serial.println("? BIOROBOTIC_ARM");
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
        int16_t desired_angle = atoi(arg);
        base_set_angle(desired_angle);
        Serial.print("# BASE ");
        Serial.println(desired_angle);
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
        shoulder_set_angle(angle);
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
        elbow_set_angle(angle);
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
        wrist_autolevel_off();
        int16_t angle = atoi(arg);
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
    stop();
    Serial.println("# STOP");
}

void scmd_autolevel()
{
    char *arg = serialCommand.next();
    if (arg == NULL)
    {
        Serial.println("# AUTOLEVEL [ON|OFF|H|V]");
    }
    else
    {
        if (strcmp(arg, "ON") == 0)
        {
            int16_t angle = shoulder_angle() + elbow_angle() + wrist_angle();
            wrist_autolevel_set(angle);
            wrist_autolevel_on();
            Serial.println("# AUTOLEVEL ON");
        }
        else if (strcmp(arg, "OFF") == 0)
        {
            wrist_autolevel_off();
            Serial.println("# AUTOLEVEL OFF");
        }
        else if (strcmp(arg, "H") == 0)
        {
            wrist_autolevel_on();
            wrist_autolevel_set(0);
            Serial.println("# AUTOLEVEL H");
        }
        else if (strcmp(arg, "V") == 0)
        {
            wrist_autolevel_set(-90);
            wrist_autolevel_on();
            Serial.println("# AUTOLEVEL V");
        }
    }
}

void scmd_reset()
{
    reset();
    Serial.println("# RESET");
}

void scmd_standby()
{
    standby();
    Serial.println("# STANDBY");
}

void scmd_beep()
{
    tone_beep();
    Serial.println("# BEEP");
}

void scmd_ventilator()
{
    char *arg = serialCommand.next();
    if (arg == NULL)
    {
        Serial.println("# VENT [STRENGTH]");
    }
    else
    {
        int16_t strength = atoi(arg);
        ventilator_blow(strength);
        Serial.print("# VENT ");
        Serial.println(strength);
    }
}
