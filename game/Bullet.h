#include "_CLASS_H_.h"
////////////////////////////КЛАСС ПУЛИ////////////////////////
class Bullet :public Entity {//класс пули
public:
	int direction; //направление пули
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir);//:Entity(image, X, Y, W, H, Name);
void update(float time);
};