/**
 * Ventilator.ino
 *
 */

const uint8_t VENTILATOR_PWM = 6;

void ventilator_init()
{
    pinMode(VENTILATOR_PWM, OUTPUT);
    digitalWrite(VENTILATOR_PWM, LOW);
}

void ventilator_blow(int16_t strength)
{
    analogWrite(VENTILATOR_PWM, strength*2.5);
}
