#include "panel.hpp"

class interrogation {
	
public:
	
	panel main_bar;
	
	void update(); // ����������
	void render(); // ��������� ����������
	
	Button *objection; // ������ ����������
	
	interrogation(){
		
		objection = new Button(WIDTH / 10, HEIGHT / 10);
		(*objection).setPosition(WIDTH / 2, HEIGHT * 0.9f);
	}	
};

void update(){
//	main_bar.update();
}

void interrogation::render(){
	main_bar.render();
	(*objection).update();
}
