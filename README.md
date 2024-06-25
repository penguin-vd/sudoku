# Sudoku Game

Welcome to the Sudoku Game - a terminal-based implementation of the classic number puzzle game!

## Features 🎮

- **Multiple Difficulty Levels**: Choose from Easy, Medium, and Hard difficulties.
- **Interactive Gameplay**: Use arrow keys to navigate the board and number keys to place digits.
- **Hints**: Get assistance with the 'h' key to place a correct number.
- **Board Completion**: Automatically checks if the board is completed correctly.
- **Resetting**: Reset the board or start a new game at any time.
- **Dynamic UI**: Adjusts to your terminal size for optimal display.

## How to Play 🕹️

1. Use arrow keys to move around the board.
2. Press '0-9' to place a number in the selected cell.
3. Press 'h' for a hint (places a correct number in a random empty cell).
4. Press 'r' to reset the board or start a new game.
5. Press 'f' to automatically complete the board.
6. Press 'q' to quit the game.

## Getting Started 🚀

This tool is tailored for Linux users and has been tested on a Manjaro machine. To run the Sudoku game, you have two options:

1. Use the provided shell script:
   ```bash
   sh run.sh
   ```

2. Compile and run manually:
   ```bash
   make
   ./sudoku
   ```

## File Structure 📂

- **main.cpp**: Entry point of the application.
- **components.cpp**: Contains the core functionality and user interaction logic. *Based on my [project-manager](https://github.com/penguin-vd/project-manager)*
- **sudoku.cpp**: Implements the Sudoku game mechanics.
- **ui_library.cpp**: Handles terminal UI rendering and input management. *Based on my [project-manager](https://github.com/penguin-vd/project-manager)*

## Demo 🎬

![newdemo](https://github.com/penguin-vd/sudoku/assets/62374225/8573c6cf-2260-44c8-b716-49f466af5757)
