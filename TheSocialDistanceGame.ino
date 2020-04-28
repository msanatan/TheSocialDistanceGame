// Marcus Sanatan (msanatan)
// March 24th, 2020
// The Social Distance Game

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "src/audio.h"
#include "src/images.h"
#include "src/Player.h"
#include "src/Pedestrian.h"
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

const int FPS = 60;
unsigned long previousTime = 0;
float totalSeconds = 0;
bool paused = false;
int score = 0;
enum state
{
  MENU,
  PLAYING,
  GAMEOVER
};
state gameState;

// HUD
int heartX = 2;
int heartXSeparator = 12;
int heartY = 0;

// Player
Player player;

// Pedestrians
const int MAX_PEDESTRIANS = 8;
const int PEDESTRIAN_SPAWN_TIME = 1; // Spawn roughly every 2 seconds
int lastSpawnTime = 0;
int spawnSecondCount = 0;
// Create array of pedestrians
Pedestrian pedestrians[MAX_PEDESTRIANS];
bool updatePedestrianFrame;
bool movePedestrians;
int activePedestrians = 0;

// addPedestrians initializes
void addPedestrians(int i)
{
  if (activePedestrians < MAX_PEDESTRIANS)
  {
    int side = random(0, 2);
    pedestrians[i].x = (side == 1) ? WIDTH : 0;
    int lane = random(1, 4);
    int pedestrianSpeed = random(2, 9);
    pedestrians[i].y = pedestrians[i].getSize() * lane;
    pedestrians[i].speedX = (side == 1) ? -pedestrianSpeed : pedestrianSpeed;
    // Selet frame based on direction pedestrian is going
    if (pedestrians[i].speedX < 0)
    {
      pedestrians[i].frame = 0;
    }
    else
    {
      pedestrians[i].frame = 4;
    }
    pedestrians[i].active = true;
    activePedestrians++;
  }
}

void reset()
{
  // Reset player properties
  player.x = WIDTH / 2;
  player.y = HEIGHT / 2;
  player.lives = 3;
  player.frame = 0;
  player.lastHit = 0;
  player.justHit = false;

  // Reset Pedestrians
  for (int i = 0; i < MAX_PEDESTRIANS; i++)
  {
    pedestrians[i].x = -20;
    pedestrians[i].active = false;
  }

  // Reset other global properties
  activePedestrians = 0;
  updatePedestrianFrame = false;
  movePedestrians = false;
  lastSpawnTime = 0;
  spawnSecondCount = 0;
  score = 0;
  totalSeconds = 0;
  previousTime = millis();
  paused = false;

  // Let's put one pedestrian in the mix
  addPedestrians(0);
}

void setup()
{
  arduboy.begin();
  arduboy.clear();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(FPS);
  gameState = MENU;
  arduboy.clear();
}

void loop()
{
  if (!arduboy.nextFrame())
  {
    return;
  }
  arduboy.pollButtons();

  switch (gameState)
  {
  case MENU:
  {
    arduboy.clear();
    // If the user presses a button, they will play
    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
    {
      reset();
      gameState = PLAYING;
    }

    Sprites::drawOverwrite(0, 0, title, 0);
    arduboy.setCursor(2 * WIDTH / 3, HEIGHT / 2);
    arduboy.print("> Play");
    break;
  }
  case PLAYING:
  {
    // Check if game over
    if (player.lives == 0)
    {
      gameState = GAMEOVER;
      return;
    }

    arduboy.clear();

    // Handle pausing mechanics
    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
    {
      paused = !paused;
      previousTime = millis();
    }

    if (paused)
    {
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

    // HUD
    for (int i = 0; i < player.lives; i++)
    {
      int xPosition = heartX + (i * heartXSeparator);
      Sprites::drawOverwrite(xPosition, heartY, heart, 0);
    }
    arduboy.setCursor(62, 0);
    arduboy.print("Score: ");
    arduboy.print(score);

    // Check if player is still justHit
    if (player.justHit)
    {
      unsigned long timeSinceHit = currentTime - player.lastHit;
      float lastHitSeconds = timeSinceHit * (1.0f / 1000.0f);

      if (static_cast<int>(lastHitSeconds) >= player.getInvincibilityDuration())
      {
        player.justHit = false;
      }
    }

    // Move player
    if (arduboy.pressed(LEFT_BUTTON) && player.x > 0)
    {
      player.x = player.x - player.speedX;
      player.frame = 1;
    }
    else if (arduboy.pressed(RIGHT_BUTTON) && player.x + player.getSize() < WIDTH)
    {
      player.x = player.x + player.speedX;
      player.frame = 0;
    }

    if (arduboy.justPressed(UP_BUTTON) && player.y > 16)
    {
      player.y = player.y - player.speedY;
    }
    else if (arduboy.justPressed(DOWN_BUTTON) && player.y + player.getSize() < HEIGHT)
    {
      player.y = player.y + player.speedY;
    }

    // Flag the pedestrian to move
    if (arduboy.everyXFrames(10))
    {
      movePedestrians = true;
    }

    // Update the frame of the Pedestrian
    if (arduboy.everyXFrames(20))
    {
      updatePedestrianFrame = true;
    }

    int nextActive = -1;
    // Update pedestrians
    for (int i = 0; i < MAX_PEDESTRIANS; i++)
    {
      // If the sprite is not active, there's not much to update
      // However, we mark it as the next available sprite to use
      if (!pedestrians[i].active)
      {
        if (nextActive == -1)
        {
          nextActive = i;
        }
        continue;
      }

      // Move active pedestrians
      if (movePedestrians)
      {
        if (pedestrians[i].active)
        {
          pedestrians[i].x += pedestrians[i].speedX;
          pedestrians[i].y += pedestrians[i].speedY;
        }
      }

      // Check for collisions
      if (pedestrians[i].collide(player.x, player.y, player.getSize(), player.getSize()) && !player.justHit)
      {
        --player.lives;
        player.justHit = true;
        player.lastHit = millis();
        sound.tones(player_hit_sfx);
      }

      // Set pedestrians off the screen to be inactive
      if (pedestrians[i].x >= WIDTH + 10 || pedestrians[i].x < -18)
      {
        pedestrians[i].active = false;
        activePedestrians--;
      }

      if (updatePedestrianFrame)
      {
        pedestrians[i].nextFrame();
      }
    }

    // Reset pedestrian flags
    updatePedestrianFrame = false;
    movePedestrians = false;

    // Add a new pedestrian
    // We use the lastSpawnTime to ensure that many frames in a second
    // don't keep spawning pedestrians
    if (score % PEDESTRIAN_SPAWN_TIME == 0 && score != lastSpawnTime)
    {
      addPedestrians(nextActive);
      lastSpawnTime = score;
    }

    // Draw pedestrians
    for (int i = 0; i < MAX_PEDESTRIANS; i++)
    {
      Sprites::drawOverwrite(pedestrians[i].x, pedestrians[i].y, pedestrianSprite, pedestrians[i].frame);
    }

    if (!player.justHit)
    {
      Sprites::drawOverwrite(player.x, player.y, playerSprite, player.frame);
    }
    else
    {
      // Let's make the Sprite flicker
      if (arduboy.everyXFrames(6))
      {
        Sprites::drawOverwrite(player.x, player.y, playerSprite, player.frame);
      }
    }
  }
  break;
  case GAMEOVER:
  {
    // If the user presses a button, send them back to the title
    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
    {
      gameState = MENU;
    }

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
