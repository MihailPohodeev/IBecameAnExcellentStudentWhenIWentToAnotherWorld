#include "player.hpp"

class panel{
public:
	
	bool isActive, // ������� �� ���� � ������ ������
	left_click, // ������ �� ����� ������ ����
	printing, // ������� �� ������� ������
	thinking, // ������ �� ������ ��������
	speaking, // ������� �� ������ ��������
	APPEARING, // ��������� ���������� ������
	DISAPPEARING; // ������������ ���������� ������
	
	string current_text, script_text, // ����� �������� � ��������� ����������
	name_text; // ������ ����� �������� ���������
	
	double anim_speed, // �������� ��������������� �������� ���������� ������
	printing_delay, // �������� ����� ������� ��������
	time_for_printing; // ������ ��� ������ �������� �� ���������� ������
	
	int text_speech_size, // ������ ����������� ������
	text_name_size, // ������ ������ ����� ���������
	symbols_count; // ������������ ���������� ��������, ����������� �� ����� ������ � ���������� ����
	
	fstream script; //����� ��� ������.
	
	person *current_person, // ������� ��������, ������� ���������� �������
	character[3];// ������� �����.
	
	Clock clock_for_printing; // ������ ��� ����������� ������ ������ � ���������� ����
	
	RectangleShape panel_shape; // ����� ������
	
	Vector2f center_bar_position; // ���������� ������� ������ ��������
	Vector2f left_person_position; // ����� ������� ��� ����������
	Vector2f right_person_position; // ������ ������� ��� ����������
	
	Vector2f bar_position; // ������� ����������� ����
	Vector2f current_left_positoin; // ������� �������� ������
	Vector2f speech_position; // ������� ������ �������
	Vector2f name_position; // ������� ������ �����
	
	Text current_speech; // ��������� ����������, �������� ������� ���� ���������
	Text person_name; // �������� ����������, �������� ��� �������� ���������
	
	Color bar_color, // ���� � ������������ ���������� ������
	text_color; // ���� ������
	
//	~~~~~�������~~~~~
	void update(bool notInventary); // ����������
	void parsing(string str); // ��������� ������ �� ���������
	void render(); // ��������� �������� ����������
	
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
		center_bar_position = bar_position = Vector2f((WIDTH - panel_shape.getSize().x) / 2, (HEIGHT - panel_shape.getSize().y) - (WIDTH - panel_shape.getSize().x) / 2);
		left_person_position = current_left_positoin = Vector2f(center_bar_position.x + panel_shape.getSize().x * 0.2f, center_bar_position.y);
		panel_shape.setPosition(center_bar_position);
		speech_position = Vector2f(center_bar_position.x + panel_shape.getSize().x / 2 - text_speech_size / 2, center_bar_position.y + panel_shape.getSize().y / 2 - text_speech_size / 2);
		name_position = Vector2f(current_left_positoin.x , bar_position.y);
		
		// ��������� �����
		bar_color = Color(255, 255, 255, 0);
		text_color = Color(0, 0, 0, 0);
		
		// �������� � �������� ������ � �������
		current_speech.setFont(main_font);
		current_speech.setCharacterSize(text_speech_size);
		current_speech.setFillColor(text_color);
		person_name.setFont(main_font);
		person_name.setCharacterSize(text_name_size);
		person_name.setFillColor(text_color);
		
		// ���������� ���������� �������� �� ���� ������
		symbols_count = WIDTH * 1.5f / text_speech_size;
		// �������� ����� ������� ���� �������� �������� � ��������
		printing_delay = 0.05f;
		// �������� ��������
		anim_speed = 15;
		
		// ��������� ������ ������� �������
		current_text = name_text = "";
		
		// ��������� ��������� �������� ������� ����������
		APPEARING = DISAPPEARING = false;
		isActive = false;
		thinking = speaking = false;
		
		// �������� �������� �� ���������� ���������
		script.open("Scripts/Script.txt");
		if(!script) cout<<"Error!!! File not open."<<'\n';
		else cout<<"File opened succsessfully."<<'\n';
		
		
		// ~~~~���������_����������~~~~
		current_person = &character[0];
		
		character[0].name = "������";
		character[0].say_txt.loadFromFile("Sprites/victor_say.png");
		character[0].think_txt.loadFromFile("Sprites/victor_think.png");
		character[0].setPosition(current_left_positoin);
		
		character[1].name = "����";
		character[1].setPosition(current_left_positoin);
		
		character[2].name = "��������";
		character[2].setPosition(current_left_positoin);
	}
};

void panel::update(bool notInventary){
	// �������� �� ������� ����� ������ ����
	if (Mouse::isButtonPressed(Mouse::Left) && !notInventary){
		if (left_click){
			// ���� ���������� ���� �������
			if(isActive){
				// ���� � ������ ������ ����� �� ����������
				if (!printing){
					thinking = speaking = false;
					speech_position.x = center_bar_position.x + panel_shape.getSize().x / 2 - text_speech_size / 2;
					getline(script, script_text); // ��������� ������ �� ���������� ���������
					// ���� ������ �������, ������� ����
					if (script_text.length() == 0) {
						isActive = false;
						DISAPPEARING = true;
						return;
					}
					parsing(script_text); // ���������� ������ �� ��������� �����
					current_text = ""; // ��������� ������� ������
					printing_delay = 0.05f; // �������� ����� ������� ���� ��������� ��������
					printing = true; // ������ ������
					
					
					// ��������� � ����������� �������� ���������
//					MultiByteToWideChar()
					
					(*current_person).isActive = false;
					for(int i = 0; i < (sizeof(character)/sizeof(person)); i++){
						cout<<character[i].name<<' '<<name_text<<'\n';
						if(character[i].name == name_text){
							(*current_person) = character[i];
							(*current_person).isActive = true;
						}
					}
					cout<<'\n';
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
	} else left_click = true;
	
	if (printing) {
		if (!thinking) speaking = true;
	}	
	
	if (Mouse::isButtonPressed(Mouse::Right)){
		(*current_person).isActive = !(*current_person).isActive;
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
	
	
	// ���������� ������������� ��������� ����������.
	panel_shape.setPosition(bar_position);
	
	
	panel_shape.setFillColor(bar_color);
	current_speech.setFillColor(text_color);
	person_name.setFillColor(text_color);
	
	current_speech.setPosition(speech_position);
	person_name.setPosition(name_position);
	
	current_speech.setString(String::fromUtf8(current_text.begin(), current_text.end()));
	person_name.setString(String::fromUtf8(name_text.begin(), name_text.end()));
}

// ������� ��������� ��������.
void panel::render(){
	window.draw((*current_person).shape);
	window.draw(panel_shape);
	window.draw(current_speech);
	window.draw(person_name);
}

// ���������� ������ �� ��������� ��������� � ������ ����������� �������������
void panel::parsing(string str){
	script_text = name_text = "";
	bool name = false;
	for (int i = 0; i < str.length(); i++){
		if (str[i] == '<') {
			name = true;
			continue;
		} else if (str[i] == '>') {
			name = false;
			continue;
		}
		if (name) name_text += str[i];
		if (str[i] == '@') thinking = true;
		if ((name == false) && (str[i] != '@')) script_text += str[i];
	}
}

// �������� ������������ ������.
void panel::anim_disappearing(){
	if(bar_color.a > 0){
		// ��������� �������
		bar_position.y += anim_speed * deltaTime;
		speech_position.y += anim_speed * deltaTime;
		name_position.y += anim_speed * deltaTime;
		//��������� �����
		text_color.a = bar_color.a--;
	} else DISAPPEARING = false;
}

// �������� ��������� ������.
void panel::anim_appearing(){
	if (bar_color.a < 255){
		text_color.a = bar_color.a++;
		if (bar_position.y > center_bar_position.y){
			bar_position.y -= anim_speed * deltaTime;
			speech_position.y -= anim_speed * deltaTime;
			name_position.y -= anim_speed * deltaTime;
		}
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
		
		// ������� �� ����� ������
		if ((line_breaks_count> symbols_count) && (script_text[i] == ' ')) {
			current_text += '\n';
			line_breaks_count = 0;
			isBreaking = true;
		}
		
		// ���������� �������
		clock_for_printing.restart();
		i += 1;
		line_breaks_count += 1;
		// ������������� ������
		if (!isBreaking) current_speech.setOrigin(Vector2f(text_speech_size * current_text.length() / 5.5f, text_speech_size));
	}
	
	// ���� ���������� �������� � ������ �����������
	if (i >= script_text.length()){
		i = 0;
		line_breaks_count = 0;
		printing = isBreaking = false;
	}
}




