#include "map.h"
extern sf::String TileMap[HEIGHT_MAP]= {
"000000000000000000000",
"0                   0",
"0   s     h         0",
"0       0000        0",
"0              00 0 0",
"0         f         0",
"0     0             0",
"0     000000000     0",
"0                   0",
"0       f  000      0",
"0                 0 0",
"0   h          00 0 0",
"0                 0 0",
"000000000000000000000",

};
void randomMapGenerate(){//�������� ����������� ����������

int randomElementX = 0;//���������� ��� �������� ���������� �������� �� �����������

int randomElementY = 0;//���������� ��� �������� ���������� �������� �� ���������

srand(time(0));//������������� ���������� ��������� �����

int countStone = 1;//���������� ���������

while (countStone>0){

randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������������� �������� �� �x� �� 1 ��

//������ �����-1. ����������� ������� ����� �� �������� ����� ������� �����

randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� �y�

if (TileMap[randomElementY][randomElementX] == ' ') {//���� ��������� ������ ������,

TileMap[randomElementY][randomElementX] = 's'; //�� ������ ���� ������.

countStone--;

}

}

}
