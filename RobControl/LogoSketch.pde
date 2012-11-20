
class LogoSketch extends EmbeddedSketch
{
    PImage logo;

    void setup()
    {
        size(300, 300);
        smooth();
        imageMode(CENTER);
        logo = loadImage("Logo.png");
    }

    void draw()
    {
        super.draw();
        background(214);
        image(logo, width / 2, height / 2);
    }
}
