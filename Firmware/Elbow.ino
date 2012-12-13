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
const uint16_t ELBOW_PWM_MIN = 50;  // 0...255
const uint16_t ELBOW_PWM_MAX = 255; // 0...255

// mechanical limits
const int16_t ELBOW_POS_MIN = 55;
const int16_t ELBOW_POS_MAX = 1023;

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
}

void elbow_set_desired_pos(int16_t pos)
{
    elbow.pos_desired = constrain(pos, ELBOW_POS_MIN, ELBOW_POS_MAX);
}

void elbow_control()
{
    elbow.pos_current = analogRead(ELBOW_POT);

    int16_t diff = elbow.pos_desired - elbow.pos_current;

    bool dir = (diff < 0);
    uint8_t speed = constrain(abs(diff) * ELBOW_CONTROLLER_P,
        ELBOW_PWM_MIN,
        ELBOW_PWM_MAX);
    if (abs(diff) <= ELBOW_TOLERANCE) speed = 0;

    digitalWrite(ELBOW_DIR, dir);
    analogWrite(ELBOW_PWM, speed);
}

int16_t elbow_position()
{
    return elbow.pos_current;
}

int16_t elbow_angle()
{
    // when the elbow is perfectly in line with the shoulder we read 810 on the
    // potentiometer. The other values can be calculated as we know that have
    // 1024 steps / 270 degrees.
    return map(elbow.pos_current, 810, 0, 0, 213);
}
