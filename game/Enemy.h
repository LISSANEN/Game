#ifndef Enemy
#define Enemy
#include "_CLASS_H_.h"
////////////////////////////КЛАСС ВРАГА////////////////////////
class Enemy :public Entity {
public:
	int direction;//направление движения врага
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);// :Entity(image, X, Y, W, H, Name);
	void checkCollisionWithMap(double Dx, double Dy);//ф-ция проверки столкновений с картой
	//void update(float time);
};//класс Enemy закрыт
#endif Enemy