#ifndef INTROPAGES_H
#define INTROPAGES_H

#include <Arduino.h>

//Title Page
void showIntro1() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(40, 8);
  display.println("DINO");
  display.setCursor(40, 27);
  display.println("JUMP");
  display.display();
}

//Instructions page
void showIntro2A() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 5);
  display.println("Press LEFT Button");
  display.setCursor(5, 15);
  display.println("to jump");
  display.setCursor(5, 30);
  display.println("Avoid Cactus!");
  display.setCursor(5, 43);
  display.println("Press RIGHT to");
  display.setCursor(5, 53);
  display.println("continue");
  display.display();
}

//Ready-to-start page
void showIntro2B() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(35, 20);
  display.println("Get Ready!");
  display.setCursor(12, 40);
  display.println("Press LEFT to start");
  display.display();
}

//Game over screen
void showGameOver() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(32, 2);
  display.println("GAME OVER!");
  display.setCursor(15, 16);
  display.print("Score : ");
  display.println(score);
  display.setCursor(15, 26);
  display.print("High : ");
  display.println(highScore);
  display.setCursor(6, 40);
  display.println("Press RIGHT to");
  display.setCursor(6, 49);
  display.println("restart");
  display.display();
}

#endif