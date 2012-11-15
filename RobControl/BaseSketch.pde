
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

        pos_desired = 512; // set to middle
    }

    void draw()
    {
        super.draw();
        background(255);

        float current_angle = positionToAngle(pos_current);
        float desired_angle = positionToAngle(pos_desired);

        fill(0);
        text(round(current_angle) + "°", 15, 35);
        fill(0, 180, 0);
        text(round(desired_angle) + "°", 15, 20);
        translate(width / 2, height / 2);

        // show robot
        stroke(0);
        strokeWeight(1);
        fill(220);
        pushMatrix();
            rotate(radians(current_angle) + 0.375 * TWO_PI);
            rect(0, 0, 150, 150);
            strokeWeight(10);
            line(25, 0, 125, 0);
        popMatrix();

        // show desired position
        pushMatrix();
            rotate(radians(desired_angle) + 0.375 * TWO_PI);
            fill(0, 180, 0, 100); // green
            stroke(0, 180, 0, 100);
            //ellipse(130, 0, 20, 20);
            strokeWeight(10);
            line(0, 0, 130, 0);
        popMatrix();
    }

    void setPositionByMouse()
    {
        PVector dirVect = new PVector(mouseX - width / 2, (height - mouseY) - height / 2);
        float angle = degrees(atan2(dirVect.x, dirVect.y)) + 135;
        angle = constrain(angle, 0, 270);

        sendPositionCommand(angleToPos(angle));
    }

    float positionToAngle(int pos)
    {
        return pos * 270.0 / 1023.0;
    }

    int angleToPos(float angle)
    {
        return round(angle * 1023.0 / 270.0);
    }

    void sendPositionCommand(int position)
    {
        pos_desired = position;
        sendSerial("BASE "+(new Integer(position)).toString());
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
