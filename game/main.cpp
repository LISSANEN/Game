#include <iostream> 
#include <sstream>
#include <SFML/Graphics.hpp>
#include "map.h" //подключили код с картой
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

	Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.


	Image heroImage;
	heroImage.loadFromFile("images/frog150.png"); // загружаем изображение игрока

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/enemy2.png"); // загружаем изображение врага

	Image BulletImage;//изображение для пули
	BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображения


	Player p(heroImage, 150, 150,75, 75, "Player1");//объект класса игрока

	std::list<Entity*>  enemies; //список врагов
	std::list<Entity*>  Bullets; //список пуль
	std::list<Entity*>::iterator it; //итератор чтобы проходить по элементам списка
	std::list<Entity*>::iterator bul;
	const int ENEMY_COUNT = 5;	//максимальное количество врагов в игре
	int enemiesCount =0;	//текущее количество врагов в игре

	//Заполняем список объектами врагами
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
	float xr = 150 + rand() % 350; // случайная координата врага на поле игры по оси “x”
	float yr = 150 + rand() %250; // случайная координата врага на поле игры по оси “y”

		//создаем врагов и помещаем в список
		enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 100, 60, "EasyEnemy"));
		enemiesCount += 1; //увеличили счётчик врагов
		
	}

	int createObjectForMapTimer = 0;//Переменная под время для генерирования камней

while (window.isOpen())
{
	float time = clock.getElapsedTime().asMicroseconds();

	if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();//игровое время в 
		//секундах идёт вперед, пока жив игрок. Перезагружать как time его не надо. 
		//оно не обновляет логику игры

		clock.restart();
		time = time / 800;

		createObjectForMapTimer += time;//наращиваем таймер
		if (createObjectForMapTimer>1000){
			randomMapGenerate();//генерация  карамелек

			createObjectForMapTimer = 0;//обнуляем таймер
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//стреляем по нажатию клавиши "P"
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P)
				{
		Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 15, 15, "Bullet", p.state));
				}
			}
		}


		p.update(time); //оживляем объект “p” класса “Player” 

		//оживляем врагов
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->update(time); //запускаем метод update()
		}

		//оживляем пули
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			(*it)->update(time); //запускаем метод update()
		}





		///////////////////////////////////////////////////////////////////////////////

		for (bul = Bullets.begin(); bul != Bullets.end(); bul++ )//говорим что проходимся от начала до конца
	{// если этот объект мертв, то удаляем его
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

		//Проверяем список на наличие "мертвых" пуль и удаляем их
for (it = Bullets.begin(); it != Bullets.end(); )//говорим что проходимся от начала до конца
	{// если этот объект мертв, то удаляем его
		if ((*it)-> life == false)	{ it = Bullets.erase(it); } 
			else  it++;//и идем курсором (итератором) к след объекту.		
	}


	//Проверка пересечения игрока с врагами
	//Если пересечение произошло, то "health = 0", игрок обездвижевается и 
	//выводится сообщение "you are lose"
	if (p.life == true){//если игрок жив
		for (it = enemies.begin(); it != enemies.end(); it++){//бежим по списку врагов
		if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy"))
				{
					p.health = 0;
					std::cout << "you are lose";
				}
			}
		}

		window.clear();

/////////////////////////////Рисуем карту/////////////////////
for (int i = 0; i < HEIGHT_MAP; i++)
	for (int j = 0; j < WIDTH_MAP; j++)
	{
	if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(200, 0, 50,50));//камушки 200
	if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(0, 0, 50,50));//карамелька 0
	if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(50, 0, 50,50));//бассейн 50
	if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(100, 0, 50,50));//сердце 100
	if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(150, 0, 50,50));//цветок 150
				

	s_map.setPosition(j * 50, i * 50);
		window.draw(s_map);
			}

		//объявили переменную здоровья и времени
		std::ostringstream playerHealthString, gameTimeString,playerScoreSting;

		playerHealthString << p.health; gameTimeString << gameTime; playerScoreSting<<p.playerScore;//формируем строку
		text.setString("Здоровье: " + playerHealthString.str() + "\nВремя игры: " + gameTimeString.str() +"\nКарамельки: " + playerScoreSting.str());//задаем строку тексту
		text.setPosition(50, 50);//задаем позицию текста
		window.draw(text);//рисуем этот текст

		window.draw(p.sprite);//рисуем спрайт объекта “p” класса “Player”

		//рисуем врагов
		for (it = enemies.begin(); it != enemies.end(); it++)
		{
			if ((*it)->life) //если враги живы
			window.draw((*it)->sprite); //рисуем 
		}

		//рисуем пули
		for (it = Bullets.begin(); it != Bullets.end(); it++)
		{
			if ((*it)->life) //если пули живы
				window.draw((*it)->sprite); //рисуем объекты
		}
	//	RenderWindow window(sf::VideoMode(1050, 700), "FroggyRun");

//menu(window);//вызов меню
		window.display();
	}
	
	return 0;
}
Clock clock;
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.




