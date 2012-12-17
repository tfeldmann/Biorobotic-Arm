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

        // Angle Output
        fill(0);
        text("Elbow ", 10, 20);

        // Sketch Description
        fill(0);
        text("Arms", 10, height - 10);

        // if not yet initialisied take received values
        if (shoulder_angle_desired == 0 && elbow_angle_desired == 0)
        {
            shoulder_angle_desired = shoulder_angle_current;
            elbow_angle_desired = elbow_angle_current;
        }

        // draw shoulder min / max angle
        // rotation is negative because 0|0 is top left.
        // fill(0, 200, 0, 30);
        // noStroke();
        // arc(shoulder.x, height - shoulder.y, 80, 80, -radians(SHOULDER_ANGLE_MAX), -radians(SHOULDER_ANGLE_MIN));
        // pushMatrix();
        //     translate(elbow.x, height - elbow.y);
        //     rotate(-atan2(elbow.y - shoulder.y, elbow.x - shoulder.x));
        //     arc(0, 0, 80, 80, -radians(ELBOW_ANGLE_MAX), -radians(ELBOW_ANGLE_MIN));
        // popMatrix();

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

        // show motor power
        line(10, 10, 10 + shoulder_motor_power, 10);
        line(10, 20, 10 + elbow_motor_power, 20);
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

