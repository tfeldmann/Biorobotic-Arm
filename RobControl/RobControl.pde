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

void setup()
{
    size(600, 600);

    String portName = Serial.list()[4];
    serial = new Serial(this, portName, 115200);
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
    String msg = serial.readStringUntil('\n');
    if (msg != null)
    {
        try
        {
            msg = trim(msg);

            // sanity checks
            if (msg.length() <= 0) return;
            if (msg.charAt(0) == '#') return;

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
                baseSketch.pos_current = Integer.parseInt(args[0]);
                handSketch.current_angle = Integer.parseInt(args[3]);
                handSketch.grip_is_open = Integer.parseInt(args[4]) != 0;
            }
        }
        catch (Exception ex)
        {
            println(ex.getMessage());
        }
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
    // println(theOscMessage); // debug the messages
    if (theOscMessage.checkAddrPattern("/gyro"))
    {
        float wrist_osc = theOscMessage.get(3).floatValue();
        handSketch.setWristAngle(map(round(wrist_osc), 0, 180, 180, 0));

        float base_osc = theOscMessage.get(5).floatValue();
        baseSketch.setDesiredAngle(map(base_osc, 0, 180, 270, 0));
    }
    if (theOscMessage.checkAddrPattern("/grip"))
    {
        sendSerial("GRIP TOGGLE");
    }
}
