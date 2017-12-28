#include "_CLASS_H_.h"
#include "map.h" 

Entity::Entity (Image &image, float X, float Y, int W, int H, std::string Name)
{
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
FloatRect Entity::getRect(){//метод получения прямоугольника. его коорд, размеры (шир,высот).
	FloatRect FR(x, y, w, h); // переменная FR типа FloatRect
	return FR;
	//Тип данных (класс) "sf::FloatRect" позволяет хранить четыре координаты прямоугольника
	//в нашей игре это координаты текущего расположения тайла на карте
	//далее это позволит спросить, есть ли ещё какой-либо тайл на этом месте 
	//эта ф-ция нужна для проверки пересечений 
	};
/*
void Entity::checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
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
*/