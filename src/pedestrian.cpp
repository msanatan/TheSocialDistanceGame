#include "Pedestrian.h"

Rect Pedestrian::getRect()
{
    return Rect{this->x + 3, this->y, 10, this->size};
}

int Pedestrian::getSize()
{
    return size;
}

void Pedestrian::nextFrame()
{
    // First 3 frames if moving to the right
    if (speedX < 0)
    {
        if (frame == 3)
        {
            frame = 0;
        }
        else
        {
            frame++;
        }
    }
    else
    { // Last 3 frames if moving to the left
        if (frame == 7)
        {
            frame = 4;
        }
        else
        {
            frame++;
        }
    }
}
