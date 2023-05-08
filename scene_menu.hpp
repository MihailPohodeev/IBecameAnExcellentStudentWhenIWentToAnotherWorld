#include "inventory.hpp"

class scene_menu{
	
	// кнопки
	Button *continue_;
	Button *main_menu;
	
	// степень прозрачности
	double alpha;
	
	// для единоразового нажатия
	bool isClick;
	
	// задний фон для затемнения
	RectangleShape shape;
	
	public:
		
		bool isActive;
		
		void update();
		void render();
		
		scene_menu(){
			continue_ = new Button(WIDTH / 5, WIDTH / 10);
			main_menu = new Button(WIDTH / 5, WIDTH / 10);
			
			(*continue_).setPosition(view.getCenter().x, view.getCenter().y - (*continue_).getSize().y * 1.5f);
			(*main_menu).setPosition(view.getCenter().x, view.getCenter().y + (*continue_).getSize().y * 1.5f);
			(*continue_).setTextSize(15);
			(*main_menu).setTextSize(15);
			(*continue_).setText("продолжить");
			(*main_menu).setText("главное меню");
			
			shape.setSize(Vector2f(WIDTH, HEIGHT * 1.5f));
			shape.setFillColor(Color(0, 0, 0, 0));
			shape.setPosition(0, 0);
			
			isActive = false;
			(*continue_).isActive = false;
			(*main_menu).isActive = false;
			isClick = false;
		}
	
};

void scene_menu::update(){
	
	if(Keyboard::isKeyPressed(Keyboard::Escape)){
		if (!isClick){
			isActive = !isActive;
		}
		isClick = true;
	}
	else{
		isClick = false;
	}
	
	if (isActive){
		if(alpha < 128){
			alpha += anim_speed * 5 * deltaTime;
			if (alpha > 128) alpha = 128;
		}
		(*continue_).isActive = true;
		(*main_menu).isActive = true;
		
		if ((*continue_).onClick()){
			isActive = false;
		}
		
		if ((*main_menu).onClick()){
			level1_start = false;
			level2_start = false;
			level2_5_start = false;
			level3_start = false;
			level4_start = false;
			level5_start = false;
			level5_5_start = false;
			level6_start = false;
			level7_start = false;
		}
	}
	else{
		if(alpha > 0){
			alpha -= anim_speed * 5 * deltaTime;
			if (alpha < 0) alpha = 0;
		}
		(*continue_).isActive = false;
		(*main_menu).isActive = false;
	}
	
	(*continue_).setPosition(view.getCenter().x, view.getCenter().y - (*continue_).getSize().y * 1.5f);
	(*main_menu).setPosition(view.getCenter().x, view.getCenter().y + (*continue_).getSize().y * 1.5f);
	shape.setFillColor(Color(0, 0, 0, (char)alpha));
}

void scene_menu::render(){
	window.draw(shape);
	(*continue_).update();
	(*main_menu).update();
}
