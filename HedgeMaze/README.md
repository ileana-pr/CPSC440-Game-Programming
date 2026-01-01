# 🌳 Hedge Maze 🧩

A time-based maze navigation game where you must find your way through three progressively challenging hedge mazes before time runs out.

## 📖 Description

Hedge Maze is a puzzle-platformer where players navigate through a series of hedge mazes using a character sprite. Each level has a 60-second time limit, and players must find the exit before time expires. The game features three levels with increasing complexity.

## 🎮 How to Play

1. **🎯 Objective**: Navigate through all three maze levels by finding the exit in each level before the 60-second timer runs out.

2. **Gameplay**:
   - ⌨️ Use arrow keys to move your character through the maze
   - 🏁 Find the exit block in each level to progress
   - ⏱️ You have 60 seconds per level to complete it
   - 🏆 Complete all 3 levels to win the game

3. **⌨️ Controls**:
   - **⬆️ Arrow Up**: Move up
   - **⬇️ Arrow Down**: Move down
   - **⬅️ Arrow Left**: Move left
   - **➡️ Arrow Right**: Move right
   - **ESC**: Exit game

## ✨ Features

- 🎚️ 3 maze levels with increasing difficulty
- ⏱️ 60-second timer per level
- 📊 Real-time timer display
- 💥 Collision detection with maze walls
- 📷 Camera scrolling that follows the player
- 🎬 Animated character sprite with directional movement
- 🎯 Level progression system
- ✅❌ Win/lose messages
- 🚀 Start position detection for each level

## 📋 Requirements

- 💻 **Visual Studio Express 2019** (or compatible version)
- 📦 Allegro 5 library (installed via NuGet packages)
- 🗺️ Mappy map files: `level1.FMP`, `level2.FMP`, `level3.FMP`
- 🖼️ Sprite sheet image: `guy.png`
- 🔤 Font file: `GROBOLD.ttf`

## 🔨 Building and Running

1. 📂 Open `HedgeMaze.sln` in Visual Studio Express 2019
2. 📦 **Restore NuGet packages** (right-click solution → Restore NuGet Packages, or build will auto-restore)
3. 🔨 Build the solution (F7 or Build → Build Solution)
4. ✅ Ensure all required assets (maps, sprites, fonts) are in the correct directories
5. ▶️ Run the game (F5 or Debug → Start Debugging)

**💡 Note**: The project uses NuGet packages for Allegro dependencies. Make sure NuGet package restore is enabled, or manually restore packages before building.

The game window is 900x480 pixels.

## ⚙️ Game Mechanics

- **⏱️ Timer System**: Each level has a 60-second countdown timer
- **💥 Collision Detection**: Map-based collision prevents walking through walls
- **📷 Camera System**: Camera follows the player, scrolling the map view
- **🏁 Exit Detection**: Special map blocks mark the exit for each level
- **🚀 Start Position**: Each level automatically finds and sets the starting position
- **🎬 Animation**: Character sprite animates based on movement direction

## 🏆 Win/Lose Conditions

- **✅ Win**: Complete all 3 levels by reaching the exit in each
- **❌ Lose**: Timer reaches 0 on any level (displays "TIME'S UP!" message)

## 📁 Files

- `Source.cpp`: Main game loop and logic
- `SpriteSheet.h` / `SpriteSheet.cpp`: Sprite rendering and animation
- `mappy_A5.h`: Map loading and rendering functions

