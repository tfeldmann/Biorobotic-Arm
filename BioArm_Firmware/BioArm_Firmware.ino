/**
 *     ____  _       ___                      _______       __
 *    / __ )(_)___  /   |  _________ ___     / ____/ |     / /
 *   / __  / / __ \/ /| | / ___/ __ `__ \   / /_   | | /| / /
 *  / /_/ / / /_/ / ___ |/ /  / / / / / /  / __/   | |/ |/ /
 * /_____/_/\____/_/  |_/_/  /_/ /_/ /_/  /_/      |__/|__/
 *
 * This is the entry point for the biorobotic-arm's firmware.
 * You can find the repository at: https://github.com/tfeldmann/Biorobotic-Arm
 *
 * Used timers:
 * ------------
 * Timer0: Arduino internal functions
 * Timer1: Control tick
 * Timer2: Base DC-Motor PWM
 * Timer3: Shoulder stepper
 * Timer4: Elbow stepper
 * Timer5: Servos in hand
 */

void setup()
{
    // serial connection (115200, 8N1)
    Serial.begin(115200);
    scmd_init();

    // base_init();
    // shoulder_init();
    // elbow_init();
    // init_hand();

    // shoulder_set_speed(1.0);
    // elbow_set_speed(1.0);

    start_control_tick(50); // 50Hz
    base_desired_angle(300);
}

void loop()
{
    scmd_update();

    // send current positions to PC
    static unsigned long timestamp = millis();
    if (millis() - timestamp > 50)
    {
        Serial.println(base_position());
        timestamp = millis();
    }
}

void start_control_tick(uint8_t freq)
{
    cli();
    TCCR1A = 0; // set entire TCCRA register to 0
    TCCR1B = 0; // same for TCCRB
    TCNT1  = 0; // initialize counter value to 0
    OCR1A  = 15625 / freq;
    TCCR1B |= (1 << WGM12);  // turn on CTC mode
    TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
    TCCR1B |= (1 << CS12) | (1 << CS10); // 1024 prescaler
    sei();
}

ISR(TIMER1_COMPA_vect)
{
    base_control();
    shoulder_control();
    elbow_control();
}
