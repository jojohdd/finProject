#include <iostream>
#include <conio.h>     //зчитування клавіш
#include <windows.h>   //затримка
#include <vector>

using namespace std;


bool gameOver;
const int width = 20; //розмір поля
const int height = 20;
int x, y, fruitX, fruitY, score; //корди голови змійти та фкута
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //напрямок руху
eDirection dir; //поточний нарямок
vector<pair<int, int>> hvost; //корди всіх сегментів тіла
int nhvost; //кілткість сегментів

void st() {
    gameOver = false;
    dir = STOP; //змійка не рухається поки не нажмуть кнопку
    x = width / 2; //позиція голови
    y = height / 2;
    fruitX = rand() % width; //місце фрукта
    fruitY = rand() % height;
    score = 0; //очки
    hvost.clear(); //очищення
    nhvost = 0;
}

void Draw() {
    system("cls"); //Очищення екрану 
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; //бортик
            if (i == y && j == x)
                cout << "O"; //голова змійки
            else if (i == fruitY && j == fruitX)
                cout << "F"; //фрукт
            else {
                bool printHv = false;
                for (auto segment : hvost) {
                    if (segment.first == j && segment.second == i) {
                        cout << "o";
                        printHv = true;
                        break;
                    }
                }
                if (!printHv)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input() { // W A S D X
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x': //Закінчення гри 
            gameOver = true;
            break;
        }
    }
}


void Logic() { //Тіло за головою
    int prevX = x;
    int prevY = y;
    int prev2X, prev2Y;
    if (nhvost > 0) {
        hvost.insert(hvost.begin(), { x, y });
        if (hvost.size() > nhvost)
            hvost.pop_back();
    }

    switch (dir) { //Переміщення змійки
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //Вихід за межі поля
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    //Зіткнення з хвостом
    for (auto segment : hvost) {
        if (segment.first == x && segment.second == y)
            gameOver = true;
    }

    //Фрукт з'їли
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nhvost++;
    }
}

int main() {
    st();
    int speed = 300;
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(speed); // затримка
    }
    cout << "Game Over!" << endl;
    return 0;
}
