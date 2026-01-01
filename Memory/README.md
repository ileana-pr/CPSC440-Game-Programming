# 🧠 Memory Game 🎴

A classic memory matching card game where players must find all matching pairs of shapes in the least number of moves.

## 📖 Description

Memory is a card matching game featuring a 5x5 grid (24 cards total, with one corner reserved for status display). The game contains 12 pairs of different shapes that are randomly shuffled at the start of each game. Players click on cards to reveal them, and must remember the positions to match pairs.

## 🎮 How to Play

1. **🎯 Objective**: Find all 12 matching pairs of shapes in the fewest moves possible.

2. **Gameplay**:
   - 🖱️ Click on a card to reveal it
   - 🖱️ Click on a second card to see if they match
   - ✅ If the cards match, they remain visible and are marked as matched
   - ❌ If the cards don't match, they flip back after 2 seconds
   - 🔄 Continue until all pairs are found

3. **⌨️ Controls**:
   - **Mouse Click**: Select and flip cards
   - **ESC**: Exit the game

## ✨ Features

- 🎴 12 unique shape pairs (24 cards total)
- 🔀 Random card shuffling for each game
- 📊 Move counter to track your progress
- 📈 Status display showing pairs remaining and moves made
- ✅ Visual feedback for matched pairs (marked with X)
- ⏱️ 2-second delay before hiding mismatched cards

## 📋 Requirements

- 💻 **Visual Studio Express 2019** (or compatible version)
- 📦 Allegro 5 library (installed via NuGet packages)
- 🔤 Font file: `GROBOLD.ttf` (included)

## 🔨 Building and Running

1. 📂 Open `Memory.sln` in Visual Studio Express 2019
2. 📦 **Restore NuGet packages** (right-click solution → Restore NuGet Packages, or build will auto-restore)
3. 🔨 Build the solution (F7 or Build → Build Solution)
4. ▶️ Run the game (F5 or Debug → Start Debugging)

**💡 Note**: The project uses NuGet packages for Allegro dependencies. Make sure NuGet package restore is enabled, or manually restore packages before building.

The game window is 640x520 pixels.

## ⚙️ Game Mechanics

- **📐 Grid Layout**: 5x5 grid with 24 playable positions
- **🔷 Shapes**: Various geometric shapes (circles, squares, triangles, diamonds, ovals, rectangles, octagons, etc.)
- **📊 Scoring**: Tracked by number of moves (fewer moves = better performance)
- **🏆 Win Condition**: All 12 pairs matched

## 📁 Files

- `game.h` / `game.cpp`: Game logic and state management
- `graphics.cpp`: Rendering and user input handling
- `GROBOLD.ttf`: Font file for text display

