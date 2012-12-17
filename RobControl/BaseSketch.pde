
class BaseSketch extends EmbeddedSketch
{
    private final static int BASE_ANGLE_MIN = -135;
    private final static int BASE_ANGLE_MAX = 135;
    public int angle_current;
    public int angle_desired;

    void setup()
    {
        size(350, 350);
        noLoop();
        smooth();

        ellipseMode(CENTER);
        rectMode(CENTER);
    }

    void draw()
    {
        background(255);

        fill(0);
        text("Base", 10, height - 10);
        text(round(angle_current) + "°", 10, 35);
        fill(0, 180, 0);
        text(round(angle_desired) + "°", 10, 20);

        scale(1, -1);
        translate(0, -height);
        translate(width / 2, height / 2);

        // show current
        stroke(0);
        strokeWeight(1);
        fill(220);
        pushMatrix();
            rotate(radians(90 - angle_current));
            rect(0, 0, 150, 150);
            strokeWeight(10);
            line(30, 0, 120, 0);
        popMatrix();

        // show desired position
        pushMatrix();
            rotate(radians(90 - angle_desired));
            fill(0, 180, 0, 100); // green
            stroke(0, 180, 0, 100);
            strokeWeight(2);
            line(20, 0, 130, 0);
        popMatrix();
    }

    void setPositionByMouse()
    {
        PVector dirVect = new PVector(mouseX - width / 2, (height - mouseY) - height / 2);
        int angle = round(90 - degrees(atan2(dirVect.y, dirVect.x)));
        setDesiredAngle(angle);
    }

    void setDesiredAngle(int angle)
    {
        angle_desired = angle;
        sendPositionCommand(round(angle));
    }

    void sendPositionCommand(int angle)
    {
        sendSerial("BASE "+(new Integer(angle)).toString());
    }

    void mouseDragged()
    {
        setPositionByMouse();
        redraw();
    }

    void mousePressed()
    {
        setPositionByMouse();
        redraw();
    }
}

