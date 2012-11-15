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

Servo wrist_servo;
Servo grip_servo;

void hand_init()
{
    wrist_servo.attach(WRIST_PWM);
    grip_servo.attach(GRIP_PWM);
}

void wrist_set_angle(uint8_t angle)
{
    wrist_servo.write(constrain(angle, 0, 180));
}

void grip_open()
{
    grip_servo.write(GRIP_MAX);
}

void grip_close()
{
    grip_servo.write(GRIP_MIN);
}

void grip_set_angle(uint8_t angle)
{
    grip_servo.write(constrain(angle, GRIP_MIN, GRIP_MAX));
}

uint8_t wrist_angle()
{
    return wrist_servo.read();
}

uint8_t grip_angle()
{
    return grip_servo.read();
}
