#include "settings.hpp"

class check_mark{
	
	RectangleShape shape; // ����� ������
	RectangleShape toggle; // ����� ��������
	
	FloatRect toggle_rect;
	
	double right_toggle_pos, // ���������� ������ �������
	left_toggle_pos, // ���������� ����� �������
	toggle_pos_X, // ������� �������� �� ��������� x
	darkness; // ������� ���������� ����� ��������
	
	bool onClick; // ��� ������������� ������� ���
	
public:
	
	bool isOn; // ������� �� �������
	
	void setPosition(Vector2f pos); // ���������� ������� ��������
	void update(); // ����������
	void animation(); // �������� ��������� � ���������� ��������
	void render(); // ��������� ��������� ��������
	
	check_mark(){
		shape.setSize(Vector2f((WIDTH + HEIGHT) / 25, (WIDTH + HEIGHT) / 50));
		shape.setFillColor(Color(255, 255, 255, 255));
		shape.setOutlineThickness(thick_size);
		shape.setOutlineColor(Color(0, 0, 0, 255));
		
		toggle.setSize(Vector2f(shape.getSize().x * 3 / 8, (WIDTH + HEIGHT) / 60));
		toggle.setFillColor(Color(128, 128, 128, 255));
		
		onClick = false;
		isOn = false;
		darkness = 128;
		
		setPosition(Vector2f(0, 0));
		
	}	
};

// ����������
void check_mark::update(){
	
	toggle_rect = shape.getGlobalBounds();
	
	if (toggle_rect.contains((Vector2f)mouse_position)){
		toggle.setFillColor(Color(64, 64, 64, 255));
		shape.setOutlineColor(Color(64, 64, 64, 255));
		if(Mouse::isButtonPressed(Mouse::Left)){
			if (!onClick){
				isOn = !isOn;
				onClick = true;
				cout<<isOn<<'\n';
			}
		} else onClick = false;
	}
	else {
		toggle.setFillColor(Color(char(darkness - 128 * pow(-1, isOn)), char(darkness - 128 * pow(-1, isOn)), char(darkness - 128 * pow(-1, isOn)), 255));
		shape.setOutlineColor(Color(0, 0, 0, 255));
	}
	
	animation();
	
	toggle.setPosition(toggle_pos_X, toggle.getPosition().y);
	shape.setFillColor(Color((char)darkness, (char)darkness, (char)darkness, 255));
}

// �������� ��������� ��������� ��������
void check_mark::animation(){
	if (isOn){
		if (toggle_pos_X < right_toggle_pos) {
			toggle_pos_X += anim_speed * 10 * deltaTime;
			if(toggle_pos_X > right_toggle_pos) toggle_pos_X = right_toggle_pos;
		}
		if (darkness < 255){
			darkness += anim_speed * 20 * deltaTime;
			if (darkness > 255) darkness = 255;
		}
	}
	else {
		if (toggle_pos_X > left_toggle_pos) {
			toggle_pos_X -= anim_speed * 10 * deltaTime;
			if(toggle_pos_X < left_toggle_pos) toggle_pos_X = left_toggle_pos;
		}
		if (darkness > 128){
			darkness -= anim_speed * 20 * deltaTime;
			if (darkness < 128) darkness = 128;
		}
	}
}

// ���������� ������� ��������
void check_mark::setPosition(Vector2f pos){
	shape.setPosition(pos);
	toggle.setPosition(pos.x + (shape.getSize().y - toggle.getSize().y) / 2, pos.y + (shape.getSize().y - toggle.getSize().y) / 2);
	
	// ���������� ����� ���������� �������
	left_toggle_pos = pos.x + (shape.getSize().y - toggle.getSize().y) / 2;
	right_toggle_pos = shape.getPosition().x + shape.getSize().x - (shape.getSize().y - toggle.getSize().y) / 2 - toggle.getSize().x;
	
	toggle_pos_X = toggle.getPosition().x;
}

// ��������� ��������� ��������
void check_mark::render(){
	window.draw(shape);
	window.draw(toggle);
}
