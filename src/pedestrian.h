#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include <Arduboy2.h>

class Pedestrian {
 private:
  int size = 16;

 public:
  int x = -20;  // So they will be offscreen when initialized
  int y;
  int speedX;
  int speedY;
  int frame;
  bool active;

  Rect getRect();
  int getSize();
  void nextFrame();
};

#endif  // !PEDESTRIAN_H
