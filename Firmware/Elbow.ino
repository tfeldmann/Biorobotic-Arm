/**
 * Elbow.ino
 *
 * Arduino      H-Bridge IC4 (see schematic)
 *  ELBOW_PWM -- 5
 *  ELBOW_DIR -- 3
 *
 * H-Bridge     Motor
 *  plus ------- red
 *  minus ------ black
 *
 * Arduino      Potentiometer
 *  ELBOW_POT -- green
 *  GND -------- black
 *  +5V -------- red
 *
 */

const uint8_t ELBOW_POT = A5;
const uint8_t ELBOW_DIR = 2;
const uint8_t ELBOW_PWM = 4;

const int8_t ELBOW_TOLERANCE = 1;
const int16_t ELBOW_PWM_MIN = 0;  // 0...255
const int16_t ELBOW_PWM_MAX = 255;  // 0...255

// mechanical limits
const int16_t ELBOW_MIN = -165;
const int16_t ELBOW_MAX =  40;

// controller settings
#define ELBOW_CONTROLLER_P 20

typedef struct
{
    volatile int16_t pos_current;
    volatile int16_t pos_desired;
} Elbow;
static Elbow elbow;


void elbow_init()
{
    pinMode(ELBOW_POT, INPUT);
    pinMode(ELBOW_DIR, OUTPUT);
    pinMode(ELBOW_PWM, OUTPUT);
    digitalWrite(ELBOW_DIR, LOW);
    digitalWrite(ELBOW_PWM, LOW);

    elbow.pos_current = analogRead(ELBOW_POT);
    elbow.pos_desired = elbow.pos_current;
}

void elbow_set_angle(int16_t angle)
{
    angle = constrain(angle, ELBOW_MIN, ELBOW_MAX);
    elbow.pos_desired = elbow_angle2pos(angle);
}

void elbow_increment_angle(int16_t angle)
{
    elbow_set_angle(angle + elbow_pos2angle(elbow.pos_desired));
}

void elbow_stop()
{
    elbow.pos_desired = elbow.pos_current;
}

void elbow_control()
{
    elbow.pos_current = analogRead(ELBOW_POT);

    int16_t diff = elbow.pos_desired - elbow.pos_current;

    bool dir = (diff < 0);
    int16_t speed = constrain(abs(diff) * ELBOW_CONTROLLER_P,
        ELBOW_PWM_MIN,
        ELBOW_PWM_MAX);
    if (abs(diff) <= ELBOW_TOLERANCE) speed = 0;

    digitalWrite(ELBOW_DIR, dir);
    analogWrite(ELBOW_PWM, speed);
}

int16_t elbow_angle()
{
    return elbow_pos2angle(elbow.pos_current);
}


/*
 * For conversion we measured these values:
 *
 *       0° <-> 810
 *     -90° <-> 397
 */
static int16_t elbow_angle2pos(int16_t angle)
{
    return map(angle, 0, -90, 810, 397);
}
static int16_t elbow_pos2angle(int16_t pos)
{
    return map(pos, 810, 397, 0, -90);
}
