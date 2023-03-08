#include "settings.hpp"

class Button{
	
	// форма кнопки
	RectangleShape shape;
	
	// текст кнопки
	Text button_text;
	
	// коллайер кнопки
	FloatRect shape_rect;
	
	// цвет кнопки
	Color shape_color;
	
public:
		
	bool isActive, // активна ли кнопка
	oldActive, // переменная для выявления изменения активности кнопки
	anim_playing; // проигрывается ли анимация
	
	Vector2f position; // стандартная позиция кнопки
	
	double alpha; // альфа-канал кнопки
	
	// ~~~ФУНКЦИИ~~~
	void update(); // обновление
	bool onClick(); // действие по клику ЛКМ
	void setPosition(int x, int y); // установить позицию
	void setSize(int width, int height); // установить размер
	void setText(string str); // установить строку
	void setTextSize(double size); // установить размер текста
	void anim_appearing(); // анимация появления
	void anim_disappearing(); // анимация исчезновения
	
	Vector2f getSize(); // получить размер кнопки
	Vector2f getPosition(); // получить позицию кнопки
	
	
	
	// конструктор
	Button(int width, int height){
		shape.setSize(Vector2f(width, height));
		shape.setOrigin(Vector2f(width / 2, height / 2));
		shape_color = Color(255, 255, 255, 255);
		button_text.setFont(main_font);
		button_text.setFillColor(Color(64, 64, 64, 255));		
		
		alpha = 255;
		
		isActive = false;
		anim_playing = false;
	}
	
};

// основная функция для применения изменения
void Button::update(){
	
	shape_rect = shape.getGlobalBounds();
	
	if (isActive != oldActive) anim_playing = true;
	
	if (isActive){
		if (anim_playing) anim_appearing();
		else {
			if(shape_rect.contains((Vector2f)mouse_position)){
				shape_color = Color(128, 128, 128, 255);
				if (Mouse::isButtonPressed(Mouse::Left)) shape_color = Color(64, 64, 64, 255);
			}
			else {
				shape_color = Color(255, 255, 255, 255);
			}
		}
	}
	else if (anim_playing){
		anim_disappearing();	
	}
	
	oldActive = isActive;
	
	shape.setFillColor(Color(shape_color.r, shape_color.g, shape_color.b, (char)alpha));
	
	window.draw(shape);
	window.draw(button_text);
}


// действие по клику ЛКМ
bool Button::onClick(){
	if ((shape_rect.contains((Vector2f)mouse_position)) && (Mouse::isButtonPressed(Mouse::Left)) && isActive){
		return true;
	}
	else return false;
}

// установить позицию формы
void Button::setPosition(int x, int y){
	shape.setPosition(Vector2f(x, y));
	button_text.setPosition(Vector2f(x, y));
	position = shape.getPosition();
}

// установить размер формы
void Button::setSize(int width, int height){
	shape.setSize(Vector2f(width, height));
}

// установить текст
void Button::setText(string str){
	button_text.setString(str);
	button_text.setOrigin(Vector2f(button_text.getCharacterSize() / 2, str.length() * button_text.getCharacterSize() / 2));
}

// установить размер шрифта
void Button::setTextSize(double size){
	button_text.setCharacterSize(size);
	button_text.setOrigin(Vector2f(button_text.getCharacterSize() / 2, button_text.getOrigin().y));
}

// получить размер кнопки
Vector2f Button::getSize(){
	return shape.getSize();
}

// получить позицию кнопки
Vector2f Button::getPosition(){
	return shape.getPosition();
}

// анимация исчезновения
void Button::anim_disappearing(){
	if (alpha > 0){
		alpha -= anim_speed * 50 * deltaTime;
		shape.move(anim_speed * 2 * deltaTime, 0);
	}
	else {
		alpha = 0;
		anim_playing = false;
	}
}

// анимация появления
void Button::anim_appearing(){
	static bool isFirst = true;
	if (isFirst) {
		shape.setPosition(2 * position.x - shape.getPosition().x, shape.getPosition().y);
		isFirst = false;
	}
	if (alpha < 255) alpha += anim_speed * 50 * deltaTime;
	if (position.x > shape.getPosition().x) shape.move(anim_speed * 2 * deltaTime, 0);
	if (shape.getPosition().x >= position.x && alpha >= 255){
		alpha = 255;
		isFirst = true;
		anim_playing = false;
	}
}

// постепенное исчезновение кнопок.
void disappearing(bool activity, Button &start, Button &settings, Button &exit){
	if (!start.anim_playing && start.isActive == activity){
		if (!settings.anim_playing && settings.isActive == activity){
			exit.isActive = activity;
		}
		settings.isActive = activity;
	}
	start.isActive = activity;
}
