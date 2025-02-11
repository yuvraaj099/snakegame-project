<h1>Snake Game in C++</h1>
<br>

<h2>Overview</h2>

This is a simple Snake game implemented in C++ using the console. The game allows players to control a snake to collect food while avoiding collisions with the walls or itself. The game supports different speed levels and displays the score.
<br><br>
<h2>Features</h2>

● Classic snake movement (Up, Down, Left, Right)

<br>● Food spawning and score tracking

<br>● Collision detection (walls and self)

<br>● Adjustable speed levels (Slow, Medium, Fast)

<br>● Console-based graphics
<br><br><br>
<h2>Requirements</h2>

● Windows OS (due to windows.h and conio.h dependencies)

<br>● C++ compiler (MinGW for Windows recommended)
<br><br><br>
<h2>Compilation & Execution</h2>

<h3>Using g++ (MinGW on Windows):</h3>

 <br>g++ -o snake_game snake_game.cpp -std=c++11 -static-libstdc++ -static-libgcc
 snake_game.exe
<br><br><br>
<h2>Controls</h2>

● W - Move Up

<br>● A - Move Left

<br>● S - Move Down

<br>● D - Move Right

<br>● 1 - Set Slow Speed

<br>● 2 - Set Medium Speed

<br>● 3 - Set Fast Speed
<br><br><br>
<h2>Game Rules</h2>

● The snake moves automatically in the chosen direction.

<br>● The snake grows when it eats food.

<br>● The game ends if the snake hits the border or itself.

<br>● The score increases when food is eaten.
<br><br><br>
<h2>Structure</h2>

● Point struct: Represents coordinates on the board.

<br>● Snake class: Handles movement, growth, and collision detection.

<br>● Board class: Manages the game state, food placement, and rendering.

<br>● main() function: Initializes the game loop and handles user input.
<br><br><br>
<h2>Future Enhancements</h2>

● Add obstacles for more challenges.

<br>● Implement a high-score system.

<br>● Improve UI with better graphics.
<br>
<h2>License</h2>

This project is open-source and free to use. Modify it as you like!
