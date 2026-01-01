# 🦷 Flappy Teeth 🎮

A side-scrolling survival game where you control a character navigating through a scrolling level, collecting food while avoiding spiders. The game features multiple levels with increasing difficulty.

## 📖 Description

Flappy Teeth is an endless runner-style game with a twist. You play as a character that must navigate through a scrolling map, collecting food items to maintain health while avoiding dangerous spiders. The game features multiple levels, each with increasing difficulty in terms of enemy count and scroll speed.

## 🎮 How to Play

1. **🎯 Objective**: Survive through all levels by collecting food and avoiding spiders. Your health decreases when hit by spiders, and you must reach the end of each level to progress.

2. **Gameplay**:
   - ➡️ The game automatically scrolls to the right
   - 🍎 Collect food items to maintain your health
   - 🕷️ Avoid spiders that will damage you on contact
   - 📈 Each level increases in difficulty with more spiders and faster scrolling
   - 🏆 Complete all 4 levels to win

3. **⌨️ Controls**:
   - **⬆️ Arrow Up**: Move up
   - **⬇️ Arrow Down**: Move down
   - **⬅️ Arrow Left**: Move left (limited to left third of screen)
   - **➡️ Arrow Right**: Move right (limited to left third of screen)
   - **Space**: Start game (from intro screen)
   - **ESC**: Exit game

## ✨ Features

- 🎚️ 4 progressively difficult levels
- ❤️ Health system (20 HP maximum)
- 📊 Health bar display
- 🍎 Food collection mechanics
- 🕷️ Spider enemies with collision detection
- 🎯 Level progression system
- 💀 Death animation sequence
- 🔊 Sound effects (food collection, spider hits, game over)
- 🎵 Background music
- 🎬 Intro screen
- ⏱️ Level display timer
- 📈 Increasing difficulty per level

## 📋 Requirements

- 💻 **Visual Studio Express 2019** (or compatible version)
- 📦 Allegro 5 library (installed via NuGet packages)
- 🗺️ Mappy map files: `level1.FMP`, `level2.FMP`, `level3.FMP`, `level4.FMP`
- 🖼️ Sprite sheet image
- 🔤 Font file: `GROBOLD.ttf`
- 🔊 Audio files:
  - `game-over-2-sound-effect-230463.mp3`
  - Spider munch sound
  - Food collection sound
  - Background music file

## 🔨 Building and Running

1. 📂 Open `FlappyTeeth.sln` in Visual Studio Express 2019
2. 📦 **Restore NuGet packages** (right-click solution → Restore NuGet Packages, or build will auto-restore)
3. 🔨 Build the solution (F7 or Build → Build Solution)
4. ✅ Ensure all required assets (maps, sprites, sounds) are in the correct directories
5. ▶️ Run the game (F5 or Debug → Start Debugging)

**💡 Note**: The project uses NuGet packages for Allegro dependencies. Make sure NuGet package restore is enabled, or manually restore packages before building.

The game window is 900x480 pixels.

## ⚙️ Game Mechanics

- **❤️ Health System**: Start with 20 HP, lose 1 HP per spider collision
- **➡️ Scrolling**: Automatic rightward scrolling at increasing speeds per level
- **💥 Collision Detection**: Map-based collision for walls, separate collision for enemies
- **🍎 Food Spawning**: Food items spawn randomly and can be collected
- **🕷️ Enemy Spawning**: Spiders spawn and move toward the player
- **🎯 Level Progression**: Complete a level by reaching the end, then advance to the next
- **💀 Game Over**: Occurs when health reaches 0, with a death animation sequence

## 📊 Level Difficulty

- **🎚️ Level 1**: Base difficulty (5 foods, 3 spiders, base scroll speed)
- **🎚️ Level 2-4**: Increasing numbers of spiders and faster scroll speeds

## 📁 Files

- `Source.cpp`: Main game loop and logic
- `SpriteSheet.h` / `SpriteSheet.cpp`: Sprite rendering and animation
- `Food.h` / `Food.cpp`: Food item mechanics
- `Spider.h` / `Spider.cpp`: Enemy spider mechanics
- `mappy_A5.h`: Map loading and rendering functions

