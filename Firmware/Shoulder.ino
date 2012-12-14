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
const int16_t SHOULDER_PWM_MIN = 0;  // 0...255
const int16_t SHOULDER_PWM_MAX = 255; // 0...255

// mechanical limits
const int16_t SHOULDER_MIN = -5;
const int16_t SHOULDER_MAX = 61;

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
    digitalWrite(SHOULDER_DIR, LOW);
    digitalWrite(SHOULDER_PWM, LOW);

    shoulder.pos_current = analogRead(SHOULDER_POT);
    shoulder.pos_desired = shoulder.pos_current;
}

void shoulder_set_angle(int16_t angle)
{
    shoulder.pos_desired = shoulder_angle2pos(constrain(angle, SHOULDER_MIN, SHOULDER_MAX));
}

void shoulder_control()
{
    shoulder.pos_current = analogRead(SHOULDER_POT);

    int16_t diff = shoulder.pos_desired - shoulder.pos_current;

    bool dir = (diff > 0);
    int16_t speed = constrain(abs(diff) * SHOULDER_CONTROLLER_P,
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
    return shoulder_pos2angle(shoulder.pos_current);
}

/*
 * For conversion we measured these values:
 *
 *      45° -> 260
 *       0° -> 45
 */
static int16_t shoulder_angle2pos(int16_t angle)
{
    return map(angle, 0, 45, 45, 260);
}
static int16_t shoulder_pos2angle(int16_t pos)
{
    return map(pos, 45, 260, 0, 45);
}
