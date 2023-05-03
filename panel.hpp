#include "player.hpp"

class panel{
public:
	
	bool isActive, // активно ли окно в данный момент
	left_click, // нажата ли левая кнопка мыши
	printing, // запущен ли процесс печати
	thinking, // думает ли сейчас персонаж
	speaking, // говорит ли сейчас персонаж
	APPEARING, // появление диалоговой панели
	DISAPPEARING, // исчезновение диалоговой панели
	isInterrogation, // режим допроса
	act_calculating, // вычисление номера акта
	help, // подсказка игроку
	next, // закончена ли анимация набора текста
	isDark; // затемнён ли экран
	
	string current_text, script_text, // текст сценария в текстовой переменной
	name_text, // строка имени текущего персонажа
	act_number; // номер акта
	
	double anim_speed, // скорость воспроизведения анимации диалоговой панели
	printing_delay, // задержка между печатью символов
	time_for_printing, // таймер для печати символов на диалоговой панели
	alpha, // степень прозрачности панели
	dark_alpha; // степень прозрачности фона затемнения
	
	int text_speech_size, // размер диалогового текста
	text_name_size, // размер текста имени персонажа
	symbols_count, // максимальное количество символов, находящихся на одной строке в диалоговом окне
	act; // номер акта
	
	fstream script; //поток для чтения.
	
	person *current_person; // текущий персонаж, который произносит реплику
	
	Clock clock_for_printing; // таймер для равномерной печати текста в диалоговом окне
	
	SoundBuffer buffer; // звук набора текста
	Sound text_appearence;
	
	RectangleShape panel_shape; // форма панели
	RectangleShape dark_background; // форма для затемнения экрана
	RectangleShape mouse_icon; // иконка мыши для обозначения клика ЛКМ
	RectangleShape arrows; // стрелочки далее
	
	Vector2f center_bar_position; // постоянная позиция панели диалогов
	Vector2f left_person_position; // левая позиция для персонажей
	Vector2f right_person_position; // правая позиция для персонажей
	
	Vector2f bar_position; // позиция диалогового окна
	Vector2f current_left_positoin; // левая позиция персонажа
	Vector2f current_right_positoin; // правая позиция персонажа
	Vector2f speech_position; // позиция текста реплики
	Vector2f name_position; // позиция текста имени
	
	Text current_speech; // текстовая переменная, хранящая текущую речь персонажа
	Text person_name; // тектовая переменная, хранящая имя текущего персонажа
	
	Color bar_color, // цвет и прозрачность диалоговой панели
	text_color, // цвет текста
	isInterrogation_text_color; // цвет текста при допросе
	
	Texture icons; // текстура иконок
	
	IntRect mouse_sprites[2]; // позиция иконки мыши на атласе иконок
	IntRect arrows_sprites[2]; // позиция иконки стрелок на атласе иконок
	
	Clock anim_clock; // таймер для анимации
	
//	~~~~~ФУНКЦИИ~~~~~
	virtual void update(bool notInventary, person *character, int size); // обновление
	virtual void parsing(string str); // разбиение текста на подтексты
	virtual void render(); // отрисовка объектов интерфейса
	
	void anim_appearing(); // анимация появления панели диалогов
	void anim_disappearing(); // анимация исчезновения панели диалогов
	void anim_text(); // анимирование набора текста
	
	panel(){
		
		// размер текста диалогов
		text_speech_size = (HEIGHT + WIDTH) / 2 * 0.025f;
		// размер текста имени текущего персонажа
		text_name_size = (HEIGHT + WIDTH) / 2 * 0.016f;
		
		// установка размеров и позиций элементам интерфейса
		panel_shape.setSize(Vector2f(WIDTH * 0.95, HEIGHT * 0.2));
		panel_shape.setOutlineThickness(thick_size);
		panel_shape.setOutlineColor(Color(0,0,0,0));
		center_bar_position = bar_position = Vector2f((WIDTH - panel_shape.getSize().x) / 2, (HEIGHT - panel_shape.getSize().y) - (WIDTH - panel_shape.getSize().x) / 2);
		left_person_position = current_left_positoin = Vector2f(center_bar_position.x + panel_shape.getSize().x * 0.2f, center_bar_position.y);
		right_person_position = current_right_positoin = Vector2f(center_bar_position.x + panel_shape.getSize().x * 0.8f, center_bar_position.y);
		panel_shape.setPosition(center_bar_position);
		speech_position = Vector2f(center_bar_position.x + panel_shape.getSize().x / 2 - text_speech_size / 2, center_bar_position.y + panel_shape.getSize().y / 2 - text_speech_size / 2);
		name_position = Vector2f(current_left_positoin.x , bar_position.y);
		
		
		// инициализация иконок
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
		
		
		// инициализация фона затемнения.
		
		isDark = true;
		dark_alpha = 255;
		dark_background.setSize(Vector2f(WIDTH, HEIGHT));
		dark_background.setFillColor(Color(0,0,0, (char)dark_alpha));
		
		
		// установка цвета
		isInterrogation_text_color = Color(0, 180, 0, 255);
		bar_color = Color(255, 255, 255, 255);
		text_color = Color(0, 0, 0, 255);
		
		// создание и загрузка текста и шрифтов
		current_speech.setFont(main_font);
		current_speech.setCharacterSize(text_speech_size);
		current_speech.setFillColor(text_color);
		person_name.setFont(main_font);
		person_name.setCharacterSize(text_name_size);
		person_name.setFillColor(text_color);
		
		// вычисление количества символов на одну строку
		symbols_count = WIDTH * 0.82f / text_speech_size;
		// задержка между выводом двух соседних символов в секундах
		printing_delay = 0.05f;
		// скорость анимации
		anim_speed = 15;
		alpha = act = 0;
		
		// обнуление строки текущей реплики
		current_text = name_text = act_number = "";
		
		// установка начальных значений булевым переменным
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
	// проверка на нажатие левой кнопки мыши
	if ((Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0, 1)) && !notInventary){
		if (left_click){
			// если диалоговое окно открыто
			if(isActive && !DISAPPEARING){
				// если в данный момент текст не печатается
				if (!printing){
					thinking = speaking = false;
					speech_position.x = center_bar_position.x + panel_shape.getSize().x / 2 - text_speech_size / 2;
					getline(script, script_text); // получение строки из текстового документа
					// если строка нулевая, закрыть окно
					if (script_text.length() == 0) {
						(*current_person).isActive = false;
						isActive = false;
						DISAPPEARING = true;
						return;
					}
					parsing(script_text); // разделение строки на отдельные части
					current_text = ""; // обнуление текущей строки
					printing_delay = 0.05f; // задержка между выводом двух отдельных символов
					printing = true; // запуск печати
					
					// активация и деактивация текущего персонажа
					(*current_person).isActive = false;
					// выбор текущего персонажа исходя из имени текущего спикера
					for(int i = 0; i < size; i++){
						if(character[i].name == name_text){
							current_person = &character[i];
							(*current_person).isActive = true;
						}
					}
				}
				// иначе, ускорить набор текста
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
	
	// отключение подсказки в виде иконки мыши
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
	
	// вывод текста на диалоговую панель
	if (printing) anim_text();
	if (DISAPPEARING) anim_disappearing();
	if (APPEARING) anim_appearing();
	
	// действия персонажей
	if (thinking) (*current_person).isThinking = true;
	else (*current_person).isThinking = false;
	
	if (speaking) (*current_person).isSpeaking = true;
	else (*current_person).isSpeaking = false;
	(*current_person).update();
	
	// изменения фона затемнения
	
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
	
	
	// обновление характеристик элементов интерфейса.
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

// функция отрисовки объектов.
void panel::render(){
	window.draw(dark_background);
	window.draw((*current_person).shape);
	window.draw(panel_shape);
	window.draw(current_speech);
	window.draw(person_name);
	if (help) window.draw(mouse_icon);
	if (!printing && alpha > 250) window.draw(arrows);
}

// разделение строки на отдельные подстроки с учётом определённых характеристик
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

// анимация исчезновения панели.
void panel::anim_disappearing(){
	if(alpha > 0){
		// изменение позиции
		bar_position.y += anim_speed * deltaTime;
		speech_position.y += anim_speed * deltaTime;
		name_position.y += anim_speed * deltaTime;
		//изменение цвета
		alpha -= anim_speed * 15 * deltaTime;
		if (alpha < 0) alpha = 0;
	} 
	else {
		DISAPPEARING = false;
		isActive = false;
	}
}

// анимация появления панели.
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

// анимация набора текста.
void panel::anim_text(){
	static int i = 0; // индекс символа в полной строке
	static int line_breaks_count = 0; // количество переводов на новую строки
	static bool isBreaking = false; // перенесена ли строка хотя бы раз
	
	time_for_printing = (double)clock_for_printing.getElapsedTime().asMicroseconds() / 1000000; // время, прощедшее с момента печати последнего символа, в секундах
	if (time_for_printing >= printing_delay) {
		
		current_text += script_text[i];
		if (printing_delay > 0.03f)	text_appearence.play();
		
		// перевод на новую строку
		if ((line_breaks_count > symbols_count) && (script_text[i] == ' ')) {
			current_text += '\n';
			line_breaks_count = 0;
			isBreaking = true;
		}
		
		// обновление таймера
		clock_for_printing.restart();
		i += 1;
		line_breaks_count += 1;
		// центрирование текста
		if (!isBreaking) current_speech.setOrigin(Vector2f(text_speech_size * current_text.length() / 3.f, text_speech_size));
	}
	
	// если количество символов в строке закончилось
	if (i >= script_text.length()){
		i = 0;
		line_breaks_count = 0;
		printing = isBreaking = false;
	}
}




