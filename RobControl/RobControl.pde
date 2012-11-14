import java.awt.*;
import processing.serial.*;
import org.gicentre.utils.multisketch.*;

Serial serialPort;
BaseSketch baseSketch;
ArmSketch  armSketch;

void setup()
{
    size(600, 300);
    setLayout(new GridLayout(0, 2)); 

    baseSketch = new BaseSketch();
    armSketch  = new ArmSketch();

    SketchPanel baseSketchPanel = new SketchPanel(this, baseSketch); 
    add(baseSketchPanel); 
    baseSketch.setIsActive(true); 

    SketchPanel armSketchPanel = new SketchPanel(this, armSketch); 
    add(armSketchPanel); 
    armSketch.setIsActive(true);

    String portName = Serial.list()[4];
    serialPort = new Serial(this, portName, 9600);
}

void draw()
{
    if (serialPort.available() > 0)
    {
        int val = serialPort.read();
    }
}

