#include "check_mark.hpp"

class Button{
	
	// текст кнопки
	Text button_text;
	
	// коллайер кнопки
	FloatRect shape_rect;
	
	// размер текста
	double text_size;
	
public:
	
	// форма кнопки
	RectangleShape shape;
	
	// цвет кнопки
	Color shape_color,
	outline_color,
	text_color;
		
	bool isActive, // активна ли кнопка
	oldActive, // переменная для выявления изменения активности кнопки
	anim_playing; // проигрывается ли анимация
	
	Vector2f position; // стандартная позиция кнопки
	
	double alpha; // альфа-канал кнопки
	
	// ~~~~~ФУНКЦИИ~~~~~
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
	
	
	Button();
	// конструктор
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

// основная функция для применения изменения
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
	button_text.setOrigin(Vector2f(((string)button_text.getString().toAnsiString()).length() * text_size / 2.6f, text_size / 2));
}

// установить размер шрифта
void Button::setTextSize(double size){
	text_size = size;
	button_text.setCharacterSize(size);
	button_text.setOrigin(Vector2f(((string)button_text.getString().toAnsiString()).length() * text_size / 2.6f, text_size / 2));
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
		button_text.move(anim_speed * 2 * deltaTime, 0);
	}
	else {
		anim_playing = false;
	}
	if (alpha < 0) alpha = 0;
	
	shape.setFillColor(Color(shape_color.r, shape_color.g, shape_color.b, (char)alpha));
}

// анимация появления
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
