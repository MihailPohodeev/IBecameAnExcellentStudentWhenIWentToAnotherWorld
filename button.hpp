#include "check_mark.hpp"

class Button{
	
	// ����� ������
	Text button_text;
	
	// �������� ������
	FloatRect shape_rect;
	
	// ������ ������
	double text_size;
	
public:
	
	// ����� ������
	RectangleShape shape;
	
	// ���� ������
	Color shape_color,
	outline_color,
	text_color;
		
	bool isActive, // ������� �� ������
	oldActive, // ���������� ��� ��������� ��������� ���������� ������
	anim_playing; // ������������� �� ��������
	
	Vector2f position; // ����������� ������� ������
	
	double alpha; // �����-����� ������
	
	// ~~~~~�������~~~~~
	void update(); // ����������
	bool onClick(); // �������� �� ����� ���
	void setPosition(int x, int y); // ���������� �������
	void setSize(int width, int height); // ���������� ������
	void setText(string str); // ���������� ������
	void setTextSize(double size); // ���������� ������ ������
	void anim_appearing(); // �������� ���������
	void anim_disappearing(); // �������� ������������
	
	Vector2f getSize(); // �������� ������ ������
	Vector2f getPosition(); // �������� ������� ������
	
	
	Button();
	// �����������
	Button(int width, int height){
		
		shape_color = Color(255, 255, 255, 0);
		outline_color = Color(0, 0, 0, 0);
		text_color = Color(0, 0, 0, 0);
		
		shape.setSize(Vector2f(width, height));
		shape.setOrigin(Vector2f(width / 2, height / 2));
		shape.setOutlineThickness(thick_size);
		button_text.setFont(main_font);
		button_text.setFillColor(Color(0, 0, 0, 0));
				
		
		alpha = 0;
		text_size = 0;
		
		isActive = false;
		anim_playing = false;
	}
	
};

// �������� ������� ��� ���������� ���������
void Button::update(){
	
	shape_rect = shape.getGlobalBounds();
	
	if (isActive != oldActive) anim_playing = true;
	
	if (isActive){
		if (anim_playing) anim_appearing();
		else {
			if(shape_rect.contains((Vector2f)mouse_position)){
				shape.setFillColor(Color(shape_color.r / 2, shape_color.g / 2, shape_color.b / 2, (char)alpha));
				if (Mouse::isButtonPressed(Mouse::Left)) shape.setFillColor(Color(shape_color.r / 4, shape_color.g / 4, shape_color.b / 4, (char)alpha));
			}
			else {
				shape.setFillColor(Color(shape_color.r, shape_color.g, shape_color.b, (char)alpha));
			}
		}
	}
	else if (anim_playing){
		anim_disappearing();	
	}
	
	oldActive = isActive;
	
	shape.setOutlineColor(Color(outline_color.r, outline_color.g, outline_color.b, (char)alpha));
	button_text.setFillColor(Color(text_color.r, text_color.g, text_color.b, (char)alpha));
	
	window.draw(shape);
	window.draw(button_text);
}


// �������� �� ����� ���
bool Button::onClick(){
	if ((shape_rect.contains((Vector2f)mouse_position)) && (Mouse::isButtonPressed(Mouse::Left)) && isActive){
		return true;
	}
	else return false;
}

// ���������� ������� �����
void Button::setPosition(int x, int y){
	shape.setPosition(Vector2f(x, y));
	button_text.setPosition(Vector2f(x, y));
	position = shape.getPosition();
}

// ���������� ������ �����
void Button::setSize(int width, int height){
	shape.setSize(Vector2f(width, height));
}

// ���������� �����
void Button::setText(string str){
	button_text.setString(str);
	button_text.setOrigin(Vector2f(((string)button_text.getString().toAnsiString()).length() * text_size / 2.6f, text_size / 2));
}

// ���������� ������ ������
void Button::setTextSize(double size){
	text_size = size;
	button_text.setCharacterSize(size);
	button_text.setOrigin(Vector2f(((string)button_text.getString().toAnsiString()).length() * text_size / 2.6f, text_size / 2));
}

// �������� ������ ������
Vector2f Button::getSize(){
	return shape.getSize();
}

// �������� ������� ������
Vector2f Button::getPosition(){
	return shape.getPosition();
}

// �������� ������������
void Button::anim_disappearing(){
	if (alpha > 0){
		alpha -= anim_speed * 50 * deltaTime;
		shape.move(anim_speed * 2 * deltaTime, 0);
		button_text.move(anim_speed * 2 * deltaTime, 0);
	}
	else {
		anim_playing = false;
	}
	if (alpha < 0) alpha = 0;
	
	shape.setFillColor(Color(shape_color.r, shape_color.g, shape_color.b, (char)alpha));
}

// �������� ���������
void Button::anim_appearing(){
	static bool isFirst = true;
	if (isFirst) {
		shape.setPosition(2 * position.x - shape.getPosition().x, shape.getPosition().y);
		button_text.setPosition(2 * position.x - button_text.getPosition().x, shape.getPosition().y);
		isFirst = false;
	}
	if (alpha < 255) alpha += anim_speed * 50 * deltaTime;
	if (position.x > shape.getPosition().x) {
		shape.move(anim_speed * 2 * deltaTime, 0);
		button_text.move(anim_speed * 2 * deltaTime, 0);
	}
	if (shape.getPosition().x >= position.x && alpha >= 255){
		isFirst = true;
		anim_playing = false;
	}
	if (alpha > 255) alpha = 255;
	
	shape.setFillColor(Color(shape_color.r, shape_color.g, shape_color.b, (char)alpha));
}

// ����������� ������������ ������.
void disappearing(bool activity, Button &start, Button &settings, Button &exit){
	if (!start.anim_playing && start.isActive == activity){
		if (!settings.anim_playing && settings.isActive == activity){
			exit.isActive = activity;
		}
		settings.isActive = activity;
	}
	start.isActive = activity;
}
