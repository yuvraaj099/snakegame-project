#include <bits/stdc++.h>
#include <conio.h> // for kbhit and getch
#include <windows.h>

using namespace std;

#define MAX_LENGTH 200
#define BOARD_WIDTH 50
#define BOARD_HEIGHT 30

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
        length = 1;
        body[0] = Point(x, y);
        direction = DIR_RIGHT;
    }

    int getLength() { return length; }

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
    const char SNAKE_BODY = '+';
    const char FOOD = 'O';
public:
    Board() {
        spawnFood();
        snake = new Snake(BOARD_WIDTH / 2, BOARD_HEIGHT / 2);
        score = 0;
    }
    ~Board() { delete snake; }

    int getScore() { return score; }

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
        for (int i = 0; i <= BOARD_HEIGHT; i++) {
            gotoxy(0, i); cout << "I";
            gotoxy(BOARD_WIDTH, i); cout << "I";
        }

        // Draw snake
        for (int i = 0; i < snake->getLength(); i++) {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
        }

        // Draw food
        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD;

        // Display score
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
        }
    }
};

// Main function
int main() {
    
    srand(time(0));
    Board* board = new Board();
    while (board->update()) {
        board->getInput();
        board->draw();
        Sleep(100);
    }
    
    board->gotoxy(BOARD_WIDTH / 2, BOARD_HEIGHT / 2);
    cout << "Game Over!";
    board->gotoxy(BOARD_WIDTH / 2, BOARD_HEIGHT / 2 + 1);
    cout << "Final Score: " << board->getScore();
   
   
    delete board;
    return 0;
}
