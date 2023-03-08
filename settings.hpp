#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;
using namespace sf;

// ���������� ���������� ������� ������.
//int WIDTH = VideoMode::getDesktopMode().width;
//int HEIGHT = VideoMode::getDesktopMode().height;
int WIDTH = 683;
int HEIGHT = 384;

double deltaTime = 0; // ���������� ���������� �������.
double anim_speed = 15.f; // �������� ������������ ��������

bool start_game = false; // ������ �� ����

Vector2i mouse_position; // ������� ����
Font main_font; // �������� ����� ����
Color main_color = Color(255, 255, 255, 255); // ������� ���� ����.

// �������� ����
RenderWindow window(VideoMode(WIDTH, HEIGHT), "I became an excelent student when I visited another world");




// ~~~~~~~~~~~~~~�����������_�������~~~~~~~~~~~~~~~



// ��������������� � ���������� ������� � ������� ����
void background_init(Texture &txt, RectangleShape &background){
	background.setSize(Vector2f(WIDTH, HEIGHT));
    background.setTexture(&txt);
    background.setOrigin(Vector2f(background.getSize().x / 2, background.getSize().y / 2));
    background.setPosition(WIDTH / 2, HEIGHT / 2);
}

// ������� �������� �������� ����� � ������
string to_string(double num){
	ostringstream result;
	result << num;
	return result.str();
}

