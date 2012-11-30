
class LogoSketch extends EmbeddedSketch
{
    PImage logo;

    void setup()
    {
        size(300, 300);
        smooth();
        noLoop();

        imageMode(CENTER);
        logo = loadImage("Logo.png");
    }

    void draw()
    {
        background(214);
        image(logo, width / 2, height / 2);
    }
}
