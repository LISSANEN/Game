#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //���������� ��� � ������
//#include "menu.h"
#include <list>
#include "_CLASS_H_.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PClass.h"



using namespace sf;

int main()
{

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1050, 700, desktop.bitsPerPixel), "FroggyRun");

	Font font;//����� 
	font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����
	text.setColor(Color::Red);//��������� ����� � �������	text.setStyle(Text::Bold);//������ �����.

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/mapp2.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//�������� ������� �����, ����������������.


	Image heroImage;
	heroImage.loadFromFile("images/frog150.png"); // ��������� ����������� ������

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/enemy2.png"); // ��������� ����������� �����

	Image BulletImage;//����������� ��� ����
	BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ �����������


	Player p(heroImage, 150, 150,75, 75, "Player1");//������ ������ ������

	std::list<Entity*>  enemies; //������ ������
	std::list<Entity*>  Bullets; //������ ����
	std::list<Entity*>::iterator it; //�������� ����� ��������� �� ��������� ������
	std::list<Entity*>::iterator bul;
	const int ENEMY_COUNT = 5;	//������������ ���������� ������ � ����
	int enemiesCount =0;	//������� ���������� ������ � ����

	//��������� ������ ��������� �������
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
	float xr = 150 + rand() % 350; // ��������� ���������� ����� �� ���� ���� �� ��� �x�
	float yr = 150 + rand() %250; // ��������� ���������� ����� �� ���� ���� �� ��� �y�

		//������� ������ � �������� � ������
		enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 100, 60, "EasyEnemy"));
		enemiesCount += 1; //��������� ������� ������
		
	}

	int createObjectForMapTimer = 0;//���������� ��� ����� ��� ������������� ������

while (window.isOpen())
{
	float time = clock.getElapsedTime().asMicroseconds();

	if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//������� ����� � 
		//�������� ��� ������, ���� ��� �����. ������������� ��� time ��� �� ����. 
		//��� �� ��������� ������ ����

		clock.restart();
		time = time / 800;

		createObjectForMapTimer += time;//���������� ������
		if (createObjectForMapTimer>1000){
			randomMapGenerate();//���������  ���������

			createObjectForMapTimer = 0;//�������� ������
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//�������� �� ������� ������� "P"
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P)
				{
		Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 15, 15, "Bullet", p.state));
				}
			}
		}


		p.update(time); //�������� ������ �p� ������ �Player� 

		//�������� ������
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //��������� ����� update()
		}

		//�������� ����
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			(*it)->update(time); //��������� ����� update()
		}





		///////////////////////////////////////////////////////////////////////////////

		for (bul = Bullets.begin(); bul != Bullets.end(); bul++ )//������� ��� ���������� �� ������ �� �����
	{// ���� ���� ������ �����, �� ������� ���
	            for (it = enemies.begin(); it != enemies.end(); it++)
				{ 
				if ((*it)->getRect().intersects((*bul)->getRect())){
				    (*it)-> life = false;
					it =enemies.erase(it);
					//p.score += 5;
					}
					}
					}

			

			/////////////////////////////////////////////////////////////////////////

		//��������� ������ �� ������� "�������" ���� � ������� ��
for (it = Bullets.begin(); it != Bullets.end(); )//������� ��� ���������� �� ������ �� �����
	{// ���� ���� ������ �����, �� ������� ���
		if ((*it)-> life == false)	{ it = Bullets.erase(it); } 
			else  it++;//� ���� �������� (����������) � ���� �������.		
	}


	//�������� ����������� ������ � �������
	//���� ����������� ���������, �� "health = 0", ����� ��������������� � 
	//��������� ��������� "you are lose"
	if (p.life == true){//���� ����� ���
		for (it = enemies.begin(); it != enemies.end(); it++){//����� �� ������ ������
		if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
				{
					p.health = 0;
					std::cout << "you are lose";
				}
			}
		}

		window.clear();

/////////////////////////////������ �����/////////////////////
for (int i = 0; i < HEIGHT_MAP; i++)
	for (int j = 0; j < WIDTH_MAP; j++)
	{
	if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(200, 0, 50,50));//������� 200
	if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(0, 0, 50,50));//���������� 0
	if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(50, 0, 50,50));//������� 50
	if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(100, 0, 50,50));//������ 100
	if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(150, 0, 50,50));//������ 150
				

	s_map.setPosition(j * 50, i * 50);
		window.draw(s_map);
			}

		//�������� ���������� �������� � �������
		std::ostringstream playerHealthString, gameTimeString,playerScoreSting;

		playerHealthString << p.health; gameTimeString << gameTime; playerScoreSting<<p.playerScore;//��������� ������
		text.setString("��������: " + playerHealthString.str() + "\n����� ����: " + gameTimeString.str() +"\n����������: " + playerScoreSting.str());//������ ������ ������
		text.setPosition(50, 50);//������ ������� ������
		window.draw(text);//������ ���� �����

		window.draw(p.sprite);//������ ������ ������� �p� ������ �Player�

		//������ ������
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			if ((*it)->life) //���� ����� ����
			window.draw((*it)->sprite); //������ 
		}

		//������ ����
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			if ((*it)->life) //���� ���� ����
				window.draw((*it)->sprite); //������ �������
		}
	//	RenderWindow window(sf::VideoMode(1050, 700), "FroggyRun");

//menu(window);//����� ����
		window.display();
	}
	
	return 0;
}
Clock clock;
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//�������� ������� �����, ����������������.




