#include "sprites.hpp"

namespace level2_nmspc{
	
	class dialog_bar{
		
		Text name;
		Text speech;
		
		bool isClick; // ��� ������������� ������� ���
		bool isPrinting; // ���������� �� � ������ ������ �����
		
		RectangleShape shape; // ����� ������
		RectangleShape name_shape; // ����� ���� � ������ ���������
		
		double alpha; // ������� ������������ ������
		double x, y; // ���������� ������
		double speed; // �������� ��������
		
		fstream script; // ����� ��������
		
		string script_text; // ������ ��������
		string current_speech; // ������� ���� ���������
		string name_character; // ��� ���������
		
		void parsing(string str); // ������ ��������
		
	public:
		
		bool isActive; // ������� �� � ������ ������ ������
		
		void update(); // ����������
		void render(); // ���������
		
		
		dialog_bar(){
			shape.setSize(Vector2f(WIDTH - 2 * (thick_size), HEIGHT * 0.2));
			shape.setOrigin(Vector2f(shape.getSize().x / 2, 0));
			shape.setFillColor(Color(255, 255, 255, 255));
			shape.setOutlineColor(Color(0, 0, 0, 255));
			shape.setOutlineThickness(thick_size);
			shape.setPosition(WIDTH / 2, HEIGHT + thick_size);
			
			name_shape.setSize(Vector2f(WIDTH / 6, WIDTH / 25));
			name_shape.setOrigin(Vector2f(name_shape.getSize().x / 2, name_shape.getSize().y / 2));
			name_shape.setFillColor(Color(200, 200, 200, 255));
			name_shape.setOutlineThickness(thick_size);
			name_shape.setOutlineColor(Color(0, 0, 0, 255));
			name_shape.setPosition(WIDTH / 9, HEIGHT + thick_size + name_shape.getSize().y / 2);
			
			name.setFont(main_font);
			name.setFillColor(Color(0, 0, 0, 255));
			name.setCharacterSize((HEIGHT + WIDTH) / 2 * 0.016f);
			name.setPosition(name_shape.getPosition().x, name_shape.getPosition().y);
			name.setString("Name");
			
			speech.setFont(main_font);
			speech.setFillColor(Color(0, 0, 0, 255));
			speech.setCharacterSize((HEIGHT + WIDTH) / 2 * 0.025f);
			speech.setPosition(WIDTH / 8, HEIGHT + shape.getSize().y / 2);
			
			x = WIDTH / 2;
			y = HEIGHT - (WIDTH - shape.getSize().x) / 2;
			
			speed = WIDTH / 4.f;
			
			isClick = false;
			isActive = false;
			isPrinting = false;
			
			script.open("Scripts/Script2.txt");
			if(!script) cout<<"Error!!! File not open."<<'\n';
			else cout<<"File opened succsessfully."<<'\n';
		}	
	};
	
	void dialog_bar::update(){
		
		if (isActive){
			// �������� ��������� ������
			if (name_shape.getPosition().y > HEIGHT){
				name_shape.move(0, -speed / 4 * deltaTime);
				name.move(0, -speed / 4 * deltaTime);
			}
			if (view.getCenter().y < HEIGHT / 2 + shape.getSize().y + 2 * thick_size){
				view.move(0, speed * deltaTime);
				if (view.getCenter().y > HEIGHT / 2 + shape.getSize().y + 2 * thick_size){
					view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2 + shape.getSize().y + 2 * thick_size + 0.001f));
				}
			}
			else{
				
				if(Mouse::isButtonPressed(Mouse::Left)){
					if (!isClick){
						if (!isPrinting){
							name_character = current_speech = "";
							getline(script, script_text);
							parsing(script_text);
							cout<<current_speech<<'\n';
							name.setString(name_character);
							speech.setString(current_speech);
//							isPrinting = true;
						}
						else{
						isPrinting = false;
						}
					}
					isClick = true;
				}
				else{
					isClick = false;
				}
				
			}
		}
		else {
			// �������� ������������ ���������� ������
			if (view.getCenter().y > HEIGHT / 2){
				view.move(0, - speed * deltaTime);
				if (view.getCenter().y < HEIGHT / 2){
					view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2));
					
				}
			}
			if (name_shape.getPosition().y < HEIGHT + name_shape.getSize().y / 2 + thick_size){
				name_shape.move(0, speed / 4 * deltaTime);
				name.move(0, speed / 4 * deltaTime);
			}
		}
		
		if (Keyboard::isKeyPressed((Keyboard::Q))) isActive = !isActive;
	}
	
	// ������ ��������
	void dialog_bar::parsing(string str){
		bool name = false;
		for(int i = 0; i < str.length(); i++){
			if (str[i] == '<') {
				name = true;
				continue;
			} 
			else if (str[i] == '>') {
				name = false;
				continue;
			}
			else if (str[i] == '@'){
				continue;
			}
			
			if (name) name_character += str[i];
			else current_speech += str[i];
		}
	}
	
	// ���������
	void dialog_bar::render(){
		window.draw(shape);
		window.draw(name_shape);
		window.draw(name);
		window.draw(speech);
	}
	
}
