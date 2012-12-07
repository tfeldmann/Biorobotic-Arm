/**
 * Hand.ino
 *
 * Arduino    Wrist Servo
 *   44 --------- orange
 *  GND --------- black
 *  +5V --------- red
 *
 * Arduino    Hand Servo
 *   46 --------- orange
 *  GND --------- black
 *  +5V --------- red
 */
#include <Servo.h>

const uint8_t WRIST_PWM = 44;
const uint8_t GRIP_PWM = 46;

const uint8_t GRIP_MAX = 25;
const uint8_t GRIP_MIN = 0;

static Servo wrist_servo;
static Servo grip_servo;
static bool grip_open_flag;

void hand_init()
{
    wrist_servo.attach(WRIST_PWM);
    grip_servo.attach(GRIP_PWM);
    grip_open();
}

void wrist_set_angle(uint8_t angle)
{
    wrist_servo.write(constrain(angle, 0, 180));
}

void grip_open()
{
    grip_servo.write(GRIP_MAX);
    grip_open_flag = true;
}

void grip_close()
{
    grip_servo.write(GRIP_MIN);
    grip_open_flag = false;
}

bool grip_is_open()
{
    return grip_open_flag;
}

uint8_t wrist_angle()
{
    return wrist_servo.read();
}
