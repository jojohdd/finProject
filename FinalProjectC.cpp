#include <iostream>
#include <conio.h>     //���������� �����
#include <windows.h>   //��������
#include <vector>

using namespace std;


bool gameOver;
const int width = 20; //����� ����
const int height = 20;
int x, y, fruitX, fruitY, score; //����� ������ ����� �� �����
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //�������� ����
eDirection dir; //�������� �������
vector<pair<int, int>> hvost; //����� ��� �������� ���
int nhvost; //������� ��������

void st() {
    gameOver = false;
    dir = STOP; //����� �� �������� ���� �� ������� ������
    x = width / 2; //������� ������
    y = height / 2;
    fruitX = rand() % width; //���� ������
    fruitY = rand() % height;
    score = 0; //����
    hvost.clear(); //��������
    nhvost = 0;
}

void Draw() {
    system("cls"); //�������� ������ 
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; //������
            if (i == y && j == x)
                cout << "O"; //������ �����
            else if (i == fruitY && j == fruitX)
                cout << "F"; //�����
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
        case 'x': //��������� ��� 
            gameOver = true;
            break;
        }
    }
}


void Logic() { //ҳ�� �� �������
    int prevX = x;
    int prevY = y;
    int prev2X, prev2Y;
    if (nhvost > 0) {
        hvost.insert(hvost.begin(), { x, y });
        if (hvost.size() > nhvost)
            hvost.pop_back();
    }

    switch (dir) { //���������� �����
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

    //����� �� ��� ����
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    //ǳ������� � �������
    for (auto segment : hvost) {
        if (segment.first == x && segment.second == y)
            gameOver = true;
    }

    //����� �'���
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
        Sleep(speed); // ��������
    }
    cout << "Game Over!" << endl;
    return 0;
}
