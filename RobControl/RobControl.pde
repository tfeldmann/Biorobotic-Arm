import java.awt.*;
import processing.serial.*;
import org.gicentre.utils.multisketch.*;

Serial serial;
BaseSketch baseSketch = new BaseSketch();
ArmSketch armSketch = new ArmSketch();
WristSketch wristSketch = new WristSketch();

void setup()
{
    size(600, 600);

    String portName = Serial.list()[4];
    serial = new Serial(this, portName, 115200);
    serial.clear();

    setLayout(new GridLayout(2, 2));

    SketchPanel baseSketchPanel = new SketchPanel(this, baseSketch);
    add(baseSketchPanel);
    baseSketch.setIsActive(true);
    baseSketch.setParentSketch(this);

    SketchPanel armSketchPanel = new SketchPanel(this, armSketch);
    add(armSketchPanel);
    armSketch.setIsActive(true);
    armSketch.setParentSketch(this);

    SketchPanel wristSketchPanel = new SketchPanel(this, wristSketch);
    add(wristSketchPanel);
    wristSketch.setIsActive(true);
    wristSketch.setParentSketch(this);
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
            if (msg.charAt(0) == '#') return;

            /*
                1. Base
                2. Shoulder
                3. Elbow
                4. Wrist
                5. Grip
            */
            String args[] = msg.split(";");
            baseSketch.pos_current = Integer.parseInt(args[0]);
            wristSketch.angle_current = Integer.parseInt(args[3]);
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
