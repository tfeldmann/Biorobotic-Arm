import java.awt.*;
import processing.serial.*;
import org.gicentre.utils.multisketch.*;

Serial serial;
BaseSketch baseSketch = new BaseSketch();
ArmSketch armSketch = new ArmSketch();
HandSketch handSketch = new HandSketch();

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

    SketchPanel handSketchPanel = new SketchPanel(this, handSketch);
    add(handSketchPanel);
    handSketch.setIsActive(true);
    handSketch.setParentSketch(this);
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
                0. Base
                1. Shoulder
                2. Elbow
                3. Wrist
                4. Grip
            */
            String args[] = msg.split(";");
            baseSketch.pos_current = Integer.parseInt(args[0]);
            handSketch.current_angle = Integer.parseInt(args[3]);
            handSketch.grip_is_open = Integer.parseInt(args[4]) != 0;
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
