#include "_CLASS_H_.h"
#include "map.h" 

Entity::Entity (Image &image, float X, float Y, int W, int H, std::string Name)
{
	x = X; y = Y; //���������� ��������� �������
		w = W; h = H; 
		name = Name; 
		moveTimer = 0;
		dx = 0; dy = 0; 
		speed = 0;

		CurrentFrame = 0;
		health = 100;
		life = true; //���������������� ���������� ���������� �����, ����� ���
		texture.loadFromImage(image); //������� ���� ����������� � ��������
		sprite.setTexture(texture); //�������� ������ ���������
	}
FloatRect Entity::getRect(){//����� ��������� ��������������. ��� �����, ������� (���,�����).
	FloatRect FR(x, y, w, h); // ���������� FR ���� FloatRect
	return FR;
	//��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� ��������������
	//� ����� ���� ��� ���������� �������� ������������ ����� �� �����
	//����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� ����� 
	//��� �-��� ����� ��� �������� ����������� 
	};
/*
void Entity::checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
	{
	for (int i = y / 50; i < (y + h) / 50; i++)//���������� �� ��������� �����
		for (int j = x / 50; j<(x + w) / 50; j++)
		{
			if (TileMap[i][j] == '0')//���� ������� - ������ �����
			{
				if (Dy > 0) {
					y = i * 50 - h;  dy = -0.1; 
					direction = rand() % (3); //����������� �������� �����
						}//�� Y 
				if (Dy < 0) {
					y = i * 50 + 50; dy = 0.1; 
					direction = rand() % (3);//����������� �������� ����� 
						}//������������ � �������� ������ 
				if (Dx > 0) {
					x = j * 50 - w; dx = -0.1; 
						direction = rand() % (3);//����������� �������� ����� 
						}//� ������ ����� �����
				if (Dx < 0) {
					x = j * 50 + 50; dx = 0.1; 
						direction = rand() % (3); //����������� �������� �����
						}// � ����� ����� �����
				}
			}
	}
*/