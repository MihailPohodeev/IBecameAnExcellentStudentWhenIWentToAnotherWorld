#include "sprites.hpp"

namespace level2_nmspc{
	
	class dialog_bar{
		
		bool isActive; // активна ли в данный момент панель
		bool isPrinting; // печатается ли в данный момент текст
		
		RectangleShape shape; // форма панели
		
		double alpha; // степень прозрачности панели
		double x, y; // координаты панели
		
		fstream script; // поток сценария
		
		string script_text; // строка сценария
		
	public:
		
		void update(); // обновление
		void render(); // отрисовка
		
		dialog_bar(){
			shape.setSize(Vector2f(WIDTH * 0.95, HEIGHT * 0.2));
			shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y));
			shape.setFillColor(Color(255, 255, 255, 0));
			shape.setOutlineColor(Color(0, 0, 0, 0));
			shape.setOutlineThickness(thick_size);
			
			x = WIDTH / 2;
			y = HEIGHT - (WIDTH - shape.getSize().x) / 2;
			
			isActive = false;
			isPrinting = false;
			
			script.open("Scripts/Script2.txt");
			if(!script) cout<<"Error!!! File not open."<<'\n';
			else cout<<"File opened succsessfully."<<'\n';
		}	
	};
	
	void dialog_bar::update(){
		if (isActive){
			// анимация появления панели
			if (alpha < 255){
				alpha += anim_speed * 20 * deltaTime;
				if (alpha > 255) alpha = 255;
			}
			else{
				if (!isPrinting){
					getline(script, script_text);
					isPrinting = true;
				}
				else{
					
				}
			}
		}
		else {
			if (alpha > 0){
				alpha -= anim_speed * 20 * deltaTime;
				if (alpha < 0) alpha = 0;
			}
		}
		
		shape.setFillColor(Color(255, 255, 255, (char)alpha));
		shape.setOutlineColor(Color(0, 0, 0, (char)alpha));
		shape.setPosition(x, y);
	}
	
	// отрисовка
	void dialog_bar::render(){
		window.draw(shape);
	}
	
}
