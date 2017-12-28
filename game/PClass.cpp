#include "_CLASS_H_.h"
#include "map.h" 
#include "PClass.h"

Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
		playerScore = 0; 
		state = stay;
		if (name == "Player1"){
			//������ ������� ���� ������������� ���
			//������ ������ ������. IntRect � ��� ���������� �����
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}
void Player::checkCollisionWithMap(float Dx, float Dy)	{
for (int i = y / 50; i < (y + h) / 50; i++)//���������� �� ��������� �����
	for (int j = x / 50; j<(x + w) / 50; j++)
	{
		if (TileMap[i][j] == '0')//���� ������� ������ �����
		{
		if (Dy > 0) { y = i * 50 - h;  dy = 0; }//�� Y 
		if (Dy < 0) { y = i * 50 + 50; dy = 0; }//������������ � �������� ������ �����
		if (Dx > 0) { x = j * 50 - w; dx = 0; }//� ������ ����� �����
		if (Dx < 0) { x = j * 50 + 50; dx = 0; }// � ����� ����� �����
		}
		if (TileMap[i][j] == 's') {
			playerScore++; //���� ����� ������, ���������� playerScore=playerScore+1;
			TileMap[i][j] = ' ';
		}
		if (TileMap[i][j] == 'f') {
			health -= 40;//���� ����� �������� ������,�� ���������� health=health-40;
			TileMap[i][j] = ' ';//������ ������
		}

		if (TileMap[i][j] == 'h') {
			health += 20;//���� ����� ��������,�� ���������� health=health+20;
			TileMap[i][j] = ' ';//������ ��������
		}
	}
}


///////////////////////////////////////////////////////////////////////////

void Player::control(){
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			state = up;
			speed = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;
		}
	}

/////////////////////////////////////////////////////////////////////////////////

void Player::update(float time) //����� "���������/����������" ������� ������.
	{
	if (life) {//���������, ��� �� �����
		control();//������� ���������� ����������
		switch (state)//�������� ��������� �������� � ����������� �� ���������
		{
		case right:{//��������� ���� ������
			dx = speed;
			sprite.setTextureRect(IntRect(75 , 75, 75, 75));
				break;
			}
		case left:{//��������� ���� �����
			dx = -speed;
			sprite.setTextureRect(IntRect(75 , 0, 75, 75));
			break;
			}
		case up:{//���� �����
			dy = -speed;
			sprite.setTextureRect(IntRect(0 , 75, 75, 75));
				break;
			}
		case down:{//���� ����
			dy = speed;
			
			sprite.setTextureRect(IntRect(0 , 0, 75, 75));
			break;
			}
		case stay:{//�����
			dy = speed;
			dx = speed;
			break;
			}
			}

			x += dx*time; //�������� �� �X�
			checkCollisionWithMap(dx, 0);//������������ ������������ �� �
			y += dy*time; //�������� �� �Y�
			checkCollisionWithMap(0, dy);//������������ ������������ �� Y

			speed = 0;    //�������� ��������, ����� �������� �����������.
			//state = stay;

			sprite.setPosition(x, y); //������ � ������� (x, y).

		if (health <= 0){ life = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
		}
	};
