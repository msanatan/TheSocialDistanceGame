#include "Player.h"

Player::Player()
{
    this->x = WIDTH / 2;
    this->y = HEIGHT / 2;
    this->speedX = 2;
    this->speedY = 16;
    this->size = 16;
    this->invincibilityDuration = 1;
    this->lives = 3;
    this->frame = 0;
    this->lastHit = 0;
    this->justHit = false;
}

Rect Player::getRect()
{
    return Rect{this->x, this->y, this->size, this->size};
}

int Player::getSize()
{
    return this->size;
}

int Player::getInvincibilityDuration()
{
    return this->invincibilityDuration;
}
