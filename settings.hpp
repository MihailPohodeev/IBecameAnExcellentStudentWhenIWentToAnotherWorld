#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <cassert>
#include <cmath>
#include <windows.h>

using namespace std;
using namespace sf;

// глобальные переменные размера экрана.
//int WIDTH = VideoMode::getDesktopMode().width;
//int HEIGHT = VideoMode::getDesktopMode().height;
int WIDTH = 683;
int HEIGHT = 384;

double deltaTime = 0; // глобальна€ переменна€ времени.
double anim_speed = 15.f; // скорость проигрывани€ анимаций
double thick_size = (WIDTH + HEIGHT)/ 300; // размер контура

int current_act = 0; // номер акта

bool debugging = false;

bool level1_start = true; // начата ли игра
bool level2_start = false; // начата ли игра
bool to_settings = false; // переход к настройкам

Vector2i mouse_position; // позици€ мыши
Font main_font; // основной шрифт игры
Color main_color = Color(255, 255, 255, 255); // главный цвет игры.

// создание окна
RenderWindow window(VideoMode(WIDTH, HEIGHT), "I became an excelent student when I visited another world");

View view(FloatRect(0.f, 0.f, WIDTH, HEIGHT));



// ~~~~~~~~~~~~~~—“јЌƒј–“Ќџ≈_‘”Ќ ÷»»~~~~~~~~~~~~~~~

// масштабирование и применение текстур к заднему фону
void background_init(Texture &txt, RectangleShape &background){
	background.setSize(Vector2f(WIDTH * 1.02f, HEIGHT));
	background.setTexture(&txt);
	background.setTextureRect(IntRect(0, 0, txt.getSize().x, txt.getSize().y));
}

// функци€ перевода дробного числа в строку
string to_string(double num){
	ostringstream result;
	result << num;
	return result.str();
}
 // перевод строки в целое число
int stoi(string str)
{
	int result = 0;
	for (int i = 0; i < str.length(); i++){
		assert((str[i] >= '0') && (str[i] <= '9'));
		result += str[i] - '0';
		result *= 10;
	}
	result /= 10;
	return result;
}

