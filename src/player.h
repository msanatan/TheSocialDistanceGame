#ifndef PLAYER_H
#define PLAYER_H

#include <Arduboy2.h>

class Player {
 private:
  int size = 16;
  int invincibilityDuration = 1;

 public:
  int x;
  int y;
  int speedX;
  int speedY;
  int lives;
  int frame;
  unsigned long lastHit;
  bool justHit;

  Player();
  Rect getRect();
  int getSize();
  int getInvincibilityDuration();
};

#endif  // !PLAYER_H
