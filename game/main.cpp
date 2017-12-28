#include <iostream>
#include <SFML/Graphics.hpp>

////////////////////////////����� ��������////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay} state;// ��� ������������ - ��������� �������
	float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����
	int w, h, health; //���������� �health�, �������� ����� ������
	bool life; //���������� �life� �����, ����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������ 
	float CurrentFrame;//������ ������� ����
	std::string name;//����� ����� ���� ������, ������ ����� ��������� �� ������
	//������� ����� ���� ���� �������� � update() � ����������� �� �����



	Entity(Image &image, float X, float Y, int W, int H, std::string Name){
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

FloatRect getRect(){//����� ��������� ��������������. ��� �����, ������� (���,�����).
	FloatRect FR(x, y, w, h); // ���������� FR ���� FloatRect
	return FR;
	//��� ������ (�����) "sf::FloatRect" ��������� ������� ������ ���������� ��������������
	//� ����� ���� ��� ���������� �������� ������������ ����� �� �����
	//����� ��� �������� ��������, ���� �� ��� �����-���� ���� �� ���� ����� 
	//��� �-��� ����� ��� �������� ����������� 
	}

	virtual void update(float time) = 0;

};





////////////////////////////����� �����////////////////////////
class Enemy :public Entity{
public:
	int direction;//����������� �������� �����
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
	if (name == "EasyEnemy"){
		//������ ������� ���� ������������� ���
		//������ ������ ������. IntRect � ��� ���������� �����
		sprite.setTextureRect(IntRect(0, 0, w, h));
		direction = rand() % (5); //����������� �������� ����� ����� ��������� �������
			//����� ��������� ��������� �����
			speed = 0.05;//���� ��������.���� ������ ������ ���������
			dx = speed;
		}
	}

void checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
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

	void update(float time)
	{
		if (name == "EasyEnemy"){//��� ��������� � ����� ������ ������ ����� �����

		if (life) {//���������, ��� �� �����
		switch (direction)//�������� ��������� �������� � ����������� �� ���������
		{
		case 0:{//��������� ���� ������
		dx = speed;
		CurrentFrame += 0.000001*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(58 * int(CurrentFrame), 54, 58, 54));
		break;
		}
		case 1:{//��������� ���� �����
		dx = -speed;
		CurrentFrame +=  0.000001*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(58 * int(CurrentFrame), 0, 58, 54));
		break;
		}
		case 2:{//���� �����
		dy = -speed;
		CurrentFrame += 0.000001*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(0 * int(CurrentFrame), 0, 58, 54));
		break;
		}
		case 3:{//���� ����
		dy = speed;
		CurrentFrame +=  0.000001*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(0 * int(CurrentFrame),54, 58, 54));
		break;
		}
		}

		x += dx*time; //�������� �� �X�
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �

		y += dy*time; //�������� �� �Y�
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y

		sprite.setPosition(x, y); //������ � ������� (x, y).

		if (health <= 0){ life = false; }//���� ������ ������ 0, ���� ����� 0, �� �������
		}
		//if (playerScoreSting = 50)
		}
	}
};//����� Enemy ������

