
class LogoSketch extends EmbeddedSketch
{
    PImage logo;

    void setup()
    {
        size(350, 350);
        smooth();
        noLoop();

        imageMode(CENTER);
        logo = loadImage("Logo.png");
    }

    void draw()
    {
        background(214);
        image(logo, width / 2, height / 2);
        fill(0);
        textAlign(CENTER);
        text("Server: "+oscP5.ip()+":5001", width / 2, height - 10);
    }
}
