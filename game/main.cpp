#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //подключили код с картой
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

//////////////////////////////МЕНЮ///////////////////

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

	if (menuNum == 1) isMenu = true ;//если нажали первую кнопку, то выходим из меню

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

////////////////////////////КЛАСС СУЩНОСТЬ////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay} state;// тип перечисления - состояние объекта
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер для будущих целей
	int w, h, health; //переменная “health”, хранящая жизни игрока
	bool life; //переменная “life” жизнь, логическая
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 
	float CurrentFrame;//хранит текущий кадр
	std::string name;//враги могут быть разные, врагов можно различать по именам
	//каждому можно дать свое действие в update() в зависимости от имени



	Entity(Image &image, float X, float Y, int W, int H, std::string Name){
		x = X; y = Y; //координата появления спрайта
		w = W; h = H; 
		name = Name; 
		moveTimer = 0;
		dx = 0; dy = 0; 
		speed = 0;

		CurrentFrame = 0;
		health = 100;
		life = true; //инициализировали логическую переменную жизни, герой жив
		texture.loadFromImage(image); //заносим наше изображение в текстуру
		sprite.setTexture(texture); //заливаем спрайт текстурой
	}

FloatRect getRect(){//метод получения прямоугольника. его коорд, размеры (шир,высот).
	FloatRect FR(x, y, w, h); // переменная FR типа FloatRect
	return FR;
	//Тип данных (класс) "sf::FloatRect" позволяет хранить четыре координаты прямоугольника
	//в нашей игре это координаты текущего расположения тайла на карте
	//далее это позволит спросить, есть ли ещё какой-либо тайл на этом месте 
	//эта ф-ция нужна для проверки пересечений 
	}

	virtual void update(float time) = 0;

};





////////////////////////////КЛАСС ВРАГА////////////////////////
class Enemy :public Entity{
public:
	int direction;//направление движения врага
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
	if (name == "EasyEnemy"){
		//Задаем спрайту один прямоугольник для
		//вывода одного игрока. IntRect – для приведения типов
		sprite.setTextureRect(IntRect(0, 0, w, h));
		direction = rand() % (5); //Направление движения врага задаём случайным образом
			//через генератор случайных чисел
			speed = 0.05;//даем скорость.этот объект всегда двигается
			dx = speed;
		}
	}

void checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
	{
	for (int i = y / 50; i < (y + h) / 50; i++)//проходимся по элементам карты
		for (int j = x / 50; j<(x + w) / 50; j++)
		{
			if (TileMap[i][j] == '0')//если элемент - тайлик земли
			{
				if (Dy > 0) {
					y = i * 50 - h;  dy = -0.1; 
					direction = rand() % (3); //Направление движения врага
						}//по Y 
				if (Dy < 0) {
					y = i * 50 + 50; dy = 0.1; 
					direction = rand() % (3);//Направление движения врага 
						}//столкновение с верхними краями 
				if (Dx > 0) {
					x = j * 50 - w; dx = -0.1; 
						direction = rand() % (3);//Направление движения врага 
						}//с правым краем карты
				if (Dx < 0) {
					x = j * 50 + 50; dx = 0.1; 
						direction = rand() % (3); //Направление движения врага
						}// с левым краем карты
				}
			}
	}

	void update(float time)
	{
		if (name == "EasyEnemy"){//для персонажа с таким именем логика будет такой

		if (life) {//проверяем, жив ли герой
		switch (direction)//делаются различные действия в зависимости от состояния
		{
		case 0:{//состояние идти вправо
		dx = speed;
		CurrentFrame += 0.000001*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(58 * int(CurrentFrame), 54, 58, 54));
		break;
		}
		case 1:{//состояние идти влево
		dx = -speed;
		CurrentFrame +=  0.000001*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(58 * int(CurrentFrame), 0, 58, 54));
		break;
		}
		case 2:{//идти вверх
		dy = -speed;
		CurrentFrame += 0.000001*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(0 * int(CurrentFrame), 0, 58, 54));
		break;
		}
		case 3:{//идти вниз
		dy = speed;
		CurrentFrame +=  0.000001*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(0 * int(CurrentFrame),54, 58, 54));
		break;
		}
		}

		x += dx*time; //движение по “X”
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х

		y += dy*time; //движение по “Y”
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

		sprite.setPosition(x, y); //спрайт в позиции (x, y).

		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем
		}
		//if (playerScoreSting = 50)
		}
	}
};//класс Enemy закрыт
int main()
{

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1050, 700, desktop.bitsPerPixel), "FroggyRun");

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст
	text.setColor(Color::Red);//покрасили текст в красный	text.setStyle(Text::Bold);//жирный текст.

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/mapp2.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
}

