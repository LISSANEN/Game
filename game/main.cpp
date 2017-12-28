#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //���������� ��� � ������
//#include "menu.h"
#include <list>

using namespace sf;
/////////////////////Menu/////////////////////////////////////////

/*void menu(RenderWindow & window) {

Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;

menuTexture1.loadFromFile("images/1111.png");

menuTexture2.loadFromFile("images/2222.png");

menuTexture3.loadFromFile("images/3333.png");

aboutTexture.loadFromFile("images/about1.png");

menuBackground.loadFromFile("images/123.jpg");

Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);

bool isMenu = 1;

int menuNum = 0;

menu1.setPosition(30, 30);

menu2.setPosition(30, 150);

menu3.setPosition(30, 270);

menuBg.setPosition(345, 0);

//////////////////////////////����///////////////////

while (isMenu)

{

menu1.setColor(Color::White);

menu2.setColor(Color::White);

menu3.setColor(Color::White);

menuNum = 0;

window.clear(Color(129, 181, 221));

if (IntRect(70, 60, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Green); menuNum = 1; }

if (IntRect(70, 170, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Green); menuNum = 2; }

if (IntRect(70, 280, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Green); menuNum = 3; }

if (Mouse::isButtonPressed(Mouse::Left))

{

	if (menuNum == 1) isMenu = true ;//���� ������ ������ ������, �� ������� �� ����

if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }

if (menuNum == 3) { window.close(); isMenu = false; }

}

window.draw(menuBg);

window.draw(menu1);

window.draw(menu2);

window.draw(menu3);

window.display();

}

////////////////////////////////////////////////////

}*/
	
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

////////////////////////////����� ������////////////////////////
class Player :public Entity {
public:
	int playerScore;//��� ���������� ����� ���� ������ � ������

	Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
		playerScore = 0; 
		state = stay;
		if (name == "Player1"){
			//������ ������� ���� ������������� ���
			//������ ������ ������. IntRect � ��� ���������� �����
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}

	void control(){
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

//����� �������� ������������ � ���������� �����
//������� �������� ������������ � ���������� �����
void checkCollisionWithMap(float Dx, float Dy)	{
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


void update(float time) //����� "���������/����������" ������� ������.
	{
	if (life) {//���������, ��� �� �����
		control();//������� ���������� ����������
		switch (state)//�������� ��������� �������� � ����������� �� ���������
		{
		case right:{//��������� ���� ������
			dx = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(75 * int(CurrentFrame), 75, 75, 75));
				break;
			}
		case left:{//��������� ���� �����
			dx = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(75 * int(CurrentFrame), 0, 75, 75));
			break;
			}
		case up:{//���� �����
			dy = -speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(0 * int(CurrentFrame), 75, 75, 75));
				break;
			}
		case down:{//���� ����
			dy = speed;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(0 * int(CurrentFrame), 0, 75, 75));
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
	}
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

////////////////////////////����� ����////////////////////////
class Bullet :public Entity{//����� ����
public:
	int direction;//����������� ����
	//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir) 
	//��� ������� ����������� ����� ����
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name){
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 15;
		life = true;
		//���� ������������� � ������������
	}


	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;// state = left
		case 1: dx = speed; dy = 0;   break;// state = right
		case 2: dx = 0; dy = -speed;   break;// state = up
		case 3: dx = 0; dy = speed;   break;// state = down
		}

		if (life){
			x += dx*time;//���� �������� ���� �� �
			y += dy*time;//�� �

		if (x <= 0) x = 50;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������ (������ ����� ���������!)
		if (y <= 0) y = 20;

		if (x >= 1050) x = 1050;// �������� ���� � ������ �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������ (������ ����� ���������!)
		if (y >= 700) y = 700;


			for (int i = y / 50; i < (y + h) / 50; i++)//���������� �� ��������� �����
				for (int j = x / 50; j < (x + w) / 50; j++)
				{
					if (TileMap[i][j] == '0')//���� ������� ��� ������ �����, ��
						life = false;// �� ���� �������
				}

			sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����
		}
	}
};



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
			randomMapGenerate();//���������  ������
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


