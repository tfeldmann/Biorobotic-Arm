
#define ELBOW_POT XX
#define ELBOW_STP 30
#define ELBOW_DIR XX
#define ELBOW_MS1 XX
#define ELBOW_MS2 XX
#define ELBOW_MS3 XX
#define ELBOW_SLP XX

#define ELBOW_SPEED_MAX 200 // Hz

void elbow_init()
{
    pinMode(ELBOW_STP, OUTPUT);
    TCCR4A = 0; // set entire TCCRA register to 0
    TCCR4B = 0; // same for TCCRB
    TCNT4  = 0; // initialize counter value to 0
    OCR4A  = 0; // timer compare register
    TCCR4B |= (1 << WGM12);  // turn on CTC mode
    TIMSK4 |= (1 << OCIE4A); // enable timer compare interrupt
}

void elbow_control()
{

}

/**
 * Sets the elbow motor speed
 * @param speed is any value between -1.0 and 1.0
 */
void elbow_set_speed(float speed)
{
    if (speed == 0)
    {
        elbow_motor_stop();
        return;
    }
    else
    {
        bool dir = (speed >= 0) ? HIGH : LOW; // todo set pin
        speed = abs(constrain(speed, -1.0, 1.0));
        OCR4A = 15624 / (ELBOW_SPEED_MAX * speed); // 15624=16Mhz/prescaler-1
        elbow_motor_start();
    }
}

void elbow_motor_stop()
{
    TCCR4B &= ~(1 << CS10);
    TCCR4B &= ~(1 << CS12);
}

void elbow_motor_start()
{
    // setting the prescaler starts the timer
    TCCR4B |= (1 << CS12) | (1 << CS10); // 1024 prescaler
}

ISR(TIMER4_COMPA_vect)
{
    pulse(ELBOW_STP); // create a short pulse (one step)
}
