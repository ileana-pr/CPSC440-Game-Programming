# ❌ Tic-Tac-Toe ⭕

A classic Tic-Tac-Toe game where you play against the computer. Get three in a row to win!

## 📖 Description

Tic-Tac-Toe is a classic strategy game played on a 3x3 grid. You play as X (red) and compete against the computer which plays as O (yellow). The goal is to be the first to get three of your marks in a row (horizontally, vertically, or diagonally). The computer makes random moves, making it a fun challenge for players of all skill levels.

## 🎮 How to Play

1. **🎯 Objective**: Get three X's in a row (horizontally, vertically, or diagonally) before the computer gets three O's.

2. **Gameplay**:
   - Click on any empty square on the board to place your X
   - The computer will automatically place an O after your turn
   - Continue alternating turns until someone wins or the board is full
   - The game ends when there's a winner or a tie

3. **⌨️ Controls**:
   - **🖱️ Mouse Click**: Place your X on an empty square
   - **Close Window**: Exit the game

## ✨ Features

- 🎯 Classic 3x3 Tic-Tac-Toe gameplay
- 🤖 Computer opponent with random move selection
- ✅ Win detection for all 8 possible winning combinations
- 🤝 Tie detection when the board is full
- 🎨 Visual feedback with red X's and yellow O's
- 📊 Status messages showing game state
- ⏱️ Auto-close after 5 seconds when game ends

## 📋 Requirements

- 💻 **Visual Studio Express 2019** (or compatible version)
- 📦 Allegro 5 library (installed via NuGet packages)
- 🔤 Font file: `GROBOLD.ttf` (included)

## 🔨 Building and Running

1. 📂 Open `TicTacToe25.sln` in Visual Studio Express 2019
2. 📦 **Restore NuGet packages** (right-click solution → Restore NuGet Packages, or build will auto-restore)
3. 🔨 Build the solution (F7 or Build → Build Solution)
4. ▶️ Run the game (F5 or Debug → Start Debugging)

**💡 Note**: The project uses NuGet packages for Allegro dependencies. Make sure NuGet package restore is enabled, or manually restore packages before building.

The game window is 640x480 pixels.

## ⚙️ Game Mechanics

- **📐 Board Layout**: 3x3 grid with 9 playable squares
- **❌ Player Symbol**: X (drawn in red)
- **⭕ Computer Symbol**: O (drawn in yellow)
- **🎯 Win Conditions**: Three in a row horizontally, vertically, or diagonally (8 total win conditions)
- **🤝 Tie Condition**: All 9 squares filled with no winner
- **🤖 AI**: Computer makes random valid moves
- **🔄 Turn System**: Player goes first, then computer, alternating until game ends

## 🏆 Win/Lose Conditions

- **✅ Win**: Get three X's in a row (any direction)
- **❌ Lose**: Computer gets three O's in a row
- **🤝 Tie**: Board is full with no winner

## 📁 Files

- `graphics.cpp`: Main game loop, rendering, and user input handling
- `logic.h` / `logic.cpp`: Game logic, board state, and win detection
- `GROBOLD.ttf`: Font file for text display

