#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>  // For _kbhit() and _getch()

using namespace std;

const int width = 30, height = 20;

class SnakeGame {
public:
    HANDLE console;
    bool gameOver;
    int x, y, foodX, foodY, score;
    vector<pair<int, int>> snake;
    enum Direction { STOP, LEFT, RIGHT, UP, DOWN };
    Direction dir;
    int speed;  // Speed control variable
    int highestScore;  // Store highest score across all games

    void GotoXY(int x, int y) {
        COORD coord = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(console, coord);
    }

    void HideCursor() {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(console, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(console, &cursorInfo);
    }

    void Setup() {
        gameOver = false;
        dir = RIGHT;  // Starting direction to the right
        x = width / 2;
        y = height / 2;

        foodX = rand() % width;
        foodY = rand() % height;

        score = 0;

        // Initialize the snake with one head and two body parts
        snake.clear();
        snake.push_back({x, y});  // Head
        snake.push_back({x - 1, y}); // First body part

        HideCursor();
        speed = 100;  // Default speed (medium speed)
    }

    void Draw() {
        GotoXY(0, 0);

        // Draw top border
        for (int i = 0; i < width + 2; i++) cout << "# ";
        cout << endl;

        // Draw grid with snake and food
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0) cout << "# ";  // Left boundary

                // Draw the head
                if (i == y && j == x) cout << "O ";
                else if (i == foodY && j == foodX) cout << "* ";  // Food
                else {
                    bool print = false;
                    // Draw snake body
                    for (auto s : snake) {
                        if (s.first == j && s.second == i) {
                            cout << "o ";
                            print = true;
                            break;
                        }
                    }
                    if (!print) cout << "  ";  // Empty space
                }

                if (j == width - 1) cout << "# ";  // Right boundary
            }
            cout << endl;
        }

        // Draw bottom border
        for (int i = 0; i < width + 2; i++) cout << "# ";
        cout << "\nScore: " << score << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a': case 'A': if (dir != RIGHT) dir = LEFT; break;
                case 'd': case 'D': if (dir != LEFT) dir = RIGHT; break;
                case 'w': case 'W': if (dir != DOWN) dir = UP; break;
                case 's': case 'S': if (dir != UP) dir = DOWN; break;
                case 'x': gameOver = true; break;
                case '1': speed = 200; break;  // Slow speed
                case '2': speed = 100; break;  // Medium speed
                case '3': speed = 50; break;   // Fast speed
                case '+': if (speed > 10) speed -= 10; break; // Increase speed
                case '-': if (speed < 200) speed += 10; break; // Decrease speed
            }
        }
    }

    void Logic() {
        int prevX = snake[0].first, prevY = snake[0].second;
        int prev2X, prev2Y;
        snake[0] = {x, y};

        // Update the body parts of the snake
        for (size_t i = 1; i < snake.size(); i++) {
            prev2X = snake[i].first;
            prev2Y = snake[i].second;
            snake[i] = {prevX, prevY};
            prevX = prev2X;
            prevY = prev2Y;
        }

        // Move the head of the snake based on the current direction
        switch (dir) {
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UP: y--; break;
            case DOWN: y++; break;
            default: break;
        }

        // Check if the snake hits the wall
        if (x < 0 || x >= width || y < 0 || y >= height) gameOver = true;

        // Check if the snake collides with itself
        for (size_t i = 1; i < snake.size(); i++) {
            if (snake[i].first == x && snake[i].second == y) gameOver = true;
        }

        // Check if the snake eats food
        if (x == foodX && y == foodY) {
            score += 1;
            snake.push_back({foodX, foodY});  // Add a new body part

            bool validFoodPosition;
            do {
                validFoodPosition = true;
                foodX = rand() % width;
                foodY = rand() % height;

                // Ensure food doesn't spawn on the snake
                for (const auto& segment : snake) {
                    if (segment.first == foodX && segment.second == foodY) {
                        validFoodPosition = false;
                        break;
                    }
                }
            } while (!validFoodPosition);
        }
    }

    void displayGameOver() {
        // Clearing screen and game over message
        system("cls");

        int centerX = width / 2 - 5;
        int centerY = height / 2;

        GotoXY(centerX - 1, centerY - 1);
        cout << "***********************";
        GotoXY(centerX - 1, centerY);
        cout << "                       ";
        GotoXY(centerX - 1, centerY + 1);
        cout << "***********************";

        // Game over message
        GotoXY(centerX, centerY);
        cout << "    GAME OVER  ";

        // Display final score
        GotoXY(centerX, centerY + 2);
        cout << "    Final Score   : " << score;

        // Display highest score
        GotoXY(centerX, centerY + 3);
        cout << "    Highest Score : " << highestScore;

        // Adding extra decoration
        GotoXY(centerX - 1, centerY + 4);
        cout << "***********************";
    }

    void playAgainPrompt() {
        char playAgain;
        cout << "\n\nDo you want to play again? (y/n): ";
        cin >> playAgain;
        if (playAgain == 'y' || playAgain == 'Y') {
            gameOver = false;
            Setup();  // Reset the game
            Run();    // Start a new game
        } else {
            cout << "\nThanks for playing! Goodbye!" << endl;
        }
    }

public:
    SnakeGame() : console(GetStdHandle(STD_OUTPUT_HANDLE)), highestScore(0) {}

    void Run() {
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(speed);  // Adjust speed
        }

        if (score > highestScore) {
            highestScore = score;
        }

        displayGameOver();

        // Ask if user wants to play again
        playAgainPrompt();
    }
};

int main() {
    SnakeGame game;
    game.Run();
    return 0;
}
