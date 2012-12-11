/**
 * Shoulder.ino
 *
 * Arduino         H-Bridge IC3 (see schematic)
 *  SHOULDER_PWM -- 5
 *  SHOULDER_DIR -- 3
 *
 * H-Bridge        Motor
 *  plus ---------- red
 *  minus --------- black
 *
 * Arduino         Potentiometer
 *  SHOULDER_POT -- orange
 *  GND ----------- black
 *  +5V ----------- red
 *
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
    uint8_t speed = constrain(abs(diff) * SHOULDER_CONTROLLER_P,
        SHOULDER_PWM_MIN,
        SHOULDER_PWM_MAX);
    if (abs(diff) <= SHOULDER_TOLERANCE) speed = 0;

    digitalWrite(SHOULDER_DIR, dir);
    analogWrite(SHOULDER_PWM, speed);
}

int16_t shoulder_position()
{
    return shoulder.pos_current;
}

int16_t shoulder_angle()
{
    // if the shoulder is perfectly horizontal we read 50 on the potentiometer.
    // The other values can be calculated as we know that have 1024 steps / 270
    // degrees.
    return map(shoulder.pos_current, 50, 1023, 0, 256);
}
