
class WristSketch extends EmbeddedSketch
{
    int current_angle;

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
        text(round(current_angle) + "°", 15, 20);

        translate(width / 2, height / 2);

        stroke(244);
        strokeWeight(10);
        line(-width / 2, 0, 0, 0);

        fill(255);
        strokeWeight(2);
        ellipse(0, 0, 30, 30);

        strokeWeight(5);
        rotate(radians(current_angle) - HALF_PI);
        stroke(255);
        line(0, 0, 200, 0);
    }
}

