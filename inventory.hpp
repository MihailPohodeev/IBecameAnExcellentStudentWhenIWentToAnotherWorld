#include "slot.hpp"

class inventory{
	
	RectangleShape background;
	
	double anim_time, // ����� ��� ��������
	alpha, // �����-����� ������� ����
	max_darkness; // ������������ ���������� ������� ����
	
	slot slots[8];
	
	Clock clock; // ������
	
public:
	
	bool isActive, // ������� �� ������ ���������
	onClick; // ��� ������������� ������� ������ ������ ����������
	
	void update(); // ����������
	void render(); // ��������� ��������� ���������
	
	inventory(){
		
		slots[0].setPosition(WIDTH * 1 / 5, HEIGHT * 0.45f);
		slots[1].setPosition(WIDTH * 2 / 5, HEIGHT * 0.45f);
		slots[2].setPosition(WIDTH * 3 / 5, HEIGHT * 0.45f);
		slots[3].setPosition(WIDTH * 4 / 5, HEIGHT * 0.45f);
		slots[4].setPosition(WIDTH * 1 / 5, HEIGHT * 0.75f);
		slots[5].setPosition(WIDTH * 2 / 5, HEIGHT * 0.75f);
		slots[6].setPosition(WIDTH * 3 / 5, HEIGHT * 0.75f);
		slots[7].setPosition(WIDTH * 4 / 5, HEIGHT * 0.75f);
		
		background.setSize(Vector2f(WIDTH, HEIGHT));
		background.setFillColor(Color(0, 0, 0, 0));
		
		alpha = 0;
		
		isActive = false;
		onClick = false;
		
	}
};

// ����������
void inventory::update(){
	
	anim_time = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
	max_darkness = 200;
	
	// ��������� ��������� �� ������� ������ "E"
	if(Keyboard::isKeyPressed(Keyboard::E)){
		if(!onClick){
			isActive = !isActive;
			clock.restart();
			onClick = true;
		}
	} else onClick = false;
	
	if(isActive){
		if (alpha < max_darkness){
			alpha += anim_speed * anim_time;
		} 
		else{
			alpha = max_darkness;
			for (char i = 0; i < 8; i++) slots[i].isActive = true;
		}
	}
	else {
		if (alpha > 0){
			for (char i = 0; i < 8; i++) slots[i].isActive = false;
			alpha -= anim_speed * anim_time;
		} else alpha = 0;
	}	
	
	for (char i = 0; i < 8; i++){
		slots[i].update();
	}
	
	background.setFillColor(Color(0, 0, 0, (char)alpha));
}

void inventory::render(){
	window.draw(background);
	for (int i = 0; i < 8; i++){
		slots[i].render();
	}
}























