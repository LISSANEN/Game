#include "_CLASS_H_.h"
#include "map.h" 
#include "PClass.h"

Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
		playerScore = 0; 
		state = stay;
		if (name == "Player1"){
			//Задаем спрайту один прямоугольник для
			//вывода одного игрока. IntRect – для приведения типов
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}
void Player::checkCollisionWithMap(float Dx, float Dy)	{
for (int i = y / 50; i < (y + h) / 50; i++)//проходимся по элементам карты
	for (int j = x / 50; j<(x + w) / 50; j++)
	{
		if (TileMap[i][j] == '0')//если элемент тайлик земли
		{
		if (Dy > 0) { y = i * 50 - h;  dy = 0; }//по Y 
		if (Dy < 0) { y = i * 50 + 50; dy = 0; }//столкновение с верхними краями карты
		if (Dx > 0) { x = j * 50 - w; dx = 0; }//с правым краем карты
		if (Dx < 0) { x = j * 50 + 50; dx = 0; }// с левым краем карты
		}
		if (TileMap[i][j] == 's') {
			playerScore++; //если взяли камень, переменная playerScore=playerScore+1;
			TileMap[i][j] = ' ';
		}
		if (TileMap[i][j] == 'f') {
			health -= 40;//если взяли ядовитый цветок,то переменная health=health-40;
			TileMap[i][j] = ' ';//убрали цветок
		}

		if (TileMap[i][j] == 'h') {
			health += 20;//если взяли сердечко,то переменная health=health+20;
			TileMap[i][j] = ' ';//убрали сердечко
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

void Player::update(float time) //метод "оживления/обновления" объекта класса.
	{
	if (life) {//проверяем, жив ли герой
		control();//функция управления персонажем
		switch (state)//делаются различные действия в зависимости от состояния
		{
		case right:{//состояние идти вправо
			dx = speed;
			sprite.setTextureRect(IntRect(75 , 75, 75, 75));
				break;
			}
		case left:{//состояние идти влево
			dx = -speed;
			sprite.setTextureRect(IntRect(75 , 0, 75, 75));
			break;
			}
		case up:{//идти вверх
			dy = -speed;
			sprite.setTextureRect(IntRect(0 , 75, 75, 75));
				break;
			}
		case down:{//идти вниз
			dy = speed;
			
			sprite.setTextureRect(IntRect(0 , 0, 75, 75));
			break;
			}
		case stay:{//стоим
			dy = speed;
			dx = speed;
			break;
			}
			}

			x += dx*time; //движение по “X”
			checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
			y += dy*time; //движение по “Y”
			checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y

			speed = 0;    //обнуляем скорость, чтобы персонаж остановился.
			//state = stay;

			sprite.setPosition(x, y); //спрайт в позиции (x, y).

		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем 
		}
	};
