#include "player.hpp"

class panel{
public:
	
	bool isActive, // ������� �� ���� � ������ ������
	left_click, // ������ �� ����� ������ ����
	printing, // ������� �� ������� ������
	thinking, // ������ �� ������ ��������
	speaking, // ������� �� ������ ��������
	APPEARING, // ��������� ���������� ������
	DISAPPEARING, // ������������ ���������� ������
	isInterrogation, // ����� �������
	act_calculating, // ���������� ������ ����
	help, // ��������� ������
	next, // ��������� �� �������� ������ ������
	isDark; // ������� �� �����
	
	string current_text, script_text, // ����� �������� � ��������� ����������
	name_text, // ������ ����� �������� ���������
	act_number; // ����� ����
	
	double anim_speed, // �������� ��������������� �������� ���������� ������
	printing_delay, // �������� ����� ������� ��������
	time_for_printing, // ������ ��� ������ �������� �� ���������� ������
	alpha, // ������� ������������ ������
	dark_alpha; // ������� ������������ ���� ����������
	
	int text_speech_size, // ������ ����������� ������
	text_name_size, // ������ ������ ����� ���������
	symbols_count, // ������������ ���������� ��������, ����������� �� ����� ������ � ���������� ����
	act; // ����� ����
	
	fstream script; //����� ��� ������.
	
	person *current_person; // ������� ��������, ������� ���������� �������
	
	Clock clock_for_printing; // ������ ��� ����������� ������ ������ � ���������� ����
	
	SoundBuffer buffer; // ���� ������ ������
	Sound text_appearence;
	
	RectangleShape panel_shape; // ����� ������
	RectangleShape dark_background; // ����� ��� ���������� ������
	RectangleShape mouse_icon; // ������ ���� ��� ����������� ����� ���
	RectangleShape arrows; // ��������� �����
	
	Vector2f center_bar_position; // ���������� ������� ������ ��������
	Vector2f left_person_position; // ����� ������� ��� ����������
	Vector2f right_person_position; // ������ ������� ��� ����������
	
	Vector2f bar_position; // ������� ����������� ����
	Vector2f current_left_positoin; // ����� ������� ���������
	Vector2f current_right_positoin; // ������ ������� ���������
	Vector2f speech_position; // ������� ������ �������
	Vector2f name_position; // ������� ������ �����
	
	Text current_speech; // ��������� ����������, �������� ������� ���� ���������
	Text person_name; // �������� ����������, �������� ��� �������� ���������
	
	Color bar_color, // ���� � ������������ ���������� ������
	text_color, // ���� ������
	isInterrogation_text_color; // ���� ������ ��� �������
	
	Texture icons; // �������� ������
	
	IntRect mouse_sprites[2]; // ������� ������ ���� �� ������ ������
	IntRect arrows_sprites[2]; // ������� ������ ������� �� ������ ������
	
	Clock anim_clock; // ������ ��� ��������
	
//	~~~~~�������~~~~~
	virtual void update(bool notInventary, person *character, int size); // ����������
	virtual void parsing(string str); // ��������� ������ �� ���������
	virtual void render(); // ��������� �������� ����������
	
	void anim_appearing(); // �������� ��������� ������ ��������
	void anim_disappearing(); // �������� ������������ ������ ��������
	void anim_text(); // ������������ ������ ������
	
	panel(){
		
		// ������ ������ ��������
		text_speech_size = (HEIGHT + WIDTH) / 2 * 0.025f;
		// ������ ������ ����� �������� ���������
		text_name_size = (HEIGHT + WIDTH) / 2 * 0.016f;
		
		// ��������� �������� � ������� ��������� ����������
		panel_shape.setSize(Vector2f(WIDTH * 0.95, HEIGHT * 0.2));
		panel_shape.setOutlineThickness(thick_size);
		panel_shape.setOutlineColor(Color(0,0,0,0));
		center_bar_position = bar_position = Vector2f((WIDTH - panel_shape.getSize().x) / 2, (HEIGHT - panel_shape.getSize().y) - (WIDTH - panel_shape.getSize().x) / 2);
		left_person_position = current_left_positoin = Vector2f(center_bar_position.x + panel_shape.getSize().x * 0.2f, center_bar_position.y);
		right_person_position = current_right_positoin = Vector2f(center_bar_position.x + panel_shape.getSize().x * 0.8f, center_bar_position.y);
		panel_shape.setPosition(center_bar_position);
		speech_position = Vector2f(center_bar_position.x + panel_shape.getSize().x / 2 - text_speech_size / 2, center_bar_position.y + panel_shape.getSize().y / 2 - text_speech_size / 2);
		name_position = Vector2f(current_left_positoin.x , bar_position.y);
		
		
		// ������������� ������
		icons.loadFromFile("Sprites/icons.png");
		
		mouse_sprites[0] = IntRect(0, 0, 8, 17);
		mouse_sprites[1] = IntRect(8, 0, 8, 17);
		
		arrows_sprites[0] = IntRect(17, 0, 16, 17);
		arrows_sprites[1] = IntRect(15, 0, 16, 17);
		
		mouse_icon.setSize(Vector2f((WIDTH + HEIGHT) * 0.02f, (WIDTH + HEIGHT) * 0.03f));
		mouse_icon.setPosition(Vector2f(WIDTH - mouse_icon.getSize().x  * 2.f, HEIGHT - mouse_icon.getSize().y * 1.5f));
		mouse_icon.setTexture(&icons);
		mouse_icon.setTextureRect(mouse_sprites[0]);
		
		arrows.setSize(Vector2f((WIDTH + HEIGHT) * 0.03f, (WIDTH + HEIGHT) * 0.015f));
		arrows.setPosition(Vector2f(panel_shape.getPosition().x + panel_shape.getSize().x - arrows.getSize().x  * 1.5f, panel_shape.getPosition().y + panel_shape.getSize().y / 2 - arrows.getSize().y * 0.5f));
		arrows.setTexture(&icons);
		arrows.setFillColor(Color(0, 0, 0, 255));
		arrows.setTextureRect(arrows_sprites[0]);
		
		
		// ������������� ���� ����������.
		
		isDark = true;
		dark_alpha = 255;
		dark_background.setSize(Vector2f(WIDTH, HEIGHT));
		dark_background.setFillColor(Color(0,0,0, (char)dark_alpha));
		
		
		// ��������� �����
		isInterrogation_text_color = Color(0, 180, 0, 255);
		bar_color = Color(255, 255, 255, 255);
		text_color = Color(0, 0, 0, 255);
		
		// �������� � �������� ������ � �������
		current_speech.setFont(main_font);
		current_speech.setCharacterSize(text_speech_size);
		current_speech.setFillColor(text_color);
		person_name.setFont(main_font);
		person_name.setCharacterSize(text_name_size);
		person_name.setFillColor(text_color);
		
		// ���������� ���������� �������� �� ���� ������
		symbols_count = WIDTH * 0.82f / text_speech_size;
		// �������� ����� ������� ���� �������� �������� � ��������
		printing_delay = 0.05f;
		// �������� ��������
		anim_speed = 15;
		alpha = act = 0;
		
		// ��������� ������ ������� �������
		current_text = name_text = act_number = "";
		
		// ��������� ��������� �������� ������� ����������
		APPEARING = DISAPPEARING = printing = false;
		isActive = false;
		thinking = speaking = act_calculating = false;
		isInterrogation = false;
		help = true;
		
		
		buffer.loadFromFile("Sounds/text.ogg");
		text_appearence.setBuffer(buffer);
		text_appearence.setVolume(5.f);
	}
};

void panel::update(bool notInventary, person *character, int size){
	// �������� �� ������� ����� ������ ����
	if ((Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0, 1)) && !notInventary){
		if (left_click){
			// ���� ���������� ���� �������
			if(isActive && !DISAPPEARING){
				// ���� � ������ ������ ����� �� ����������
				if (!printing){
					thinking = speaking = false;
					speech_position.x = center_bar_position.x + panel_shape.getSize().x / 2 - text_speech_size / 2;
					getline(script, script_text); // ��������� ������ �� ���������� ���������
					// ���� ������ �������, ������� ����
					if (script_text.length() == 0) {
						(*current_person).isActive = false;
						isActive = false;
						DISAPPEARING = true;
						return;
					}
					parsing(script_text); // ���������� ������ �� ��������� �����
					current_text = ""; // ��������� ������� ������
					printing_delay = 0.05f; // �������� ����� ������� ���� ��������� ��������
					printing = true; // ������ ������
					
					// ��������� � ����������� �������� ���������
					(*current_person).isActive = false;
					// ����� �������� ��������� ������ �� ����� �������� �������
					for(int i = 0; i < size; i++){
						if(character[i].name == name_text){
							current_person = &character[i];
							(*current_person).isActive = true;
						}
					}
				}
				// �����, �������� ����� ������
				else{
					printing_delay = 0.01f;
				}
			}
			else if (!DISAPPEARING){
				APPEARING = true;
			}
		}
		left_click = false;
	}
	else left_click = true;
	
	if (printing) {
		if (!thinking) speaking = true;
	}	
	
	// ���������� ��������� � ���� ������ ����
	if(alpha > 2) help = false;
	else help = true;
	
	
	
	if (((double)anim_clock.getElapsedTime().asMicroseconds() / 1000000) > 1) {
		mouse_icon.setTextureRect(mouse_sprites[1]);
		arrows.setTextureRect(arrows_sprites[0]);
	}
	else {
		mouse_icon.setTextureRect(mouse_sprites[0]);
		arrows.setTextureRect(arrows_sprites[1]);
	}
	
	// ����� ������ �� ���������� ������
	if (printing) anim_text();
	if (DISAPPEARING) anim_disappearing();
	if (APPEARING) anim_appearing();
	
	// �������� ����������
	if (thinking) (*current_person).isThinking = true;
	else (*current_person).isThinking = false;
	
	if (speaking) (*current_person).isSpeaking = true;
	else (*current_person).isSpeaking = false;
	(*current_person).update();
	
	// ��������� ���� ����������
	
	if (isDark){
		if (dark_alpha < 255){
			dark_alpha += anim_speed * 15 * deltaTime;
			if (dark_alpha > 255) dark_alpha = 255;
		}
	}
	else {
		if (dark_alpha > 0){
			dark_alpha -= anim_speed * 15 * deltaTime;
			if (dark_alpha < 0) dark_alpha = 0;
		}
	}
	
	
	// ���������� ������������� ��������� ����������.
	panel_shape.setPosition(bar_position);
	
	panel_shape.setFillColor(Color(255, 255, 255, (char)alpha));
	
	if (isInterrogation) {
		current_speech.setFillColor(Color(0, 100, 0, (char)alpha));
		person_name.setFillColor(Color(0,100,0, (char)alpha));
		panel_shape.setOutlineColor(Color(0,100,0, (char)alpha));
	}
	else {
		current_speech.setFillColor(Color(0, 0, 0, (char)alpha));
		person_name.setFillColor(Color(0,0,0, (char)alpha));
		panel_shape.setOutlineColor(Color(0,0,0, (char)alpha));
	}
	
	dark_background.setFillColor(Color(0, 0, 0, (char)dark_alpha));
	
	
	current_speech.setPosition(speech_position);
	person_name.setPosition((*current_person).shape.getPosition().x, name_position.y);
	
//	current_speech.setString(String::fromUtf8(current_text.begin(), current_text.end()));
//	person_name.setString(String::fromUtf8(name_text.begin(), name_text.end()).toAnsiString());
	
	current_speech.setString(current_text);
	person_name.setString(name_text);
	
	for (int i = 0; i < size; i++) {
		character[i].printing = printing;
	}
	
	if ((double)anim_clock.getElapsedTime().asMicroseconds() / 1000000 >= 2) anim_clock.restart();
	
}

// ������� ��������� ��������.
void panel::render(){
	window.draw(dark_background);
	window.draw((*current_person).shape);
	window.draw(panel_shape);
	window.draw(current_speech);
	window.draw(person_name);
	if (help) window.draw(mouse_icon);
	if (!printing && alpha > 250) window.draw(arrows);
}

// ���������� ������ �� ��������� ��������� � ������ ����������� �������������
void panel::parsing(string str){
	script_text = name_text = "";
	bool name = false;
	for (int i = 0; i < str.length(); i++){
		
		if (str[i] == '['){
			act_number = "";
			act_calculating = true;
			continue;
		}
		else if (str[i] == ']'){
			act_calculating = false;
			act = stoi(act_number);
			continue;
		}
		else if (str[i] == '<') {
			name = true;
			continue;
		} 
		else if (str[i] == '>') {
			name = false;
			continue;
		}
		
		if (act_calculating){
			act_number += str[i];
		}
		else {
			if (name) name_text += str[i];
			if (str[i] == '@') thinking = true;
			if (str[i] == '%') (*current_person).isDizziness = true;
			if ((name == false) && (str[i] != '@') && (str[i] != '%')) script_text += str[i];
		}
	}
}

// �������� ������������ ������.
void panel::anim_disappearing(){
	if(alpha > 0){
		// ��������� �������
		bar_position.y += anim_speed * deltaTime;
		speech_position.y += anim_speed * deltaTime;
		name_position.y += anim_speed * deltaTime;
		//��������� �����
		alpha -= anim_speed * 15 * deltaTime;
		if (alpha < 0) alpha = 0;
	} 
	else {
		DISAPPEARING = false;
		isActive = false;
	}
}

// �������� ��������� ������.
void panel::anim_appearing(){
	if (alpha < 255){
		alpha += anim_speed * 15 * deltaTime;
		if (bar_position.y > center_bar_position.y){
			bar_position.y -= anim_speed * deltaTime;
			speech_position.y -= anim_speed * deltaTime;
			name_position.y -= anim_speed * deltaTime;
		}
		if (alpha > 255) alpha = 255;
	}
	else{
		APPEARING = false;
		isActive = true;
	}
}

// �������� ������ ������.
void panel::anim_text(){
	static int i = 0; // ������ ������� � ������ ������
	static int line_breaks_count = 0; // ���������� ��������� �� ����� ������
	static bool isBreaking = false; // ���������� �� ������ ���� �� ���
	
	time_for_printing = (double)clock_for_printing.getElapsedTime().asMicroseconds() / 1000000; // �����, ��������� � ������� ������ ���������� �������, � ��������
	if (time_for_printing >= printing_delay) {
		
		current_text += script_text[i];
		if (printing_delay > 0.03f)	text_appearence.play();
		
		// ������� �� ����� ������
		if ((line_breaks_count > symbols_count) && (script_text[i] == ' ')) {
			current_text += '\n';
			line_breaks_count = 0;
			isBreaking = true;
		}
		
		// ���������� �������
		clock_for_printing.restart();
		i += 1;
		line_breaks_count += 1;
		// ������������� ������
		if (!isBreaking) current_speech.setOrigin(Vector2f(text_speech_size * current_text.length() / 3.f, text_speech_size));
	}
	
	// ���� ���������� �������� � ������ �����������
	if (i >= script_text.length()){
		i = 0;
		line_breaks_count = 0;
		printing = isBreaking = false;
	}
}




