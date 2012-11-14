
class BaseSketch extends EmbeddedSketch
{
    public int pos_current;
    public int pos_desired;

    void setup()
    {
        size(300, 300);
        smooth();
        ellipseMode(CENTER);
        rectMode(CENTER);
    }

    void draw()
    {
        super.draw();
        background(255);

        float current_angle = positionToAngle(pos_current);
        float desired_angle = positionToAngle(pos_desired);

        // show robot
        text(round(current_angle) + "°", 15, 30);
        translate(width / 2, height / 2);
        pushMatrix();
            rotate(radians(current_angle) + 0.375 * TWO_PI);
            strokeWeight(1);
            fill(255);
            rect(0, 0, 150, 150);
            strokeWeight(10);
            line(25, 0, 125, 0);
        popMatrix();

        // show desired position
        pushMatrix();
            rotate(radians(desired_angle) + 0.375 * TWO_PI);
            fill(0, 180, 0); // green
            noStroke();
            ellipse(130, 0, 20, 20);
        popMatrix();
    }

    void mouseDragged()
    {
        PVector dirVect = new PVector(mouseX - width / 2, (height - mouseY) - height / 2);
        float angle = degrees(atan2(dirVect.x, dirVect.y)) + 135;
        angle = constrain(angle, 0, 270);
        pos_desired = angleToPos(angle);
        sendSerial("BASE "+(new Integer(mouseY)).toString());
    }

    float positionToAngle(int pos)
    {
        return pos * 270.0 / 1023.0;
    }

    int angleToPos(float angle)
    {
        return round(angle * 1023.0 / 270.0);
    }
}

