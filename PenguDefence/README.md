# 🐧 Pengu Defence ❄️

A tower defense-style game where you defend your iceberg from falling penguins by firing snowballs at them. Prevent penguins from landing on your iceberg to keep it afloat!

## 📖 Description

Pengu Defence is a defense game where you control a penguin cannon on an iceberg. Penguins drop from the top of the screen, and you must shoot them down with snowballs before they land on your iceberg. Each penguin that lands reduces your iceberg's lives. Survive as long as possible and achieve the highest score!

## 🎮 How to Play

1. **🎯 Objective**: Defend your iceberg by shooting down falling penguins with snowballs. Prevent penguins from landing on your iceberg to avoid losing lives.

2. **Gameplay**:
   - ⬅️➡️ Use left/right arrow keys to aim your cannon
   - ❄️ Press spacebar to fire snowballs
   - 🎯 Hit penguins before they reach the iceberg
   - ❤️ Each penguin that lands reduces your iceberg's lives
   - 💀 Game ends when all lives are lost

3. **⌨️ Controls**:
   - **⬅️ Arrow Left**: Rotate cannon left (aim left)
   - **➡️ Arrow Right**: Rotate cannon right (aim right)
   - **Spacebar**: Fire snowball
   - **ESC**: Exit game

## ✨ Features

- 🎯 Rotating cannon for aiming
- ❄️ Snowball projectile system
- 🐧 Multiple penguins dropping simultaneously (7 penguins)
- 💥 Collision detection between snowballs and penguins
- 📊 Score tracking system
- ❤️ Lives system for the iceberg
- 🖼️ Background image support
- 💀 Game over screen with final score
- 🎲 Random penguin spawning

## 📋 Requirements

- 💻 **Visual Studio Express 2019** (or compatible version)
- 📦 Allegro 5 library (installed via NuGet packages)
- 🔤 Font file: `GROBOLD.TTF` (falls back to built-in font if not found)
- 🖼️ Background image: `background.png` (optional, creates default sky blue background if not found)

## 🔨 Building and Running

1. 📂 Open `PenguDefence.sln` in Visual Studio Express 2019
2. 📦 **Restore NuGet packages** (right-click solution → Restore NuGet Packages, or build will auto-restore)
3. 🔨 Build the solution (F7 or Build → Build Solution)
4. ✅ Ensure the font file is in the executable directory (optional)
5. ▶️ Run the game (F5 or Debug → Start Debugging)

**💡 Note**: The project uses NuGet packages for Allegro dependencies. Make sure NuGet package restore is enabled, or manually restore packages before building.

The game window is 640x520 pixels.

## ⚙️ Game Mechanics

- **🎯 Cannon System**: Rotatable cannon that fires snowballs in the direction it's aimed
- **❄️ Projectile Physics**: Snowballs travel in a straight line from the cannon
- **🐧 Penguin Spawning**: Penguins spawn at random positions from the top of the screen
- **💥 Collision Detection**: Snowballs destroy penguins on contact
- **❤️ Lives System**: Iceberg has a limited number of lives that decrease when penguins land
- **📊 Scoring**: Points are awarded for each penguin shot down
- **💀 Game Over**: Occurs when iceberg lives reach 0, displays final score

## 🎮 Game Objects

- **🏔️ Iceberg**: Your base that must be defended (bottom of screen)
- **🐧 Penguin Firing**: The cannon you control (on the iceberg)
- **❄️ Snowballs**: Projectiles you fire (up to 10 active at once)
- **🐧 Dropping Penguins**: Enemies that fall from the top (7 total)

## 📁 Files

- `PenguDefence.cpp`: Main game loop and logic
- `iceberg.h` / `iceberg.cpp`: Iceberg rendering and lives management
- `penguinFiring.h` / `penguinFiring.cpp`: Cannon control and rotation
- `snowball.h` / `snowball.cpp`: Projectile mechanics
- `penguinDropping.h` / `penguinDropping.cpp`: Enemy penguin behavior

