// Marcus Sanatan (msanatan)
// March 24th, 2020
// The Social Distance Game

#include <Arduboy2.h>
Arduboy2 arduboy;

const unsigned char PROGMEM playerSprite[] =
{
  // width, height,
  16, 16,
  // FRAME 00
  0x00, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x04, 0x04, 0xfc, 0xfc, 0x04, 0x04, 0xfc, 0xfc, 0x00, 0x00,
  0x00, 0x00, 0x1f, 0x1f, 0x3f, 0x7f, 0x3c, 0x1c, 0x1f, 0x3f, 0x7c, 0x3c, 0x1f, 0x1f, 0x00, 0x00,
  // FRAME 01
  0x00, 0x00, 0xfc, 0xfc, 0x04, 0x04, 0xfc, 0xfc, 0x04, 0x04, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0x00,
  0x00, 0x00, 0x1f, 0x1f, 0x3c, 0x7c, 0x3f, 0x1f, 0x1c, 0x3c, 0x7f, 0x3f, 0x1f, 0x1f, 0x00, 0x00,
};

const unsigned char PROGMEM heart[] =
{
  // width, height,
  8, 8,
  0x1e, 0x3f, 0x7f, 0xfe, 0xfe, 0x7f, 0x3f, 0x1e,
};

const unsigned char PROGMEM pedestrianSprite[] =
{
// width, height,
16, 16,
// FRAME 00
0x00, 0x00, 0x00, 0x3c, 0x7e, 0xf3, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x20, 0x00, 0x00, 0x00, 0x00, 
// FRAME 01
0x00, 0x00, 0x00, 0x78, 0xfc, 0xe6, 0xe6, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0x78, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x71, 0x71, 0x71, 0x71, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 
// FRAME 02
0x00, 0x00, 0x00, 0xf0, 0xf8, 0xcc, 0xcc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x23, 0x73, 0x73, 0x23, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
// FRAME 03
0x00, 0x00, 0x00, 0x78, 0xfc, 0xe6, 0xe6, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0x78, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x71, 0x71, 0x71, 0x71, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 
// FRAME 04
0x00, 0x00, 0x00, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf3, 0x7e, 0x3c, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x20, 0x00, 0x00, 0x00, 0x00, 
// FRAME 05
0x00, 0x00, 0x00, 0x78, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xe6, 0xe6, 0xfc, 0x78, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x71, 0x71, 0x71, 0x71, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 
// FRAME 06
0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xcc, 0xcc, 0xf8, 0xf0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x23, 0x73, 0x73, 0x23, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
// FRAME 07
0x00, 0x00, 0x00, 0x78, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xe6, 0xe6, 0xfc, 0x78, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x71, 0x71, 0x71, 0x71, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const int FPS = 60;
unsigned long previousTime = 0;
float totalSeconds = 0;
bool paused = false;
int score = 0;

// HUD
int heartX = 2;
int heartXSeparator = 12;
int heartY = 0;

// Player
class Player {
  public:
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    int speedX = 2;
    int speedY = 16;
    int lives = 3;
    int frame = 0;

    int getSize() {
      return size;
    }

  private:
    int size = 16;
};

Player player;

//int playerX = WIDTH / 2;
//int playerY = HEIGHT / 2;
//const int PLAYER_SIZE = 16;
//int playerFrame = 0;
//int playerXSpeed = 2;
//int playerYSpeed = 16;
//int lives = 3;

// Pedestrians
class Pedestrian {
  public:
    int x = -20; // So they will be offscreen when initialized
    int y;
    int speedX;
    int speedY;
    int frame;
    bool active;

    void nextFrame() {
      // First 3 frames if moving to the right
      if (speedX < 0) {
        if (frame == 3) {
          frame = 0;
        } else {
          frame++;
        }
      } else { // Last 3 frames if moving to the left
        if (frame == 7) {
          frame = 4;
        } else {
          frame++;
        }
      }
    }
};

const int MAX_PEDESTRIANS = 8;
const int PEDESTRIAN_SPAWN_TIME = 1; // Spawn roughly every 2 seconds
int lastSpawnTime = 0;
int spawnSecondCount = 0;
// Create array of pedestrians
Pedestrian pedestrians[MAX_PEDESTRIANS];
const int PEDESTRIAN_SIZE = 16;
//const int pedestrianSpeed = 3;
bool updatePedestrianFrame;
bool movePedestrians;
int activePedestrians = 0;

// addPedestrians initializes
void addPedestrians(int i) {
  if (activePedestrians < MAX_PEDESTRIANS) {
    int side = random(0, 2);
    pedestrians[i].x = (side == 1) ? WIDTH : 0;
    int lane = random(1, 4);
    int pedestrianSpeed = random(2, 9);
    pedestrians[i].y = PEDESTRIAN_SIZE * lane;
    pedestrians[i].speedX = (side == 1) ? -pedestrianSpeed : pedestrianSpeed;
    // Selet frame based on direction pedestrian is going
    if (pedestrians[i].speedX < 0) {
      pedestrians[i].frame = 0;
    } else {
      pedestrians[i].frame = 4;
    }
    pedestrians[i].active = true;
    activePedestrians++;
  }
  
}


void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(FPS);
  addPedestrians(0);
  previousTime = millis();
  arduboy.clear();
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }
  arduboy.pollButtons();

  // Handle pausing mechanics
  if (arduboy.justPressed(A_BUTTON)) {
    paused = !paused;
    previousTime = millis();
  }

  if (paused) {
    return;
  }

  // Manually get delta time
  unsigned long currentTime = millis();
  unsigned long deltaTime = currentTime - previousTime;
  previousTime = currentTime;
  float deltaSeconds = deltaTime * (1.0f / 1000.0f);
  // Add it to our total time
  totalSeconds += deltaSeconds;
  // Convert to integer to update our score
  score = static_cast<int>(totalSeconds);

  arduboy.clear();
  // HUD
  for (int i = 0; i < player.lives; i++) {
    int xPosition = heartX + (i * heartXSeparator);
    Sprites::drawOverwrite(xPosition, heartY, heart, 0);
  }
  arduboy.setCursor(62, 0);
  arduboy.print("Score: ");
  arduboy.print(score);

  // Move player
  if (arduboy.pressed(LEFT_BUTTON) && player.x > 0) {
    player.x = player.x - player.speedX;
    player.frame = 1;
  } else if (arduboy.pressed(RIGHT_BUTTON) && player.x + player.getSize() < WIDTH) {
    player.x = player.x + player.speedX;
    player.frame = 0;
  }

  if (arduboy.justPressed(UP_BUTTON) && player.y > 16) {
    player.y = player.y - player.speedY;
  } else if (arduboy.justPressed(DOWN_BUTTON) && player.y + player.getSize() < HEIGHT) {
    player.y = player.y + player.speedY;
  }

  // Flag the pedestrian to move
  if (arduboy.everyXFrames(10)) {
    movePedestrians = true;
  }

  // Update the frame of the Pedestrian
  if (arduboy.everyXFrames(20)) {
    updatePedestrianFrame = true;
  }

  int nextActive = -1;
  // Update pedestrians
  for (int i = 0; i < MAX_PEDESTRIANS; i++)  {
    // If the sprite is not active, there's not much to update
    // However, we mark it as the next available sprite to use
    if (!pedestrians[i].active) {
      if (nextActive == -1) {
        nextActive = i;
      }
      continue;
    }

    // Move active pedestrians
    if (movePedestrians) {
      if (pedestrians[i].active) {
        pedestrians[i].x += pedestrians[i].speedX;
        pedestrians[i].y += pedestrians[i].speedY;
      }
    }

    // Set pedestrians off the screen to be inactive
    if (pedestrians[i].x >= WIDTH + 10 || pedestrians[i].x < -18) {
      pedestrians[i].active = false;
      activePedestrians--;
    }

    if (updatePedestrianFrame) {
      pedestrians[i].nextFrame();
    }
  }

  // Reset pedestrian flags
  updatePedestrianFrame = false;
  movePedestrians = false;

  // Add a new pedestrian
  // We use the lastSpawnTime to ensure that many frames in a second
  // don't keep spawning pedestrians
  if (score % PEDESTRIAN_SPAWN_TIME == 0 && score != lastSpawnTime) {
    addPedestrians(nextActive);
    lastSpawnTime = score;
  }

  // Draw pedestrians
  for (int i = 0; i < MAX_PEDESTRIANS; i++)  {
    Sprites::drawOverwrite(pedestrians[i].x, pedestrians[i].y, pedestrianSprite, pedestrians[i].frame);
  }

  Sprites::drawOverwrite(player.x, player.y, playerSprite, player.frame);
  arduboy.display();
}
