/**
 * Helper.ino
 */
void pulse(uint8_t pin)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    digitalWrite(pin, LOW);
}
