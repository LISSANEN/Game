//#include "_CLASS_H_.h"
////////////////////////////����� ������////////////////////////
class Player :public Entity {
public:
	int playerScore;//��� ���������� ����� ���� ������ � ������
	Player(Image &image, float X, float Y, int W, int H, std::string Name); //:Entity(image, X, Y, W, H, Name);
	void control();
		
void checkCollisionWithMap(float Dx, float Dy);
void update(float time); //����� "���������/����������" ������� ������.
};