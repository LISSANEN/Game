#include "_CLASS_H_.h"
////////////////////////////����� ����////////////////////////
class Bullet :public Entity {//����� ����
public:
	int direction; //����������� ����
	Bullet(Image &image, float X, float Y, int W, int H, std::string  Name, int dir);//:Entity(image, X, Y, W, H, Name);
void update(float time);
};