/* MMA8452Q Example Code
by: Jim Wright
Based on original example code by: Jim Lindblom, SparkFun Electronics
date: March 28, 2012
license: Beerware - Use this code however you'd like. If you
find it useful you can buy me a beer some time.

This example code is essentially the same as the original code written
by Jim Lindblom, with the exception that the standard Arduino Wire library
is used instead of the custom i2c library originally supplied.
At the time of this writing, the release version of the Arduino Wire
library does not support repeated start commands, which are required by this
chip.  A revised Wire library with the necessary patch applied was committed
on Feb 18, 2012.  For this code to work, you will need to replace your Wire
library with the version at: https://github.com/arduino/Arduino/tree/master/libraries/Wire

Presumably, Arduino software after v1.0 should have this new code built in.


This code should provide example usage for most features of
the MMA8452Q 3-axis, I2C accelerometer. In the loop function
the accelerometer interrupt outputs will be polled, and either
the x/y/z accel data will be output, or single/double-taps,
portrait/landscape changes will be announced to the serial port.
Feel free to comment/uncomment out some of the Serial.print
lines so you can see the information you're most intereseted in.

The skeleton is here, feel free to cut/paste what code you need.
Play around with the settings in initMMA8452Q. Try running the
code without printing the accel values, to really appreciate
the single/double-tap and portrait landscape functions. The
P/L stuff is really neat, something not many accelerometers have.

Hardware setup:
MMA8452 Breakout ------------ Arduino
   3.3V --------------------- 3.3V
   SDA ----------------------- A4
   SCL ----------------------- A5
   INT2 ---------------------- D3
   INT1 ---------------------- D2
   GND ---------------------- GND

SDA and SCL should have external pull-up resistors (to 3.3V).
10k resistors worked for me. They should be on the breakout
board.

Arduino Mega boards have SDA on pin 20, and SCL on pin 21.  Please wire your board accordin

*/
#include <Wire.h>

// the SparkFun breakout board defaults to 1, set to 0 if SA0 jumper on the bottom of the board is set
#define SA0 1
#if SA0
    #define MMA8452_ADDRESS 0x1D  // SA0 is high, 0x1C if low
#else
    #define MMA8452_ADDRESS 0x1C
#endif

/* Set the scale below either 2, 4 or 8*/
const byte SCALE = 4;  // Sets full-scale range to +/-2, 4, or 8g. Used to calc real g values.
/* Set the output data rate below. Value should be between 0 and 7*/
const byte dataRate = 0;  // 0=800Hz, 1=400, 2=200, 3=100, 4=50, 5=12.5, 6=6.25, 7=1.56

/* Pin definitions */
int int1Pin = 2;  // These can be changed, 2 and 3 are the Arduinos ext int pins
int int2Pin = 3;

int accelCount[3];  // Stores the 12-bit signed value
float accelG[3];  // Stores the real accel value in g's

void collision_init()
{
    Wire.begin(); // join i2c bus (address optional for master)

    /* Read the WHO_AM_I register, this is a good test of communication */
    byte c = readRegister(0x0D);  // Read WHO_AM_I register
    if (c == 0x2A) // WHO_AM_I should always be 0x2A
    {
        initMMA8452(SCALE, dataRate);  // init the accelerometer if communication is OK
        // Serial.println("# Collision sensor found");
    }
    else
    {
        Serial.print("!03 Could not connect to MMA8452Q: 0x");
        Serial.println(c, HEX);
        while (1);  // Loop forever if communication doesn't happen
    }
}

byte val = 0;

void collision_update()
{
    static byte source;

    // /* If int1 goes high, all data registers have new data */
    // if (digitalRead(int1Pin)==1)  // Interrupt pin, should probably attach to interrupt function
    // {
    //     readAccelData(accelCount);  // Read the x/y/z adc values

    //     /* Below we'll print out the ADC values for acceleration
    //     for (int i=0; i<3; i++)
    //     {
    //         Serial.print(accelCount[i]);
    //         Serial.print("\t\t");
    //     }
    //     Serial.println();*/

    //     /* Now we'll calculate the accleration value into actual g's */
    //     for (int i=0; i<3; i++)
    //         accelG[i] = (float) accelCount[i]/((1<<12)/(2*SCALE));  // get actual g value, this depends on scale being set
    //     /* print out values */
    //     for (int i=0; i<3; i++)
    //     {
    //         Serial.print(accelG[i], 4);  // Print g values
    //         Serial.print("\t\t");  // tabs in between axes
    //     }
    //     Serial.println();
    // }

    /* If int2 goes high, either p/l has changed or there's been a single/double tap */
    if (digitalRead(int2Pin)==1 || 1)
    {
        source = readRegister(0x0C);  // Read the interrupt source reg.
        if ((source & 0x08)==0x08)  // Otherwise, if tap register is set go check that
            tapHandler();
    }
}

void readAccelData(int * destination)
{
    byte rawData[6];  // x/y/z accel register data stored here

    readRegisters(0x01, 6, &rawData[0]);  // Read the six raw data registers into data array

    /* loop to calculate 12-bit ADC and g value for each axis */
    for (int i=0; i<6; i+=2)
    {
        destination[i/2] = ((rawData[i] << 8) | rawData[i+1]) >> 4;  // Turn the MSB and LSB into a 12-bit value
        if (rawData[i] > 0x7F)
        {  // If the number is negative, we have to make it so manually (no 12-bit data type)
            destination[i/2] = ~destination[i/2] + 1;
            destination[i/2] *= -1;  // Transform into negative 2's complement #
        }
    }
}

/* This function will read the status of the tap source register.
And print if there's been a single or double tap, and on what
axis. */
void tapHandler()
{
    byte source = readRegister(0x22);  // Reads the PULSE_SRC register

    // if ((source & 0x10)==0x10)  // If AxX bit is set
    // {
    //     if ((source & 0x08)==0x08)  // If DPE (double puls) bit is set
    //         Serial.print("    Double Tap (2) on X");  // tabbing here for visibility
    //     else
    //         Serial.print("Single (1) tap on X");

    //     if ((source & 0x01)==0x01)  // If PoIX is set
    //         Serial.println(" +");
    //     else
    //         Serial.println(" -");
    // }

    // if ((source & 0x20)==0x20)  // If AxY bit is set
    // {
    //     if ((source & 0x08)==0x08)  // If DPE (double puls) bit is set
    //         Serial.print("    Double Tap (2) on Y");
    //     else
    //         Serial.print("Single (1) tap on Y");

    //     if ((source & 0x02)==0x02)  // If PoIY is set
    //         Serial.println(" +");
    //     else
    //         Serial.println(" -");
    // }

    // if ((source & 0x40)==0x40)  // If AxZ bit is set
    // {
    //     if ((source & 0x08)==0x08)  // If DPE (double puls) bit is set
    //         Serial.print("    Double Tap (2) on Z");
    //     else
    //         Serial.print("Single (1) tap on Z");
    //     if ((source & 0x04)==0x04)  // If PoIZ is set
    //         Serial.println(" +");
    //     else
    //         Serial.println(" -");
    // }

    if ((source & 0x40) == 0x40 || (source & 0x20) == 0x20 || (source & 0x10) == 0x10)
    {
        stop();
        tone_collision();
        Serial.println("!02 Collision detected");
    }
}

/* This function will read the p/l source register and
print what direction the sensor is now facing */
void portraitLandscapeHandler()
{
byte pl = readRegister(0x10);  // Reads the PL_STATUS register
switch((pl&0x06)>>1)  // Check on the LAPO[1:0] bits
{
    case 0:
        Serial.print("Portrait up, ");
        break;
    case 1:
        Serial.print("Portrait Down, ");
        break;
    case 2:
        Serial.print("Landscape Right, ");
        break;
    case 3:
        Serial.print("Landscape Left, ");
        break;
    }
    if (pl&0x01)  // Check the BAFRO bit
        Serial.print("Back");
    else
        Serial.print("Front");
    if (pl&0x40)  // Check the LO bit
        Serial.print(", Z-tilt!");
    Serial.println();
}

/* Initialize the MMA8452 registers
See the many application notes for more info on setting
all of these registers:
http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=MMA8452Q

Feel free to modify any values, these are settings that work well for me.
*/
void initMMA8452(byte fsr, byte dataRate)
{
    MMA8452Standby();  // Must be in standby to change registers

    /* Set up the full scale range to 2, 4, or 8g. */
    if ((fsr==2)||(fsr==4)||(fsr==8))
    writeRegister(0x0E, fsr >> 2);
    else
    writeRegister(0x0E, 0);

    /* Setup the 3 data rate bits, from 0 to 7 */
    writeRegister(0x2A, readRegister(0x2A) & ~(0x38));
    if (dataRate <= 7)
    writeRegister(0x2A, readRegister(0x2A) | (dataRate << 3));

    /* Set up portrait/landscap registers - 4 steps:
     1. Enable P/L
     2. Set the back/front angle trigger points (z-lock)
     3. Set the threshold/hysteresis angle
     4. Set the debouce rate
    // For more info check out this app note: http://cache.freescale.com/files/sensors/doc/app_note/AN4068.pdf */
    writeRegister(0x11, 0x40);  // 1. Enable P/L
    writeRegister(0x13, 0x44);  // 2. 29deg z-lock (don't think this register is actually writable)
    writeRegister(0x14, 0x84);  // 3. 45deg thresh, 14deg hyst (don't think this register is writable either)
    writeRegister(0x12, 0x50);  // 4. debounce counter at 100ms (at 800 hz)

    /* Set up single and double tap - 5 steps:
     1. Set up single and/or double tap detection on each axis individually.
     2. Set the threshold - minimum required acceleration to cause a tap.
     3. Set the time limit - the maximum time that a tap can be above the threshold
     4. Set the pulse latency - the minimum required time between one pulse and the next
     5. Set the second pulse window - maximum allowed time between end of latency and start of second pulse
     for more info check out this app note: http://cache.freescale.com/files/sensors/doc/app_note/AN4072.pdf */
    // writeRegister(0x21, 0x7F);  // 1. enable single/double taps on all axes
    writeRegister(0x21, 0x55);  // 1. single taps only on all axes
    // writeRegister(0x21, 0x6A);  // 1. double taps only on all axes

    writeRegister(0x23, 0x10);  // 2. x thresh at 2g, multiply the value by 0.0625g/LSB to get the threshold
    writeRegister(0x24, 0x10);  // 2. y thresh at 2g, multiply the value by 0.0625g/LSB to get the threshold
    writeRegister(0x25, 0x16);  // 2. z thresh at .5g, multiply the value by 0.0625g/LSB to get the threshold

    writeRegister(0x26, 0x30);  // 3. 30ms time limit at 800Hz odr, this is very dependent on data rate, see the app note
    writeRegister(0x27, 0xA0);  // 4. 200ms (at 800Hz odr) between taps min, this also depends on the data rate
    writeRegister(0x28, 0xFF);  // 5. 318ms (max value) between taps max

    /* Set up interrupt 1 and 2 */
    writeRegister(0x2C, 0x02);  // Active high, push-pull interrupts
    writeRegister(0x2D, 0x19);  // DRDY, P/L and tap ints enabled
    writeRegister(0x2E, 0x01);  // DRDY on INT1, P/L and taps on INT2

    MMA8452Active();  // Set to active to start reading
}

/* Sets the MMA8452 to standby mode.
It must be in standby to change most register settings */
void MMA8452Standby()
{
    byte c = readRegister(0x2A);
    writeRegister(0x2A, c & ~(0x01));
}

/* Sets the MMA8452 to active mode.
Needs to be in this mode to output data */
void MMA8452Active()
{
    byte c = readRegister(0x2A);
    writeRegister(0x2A, c | 0x01);
}

/* Read i registers sequentially, starting at address
into the dest byte arra */
void readRegisters(byte address, int i, byte * dest)
{
    Wire.beginTransmission(MMA8452_ADDRESS); // Open communications with device

    Wire.write(address);   // write register address
    Wire.endTransmission(false); // don't send a stop

    Wire.requestFrom(MMA8452_ADDRESS, i);

    int j = 0;
    while(Wire.available())    // slave may send less than requested
    {
        dest[j] = Wire.read();    // receive a byte as character
        j++;
    }
    Wire.endTransmission();    // stop transmitting
}

/* read a single byte from address and return it as a byte */
byte readRegister(uint8_t address)
{
    byte data;

    // From MMA8452Q Datasheet, Table 10. I2C Device Address Sequence
    // Command [6:1]Device Address  [0]SA0 [6:0]Device Address  R/W   8-bit Final Value
    // Read    001110               0       0x1C                1     0x39
    // Write   001110               0       0x1C                0     0x38
    // Read    001110               1       0x1D                1     0x3B
    // Write   001110               1       0x1D                0     0x3A


    Wire.beginTransmission(MMA8452_ADDRESS); // Open communications with device

    Wire.write(address);   // write register address
    Wire.endTransmission(false); // don't send a stop

    Wire.requestFrom(MMA8452_ADDRESS, 1);

    data = Wire.read();   // Get MSB result
    Wire.endTransmission();    // stop transmitting

    return data;
}

/* Writes a single byte (data) into address */
void writeRegister(unsigned char address, unsigned char data)
{
    Wire.beginTransmission(MMA8452_ADDRESS);  // Open communications with device
    Wire.write(address);        // write register address
    Wire.write(data);
    Wire.endTransmission();    // stop transmitting
}
