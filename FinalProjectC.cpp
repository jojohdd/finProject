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
