import oscP5.*;
import java.awt.*;
import processing.serial.*;
import org.gicentre.utils.multisketch.*;

Serial serial;
OscP5 oscP5;
BaseSketch baseSketch = new BaseSketch();
ArmSketch armSketch = new ArmSketch();
HandSketch handSketch = new HandSketch();
LogoSketch logoSketch = new LogoSketch();

int active_component = 0;
int gyro_pitch, gyro_pitch_old;
int gyro_yaw, gyro_yaw_old;

void setup()
{
    size(700, 700);
    noLoop();

    String portName = Serial.list()[4];
    println(portName);
    serial = new Serial(this, portName, 19200);
    serial.clear();

    oscP5 = new OscP5(this, 5001);
    setLayout(new GridLayout(2, 2));

    SketchPanel baseSketchPanel = new SketchPanel(this, baseSketch);
    add(baseSketchPanel);
    baseSketch.setIsActive(true);
    baseSketch.setParentSketch(this);

    SketchPanel armSketchPanel = new SketchPanel(this, armSketch);
    add(armSketchPanel);
    armSketch.setIsActive(true);
    armSketch.setParentSketch(this);

    SketchPanel handSketchPanel = new SketchPanel(this, handSketch);
    add(handSketchPanel);
    handSketch.setIsActive(true);
    handSketch.setParentSketch(this);

    SketchPanel logoSketchPanel = new SketchPanel(this, logoSketch);
    add(logoSketchPanel);
    logoSketch.setIsActive(true);
    logoSketch.setParentSketch(this);
}

void draw()
{
    // do nothing.
}

void serialEvent(Serial serial)
{
    try
    {
        String msg = serial.readStringUntil('\n');
        if (msg != null)
        {
            msg = trim(msg);

            // sanity checks
            if (msg.length() <= 0) return;
            if (msg.charAt(0) == '#') return;

            // println(msg); // for debugging

            // received position update
            if (msg.charAt(0) == 'P')
            {
                // remove 'P'
                msg = msg.substring(1, msg.length());

                /*
                    position data comes in this order:
                    0. Base
                    1. Shoulder
                    2. Elbow
                    3. Wrist
                    4. Grip
                */
                String args[] = msg.split(";");
                if (args.length == 5)
                {
                    baseSketch.angle_current = Integer.parseInt(args[0]);
                    armSketch.shoulder_angle_current = Integer.parseInt(args[1]);
                    armSketch.elbow_angle_current = Integer.parseInt(args[2]);
                    handSketch.angle_current = Integer.parseInt(args[3]);
                    handSketch.grip_is_open = Integer.parseInt(args[4]) != 0;
                }
            }

            // received status update
            if (msg.charAt(0) == 'S')
            {
                // remove 'S'
                msg = msg.substring(1, msg.length());

                /*
                    status data comes in this order:
                    0. motor 1 current
                    1. motor 2 current
                    2. motor 3 current
                */
                String args[] = msg.split(";");
                if (args.length == 3)
                {
                    armSketch.shoulder_motor_power = Integer.parseInt(args[1]);
                    armSketch.elbow_motor_power = Integer.parseInt(args[2]);
                }
            }

            baseSketch.redraw();
            armSketch.redraw();
            handSketch.redraw();
        }
    }
    catch (Exception ex)
    {
        println(ex.getMessage());
    }
}

void sendSerial(String cmd)
{
    if (serial == null) return;
    serial.write(cmd);
    serial.write("\n");
}

void oscEvent(OscMessage theOscMessage)
{
    print(theOscMessage);

    /**
     * Simple Buttons
     */
    if (theOscMessage.checkAddrPattern("/grip"))
    {
        sendSerial("GRIP TOGGLE");
    }
    if (theOscMessage.checkAddrPattern("/autolevelon"))
    {
        sendSerial("AUTOLEVEL ON");
    }
    if (theOscMessage.checkAddrPattern("/autoleveloff"))
    {
        sendSerial("AUTOLEVEL OFF");
    }
    if (theOscMessage.checkAddrPattern("/autolevelh"))
    {
        sendSerial("AUTOLEVEL H");
    }
    if (theOscMessage.checkAddrPattern("/autolevelv"))
    {
        sendSerial("AUTOLEVEL V");
    }

    /**
     * Gyro controls
     */
    if (theOscMessage.checkAddrPattern("/elbow"))
    {
        println("Elbow");
        if (active_component == 1) active_component = 0;
        else active_component = 1;
    }
    if (theOscMessage.checkAddrPattern("/shoulder"))
    {
        println("Shoulder");
        if (active_component == 2) active_component = 0;
        else active_component = 2;
    }
    if (theOscMessage.checkAddrPattern("/base"))
    {
        println("Shoulder");
        if (active_component == 3) active_component = 0;
        else active_component = 3;
    }

    // Reading (and setting) gyro values
    if (theOscMessage.checkAddrPattern("/gyro"))
    {
        // get new raw gyro value
        gyro_pitch_old = gyro_pitch;
        gyro_pitch = round(theOscMessage.get(3).floatValue());

        gyro_yaw_old = gyro_yaw;
        gyro_yaw = round(theOscMessage.get(5).floatValue());

        int delta_pitch = gyro_pitch - gyro_pitch_old;
        int delta_yaw = gyro_yaw - gyro_yaw_old;

        if (active_component == 1) // elbow
        {
             armSketch.elbow_incDesiredAngle(delta_pitch);
        }

        if (active_component == 2) // shoulder
        {
            armSketch.shoulder_incDesiredAngle(delta_pitch);
        }

        if (active_component == 3) // base
        {
            baseSketch.incDesiredAngle(delta_yaw);
        }
    }

    baseSketch.redraw();
    armSketch.redraw();
    handSketch.redraw();
}
