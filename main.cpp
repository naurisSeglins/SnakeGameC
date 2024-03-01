#include <iostream>
// for _getch() function
#include <conio.h> 
// for sleep
#include <chrono>
#include <thread>

using namespace std;

bool gameOver = false;

//screen size
const int width = 20;
const int height = 20;

// start position
int x = width / 2;
int y = height / 2;
int foodX = rand() % width;
int foodY = rand() % height;

// snake direction
char dir;

//score
int score = 0;

//tail with limit 100
int tailX[100], tailY[100];
int nTail = 0;

void drawScreen() {
    //clear screen
    system("cls");

    // draw top line
    // add + 2 because there are 2 lines on sides
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            //draw left side
            if (j == 0)
                cout << "#";
            //draw snakes head
            if (i == y && j == x)
                cout << "O";
            //draw food
            else if (i == foodY && j == foodX)
                cout << "F";
            // draw empty space and tail
            else {
                bool print = false;
                //add tail
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                // if not tail then empty space
                if (!print)
                    cout << " ";
            }
            //draw right side on the last column
            if (j == width -1)
                cout << "#";
        }
        cout << endl;
    }
    // draw bottom line
    for (int i = 0; i < width +2; i++)
        cout << "#";
    // show score
    cout << endl;
    cout << "Score:" << score << endl;
}

void moveControl() {
    // is keyboard pressed
    if (_kbhit()) {
        // what is pressed
        switch (_getch()){
        case 'a':
            dir = 'a';
            break;
        case 'd':
            dir = 'd';
            break;
        case 's':
            dir = 's';
            break;
        case 'w':
            dir = 'w';
            break;
        }
    }
}

void gameLogic() {
    
    //save previous position of the first tail segment before any update
    int prevX = tailX[0];
    int prevY = tailY[0];
    //update the position of the first tail segment 
    tailX[0] = x;
    tailY[0] = y;

    int prev2X, prev2Y;
    //starting from the second segment update their positions
    for (int i = 1; i < nTail; i++) {
        //save existing posistion
        prev2X = tailX[i];
        prev2Y = tailY[i];
        //give the new position
        tailX[i] = prevX;
        tailY[i] = prevY;
        //update the new position with existing
        prevX = prev2X;
        prevY = prev2Y;
    }

    //set direction for the snake
    switch (dir) {
    case 'a':
        x--;
        break;
    case 'd':
        x++;
        break;
    case 'w':
        y--;
        break;
    case 's':
        y++;
        break;
    default:
        break;
    }

    //if hit the wall then game over
    if (x >= width || x < 0)
        gameOver = true;
    if (y >= height || y < 0)
        gameOver = true;

    //if tails coordinates are equal to snakes heads coordinates game over
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    //if ate the food then add score and spawn new food
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        nTail++;
    }
}

int main() {
    while (!gameOver) {
        drawScreen();
        moveControl();
        gameLogic();
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
    return 0;
}