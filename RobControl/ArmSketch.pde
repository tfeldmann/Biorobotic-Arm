/**
 * ArmSketch.ino
 */
class ArmSketch extends EmbeddedSketch
{
    // constants
    public static final int LOWER_ARM_LENGTH = 120;
    public static final int UPPER_ARM_LENGTH = 120;

    // variables
    PVector shoulder;
    PVector elbow;
    PVector p;

    // this values are reveived over serial connection
    public int pos_current_shoulder;
    public int pos_current_elbow;

    void setup()
    {
        size(300, 300);
        noLoop();
        smooth();

        shoulder = new PVector(30, 100);
        p = new PVector(100, 100);
        elbow = getElbowPosition();
        ellipseMode(CENTER);
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

        // desired arms
        stroke(218, 120, 14);
        strokeWeight(2);

        fill(255, 255, 255, 10);
        line(shoulder.x, height - shoulder.y, elbow.x, height - elbow.y);
        line(elbow.x, height - elbow.y, p.x, height - p.y);
        ellipse(shoulder.x, height - shoulder.y, 240, 240);
        // ellipse(elbow.x, height - elbow.y, 10, 10);
        ellipse(p.x, height - p.y, 240, 240);
    }

    void mouseDragged()
    {
        p = new PVector(mouseX, height - mouseY);
        elbow = getElbowPosition();
        redraw();
    }

    PVector getElbowPosition()
    {
        return circleIntersection(shoulder, LOWER_ARM_LENGTH, p, UPPER_ARM_LENGTH);
    }

    PVector circleIntersection(PVector p1, float r1, PVector p2, float r2)
    {
        float d, a, h;
        float dx, dy;

        dx = p2.x - p1.x;
        dy = p2.y - p1.y;

        PVector dvect = new PVector(p1.x - p2.x, p1.y - p2.y);
        d = dvect.mag();
        a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
        h = sqrt(r1 * r1 - a * a);

        PVector sp1 = new PVector();
        sp1.x = p1.x + (a/d) * dx - (h/d) * dy;   // upper intersection
        sp1.y = p1.y + (a/d) * dy + (h/d) * dx;
        sp1.z = p1.z;                             // take z-coordinate

        return(sp1);
    }
}

