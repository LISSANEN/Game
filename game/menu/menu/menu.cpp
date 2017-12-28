// menu.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

using namespace sf;
void menu(RenderWindow & window) {
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
			if (menuNum == 1) isMenu = false;//���� ������ ������ ������, �� ������� �� ���� 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3)  { window.close(); isMenu = false; }
 
		}
 
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		
		window.display();
	}
	////////////////////////////////////////////////////
	
}
int main()
{
RenderWindow window(sf::VideoMode(600, 533), "FroggyRun");
	menu(window);//����� ����
return 0;
}

