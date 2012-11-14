
class BaseSketch extends EmbeddedSketch
{
    void setup()
    {
        size(300, 300);
        smooth();
    }

    void draw()
    {
        super.draw();  
        background(200);
    }
}

