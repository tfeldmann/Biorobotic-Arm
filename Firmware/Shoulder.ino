/**
 * Shoulder.ino
 *
 * Arduino         H-Bridge
 *  SHOULDER_PWM -- 5
 *  SHOULDER_DIR -- 3
 *
 * H-Bridge     Motor
 *  Plus ------- Plus
 *  Minus ------ Minus
 *
 * Arduino         Potentiometer
 *  SHOULDER_POT -- yellow
 *  GND ----------- black
 *  +5V ----------- red
 */

const uint8_t SHOULDER_POT = A4;
const uint8_t SHOULDER_DIR = 7;
const uint8_t SHOULDER_PWM = 9;

const int8_t SHOULDER_TOLERANCE = 1;
const uint16_t SHOULDER_PWM_MIN = 50;  // 0...255
const uint16_t SHOULDER_PWM_MAX = 255; // 0...255

// controller settings
#define SHOULDER_CONTROLLER_P 20

typedef struct
{
    volatile int16_t pos_current;
    volatile int16_t pos_desired;
} Shoulder;
static Shoulder shoulder;


void shoulder_init()
{
    pinMode(SHOULDER_POT, INPUT);
    pinMode(SHOULDER_DIR, OUTPUT);
    pinMode(SHOULDER_PWM, OUTPUT);
}

void shoulder_set_desired_pos(int16_t pos)
{
    shoulder.pos_desired = pos;
}

void shoulder_control()
{
    shoulder.pos_current = analogRead(SHOULDER_POT);

    int16_t diff = shoulder.pos_desired - shoulder.pos_current;

    bool dir = (diff > 0);
    uint8_t speed = constrain(abs(diff) * SHOULDER_CONTROLLER_P, SHOULDER_PWM_MIN, SHOULDER_PWM_MAX);
    if (abs(diff) <= SHOULDER_TOLERANCE) speed = 0;

    digitalWrite(SHOULDER_DIR, dir);
    analogWrite(SHOULDER_PWM, speed);
}

int16_t shoulder_position()
{
    return shoulder.pos_current;
}
