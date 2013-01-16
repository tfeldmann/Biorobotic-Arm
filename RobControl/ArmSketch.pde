/**
 * ArmSketch.ino
 */
class ArmSketch extends EmbeddedSketch
{
    // drawing parameters (robot geometry)
    public static final int ARM_LENGTH = 150;
    public static final float SHOULDER_ANGLE_MIN = -5;
    public static final float SHOULDER_ANGLE_MAX = 60;
    public static final float ELBOW_ANGLE_MIN = -165;
    public static final float ELBOW_ANGLE_MAX = 40;
    PVector shoulder = new PVector(30, 100);

    // desired values
    private int shoulder_angle_desired;
    private int elbow_angle_desired;

    // we receive these values from the robot [degrees]
    public int shoulder_angle_current;
    public int elbow_angle_current;

    // measuring motor power
    public int shoulder_motor_power;
    public int elbow_motor_power;


    void setup()
    {
        size(350, 350);
        noLoop();
        smooth();
    }

    void draw()
    {
        background(230);

        // Show remotely controlled component
        fill(0);
        if (active_component == 1)
            text("Remote: Elbow", 10, 20);
        if (active_component == 2)
            text("Remote: Shoulder", 10, 20);

        // Sketch Description
        fill(0);
        text("Arms", 10, height - 10);

        // if not yet initialisied take received values
        if (shoulder_angle_desired == 0 && elbow_angle_desired == 0)
        {
            shoulder_angle_desired = shoulder_angle_current;
            elbow_angle_desired = elbow_angle_current;
        }

        // desired arm position
        stroke(255, 170, 60);
        strokeWeight(7);
        pushMatrix();
            // flip everything upside down
            scale(1, -1);
            translate(0, -height);

            // shoulder
            translate(shoulder.x, shoulder.y);
            rotate(radians(shoulder_angle_desired));
            line(0, 0, ARM_LENGTH, 0);

            // elbow
            translate(ARM_LENGTH, 0);
            rotate(radians(elbow_angle_desired));
            line(0, 0, ARM_LENGTH, 0);
        popMatrix();


        // show actual robot position
        stroke(0);
        strokeWeight(2);
        pushMatrix();
            // flip everything upside down
            scale(1, -1);
            translate(0, -height);

            // shoulder
            translate(shoulder.x, shoulder.y);
            rotate(radians(shoulder_angle_current));
            line(0, 0, ARM_LENGTH, 0);

            // elbow
            translate(ARM_LENGTH, 0);
            rotate(radians(elbow_angle_current));
            line(0, 0, ARM_LENGTH, 0);
        popMatrix();
    }

    void mouseDragged()
    {
        PVector mouse_pos = new PVector(mouseX, height - mouseY);
        PVector intersection = circleIntersection(shoulder, ARM_LENGTH, mouse_pos, ARM_LENGTH);

        int shoulder_angle = round(degrees(atan2(intersection.y - shoulder.y, intersection.x - shoulder.x)));
        int elbow_angle = round(degrees(atan2(mouse_pos.y - intersection.y, mouse_pos.x - intersection.x)) - shoulder_angle_desired);

        if (shoulder_angle >= SHOULDER_ANGLE_MIN && shoulder_angle <= SHOULDER_ANGLE_MAX &&
            elbow_angle >= ELBOW_ANGLE_MIN && elbow_angle <= ELBOW_ANGLE_MAX)
        {
            shoulder_angle_desired = shoulder_angle;
            elbow_angle_desired = elbow_angle;
        }
        sendMoveCommand(shoulder_angle_desired, elbow_angle_desired);
        redraw();
    }

    void mousePressed()
    {
        mouseDragged();
    }

    void sendMoveCommand(int shoulder_angle, int elbow_angle)
    {
        sendSerial("SHOULDER "+(new Integer(shoulder_angle)).toString());
        sendSerial("ELBOW "+(new Integer(elbow_angle)).toString());
    }

    void elbow_incDesiredAngle(int angle)
    {
        elbow_angle_desired += angle;
        sendSerial("ELBOW "+(new Integer(elbow_angle_desired)).toString());
    }

    void shoulder_incDesiredAngle(int angle)
    {
        shoulder_angle_desired += angle;
        sendSerial("SHOULDER "+(new Integer(shoulder_angle_desired)).toString());
    }

    PVector circleIntersection(PVector p1, float r1, PVector p2, float r2)
    {
        float dx = p2.x - p1.x;
        float dy = p2.y - p1.y;

        PVector dvect = new PVector(p1.x - p2.x, p1.y - p2.y);
        float d = dvect.mag();
        float a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
        float h = sqrt(r1 * r1 - a * a);

        // upper intersection
        PVector sp1 = new PVector();
        sp1.x = p1.x + (a/d) * dx - (h/d) * dy;
        sp1.y = p1.y + (a/d) * dy + (h/d) * dx;
        sp1.z = p1.z; // z-coordinate is not used

        // return only upper intersection
        return sp1;
    }
}

