/**
 * ArmSketch.ino
 */
class ArmSketch extends EmbeddedSketch
{
    // constants (robot geometry)
    public static final int ARM_LENGTH = 120;
    public static final float SHOULDER_ANGLE_MIN = -20;
    public static final float SHOULDER_ANGLE_MAX = 70;
    public static final float ELBOW_ANGLE_MIN = -90;
    public static final float ELBOW_ANGLE_MAX = 90;

    // variables
    PVector shoulder;
    PVector elbow;
    PVector pos_desired;

    // we receive these values from the robot as raw potentiometer values (0...1023)
    public int pos_current_shoulder;
    public int pos_current_elbow;


    void setup()
    {
        size(300, 300);
        noLoop();
        smooth();

        shoulder = new PVector(30, 100);
        pos_desired = new PVector(100, 100);
        ellipseMode(CENTER);
        elbow = new PVector(0, 0);
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

        if (elbow != null)
        {
            // draw shoulder min / max angle
            // rotation is negative because 0|0 is top left.
            fill(0, 200, 0, 30);
            noStroke();
            arc(shoulder.x, height - shoulder.y, 80, 80, -radians(SHOULDER_ANGLE_MAX), -radians(SHOULDER_ANGLE_MIN));
            pushMatrix();
                translate(elbow.x, height - elbow.y);
                rotate(-atan2(elbow.y - shoulder.y, elbow.x - shoulder.x));
                arc(0, 0, 80, 80, -radians(ELBOW_ANGLE_MAX), -radians(ELBOW_ANGLE_MIN));
            popMatrix();

            // desired arm position
            stroke(255, 170, 60);
            strokeWeight(7);
            line(shoulder.x, height - shoulder.y, elbow.x, height - elbow.y);
            line(elbow.x, height - elbow.y, pos_desired.x, height - pos_desired.y);
        }
    }

    void mouseDragged()
    {
        pos_desired = new PVector(mouseX, height - mouseY);
        PVector[] intersections = circleIntersections(shoulder, ARM_LENGTH, pos_desired, ARM_LENGTH);

        // check if chosen position is mechanically possible
        for (PVector intersection : intersections)
        {
            float shoulder_angle = degrees(atan2(intersection.y - shoulder.y, intersection.x - shoulder.x));
            float elbow_angle = degrees(atan2(pos_desired.y - intersection.y, pos_desired.x - intersection.x)) - shoulder_angle;
            if (shoulder_angle > SHOULDER_ANGLE_MIN && shoulder_angle < SHOULDER_ANGLE_MAX
                && elbow_angle > ELBOW_ANGLE_MIN && elbow_angle < ELBOW_ANGLE_MAX)
            {
                elbow = intersection;
            }
        }
        redraw();
    }

    PVector[] circleIntersections(PVector p1, float r1, PVector p2, float r2)
    {
        float dx = p2.x - p1.x;
        float dy = p2.y - p1.y;

        PVector dvect = new PVector(p1.x - p2.x, p1.y - p2.y);
        float d = dvect.mag();
        float a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
        float h = sqrt(r1 * r1 - a * a);

        // lower intersection
        PVector sp1 = new PVector();
        sp1.x = p1.x + (a/d) * dx + (h/d) * dy;
        sp1.y = p1.y + (a/d) * dy - (h/d) * dx;
        sp1.z = p1.z; // z-coordinate is not used

        // upper intersection
        PVector sp2 = new PVector();
        sp2.x = p1.x + (a/d) * dx - (h/d) * dy;
        sp2.y = p1.y + (a/d) * dy + (h/d) * dx;
        sp2.z = p1.z; // z-coordinate is not used

        // return both intersection points in an array
        return new PVector[] {sp1, sp2};
    }
}

