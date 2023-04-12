#include "inventory.hpp"

class person{
public:
	RectangleShape shape; // ����� ���������
	
	Texture say_txt, // ������� ���������
	think_txt;
	
	string name; // ��� ���������
	
	bool isSpeaking, // ������� �� ��������
	isThinking, // ������ �� ��������
	isActive, // ������� �� ��������
	oldActive, // ���������� ��� �������� ��������� ������� ���������� ���������
	anim_playing;
	
	Vector2f shape_origin[2], // ������� ������ ��� ������������
	position;
	
	IntRect say[2], // ������� �������� "���������" �� ������
	think[4]; // ������� "���������" �� ������
	
	Clock anim_clock;
	
	int anim_count, // ������� ������ ��������
	moving_coefficient; // ����������� �������� ��������� ��� ��������
	
	double alpha; // �����-����� ���������
	
	// �������� ���������
	void update();
	void saying();
	void thinking();
	void idle();
	
	// ���������� ����������� �������
	void setPosition(Vector2f pos);
	
	void anim_disappearing();
	void anim_appearing();
	
	person(){
		shape.setSize(Vector2f(WIDTH * 0.2f, HEIGHT * 0.65f));
		shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y));
		shape.setTexture(&think_txt);
		
		moving_coefficient = 5;
		
		say[0] = IntRect(100, 1, 500, 1023);
		say[1] = IntRect(600, 1, 500, 1023);
		
		think[0] = IntRect(550, 1040, 500, 1023);
		think[1] = IntRect(1045, 1040, 500, 1023);
		think[2] = IntRect(2060, 1040, 500, 1023);
		think[3] = IntRect(1045, 1040, 500, 1023);
		
		shape_origin[0] = shape.getOrigin();
		shape_origin[1] = Vector2f(shape.getOrigin().x + moving_coefficient, shape.getOrigin().y);
		
		isThinking = isSpeaking = isActive = oldActive = anim_playing = false;
		
		alpha = 0;
	}
	
};

void person::update(){
	if (isSpeaking) saying();
	else if (isThinking) thinking();
//	else idle();

	if (isActive != oldActive) anim_playing = true;
	
	if (anim_playing){
		if (isActive) anim_appearing();
		else anim_disappearing();
	}

	oldActive = isActive;
	
	shape.setFillColor(Color(255, 255, 255, (char)alpha));
}

// �������� ���������
void person::saying(){
	if ((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 > 0.25f) {
		anim_count++;
		anim_clock.restart();
	}
	shape.setTexture(&say_txt);
	if (anim_count > 1) anim_count = 0;
	shape.setOrigin(shape_origin[anim_count]);
	shape.setTextureRect(say[anim_count]);
}

// �������� �����������
void person::thinking(){
	if ((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 > 1.f) {
		anim_count++;
		anim_clock.restart();
	}
	if (anim_count > 3) anim_count = 0;
//	shape.setOrigin(shape_origin[anim_count]);
	shape.setTexture(&think_txt);
	shape.setTextureRect(think[anim_count]);
}

inline void person::setPosition(Vector2f pos) {
	position = pos;
	shape.setPosition(pos);
}

// �������� ������������ ��������
void person::anim_disappearing(){
	if (alpha > 0){
		alpha -= anim_speed * 50 * deltaTime;
		shape.move( - anim_speed * 2 * deltaTime, 0);
	}
	else {
		alpha = 0;
		anim_playing = false;
	}
}

void person::anim_appearing(){
	if (alpha < 255) alpha += anim_speed * 50 * deltaTime;
	if (position.x > shape.getPosition().x) shape.move(anim_speed * 2 * deltaTime, 0);
	if (shape.getPosition().x >= position.x && alpha >= 255){
		alpha = 255;
		anim_playing = false;
	}
}
