#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    int size = 16;
    int invincibilityDuration = 1;

public:
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    int speedX = 2;
    int speedY = 16;
    int lives = 3;
    int frame = 0;
    unsigned long lastHit = 0;
    bool justHit = false;

    int getSize()
    {
        return size;
    }

    int getInvincibilityDuration()
    {
        return invincibilityDuration;
    }
};

#endif // !PLAYER_H
