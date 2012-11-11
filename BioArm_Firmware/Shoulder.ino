
#define SHOULDER_POT XX
#define SHOULDER_STP 32
#define SHOULDER_DIR XX
#define SHOULDER_MS1 XX
#define SHOULDER_MS2 XX
#define SHOULDER_MS3 XX
#define SHOULDER_SLP XX

#define SHOULDER_SPEED_MAX 200 // Hz

void shoulder_init()
{
    pinMode(SHOULDER_STP, OUTPUT);
    TCCR3A = 0; // set entire TCCRA register to 0
    TCCR3B = 0; // same for TCCRB
    TCNT3  = 0; // initialize counter value to 0
    OCR3A  = 0; // timer compare register
    TCCR3B |= (1 << WGM12);  // turn on CTC mode
    TIMSK3 |= (1 << OCIE3A); // enable timer compare interrupt
}

void shoulder_control()
{

}

/**
 * Sets the shoulder motor speed
 * @param speed is any value between -1.0 and 1.0
 */
void shoulder_set_speed(float speed)
{
    if (speed == 0)
    {
        shoulder_motor_stop();
        return;
    }
    else
    {
        bool dir = (speed >= 0) ? HIGH : LOW;
        //digitalWrite(SHOULDER_DIR, dir);
        speed = abs(constrain(speed, -1.0, 1.0));
        OCR3A = 15624 / (SHOULDER_SPEED_MAX * speed); // 15624=16Mhz/prescaler-1
        shoulder_motor_start();
    }
}

void shoulder_motor_stop()
{
    TCCR3B &= ~(1 << CS10);
    TCCR3B &= ~(1 << CS12);
}

void shoulder_motor_start()
{
    // setting the prescaler starts the timer
    TCCR3B |= (1 << CS12) | (1 << CS10); // 1024 prescaler
}

ISR(TIMER3_COMPA_vect)
{
    pulse(SHOULDER_STP); // create a short pulse (one step)
}
