#include "panel.hpp"

class interrogation : public panel{
	
	bool isObjectsEquals(object obj1, object obj2){
		if (obj1.description == obj2.description) return true;
		return false;
	}
	
	RectangleShape heart; // форма сердечка
	
public:

	int lifes; // количество очков терпения
	
	void update(bool notInventary, person *character, int size); // обновление
	void render(); // отрисовка интерфейса
	
	Button *objection; // кнопка возражения
	Button *more_details; // кнопка "подробнее"
	
	bool more; // больше информации
	bool isInterrogation; // режим допроса
	bool isCorrect; // верно ли выбрана позиция возражения
	bool isFound; // найдено ли противоречие
	bool dialog; // диалог без допроса
	bool isNesessaryObjFound; // найден ли необходимый объект
	bool click; // для программного вызова новой реплики
	bool appear_objection_button; // для появления кнопки
	
	float green_level; // уровень зеленого цвета
	
	inventory _inventory;
	
	int interrog_act, true_act, nessesary_obj;
	
	object rec;
	
	interrogation() : panel() {
		
		heart.setSize(Vector2f(WIDTH / 20, WIDTH / 20));
		heart.setPosition(0,0);
		
		lifes = 5;
		
		rec.description = "\"Зендей Слипанов, раса: Великан\" ...знал жертву заочно по рассказам друзей...";
		
		isActive = click = appear_objection_button = false;
		
		more = isFound = dialog = isNesessaryObjFound = false;
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
	
	if ((Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0, 1) || click) && !notInventary){
		
		click = false;
		bool isNewAct = false; // доступен ли новый акт
		
		if (left_click){
			if(isActive && !DISAPPEARING){
				if (!printing){
				
					if ((*more_details).onClick() && current_text.length() != 0){
						(*more_details).isActive = false;
						(*objection).isActive = false;
						more = true;
						if (act == nessesary_obj) isNesessaryObjFound = true;
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
						
						if (dialog){
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
						else if (!more){
							
							if (act != interrog_act) {
								(*more_details).isActive = true;
								(*objection).isActive = true;
							}
							else{
								(*more_details).isActive = false;
								(*objection).isActive = false;
							}
							while(script_text[0] != '[')
								getline(script, script_text);
								
							for (int i = 0; i < script_text.length(); i++){
								if (script_text[i] == '['){
									isAct = true;
									isNewAct = true;
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
					
					if(isInterrogation && isNewAct && !more && !isFound) appear_objection_button = true;
					else appear_objection_button = false;
					
				}
				else {
					if (!appear_objection_button) printing_delay = 0.01f;
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
		
		if (green_level < 128) green_level += anim_speed * 5 * deltaTime;
		else green_level = 128;
		
		if (act == interrog_act) {
			(*objection).isActive = false;
			(*more_details).isActive = false;
			current_text = "";
			script_text = "Не могли бы вы еще раз повторить ваш рассказ?";
			printing = true;
			script.clear();
			script.seekg(0);
			act = 0;
			appear_objection_button = false;
		}
		
		if (appear_objection_button) (*objection).isActive = true;
		else (*objection).isActive = false;
		
		_inventory.trigger_notification("Обновлено: Досье Слипанова", rec, 0);
		
		if (_inventory.isActive){
			if ((*_inventory.choose).onClick() && !isFound){
				if(act == true_act && isObjectsEquals(_inventory.current, rec)){
					while(script_text[0] != 'c'){
						if (script_text != "") cout<<script_text[0]<<'\n';
						getline(script, script_text);
						more = false;
						(*objection).isActive = false;
						(*more_details).isActive = false;
					}
					isFound = dialog = true;
					getline(script, script_text);
					_inventory.isActive = false;
					click = true;
				}
				else {
					current_text = "";
					script_text = "Не думаю, что это хороший выбор...";
					printing = true;
					lifes--;
					_inventory.isActive = false;
				}
			}
		}
	}
	else {
		(*objection).isActive = false;
		
		if (green_level > 0) green_level -= anim_speed * 5 * deltaTime;
		else green_level = 0;
		
		if (act == interrog_act){
			if (isNesessaryObjFound) isInterrogation = true;
			else{
				script_text = "Не думаю, что я собрал достаточное количество информации для начала допроса. Мне стоит подробнее распросить подозреваемого...";
				printing = true;
			}
			script.clear();
			script.seekg(0);
			act = 0;
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
	for (int i = 0; i < lifes; i++){
		window.draw(heart);
		heart.move(heart.getSize().x, 0);
	}
	heart.setPosition(0, 0);
	_inventory.render();
}
