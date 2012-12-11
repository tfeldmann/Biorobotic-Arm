/**
 * Elbow.ino
 *
 * Arduino      H-Bridge
 *  ELBOW_PWM -- 5
 *  ELBOW_DIR -- 3
 *
 * H-Bridge     Motor
 *  Plus ------- Plus
 *  Minus ------ Minus
 *
 * Arduino      Potentiometer
 *  ELBOW_POT -- yellow
 *  GND -------- black
 *  +5V -------- red
 */

const uint8_t ELBOW_POT = A5;
const uint8_t ELBOW_DIR = 2;
const uint8_t ELBOW_PWM = 4;

const int8_t ELBOW_TOLERANCE = 1;
const uint16_t ELBOW_PWM_MIN = 50;  // 0...255
const uint16_t ELBOW_PWM_MAX = 255; // 0...255

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
    elbow.pos_desired = pos;
}

void elbow_control()
{
    elbow.pos_current = analogRead(ELBOW_POT);

    int16_t diff = elbow.pos_desired - elbow.pos_current;

    bool dir = (diff < 0);
    uint8_t speed = constrain(abs(diff) * ELBOW_CONTROLLER_P, ELBOW_PWM_MIN, ELBOW_PWM_MAX);
    if (abs(diff) <= ELBOW_TOLERANCE) speed = 0;

    digitalWrite(ELBOW_DIR, dir);
    analogWrite(ELBOW_PWM, speed);
}

int16_t elbow_position()
{
    return elbow.pos_current;
}