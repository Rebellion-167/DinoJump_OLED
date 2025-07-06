//Including required libraries and header files
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "Bitmaps.h"
#include "Game_Variables.h"
#include "Helper_Functions.h"
#include "Intro_Pages.h"

/* ---------------- Arduino Setup ----------------------*/
void setup() {
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();

  //Resetting high score on every boot
  highScore = 0;
  EEPROM.put(0, highScore);

  randomSeed(analogRead(A0));  // For cactus type randomization
  resetGameVars();
  showIntro1();  //Showing initial intro page
}

/* ------------------ Arduino loop ----------------------*/
void loop() {
  switch (gameState) {

    /* ------------ INTRO PAGE 1: Title -------------- */
    case INTRO1:
      // Draw static intro content only once
      static bool intro1Drawn = false;
      if (!intro1Drawn) {
        showIntro1();  // Draw "DINO JUMP" title
        intro1Drawn = true;
      }

      // Blink "Press RIGHT button"
      if (millis() - lastBlinkTime >= blinkInterval) {
        lastBlinkTime = millis();
        blinkVisible = !blinkVisible;

        display.setTextSize(1);
        display.setCursor(14, 52);
        if (blinkVisible) {
          display.setTextColor(SSD1306_WHITE);
          display.println("Press RIGHT button");
        } else {
          display.setTextColor(SSD1306_BLACK);  // Draw black text to "erase"
          display.println("Press RIGHT button");
        }
        display.display();
      }

      // Move to next intro page if RIGHT button pressed
      if (digitalRead(RIGHT_BTN) == LOW) {
        delay(200);
        showIntro2A();
        gameState = INTRO2A;
        intro1Drawn = false;  // Reset for next time
      }
      break;


    /* ------------- INTRO PAGE 2A: Instructions ------- */
    case INTRO2A:
      if (digitalRead(RIGHT_BTN) == LOW) {
        delay(200);
        showIntro2B();
        gameState = INTRO2B;
      }
      break;

    /* ------------- INTRO PAGE 2B : Get Ready --------- */
    case INTRO2B:
      if (digitalRead(LEFT_BTN) == LOW) {
        delay(200);

        // Show "Starting..." message
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(20, 28);
        display.println("Starting....");
        display.display();

        delay(1000);  // Short pause before animation

        //Setting up animation variables
        int animDinoX = -DINO_WIDTH;
        int animCactusX = SCREEN_WIDTH + 20;
        int animStep = 2;

        //Animating Dino and Cactus sliding in
        while (animDinoX < dinoX || animCactusX > cactusX) {
          display.clearDisplay();
          display.drawLine(0, groundY, SCREEN_WIDTH, groundY, SSD1306_WHITE);

          //Animating Dino
          if (animDinoX < dinoX) animDinoX += animStep;
          display.drawBitmap(animDinoX, dinoY, DinoBitmap, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);

          //Animating Cactus
          if (animCactusX > cactusX) animCactusX -= animStep;
          display.drawBitmap(animCactusX, cactusY, activeCactusBitmap, cactusWidth, cactusHeight, SSD1306_WHITE);

          display.display();
          delay(30);
        }

        //Pausing Briefly after animation
        delay(800);

        //Transitioning to gameplay
        display.clearDisplay();
        display.display();
        resetGameVars();
        gameState = PLAYING;
      }
      break;
    /* ------------ GAMEPLAY ---------------*/
    case PLAYING:
      //Jump control
      if (digitalRead(LEFT_BTN) == LOW && !isJumping) {
        velocity = jumpStrength;
        isJumping = true;
        playJumpSound();
      }

      //Applying physics
      dinoY += velocity;
      velocity += gravity;
      if (dinoY >= groundY - DINO_HEIGHT) {
        dinoY = groundY - DINO_HEIGHT;
        velocity = 0;
        isJumping = false;
      }

      //Cactus movements
      cactusX -= cactusSpeed;
      if (cactusX < -cactusWidth) {
        resetCactus();
        score++;
        updateDifficulty();
      }

      //Collision detection
      if (checkCollision()) {
        gameState = GAME_OVER;
        playGameOverSound();
        if (score > highScore) {
          highScore = score;
          EEPROM.put(0, highScore);  // Saving to EEPROM
        }
        flashGroundLineStatic(
          groundY, 3, 150,
          dinoX, dinoY, DinoBitmap,
          cactusX, cactusY, activeCactusBitmap,
          cactusWidth, cactusHeight,
          score);
        showGameOver();
        break;
      }

      //Rendering game frame
      display.clearDisplay();
      drawGroundDecor();
      display.drawLine(0, groundY, SCREEN_WIDTH, groundY, SSD1306_WHITE);
      display.drawBitmap(dinoX, dinoY, DinoBitmap, DINO_WIDTH, DINO_HEIGHT, SSD1306_WHITE);
      display.drawBitmap(cactusX, cactusY, activeCactusBitmap, cactusWidth, cactusHeight, SSD1306_WHITE);
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.print("Score: ");
      display.print(score);

      if (score > highScore && score > 0) {
        display.fillCircle(60, 3, 2, SSD1306_WHITE);
      }
      display.display();
      break;

    /* ------------- GAME OVER SCREEN ------------------ */
    case GAME_OVER:
      if (digitalRead(RIGHT_BTN) == LOW) {
        delay(200);
        display.clearDisplay();
        display.display();
        resetGameVars();
        gameState = PLAYING;
      }
      break;
  }
  delay(30);  // Frame pacing
}
