/**
 * Hand.ino
 *
 * Arduino        Wrist Servo
 *  WRIST_PWM ---- orange
 *        GND ---- black
 *        +5V ---- red
 *
 * Arduino        Hand Servo
 *  GRIP_PWM ----- orange
 *       GND ----- black
 *       +5V ----- red
 */
#include <Servo.h>

static Servo wrist_servo;
static Servo grip_servo;

// hardware connections
const uint8_t WRIST_PWM = 46;
const uint8_t GRIP_PWM = 44;

// mechanical limits
const uint8_t GRIP_CLOSE = 0;
const uint8_t GRIP_OPEN = 40;
const int16_t WRIST_MIN = -80;
const int16_t WRIST_MAX = 90;

static bool grip_open_flag;
volatile bool wrist_autolevel_enabled;
volatile int16_t wrist_autolevel_angle;


void hand_init()
{
    wrist_servo.attach(WRIST_PWM);
    grip_servo.attach(GRIP_PWM);
    grip_open();

    wrist_autolevel_enabled = false;
}


void grip_open()
{
    grip_servo.write(GRIP_OPEN);
    grip_open_flag = true;
}

void grip_close()
{
    grip_servo.write(GRIP_CLOSE);
    grip_open_flag = false;
}

bool grip_is_open()
{
    return grip_open_flag;
}


void wrist_set_angle(int16_t angle)
{
    angle = constrain(angle, WRIST_MIN, WRIST_MAX);
    wrist_servo.write(wrist_angle2pos(angle));
}

int16_t wrist_angle()
{
    return wrist_pos2angle(wrist_servo.read());
}

/*
 * For conversion we measured these values:
 *
 *      90° <-> 7
 *       0° <-> 98
 */
int16_t wrist_angle2pos(int16_t angle)
{
    int16_t pos = map(angle, 90, 0, 7, 98);
    return pos;
}

int16_t wrist_pos2angle(int16_t pos)
{
    int16_t angle = map(pos, 7, 98, 90, 0);
    return angle;
}


void wrist_autolevel_on()
{
    wrist_autolevel_enabled = true;
}

void wrist_autolevel_off()
{
    wrist_autolevel_enabled = false;
}

void wrist_autolevel_set(int16_t angle)
{
    wrist_autolevel_angle = angle;
}


void hand_control()
{
    if (wrist_autolevel_enabled)
    {
        int16_t angle =
            wrist_autolevel_angle
            - shoulder_angle()
            - elbow_angle();
        wrist_set_angle(angle);
    }
}
