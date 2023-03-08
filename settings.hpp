#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;
using namespace sf;

// глобальные переменные размера экрана.
//int WIDTH = VideoMode::getDesktopMode().width;
//int HEIGHT = VideoMode::getDesktopMode().height;
int WIDTH = 683;
int HEIGHT = 384;

double deltaTime = 0; // глобальная переменная времени.
double anim_speed = 15.f; // скорость проигрывания анимаций

bool start_game = false; // начата ли игра

Vector2i mouse_position; // позиция мыши
Font main_font; // основной шрифт игры
Color main_color = Color(255, 255, 255, 255); // главный цвет игры.

// создание окна
RenderWindow window(VideoMode(WIDTH, HEIGHT), "I became an excelent student when I visited another world");




// ~~~~~~~~~~~~~~СТАНДАРТНЫЕ_ФУНКЦИИ~~~~~~~~~~~~~~~



// масштабирование и применение текстур к заднему фону
void background_init(Texture &txt, RectangleShape &background){
	background.setSize(Vector2f(WIDTH, HEIGHT));
    background.setTexture(&txt);
    background.setOrigin(Vector2f(background.getSize().x / 2, background.getSize().y / 2));
    background.setPosition(WIDTH / 2, HEIGHT / 2);
}

// функция перевода дробного числа в строку
string to_string(double num){
	ostringstream result;
	result << num;
	return result.str();
}

