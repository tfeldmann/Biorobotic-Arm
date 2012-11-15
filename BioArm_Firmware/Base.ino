/**
 * Base.ino
 *
 * Arduino    H-Bridge
 *    4 --------- 5
 *   52 --------- 3
 *
 * H-Bridge   Motor
 *  OP1 --------- blue
 *  OP2 --------- white
 *
 * Arduino    Potentiometer
 *   A0 --------- yellow
 *  GND --------- black
 *  +5V --------- red
 */

const uint8_t BASE_POT = A0;
const uint8_t BASE_DIR = 52;
const uint8_t BASE_PWM = 4;  // uses timer0

const uint16_t BASE_PWM_MIN = 30;
const uint16_t BASE_PWM_MAX = 255;
const int8_t BASE_TOLERANCE = 1;

// controller settings
#define BASE_CONTROLLER_P 20

typedef struct
{
    volatile int16_t pos_desired;
    volatile int16_t pos_current;
} Base;
Base base;


void base_init()
{
    pinMode(BASE_POT, INPUT);
    pinMode(BASE_DIR, OUTPUT);
    pinMode(BASE_PWM, OUTPUT);
}

void base_desired_pos(int16_t pos)
{
    base.pos_desired = pos;
}

void base_control()
{
    base.pos_current = analogRead(BASE_POT);
    int16_t diff = base.pos_desired - base.pos_current;

    bool dir = (diff > 0);
    uint8_t speed = constrain(abs(diff) * BASE_CONTROLLER_P, BASE_PWM_MIN, BASE_PWM_MAX);
    if (abs(diff) <= BASE_TOLERANCE) speed = 0;

    digitalWrite(BASE_DIR, dir);
    analogWrite(BASE_PWM, speed);
}

void base_update()
{
    // interpolate here
}

int16_t base_position()
{
    return base.pos_current;
}
