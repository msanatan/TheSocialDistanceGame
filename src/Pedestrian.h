#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

class Pedestrian
{
private:
    int size = 16;

public:
    int x = -20; // So they will be offscreen when initialized
    int y;
    int speedX;
    int speedY;
    int frame;
    bool active;

    int getSize();
    void nextFrame();
    bool collide(int x, int y, int width, int height);
};

#endif // !PEDESTRIAN_H
