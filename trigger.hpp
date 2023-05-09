#include "drop_menu.hpp"

class trigger{
	
	RectangleShape shape;
	
	FloatRect collider;
	
public:
	
	RectangleShape image;
	Texture image_txt;
	
	bool isImage;
	
	bool intersects(FloatRect object);
	void setPosition(double x, double y);
	void setOrigin(Vector2f s);
	void render();
	
	trigger(int width, int height){
		isImage = false;
		shape.setSize(Vector2f(width, height));
	}
};

void trigger::setOrigin(Vector2f s){
	shape.setOrigin(s);
}

// установка позиции
void trigger::setPosition(double x, double y){
	shape.setPosition(x, y);
	image.setPosition(x, y);
}

// отрисовка коллайдера
void trigger::render(){
	if (debugging) window.draw(shape);
	if (isImage) window.draw(image);
}

// проверка на пересечение
bool trigger::intersects(FloatRect object){
	collider = shape.getGlobalBounds();
	if (collider.intersects(object)){
		return true;
	}
}
