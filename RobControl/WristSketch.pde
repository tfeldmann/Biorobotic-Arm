
class WristSketch extends EmbeddedSketch
{
    int current_angle;
    boolean isOpen; // todo: in firmware übernehmen

    void setup()
    {
        size(300, 300);
        smooth();
        ellipseMode(CENTER);
        sendSerial("GRIP CLOSE");
        isOpen = false;
    }

    void draw()
    {
        super.draw();
        background(220);

        fill(0);
        text("Wrist", 10, height - 10);
        text(round(current_angle) + "°", 15, 20);

        translate(width / 2, height / 2);

        // wrist
        pushMatrix();
            rotate(radians(current_angle) - HALF_PI);
            strokeWeight(20);
            stroke(0);
            line(0, 0, 100, 0);
        popMatrix();

        // joint
        fill(255);
        stroke(0);
        strokeWeight(2);
        ellipse(0, 0, 40, 40);

        // upper arm
        stroke(255);
        strokeWeight(20);
        line(-width / 2, 0, 0, 0);
    }

    void setPositionByMouse()
    {
        PVector d = new PVector(mouseX - width / 2, mouseY - height / 2);
        if (d.mag() < 20)
        {
            if (isOpen)
            {
                sendSerial("GRIP CLOSE");
                isOpen = false;
            }
            else
            {
                sendSerial("GRIP OPEN");
                isOpen = true;
            }
            return;
        }
        PVector dirVect = new PVector(mouseX - width / 2, (height - mouseY) - height / 2);
        float angle = degrees(atan2(dirVect.x, dirVect.y));
        current_angle = constrain(round(angle), 0, 180);
        sendSerial("WRIST "+(new Integer(current_angle)).toString());
    }

    void mouseDragged()
    {
        setPositionByMouse();
    }

    void mousePressed()
    {
        setPositionByMouse();
    }
}
