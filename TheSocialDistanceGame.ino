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

const unsigned char PROGMEM title[] =
{
  // width, height,
  68, 27,
  0x03, 0x7f, 0x7f, 0x03, 0x03, 0x00, 0x00, 0x7f, 0x7f, 0x18, 0x18, 0x78, 0x78, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7b, 0x7b, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7b, 0x7b, 0x7b, 0x7b, 0x7b, 0x00, 0x00, 0x3c, 0x7f, 0x63, 0x63, 0x7f, 0x3c, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x63, 0x63, 0x00, 0x00, 0x00, 0x7b, 0x7b, 0x00, 0x00, 0x7b, 0x7b, 0x7b, 0x7b, 0x7f, 0x7f, 0x00, 0x00, 0x7f, 0x7f, 0x5d,
  0xfc, 0xfc, 0x8c, 0x8c, 0xfc, 0xf0, 0x00, 0x00, 0xe4, 0xec, 0xe4, 0x00, 0x00, 0xb0, 0xfc, 0xec, 0xec, 0xec, 0xcc, 0x00, 0x00, 0x30, 0x30, 0xfc, 0xfc, 0xb0, 0x00, 0x00, 0xec, 0xec, 0xec, 0xec, 0xec, 0xfc, 0xfc, 0x00, 0x00, 0xfc, 0xfc, 0x0c, 0x0c, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x8c, 0x8c, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xec, 0xec, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xf1, 0xf1, 0x31, 0xb1, 0xb1, 0xb0, 0x00, 0x00, 0x91, 0xb1, 0xb1, 0xb0, 0xb0, 0xf1, 0xf1, 0x01, 0x01, 0xf1, 0xf0, 0x30, 0xf0, 0xf0, 0x30, 0xf1, 0xf1, 0x01, 0x00, 0xf0, 0xf1, 0xb1, 0xb1, 0xf1, 0xf1, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0x07, 0x06, 0x07, 0x07, 0x07, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const int FPS = 60;
unsigned long previousTime = 0;
float totalSeconds = 0;
bool paused = false;
int score = 0;
enum state {MENU, PLAYING, GAMEOVER};
state gameState;

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
    int lastHit;
    bool justHit;

    int getSize() {
      return size;
    }

    int getInvincibilityDuration() {
      return invincibilityDuration;
    }

  private:
    int size = 16;
    int invincibilityDuration = 1;
};

Player player;

// Pedestrians
class Pedestrian {
  public:
    int x = -20; // So they will be offscreen when initialized
    int y;
    int speedX;
    int speedY;
    int frame;
    bool active;

    int getSize() {
      return size;
    }

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

    bool collide(int x, int y, int width, int height) {
      return x < this->x + this->size &&
             x + width > this->x &&
             y < this->y + this->size &&
             y + height > this->y;
    }

  private:
    int size = 16;
};

const int MAX_PEDESTRIANS = 8;
const int PEDESTRIAN_SPAWN_TIME = 1; // Spawn roughly every 2 seconds
int lastSpawnTime = 0;
int spawnSecondCount = 0;
// Create array of pedestrians
Pedestrian pedestrians[MAX_PEDESTRIANS];
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
    pedestrians[i].y = pedestrians[i].getSize() * lane;
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
  gameState = PLAYING;
  previousTime = millis();
  arduboy.clear();
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }
  arduboy.pollButtons();

  switch (gameState) {
    case MENU: {
        Sprites::drawOverwrite(0, 0, title, 0);
        break;
      }
    case PLAYING: {
        // Check if game over
        if (player.lives == 0) {
          gameState = GAMEOVER;
          return;
        }

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

        // Check if player is still justHit
        if (player.justHit) {
          unsigned long timeSinceHit = currentTime - player.lastHit;
          float lastHitSeconds = timeSinceHit * (1.0f / 1000.0f);

          if (lastHitSeconds >= player.getInvincibilityDuration()) {
            player.justHit = false;
          }
        }

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

          // Check for collisions
          if (pedestrians[i].collide(player.x, player.y, player.getSize(), player.getSize()) && !player.justHit) {
            player.lives--;
            player.justHit = true;
            player.lastHit = millis();
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

        if (!player.justHit) {
          Sprites::drawOverwrite(player.x, player.y, playerSprite, player.frame);
        } else {
          // Let's make the Sprite flicker
          if (arduboy.everyXFrames(6)) {
            Sprites::drawOverwrite(player.x, player.y, playerSprite, player.frame);
          }
        }
      }
      break;
    case GAMEOVER: {
        arduboy.clear();
        arduboy.setTextSize(2);
        arduboy.print("Game Over");
        arduboy.setCursor(0, 20);
        arduboy.print("Score:");
        arduboy.print(score);
        arduboy.setTextSize(1);
        arduboy.setCursor(0, 50);
        arduboy.print("Press A to continue");
      }
      break;
  }
  // Render the state of the game scene
  arduboy.display();
}
