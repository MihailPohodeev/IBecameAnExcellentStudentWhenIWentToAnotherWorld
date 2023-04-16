#include "prepearing.hpp"

int main()
{
//	RectangleShape logo;
//	RectangleShape background;
//	logo.setSize(Vector2f(WIDTH / 3, HEIGHT / 2));
//	logo.setOrigin(Vector2f(logo.getSize().x / 2, logo.getSize().y / 2));
//	logo.setPosition(WIDTH / 2, HEIGHT / 2);
//	background.setSize(Vector2f(WIDTH, HEIGHT));
//	background.setFillColor(Color(128, 128, 128, 255));
//	
//	Texture mehmat;
//	Texture sfedu;
//	
//	mehmat.loadFromFile("Sprites/mehmat_logo.png");
//	sfedu.loadFromFile("Sprites/sfedu_logo.png");
//	
//	logo.setTexture(&sfedu);
//	
//	window.clear();
//	window.draw(logo);
//	window.display();
////	window.draw()
//	
	setlocale(LC_ALL, "Russian");    
    main_font.loadFromFile("Fonts/Chava-Regular.ttf");
//    // текстура заднего фона
//
//
//	Sleep(2000);
//	
//	logo.setTexture(&mehmat);
//	logo.setSize(Vector2f(WIDTH / 3, WIDTH / 5));
//	logo.setOrigin(Vector2f(logo.getSize().x / 2, logo.getSize().y / 2));
//	logo.setTextureRect(IntRect(0, 0, mehmat.getSize().x, mehmat.getSize().y));
//	window.clear();
//	window.draw(background);
//	window.draw(logo);
//	window.display();
//	Sleep(2000);
	
	while(window.isOpen()){
		view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2));
//	    constructor::menu();
//	    if (to_settings) constructor::settings();
//	  	if (level1_start) constructor::game();
		if (level1_start) constructor::level2();
//		constructor::level2();
	}
	
    return 0;
}
