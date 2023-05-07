#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

// ���������� ���������� ������� ������.
int WIDTH = VideoMode::getDesktopMode().width;
int HEIGHT = VideoMode::getDesktopMode().height;
//int WIDTH = 683;
//int HEIGHT = 384;

double deltaTime = 0; // ���������� ���������� �������.
double anim_speed = 15.f; // �������� ������������ ��������
double thick_size = (WIDTH + HEIGHT)/ 300; // ������ �������

int current_act = 0; // ����� ����

bool debugging = false;

bool level1_start = false; // ������ �� ����
bool level2_start = false; // ������ �� ���� 2
bool level2_5_start = false; // ������� � ������ 2_5
bool level3_start = false; // ������� � ������ 3
bool level4_start = false; // ������� � ������ 4
bool level5_start = false; // ������� � ������ 5
bool level5_5_start = false; // ������� � ������ 5_5
bool level6_start = true; // ������� � ������ 5
bool level7_start = false;
bool to_settings = false; // ������� � ����������

Vector2i mouse_position; // ������� ����
Font main_font; // �������� ����� ����
Color main_color = Color(255, 255, 255, 255); // ������� ���� ����.
enum direction {STOP, UP, DOWN, RIGHT, LEFT}; // ������������ ��� �����������

// �������� ����
RenderWindow window(VideoMode(WIDTH, HEIGHT), "I became an excelent student when I visited another world", Style::Fullscreen);

View view(FloatRect(0.f, 0.f, WIDTH, HEIGHT));





// ~~~~~~~~~~~~~~�����������_�������~~~~~~~~~~~~~~~

// ��������������� � ���������� ������� � ������� ����
void background_init(Texture &txt, RectangleShape &background){
	background.setSize(Vector2f(WIDTH * 1.02f, HEIGHT));
	background.setTexture(&txt);
	background.setTextureRect(IntRect(0, 0, txt.getSize().x, txt.getSize().y));
}

// ������� �������� �������� ����� � ������
string to_string(double num){
	ostringstream result;
	result << num;
	return result.str();
}
 // ������� ������ � ����� �����
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

