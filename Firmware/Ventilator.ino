/**
 * Ventilator.ino
 *
 */

const uint8_t VENTILATOR_PWM = 3;

void ventilator_init()
{
    pinMode(VENTILATOR_PWM, OUTPUT);
    digitalWrite(VENTILATOR_PWM, LOW);
}

void ventilator_blow(int16_t strength)
{
    int16_t pwm = map(strength, 0, 100, 0, 255);
    analogWrite(VENTILATOR_PWM, pwm);
}
