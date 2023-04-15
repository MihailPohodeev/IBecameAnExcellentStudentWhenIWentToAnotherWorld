#include "sprites.hpp"

namespace level2_nmspc{
	
	class dialog_bar{
		
		bool isActive; // ������� �� � ������ ������ ������
		bool isPrinting; // ���������� �� � ������ ������ �����
		
		RectangleShape shape; // ����� ������
		
		double alpha; // ������� ������������ ������
		double x, y; // ���������� ������
		double speed; // �������� ��������
		
		fstream script; // ����� ��������
		
		string script_text; // ������ ��������
		
	public:
		
		void update(); // ����������
		void render(); // ���������
		
		dialog_bar(){
			shape.setSize(Vector2f(WIDTH - 2 * (thick_size), HEIGHT * 0.2));
			shape.setOrigin(Vector2f(shape.getSize().x / 2, 0));
			shape.setFillColor(Color(255, 255, 255, 255));
			shape.setOutlineColor(Color(0, 0, 0, 255));
			shape.setOutlineThickness(thick_size);
			shape.setPosition(WIDTH / 2, HEIGHT + thick_size);
			
			x = WIDTH / 2;
			y = HEIGHT - (WIDTH - shape.getSize().x) / 2;
			
			speed = 100;
			
			isActive = true;
			isPrinting = false;
			
			script.open("Scripts/Script2.txt");
			if(!script) cout<<"Error!!! File not open."<<'\n';
			else cout<<"File opened succsessfully."<<'\n';
		}	
	};
	
	void dialog_bar::update(){
		if (isActive){
			// �������� ��������� ������
			if (view.getCenter().y < HEIGHT / 2 + shape.getSize().y + 2 * thick_size){
				view.move(0, speed * deltaTime);
				if (view.getCenter().y > HEIGHT / 2 + shape.getSize().y){
					view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2 + shape.getSize().y + 2 * thick_size));
				}
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
			if (view.getCenter().y > HEIGHT / 2){
				view.move(0, - speed * deltaTime);
				if (view.getCenter().y < HEIGHT / 2){
					view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2));
				}
			}
		}
		
		if (Keyboard::isKeyPressed((Keyboard::Q))) isActive = !isActive;
	}
	
	// ���������
	void dialog_bar::render(){
		window.draw(shape);
	}
	
}
