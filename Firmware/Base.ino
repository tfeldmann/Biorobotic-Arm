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
const uint16_t BASE_PWM_MIN = 50;  // 0...255
const uint16_t BASE_PWM_MAX = 200;  // 0...255

// controller settings
#define BASE_CONTROLLER_KP 10

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
    digitalWrite(BASE_DIR, LOW);
    digitalWrite(BASE_PWM, LOW);

    base.pos_current = analogRead(BASE_POT);
    base.pos_desired = base.pos_current;
}

void base_set_angle(int16_t angle)
{
    base.pos_desired = base_angle2pos(angle);
}

void base_increment_angle(int16_t angle)
{
    base_set_angle(angle + base_pos2angle(base.pos_current));
}

void base_stop()
{
    base.pos_desired = base.pos_current;
}

void base_control()
{
    // input
    base.pos_current = analogRead(BASE_POT);

    // control
    int16_t delta = base.pos_desired - base.pos_current;
    int16_t speed = BASE_CONTROLLER_KP * delta;

    // output
    bool dir = (speed > 0);
    speed = constrain(abs(speed), BASE_PWM_MIN, BASE_PWM_MAX);
    if (abs(delta) <= BASE_TOLERANCE) speed = 0;

    digitalWrite(BASE_DIR, dir);
    analogWrite(BASE_PWM, speed);
}


int16_t base_angle()
{
    return base_pos2angle(base.pos_current);
}

/*
 * For conversion we measured these values:
 *
 *       -135° <-> 1023
 *        135° <-> 0
 */
static int16_t base_angle2pos(int16_t angle)
{
    return map(angle, -135, 135, 1023, 0);
}
static int16_t base_pos2angle(int16_t pos)
{
    return map(pos, 1023, 0, -135, 135);
}
