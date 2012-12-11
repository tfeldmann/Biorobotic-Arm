/**
 * Base.ino
 *
 * Arduino      H-Bridge IC2 (see schematic)
 *  BASE_PWM --- 5
 *  BASE_DIR --- 3
 *
 * H-Bridge     Motor
 *  plus ------- red
 *  minus ------ black
 *
 * Arduino      Potentiometer
 *  BASE_POT --- yellow
 *  GND -------- black
 *  +5V -------- red
 *
 */

const uint8_t BASE_POT = A3;
const uint8_t BASE_DIR = 12;
const uint8_t BASE_PWM = 13;  // uses timer0

const int8_t BASE_TOLERANCE = 1;
const uint16_t BASE_PWM_MIN = 60;  // 0...255
const uint16_t BASE_PWM_MAX = 150;  // 0...255

// controller settings
#define BASE_CONTROLLER_P 5

typedef struct
{
    volatile int16_t pos_current;
    volatile int16_t pos_desired;
} Base;
static Base base;


void base_init()
{
    pinMode(BASE_POT, INPUT);
    pinMode(BASE_DIR, OUTPUT);
    pinMode(BASE_PWM, OUTPUT);
}

void base_set_desired_pos(int16_t pos)
{
    base.pos_desired = pos;
}

void base_control()
{
    base.pos_current = analogRead(BASE_POT);

    int16_t diff = base.pos_desired - base.pos_current;

    bool dir = (diff > 0);
    uint8_t speed = constrain(abs(diff) * BASE_CONTROLLER_P,
        BASE_PWM_MIN,
        BASE_PWM_MAX);
    if (abs(diff) <= BASE_TOLERANCE) speed = 0;

    digitalWrite(BASE_DIR, dir);
    analogWrite(BASE_PWM, speed);
}

int16_t base_position()
{
    return base.pos_current;
}
