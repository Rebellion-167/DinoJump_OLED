#ifndef GAMEVARIABLES_H
#define GAMEVARIABLES_H

#include <Arduino.h>

/*-------------- OLED Setup -------------------*/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_DC 8
#define OLED_RST 9
#define OLED_CS 10
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RST, OLED_CS);

/*-------------- Input Pins --------------------*/
const int LEFT_BTN = 2;   // Jump, Advance
const int RIGHT_BTN = 3;  // Start / Reset

#define BUZZER_PIN 5  //Buzzer Pin

/*---------------- Game Constants ----------------*/
const int groundY = 55;
const int gravity = 1;
const int jumpStrength = -12;
int cactusSpeed = 3;

/*------------------ Game Variables --------------*/
int dinoX = 10;
int dinoY;
int velocity;
bool isJumping;

int cactusX;
int cactusY;
int cactusWidth;
int cactusHeight;
const unsigned char* activeCactusBitmap;

int score = 0;
int highScore = 0;

bool blinkVisible = true;
unsigned long lastBlinkTime = 0;
const unsigned long blinkInterval = 700;

/*-------------------- Game State Enum ---------------*/
enum State { INTRO1,
             INTRO2A,
             INTRO2B,
             PLAYING,
             GAME_OVER };
State gameState = INTRO1;

#endif