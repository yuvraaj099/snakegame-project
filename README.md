<h1>Snake Game in C++</h1>

<h3>Overview</h3>

<br>This is a simple Snake game implemented in C++ using the console. The game allows players to control a snake to collect food while avoiding collisions with the walls or itself. The game supports different speed levels and displays the score.

<h2>Features</h2>

<br>● Classic snake movement (Up, Down, Left, Right)

<br>● Food spawning and score tracking

<br>● Collision detection (walls and self)

<br>● Adjustable speed levels (Slow, Medium, Fast)

<br>● Console-based graphics

<h2>Requirements</h2>

<br>● Windows OS (due to windows.h and conio.h dependencies)

<br>● C++ compiler (MinGW for Windows recommended)

<h2>Compilation & Execution</h2>

<h3>Using g++ (MinGW on Windows):</h3>

 <br>g++ -o snake_game snake_game.cpp -std=c++11 -static-libstdc++ -static-libgcc
 snake_game.exe

<h2>Controls</h2>

<br>● W - Move Up

<br>● A - Move Left

<br>● S - Move Down

<br>● D - Move Right

<br>● 1 - Set Slow Speed

<br>● 2 - Set Medium Speed

<br>● 3 - Set Fast Speed

<h2>Game Rules</h2>

<br>● The snake moves automatically in the chosen direction.

<br>● The snake grows when it eats food.

<br>● The game ends if the snake hits the border or itself.

<br>● The score increases when food is eaten.

<h2>Structure</h2>

<br>● Point struct: Represents coordinates on the board.

<br>● Snake class: Handles movement, growth, and collision detection.

<br>● Board class: Manages the game state, food placement, and rendering.

<br>● main() function: Initializes the game loop and handles user input.

<h2>Future Enhancements</h2>

<br>● Add obstacles for more challenges.

<br>● Implement a high-score system.

<br>● Improve UI with better graphics.

<h2>License</h2>

This project is open-source and free to use. Modify it as you like!
