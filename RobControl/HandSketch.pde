
class HandSketch extends EmbeddedSketch
{
    int current_angle;
    boolean grip_is_open;

    void setup()
    {
        size(300, 300);
        smooth();
        ellipseMode(CENTER);
    }

    void draw()
    {
        super.draw();
        background(220);

        fill(0);
        text("Hand", 10, height - 10);
        text(round(current_angle) + "°", 15, 20);

        translate(width / 2, height / 2);

        // wrist
        pushMatrix();
            rotate(radians(current_angle) - HALF_PI);
            stroke(0);
            if (grip_is_open)
            {
                strokeWeight(10);
                line(0, -16, 100, -16);
                line(0, 16, 100, 16);
            }
            else
            {
                strokeWeight(20);
                line(0, 0, 100, 0);
            }
        popMatrix();

        // joint
        fill(255);
        stroke(0);
        strokeWeight(2);
        ellipse(0, 0, 40, 40);

        // arm
        stroke(255);
        strokeWeight(20);
        line(-width / 2, 0, 0, 0);
    }

    void setWristAngleByClick()
    {
        // abort if clicked in unavailable position to avoid instant jump from 180° to 0°
        if (mouseX < width / 2) return;

        PVector dirVect = new PVector(mouseX - width / 2, (height - mouseY) - height / 2);
        float angle = degrees(atan2(dirVect.x, dirVect.y));
        sendSerial("WRIST "+(new Integer(constrain(round(angle), 0, 180))).toString());
    }

    void mouseDragged()
    {
        // set grip when clicked on center
        PVector d = new PVector(mouseX - width / 2, mouseY - height / 2);
        if (d.mag() > 20)
        {
            setWristAngleByClick();
        }
    }

    void mousePressed()
    {
        // set grip when clicked on center
        PVector d = new PVector(mouseX - width / 2, mouseY - height / 2);
        if (d.mag() < 20)
        {
            sendSerial("GRIP TOGGLE");
        }
        else
        {
            setWristAngleByClick();
        }
    }

}
