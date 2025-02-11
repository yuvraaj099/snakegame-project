<h1>Snake Game in C++</h1>

Overview

This is a simple Snake game implemented in C++ using the console. The game allows players to control a snake to collect food while avoiding collisions with the walls or itself. The game supports different speed levels and displays the score.

Features

Classic snake movement (Up, Down, Left, Right)

Food spawning and score tracking

Collision detection (walls and self)

Adjustable speed levels (Slow, Medium, Fast)

Console-based graphics

Requirements

Windows OS (due to windows.h and conio.h dependencies)

C++ compiler (MinGW for Windows recommended)

Compilation & Execution

Using g++ (MinGW on Windows):

 g++ -o snake_game snake_game.cpp -std=c++11 -static-libstdc++ -static-libgcc
 snake_game.exe

Controls

W - Move Up

A - Move Left

S - Move Down

D - Move Right

1 - Set Slow Speed

2 - Set Medium Speed

3 - Set Fast Speed

Game Rules

The snake moves automatically in the chosen direction.

The snake grows when it eats food.

The game ends if the snake hits the border or itself.

The score increases when food is eaten.

Structure

Point struct: Represents coordinates on the board.

Snake class: Handles movement, growth, and collision detection.

Board class: Manages the game state, food placement, and rendering.

main() function: Initializes the game loop and handles user input.

Future Enhancements

Add obstacles for more challenges.

Implement a high-score system.

Improve UI with better graphics.

License

This project is open-source and free to use. Modify it as you like!
