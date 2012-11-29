/**
 * ProgrammingSketch.ino
 */

import g4p_controls.*;

class ProgrammingSketch extends EmbeddedSketch
{
    GTextArea txa1;
    PImage logo;

    void setup()
    {
        size(300, 300);
        // G4P.setGlobalColorScheme(GCScheme.RED_SCHEME);
        smooth();
        imageMode(CENTER);
        logo = loadImage("Logo.png");

        txa1 = new GTextArea(this, 10, 80, 200, 160);
        txa1.tag = "txa1";
        txa1.setDefaultText("Text area 1");
        txa1.setText("asd");
        txa1.setText("asodj", 2);
    }

    void draw()
    {
        super.draw();
        background(214);
    }
}
