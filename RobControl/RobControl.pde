import java.awt.*;
import processing.serial.*;
import org.gicentre.utils.multisketch.*;

Serial serial;
BaseSketch baseSketch;
ArmSketch  armSketch;

void setup()
{
    size(600, 300);

    String portName = Serial.list()[4];
    serial = new Serial(this, portName, 115200);
    serial.clear();

    setLayout(new GridLayout(0, 2));
    baseSketch = new BaseSketch();
    armSketch  = new ArmSketch();

    SketchPanel baseSketchPanel = new SketchPanel(this, baseSketch);
    add(baseSketchPanel);
    baseSketch.setIsActive(true);
    baseSketch.setParentSketch(this);

    SketchPanel armSketchPanel = new SketchPanel(this, armSketch);
    add(armSketchPanel);
    armSketch.setIsActive(true);
    armSketch.setParentSketch(this);
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
            baseSketch.pos_current = Integer.parseInt(msg);
            println(baseSketch.pos_current);
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
