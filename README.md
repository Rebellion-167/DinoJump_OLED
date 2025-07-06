# 🦖 Dino Jump Game on OLED with Arduino Nano

A minimalist side-scrolling Dino Jump game developed using an **OLED SPI display** and an **Arduino Nano**. The game features custom bitmaps, game state management, sound effects via buzzer, EEPROM-based high score tracking, and a clean modular codebase using header files. 

##  🎮 Gameplay Features

- Controls the Dino with physical buttons
- Avoid randomly generated cactus obstacles
- Game over detection using bounding box collision
- Buzzer sound effects for jumping and game over
- High score saved using EEPROM
- Increasing difficulty as score increases

## 🧩 Code Structure

The project is modularized for clarity and ease of maintenance:

- `Dino_Jump_Game.ino` - Main loop and game state handler
- `Bitmaps.h` - Custom graphics for the Dino and Cactus
- `Game_Variables.h` - Game constants and global variables
- `Helper_Functions.h` - Game logic, sound, and helpers
- `Intro_Pages.h` - Intro screen and Game Over UI logic

## 🔧 Hardware Required

- Arduino Nano (or compatible)
- 128x64 OLED display (SPI interface)
- 2 Push Buttons (for jump and advance)
- Passive buzzer
- Breadboard

©️ 2025 Barnik Chakraborty
<br>
*Built for fun, learning and pixel-perfect jumping*
