#include "slot.hpp"

class inventory{
	
	RectangleShape background;
	
	double anim_time, // ����� ��� ��������
	alpha, // �����-����� ������� ����
	max_darkness; // ������������ ���������� ������� ����
	
	slot slots[8]; // ������ �����
	
	Clock clock; // ������
	
	Text inventary_title; // ������� "���������"
	
	Button *change_category; // ������ ����� ��������� ��������� "������ / ��������";
	
	enum category {RECORDS, ITEMS}; // ������������ ��� �������� ������� ��������� ��������
	category current_category;
	
public:
	
	bool isActive, // ������� �� ������ ���������
	onPress, // ��� ������������� ������� ������ ������ ����������
	onClick; // ��� ������������� ������� ���
	
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
		max_darkness = 200;
		
		isActive = false;
		onPress = onClick = false;
		
		current_category = ITEMS;
		change_category = new Button(WIDTH * 0.25f, HEIGHT * 0.1f);
		(*change_category).setPosition(WIDTH * 3 / 4, HEIGHT / 6);
		(*change_category).setText("������");
		(*change_category).setTextSize((WIDTH + HEIGHT) / 2 * 0.03f);
		(*change_category).isActive = false;
		
		inventary_title.setFont(main_font);
		inventary_title.setFillColor(Color(255, 255, 255, 0));
		inventary_title.setCharacterSize((HEIGHT + WIDTH) / 25);
		inventary_title.setString("���������");
		inventary_title.setOutlineColor(Color(0, 0, 0, 255));
		inventary_title.setOutlineThickness(thick_size);
		inventary_title.setOrigin(Vector2f(((string)inventary_title.getString().toAnsiString()).length() * inventary_title.getCharacterSize() / 3.f, inventary_title.getCharacterSize() / 2));
		inventary_title.setPosition(Vector2f(WIDTH / 4, HEIGHT / 6));
		
	}
};

// ����������
void inventory::update(){
	
	anim_time = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
	
	
	// ��������� ��������� �� ������� ������ "E"
	if(Keyboard::isKeyPressed(Keyboard::E)){
		if(!onPress){
			isActive = !isActive;
			clock.restart();
			onPress = true;
		}
	} else onPress = false;
	
	if(isActive){
		if (alpha < max_darkness){
			alpha += anim_speed * anim_time;
		} 
		else{
			alpha = max_darkness;
			(*change_category).isActive = true;
			for (char i = 0; i < 8; i++) slots[i].isActive = true;
		}
		
		if ((*change_category).onClick()){
			if(!onClick){
				if (current_category == ITEMS){
					current_category = RECORDS;
					(*change_category).setText("��������");
					cout<<"items\n";
				}
				else{
					current_category = ITEMS;
					(*change_category).setText("������");
					cout<<"records\n";
				}
				onClick = true;
			}
		}
		else onClick = false;
		
	}
	else {
		(*change_category).isActive = false;
		if (alpha > 0){
			for (char i = 0; i < 8; i++) slots[i].isActive = false;
			alpha -= anim_speed * anim_time;
		} else alpha = 0;
	}	
	
	for (char i = 0; i < 8; i++){
		slots[i].update();
	}
	
	background.setFillColor(Color(0, 0, 0, (char)alpha));
	
	inventary_title.setFillColor(Color(255, 255, 255, (char)255 * alpha / max_darkness));
	inventary_title.setOutlineColor(Color(0, 0, 0, (char)255 * alpha / max_darkness));
}

void inventory::render(){
	window.draw(background);
	for (int i = 0; i < 8; i++){
		slots[i].render();
	}
	window.draw(inventary_title);
	(*change_category).update();
}
























