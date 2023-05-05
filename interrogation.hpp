#include "panel.hpp"

class interrogation : public panel{
	
public:
	
	
	void update(bool notInventary, person *character, int size); // обновление
	void render(); // отрисовка интерфейса
	
	Button *objection; // кнопка возражения
	Button *more_details; // кнопка "подробнее"
	
	bool more; // больше информации
	bool isInterrogation; // режим допроса
	bool isCorrect; // верно ли выбрана позиция возражения
	
	float green_level; // уровень зеленого цвета
	
	inventory _inventory;
	
	int interrog_act, true_act;
	
	interrogation() : panel() {
		
		isActive = false;
		
		more = false;
		isInterrogation = false;
		
		_inventory.isInterrogation = true;
		
		symbols_count = WIDTH * 0.65f / text_speech_size;
		
		panel_shape.setFillColor(Color(0,0,0,0));
		green_level = 0;
		
		objection = new Button(WIDTH / 7, HEIGHT / 13);
		more_details = new Button(WIDTH / 7, HEIGHT / 13);
		speech_position = Vector2f(panel_shape.getSize().x * 0.4f, panel_shape.getPosition().y * 1.1f);
		
		(*objection).setPosition(panel_shape.getSize().x + (WIDTH - panel_shape.getSize().x) / 2 - (*objection).getSize().x * 0.7f, panel_shape.getPosition().y + panel_shape.getSize().y / 4);
		(*objection).setText("возразить");
		(*objection).setTextSize((WIDTH + HEIGHT) / 2 * 0.025f);
		(*objection).isActive = false;
		(*objection).shape_color = Color(200, 200, 200, 0);
		(*objection).outline_color = Color(0, 180, 0, 0);
		(*objection).text_color = Color(0, 180, 0, 0);
		
		(*more_details).setPosition(panel_shape.getSize().x + (WIDTH - panel_shape.getSize().x) / 2 - (*objection).getSize().x * 0.7f, panel_shape.getPosition().y + panel_shape.getSize().y * 0.75f);
		(*more_details).setText("подробнее");
		(*more_details).setTextSize((WIDTH + HEIGHT) / 2 * 0.025f);
		(*more_details).isActive = false;
		(*more_details).shape_color = Color(200, 200, 200, 0);
		(*more_details).outline_color = Color(0, 180, 0, 0);
		(*more_details).text_color = Color(0, 180, 0, 0);
	}	
};

// обновление
void interrogation::update(bool notInventary, person *character, int size){
	
	if ((Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0, 1)) && !notInventary){
		if (left_click){
			if(isActive && !DISAPPEARING){
				if (!printing){
				
					if ((*more_details).onClick() && current_text.length() != 0){
						(*more_details).isActive = false;
						(*objection).isActive = false;
						more = true;
					}
					
					if ((*objection).onClick()){
						_inventory.start = true;
					}
					else if(!_inventory.isActive){
						getline(script, script_text);
						printing_delay = 0.05f;
						bool isAct = false;
						string act_str = current_text = name_text = "";
						thinking = false;
						bool name = false;
						string speech = "";
						if (!more){
							
							(*more_details).isActive = true;
							(*objection).isActive = true;
							while(script_text[0] != '[')
								getline(script, script_text);
								
							for (int i = 0; i < script_text.length(); i++){
								if (script_text[i] == '['){
									isAct = true;
									continue;
								}
								else if (script_text[i] == ']'){
									isAct = false;
									act = stoi(act_str);
									continue;
								}
								else if (script_text[i] == '<') {
									name = true;
									continue;
								} 
								else if (script_text[i] == '>') {
									name = false;
									continue;
								}
								
								if (script_text[i] == '@') thinking = true;
								
								if (isAct) act_str += script_text[i];
								else if (name) name_text += script_text[i];
								else if ((name == false) && (script_text[i] != '@') && (script_text[i] != '%')) speech += script_text[i];
							}
							script_text = speech;
							printing = true;
						}
						else{
							for (int i = 0; i < script_text.length(); i++){
								if (script_text[i] == '{'){
									continue;
								}
								else if (script_text[i] == '}'){
									more = false;
									continue;
								}
								else if (script_text[i] == '<') {
									name = true;
									continue;
								} 
								else if (script_text[i] == '>') {
									name = false;
									continue;
								}
								
								if (name) name_text += script_text[i];
								if (script_text[i] == '@') thinking = true;
								if ((name == false) && (script_text[i] != '@') && (script_text[i] != '%')) speech += script_text[i];
							}
							script_text = speech;
							printing = true;
						}
						
						if (script_text.length() == 0) {
							(*current_person).isActive = false;
							isActive = false;
							DISAPPEARING = true;
							return;
						}
						
						(*current_person).isActive = false;
						// выбор текущего персонажа исходя из имени текущего спикера
						for(int i = 0; i < size; i++){
							if(character[i].name == name_text){
								current_person = &character[i];
								(*current_person).isActive = true;
							}
						}	
					}
				}
				else {
					printing_delay = 0.01f;
				}
			}
			else if (!DISAPPEARING){
				APPEARING = true;
				(*objection).isActive = false;
				(*more_details).isActive = false;
			}
			
			left_click = false;
		}
	}
	else{
		left_click = true;
	}
	
	if (isInterrogation){		
		if(!more) (*objection).isActive = true;
		
		if (green_level < 128) green_level += anim_speed * 5 * deltaTime;
		else green_level = 128;
		
		if (act == interrog_act) {
			script.clear();
			script.seekg(0);
		}
		
		if (_inventory.isActive){
			if ((*_inventory.choose).onClick()){
				if(act == true_act) cout<<"Da!"<<'\n';
				else cout<<"No!"<<'\n';
			}
		}
	}
	else {
		(*objection).isActive = false;
		
		if (green_level > 0) green_level -= anim_speed * 5 * deltaTime;
		else green_level = 0;
		
		if (act == interrog_act) {
			isInterrogation = true;
			script.clear();
			script.seekg(0);
		}
	}
	
	if (DISAPPEARING) {
		anim_disappearing();
		(*objection).isActive = false;
		(*more_details).isActive = false;
	}
	if (APPEARING) anim_appearing();
	
	if (printing) {
		anim_text();
		if (!thinking) 
			speaking = true;
	}
	else speaking = false;
	
	// действия персонажей
	if (thinking) (*current_person).isThinking = true;
	else (*current_person).isThinking = false;
	
	if (speaking) (*current_person).isSpeaking = true;
	else (*current_person).isSpeaking = false;
	(*current_person).update();
	
	_inventory.update();
	
	current_speech.setFillColor(Color(0, (char)green_level, 0, (char)alpha));
	person_name.setFillColor(Color(0, (char)green_level, 0, (char)alpha));
	panel_shape.setFillColor(Color(255, 255, 255, (char)alpha));
	panel_shape.setOutlineColor(Color(0, (char)green_level, 0, (char)alpha));
	dark_background.setFillColor(Color(0, 0, 0, (char)dark_alpha));
	(*more_details).outline_color = Color(0, (char)green_level, 0, 0);
	(*more_details).text_color = Color(0, (char)green_level, 0, 0);
	(*objection).outline_color = Color(0, (char)green_level, 0, 0);
	(*objection).text_color = Color(0, (char)green_level, 0, 0);
	
	current_speech.setString(current_text);
	person_name.setString(name_text);
	
	panel_shape.setPosition(bar_position);
	current_speech.setPosition(speech_position);
	person_name.setPosition(current_left_positoin.x, name_position.y);
}

// отрисовка
void interrogation::render(){
	
	window.draw(dark_background);
	window.draw((*current_person).shape);
	window.draw(panel_shape);
	window.draw(current_speech);
	window.draw(person_name);
	if (help) window.draw(mouse_icon);
	(*objection).update();
	(*more_details).update();
	_inventory.render();
}
