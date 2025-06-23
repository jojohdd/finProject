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
