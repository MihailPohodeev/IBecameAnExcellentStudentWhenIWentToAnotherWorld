#include "drop_menu.hpp"

// класс €чейки инвентар€
class slot{
	
	RectangleShape shape; // форма €чейки
	
	FloatRect shape_rect; // коллайдер €чейки
	
	Color slot_color; // цвет слота
	
	double alpha; // альфа-канал €чейки
		
public:	

	bool isActive; // активна ли €чейка
	
	void update(); // обновление
	void render(); // отрисовка
	void setPosition(Vector2f pos); // установить позицию €чейки
	void setPosition(double x, double y); // установить позицию €чейки
	Vector2f getPosition(); // получить позицию €чейки
	
	// конструктор
	slot(){
		
		slot_color = Color(main_color.r, main_color.g, main_color.b, 0);
		
		shape.setSize(Vector2f(HEIGHT * 0.2f, HEIGHT * 0.2f));
		shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y / 2));
		shape.setFillColor(slot_color);
		shape.setOutlineThickness(thick_size);
		shape.setOutlineColor(Color(0, 0, 0, 0));
		
		isActive = false;
	}
};

// обновление
void slot::update(){
	// просцЄт текущей колизии кнопки
	shape_rect = shape.getGlobalBounds();
	
	// при активном состо€нии кнопки
	if (isActive){
		if(alpha < 255) {
			alpha += 510 * deltaTime;
			if (alpha > 255) alpha = 255;
		}
		else {
			alpha = 255;
			// изменение цвета формы €чейки
			if (shape_rect.contains((Vector2f)mouse_position)){
				if (Mouse::isButtonPressed(Mouse::Left)) slot_color = Color(main_color.r / 2.f, main_color.g / 2.f, main_color.b / 2.f, (char)alpha);
				else slot_color = Color(main_color.r / 1.5f, main_color.g / 1.5f, main_color.b / 1.5f, (char)alpha);
			}
			else {
				slot_color = Color(main_color.r, main_color.g, main_color.b, (char)alpha);
			}
		}
	}
	else{
		if (alpha > 0) {
			alpha -= 510 * deltaTime;
			if (alpha < 0) alpha = 0;
		} else alpha = 0;	
	}
	
	slot_color = Color(slot_color.r, slot_color.g, slot_color.b, (char)alpha);
	
	shape.setFillColor(slot_color);
	shape.setOutlineColor(Color(0, 0, 0, char(alpha)));
}

// установить координаты
void slot::setPosition(Vector2f pos){
	shape.setPosition(pos);
}

// установить координаты
void slot::setPosition(double x, double y){
	shape.setPosition(x, y);
}

// получить координаты
Vector2f slot::getPosition(){
	return shape.getPosition();
}

// отрисовка
void slot::render(){
	window.draw(shape);
}
