#include "button.hpp"

class drop_down_menu{
	
	// форма
	RectangleShape back;
	
	Color color;
	
	FloatRect back_rect;
	
	bool isActive; // активен ли элемент
	bool isDrop; // выброшены ли пункты меню
	bool OnClick; // для единоразового нажатия ЛКМ
	
	double alpha; // уровень прозрачности объекта
	double scale; // масштаб формы
	double width, height, max_height; // размеры формы
	
	int menu_count;
	
public:
	
	void update();
	void droping(); // выбрасывание пунтов меню
	void undroping(); // возврат формы к исходному состоянию
	void setPosition(Vector2f pos); // установить позицию меню
	void render();
	
	drop_down_menu(){
		
		scale = 1.f;
		alpha = 255;
		color = main_color;
		
		isActive = true;
		isDrop = OnClick = false;
		
		width = WIDTH * 0.3f;
		height = HEIGHT * 0.1f;
		
		menu_count = 6;
		max_height = height * menu_count;
		
		back.setSize(Vector2f(width, height));
		back.setOutlineThickness(thick_size);
		back.setOutlineColor(Color(0,0,0,(char)alpha));
		back.setFillColor(color);
		
	}
	
};

// обновление
void drop_down_menu::update(){
	
	back_rect = back.getGlobalBounds();
	
	if (back_rect.contains((Vector2f)mouse_position)){
		if (!isDrop){
			color = Color(128, 128, 128, (char)alpha);
			if(Mouse::isButtonPressed(Mouse::Left)){
				if (!OnClick){
					if (!isDrop) color = Color(64, 64, 64, (char)alpha);
					isDrop = !isDrop;
					OnClick = true;
				}
			}
			else OnClick = false;
		}
	}
	else{
		color = main_color;
		if(Mouse::isButtonPressed(Mouse::Left)){
			isDrop = false;
		}
	}
	
	if (isDrop) droping();
	else undroping();
	
	back.setFillColor(color);
	back.setSize(Vector2f(width, height));
	
}

// выбрасывание пунктов меню
void drop_down_menu::droping() {
	if (height < max_height) height += anim_speed * 100 * deltaTime;
	else height = max_height;
	
	back.setSize(Vector2f(width, height));
}

// возврат меню к исходному состоянию
void drop_down_menu::undroping() {
	if (height > max_height / menu_count) height -= anim_speed * 100 * deltaTime;
	else height = max_height / menu_count;
	back.setSize(Vector2f(width, height));
}

void drop_down_menu::setPosition(Vector2f pos){
	back.setPosition(pos);
}

// отрисовка элементов
void drop_down_menu::render(){
	window.draw(back);
}









































