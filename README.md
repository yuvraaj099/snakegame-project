A#include <bits/stdc++.h>
#include <conio.h> // for kbhit and getch
#include <windows.h>

using namespace std;

#define MAX_LENGTH 200
#define BOARD_WIDTH 50
#define BOARD_HEIGHT 20

// Directions
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

// Point structure to represent coordinates
struct Point {
    int xCoord, yCoord;
    Point() {}
    Point(int x, int y) : xCoord(x), yCoord(y) {}
};

// Snake class
class Snake {
    int length;
    char direction;
public:
    Point body[MAX_LENGTH];
    Snake(int x, int y) {
        length = 3;  // Start with 3 body parts
        body[0] = Point(x, y);  // Snake head
        body[1] = Point(x - 1, y);  // First body part
        body[2] = Point(x - 2, y);  // Second body part
        direction = DIR_RIGHT;
    }

    int getLength() { 
        return length; 
    }

    void changeDirection(char newDirection) {
        if ((newDirection == DIR_UP && direction != DIR_DOWN) ||
            (newDirection == DIR_DOWN && direction != DIR_UP) ||
            (newDirection == DIR_LEFT && direction != DIR_RIGHT) ||
            (newDirection == DIR_RIGHT && direction != DIR_LEFT)) {
            direction = newDirection;
        }
    }

    bool move(Point food) {
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

        switch (direction) {
            case DIR_UP: body[0].yCoord--; break;
            case DIR_DOWN: body[0].yCoord++; break;
            case DIR_LEFT: body[0].xCoord--; break;
            case DIR_RIGHT: body[0].xCoord++; break;
        }

        // Check if the snake hits the border
        if (body[0].xCoord < 1 || body[0].xCoord >= BOARD_WIDTH ||
            body[0].yCoord < 1 || body[0].yCoord >= BOARD_HEIGHT) {
            return false;
        }

        // Check if the snake bites itself
        for (int i = 1; i < length; i++) {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord) {
                return false;
            }
        }

        // Check if the snake eats food
        if (body[0].xCoord == food.xCoord && body[0].yCoord == food.yCoord) {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
            length++;
        }

        return true;
    }
};

// Board class
class Board {
    Snake* snake;
    Point food;
    int score;
    const char SNAKE_BODY = '+';  // Snake body
    const char SNAKE_HEAD = '@';  // Snake head
    const char FOOD = 'O';        // Food
    int speed;  // Speed control variable
public:
    Board() {
        spawnFood();
        snake = new Snake(BOARD_WIDTH / 2, BOARD_HEIGHT / 2);
        score = 0;
        speed = 100;  // Default speed (medium speed)
    }
    ~Board() { delete snake; }

    int getScore() { 
        return score; 
    }

    void spawnFood() {
        int x = 1 + rand() % (BOARD_WIDTH - 2);
        int y = 1 + rand() % (BOARD_HEIGHT - 2);
        food = Point(x, y);
    }

    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void displayCurrentScore() {
        gotoxy(BOARD_WIDTH + 2, 0);
        cout << "Score: " << score;
    }

    void draw() {
        system("cls");

        // Draw borders
        for (int i = 0; i <= BOARD_WIDTH; i++) {
            gotoxy(i, 0); cout << "_";
            gotoxy(i, BOARD_HEIGHT); cout << "_";
        }
        for (int i = 1; i <= BOARD_HEIGHT; i++) {
            gotoxy(0, i); cout << "|";
            gotoxy(BOARD_WIDTH, i); cout << "|";
        }

        // Draw snake head
        gotoxy(snake->body[0].xCoord, snake->body[0].yCoord);
        cout << SNAKE_HEAD;

        // Draw snake body
        for (int i = 1; i < snake->getLength(); i++) {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
        }

        // Draw food
        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD;

        // Display scores
        displayCurrentScore();
    }

    bool update() {
        bool isAlive = snake->move(food);
        if (!isAlive) return false;

        if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord) {
            score++;
            spawnFood();
        }
        return true;
    }

    void getInput() {
        if (_kbhit()) {
            int key = _getch();
            if (key == 'w' || key == 'W') snake->changeDirection(DIR_UP);
            else if (key == 'a' || key == 'A') snake->changeDirection(DIR_LEFT);
            else if (key == 's' || key == 'S') snake->changeDirection(DIR_DOWN);
            else if (key == 'd' || key == 'D') snake->changeDirection(DIR_RIGHT);
            else if (key == '1') {  // Slow speed
                speed = 200;  // Slow speed
            }
            else if (key == '2') {  // Medium speed
                speed = 100;  // Medium speed (default)
            }
            else if (key == '3') {  // Fast speed
                speed = 50;  // Fast speed
            }
        }
    }

    int getSpeed() {
        return speed;
    }

    void setSpeed(int newSpeed) {
        speed = newSpeed;
    }

    void displayGameOver() {
        // Clearing the screen and setting the position for game over message
        system("cls");

        int centerX = BOARD_WIDTH / 2 - 5;
        int centerY = BOARD_HEIGHT / 2;

        // Decorative box
        gotoxy(centerX - 1, centerY - 1);
        cout << "***********************";
        gotoxy(centerX - 1, centerY);
        cout << "                       ";
        gotoxy(centerX - 1, centerY + 1);
        cout << "***********************";

        // "Game Over" message
        gotoxy(centerX, centerY);
        cout << "    GAME OVER  ";

        // Final score message
        gotoxy(centerX, centerY + 2);
        cout << "    Final Score: " << getScore();

        // Adding some extra decoration
        gotoxy(centerX - 1, centerY + 3);
        cout << "***********************";
    }
};

// Main function
int main() {
    srand(time(0));

    // Ask for speed level
    int speedLevel;
    cout << "Select speed level (1 - Slow, 2 - Medium, 3 - Fast):\n";
    
    // Getting the speed level input from the user
    while (true) {
        cin >> speedLevel;
        if (speedLevel == 1 || speedLevel == 2 || speedLevel == 3) {
            break;  // If valid input, break the loop
        }
        else {
            cout << "Invalid input. Please choose 1 (Slow), 2 (Medium), or 3 (Fast):\n";
        }
    }

    // Create the board and set speed based on the user's input
    Board* board = new Board();
    if (speedLevel == 1) {
        board->setSpeed(200);  // Slow speed
    } else if (speedLevel == 2) {
        board->setSpeed(100);  // Medium speed
    } else if (speedLevel == 3) {
        board->setSpeed(50);   // Fast speed
    }

    // Game loop
    while (board->update()) {
        board->getInput();
        board->draw();
        Sleep(board->getSpeed());  // Control speed using Sleep based on user input
    }

    // Display the Game Over screen
    board->displayGameOver();

    // Clean up memory
    delete board;
    return 0;
}
