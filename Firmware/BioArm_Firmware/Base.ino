
#define BASE_POT A0
#define BASE_DIR  3
#define BASE_PWM  4 // 4 or 13 (uses timer0)

#define BASE_DIR_CCW HIGH
#define BASE_DIR_CW   LOW
#define BASE_PWM_MIN   40
#define BASE_PWM_MAX  255

int desired_value;

void base_init()
{
    pinMode(BASE_DIR, OUTPUT);
    pinMode(BASE_PWM, OUTPUT);
}

void base_control()
{

}

void base_update()
{
    int16_t val = 300;

    int16_t poti_value = analogRead(BASE_POT);

    // select direction
    digitalWrite(BASE_DIR, (poti_value > val) ? BASE_DIR_CCW : BASE_DIR_CW);

    // run
    int16_t speed = BASE_PWM_MAX;
    int16_t distance = abs(poti_value - val);
    if (distance < BASE_PWM_MAX)
    {
        speed = distance;
    }
    analogWrite(BASE_PWM, speed);

    Serial.println("base");
}
