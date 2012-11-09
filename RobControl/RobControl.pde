import oscP5.*;

OscP5 oscP5;
float p1, p2, p3;
float maxValue = 127;

void setup()
{
    size(400,400);
    smooth();
    oscP5 = new OscP5(this, 5001);
}

void draw()
{
    background(#000000);

    float rectWidth = width / 3;

    fill(#FF0000);
    rect(0, height, rectWidth, - height / maxValue * p1);

    fill(#00FF00);
    rect(rectWidth, height, rectWidth, - height / maxValue * p2);

    fill(#0000FF);
    rect(rectWidth * 2, height, rectWidth, - height / maxValue * p3);
}

void oscEvent(OscMessage theOscMessage)
{
    if(theOscMessage.checkAddrPattern("/gyro"))
    {
        p1 = theOscMessage.get(3).floatValue();
        p2 = theOscMessage.get(4).floatValue();
        p3 = theOscMessage.get(5).floatValue();
    }
}
