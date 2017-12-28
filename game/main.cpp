#include <iostream>
#include <SFML/Graphics.hpp>


//////////////////////////// Ћј—— —”ўЌќ—“№////////////////////////
class Entity {
public:
	enum { left, right, up, down, stay} state;// тип перечислени€ - состо€ние объекта
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер дл€ будущих целей
	int w, h, health; //переменна€ УhealthФ, хран€ща€ жизни игрока
	bool life; //переменна€ УlifeФ жизнь, логическа€
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт 
	float CurrentFrame;//хранит текущий кадр
	std::string name;//враги могут быть разные, врагов можно различать по именам
	//каждому можно дать свое действие в update() в зависимости от имени



	Entity(Image &image, float X, float Y, int W, int H, std::string Name){
		x = X; y = Y; //координата по€влени€ спрайта
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

FloatRect getRect(){//метод получени€ пр€моугольника. его коорд, размеры (шир,высот).
	FloatRect FR(x, y, w, h); // переменна€ FR типа FloatRect
	return FR;
	//“ип данных (класс) "sf::FloatRect" позвол€ет хранить четыре координаты пр€моугольника
	//в нашей игре это координаты текущего расположени€ тайла на карте
	//далее это позволит спросить, есть ли ещЄ какой-либо тайл на этом месте 
	//эта ф-ци€ нужна дл€ проверки пересечений 
	}

	virtual void update(float time) = 0;

};


//////////////////////////// Ћј—— ѕ”Ћ»////////////////////////
class Bullet :public Entity{//класс пули
public:
	int direction;//направление пули
	//всЄ так же, только вз€ли в конце состо€ние игрока (int dir) 
	//дл€ задани€ направлени€ полЄта пули
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir) :Entity(image, X, Y, W, H, Name){
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 15;
		life = true;
		//выше инициализаци€ в конструкторе
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
			x += dx*time;//само движение пули по х
			y += dy*time;//по у

		if (x <= 0) x = 50;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
		if (y <= 0) y = 20;

		if (x >= 1050) x = 1050;// задержка пули в правой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
		if (y >= 700) y = 700;


			for (int i = y / 50; i < (y + h) / 50; i++)//проходимс€ по элементам карты
				for (int j = x / 50; j < (x + w) / 50; j++)
				{
					if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
						life = false;// то пул€ умирает
				}

			sprite.setPosition(x + w / 2, y + h / 2);//задаетс€ позицию пули
		}
	}
};
