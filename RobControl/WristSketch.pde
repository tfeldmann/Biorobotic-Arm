
class WristSketch extends EmbeddedSketch
{
    int angle_current;

    void setup()
    {
        size(300, 300);
        smooth();
    }

    void draw()
    {
        super.draw();
        background(100);
    }
}

