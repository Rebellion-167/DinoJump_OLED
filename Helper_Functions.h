#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <Arduino.h>

//Randomly choose cactus type and reset its position
void resetCactus() {
  if (random(2) == 0) {  //picking small
    cactusWidth = CACTUS_S_WIDTH;
    cactusHeight = CACTUS_S_HEIGHT;
    activeCactusBitmap = cactusSmallBitmap;
  } else {  //picking tall
    cactusWidth = CACTUS_T_WIDTH;
    cactusHeight = CACTUS_T_HEIGHT;
    activeCactusBitmap = cactusTallBitmap;
  }
  cactusX = SCREEN_WIDTH + 20;
  cactusY = groundY - cactusHeight;
}

//Resets dino and cactus for new game
void resetGameVars() {
  dinoY = groundY - DINO_HEIGHT;
  velocity = 0;
  isJumping = false;
  score = 0;
  resetCactus();
  cactusSpeed = 3;
}

// Axis-Aligned Bounding Box collision detection
bool checkCollision() {
  return (
    dinoX < cactusX + cactusWidth && dinoX + DINO_WIDTH > cactusX && dinoY < cactusY + cactusHeight && dinoY + DINO_HEIGHT > cactusY);
}

//Jump Sound
void playJumpSound() {
  tone(BUZZER_PIN, 1000, 100);
}

//Game Over Sound
void playGameOverSound() {
  tone(BUZZER_PIN, 300, 200);
  delay(250);
  tone(BUZZER_PIN, 100, 200);
}

//Changing difficulty
void updateDifficulty() {
  if (score > 0 && score % 5 == 0) {
    //Increasing speed every 5 points, up to a limit
    if (cactusSpeed < 7) {
      cactusSpeed++;
    }
  }
}

//Random dots beneath the line
void drawGroundDecor() {
  const int dotY1 = groundY + 3;  // Slightly below the ground line
  const int dotY2 = groundY + 5;
  int dotSpacing = 10;  // Space between dots

  // Drawing dots at fixed X positions
  for (int x = 5; x < SCREEN_WIDTH; x += dotSpacing) {
    display.drawPixel(x, dotY1, SSD1306_WHITE);

    if (x + dotSpacing / 2 < SCREEN_WIDTH) {
      display.drawPixel(x + dotSpacing / 2, dotY2, SSD1306_WHITE);
    }
  }
}

//Flashing the ground line when collision occurs
void flashGroundLineStatic(
  int groundY, int flashes, int flashDelay,
  int dinoX, int dinoY, const unsigned char* dinoBitmap,
  int cactusX, int cactusY, const unsigned char* cactusBitmap,
  int cactusW, int cactusH, int score) {
  for (int i = 0; i < flashes; i++) {
    display.clearDisplay();

    // Draw everything except the ground
    display.drawBitmap(dinoX, dinoY, dinoBitmap, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
    display.drawBitmap(cactusX, cactusY, cactusBitmap, cactusW, cactusH, SSD1306_WHITE);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("Score: ");
    display.print(score);

    // Draw dirt (dot layer)
    for (int x = 0; x < SCREEN_WIDTH; x += 6) {
      if ((x / 6) % 2 == 0)  // alternating pattern
        display.drawPixel(x, groundY + 3, SSD1306_WHITE);
    }

    // Skip ground in this frame
    display.display();
    delay(flashDelay);

    // Same frame but with ground
    display.drawLine(0, groundY, SCREEN_WIDTH, groundY, SSD1306_WHITE);
    display.display();
    delay(flashDelay);
  }
}

#endif