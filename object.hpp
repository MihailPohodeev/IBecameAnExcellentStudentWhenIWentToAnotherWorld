#include "trigger.hpp"

class object{
public:	
	RectangleShape shape; // форма объекта
	
	string description; // описание объекта
	
	void setTexture(Texture &txt){
		shape.setTexture(&txt);
	}
	
	object(){
		shape.setSize(Vector2f(HEIGHT * 0.15f, HEIGHT * 0.15f));
		shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y / 2));
	}
};
