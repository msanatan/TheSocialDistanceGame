#include "Pedestrian.h"

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

bool Pedestrian::collide(int x, int y, int width, int height)
{
    return x < this->x + this->size &&
           x + width > this->x &&
           y < this->y + this->size &&
           y + height > this->y;
}
