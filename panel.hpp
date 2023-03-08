#include "player.hpp"

class panel{
public:
	
	bool isActive, // активно ли окно в данный момент
	left_click, // нажата ли левая кнопка мыши
	printing, // запущен ли процесс печати
	thinking, // думает ли сейчас персонаж
	speaking, // говорит ли сейчас персонаж
	APPEARING, // появление диалоговой панели
	DISAPPEARING; // исчезновение диалоговой панели
	
	string current_text, script_text, // текст сценария в текстовой переменной
	name_text; // строка имени текущего персонажа
	
	double anim_speed, // скорость воспроизведения анимации диалоговой панели
	printing_delay, // задержка между печатью символов
	time_for_printing; // таймер для печати символов на диалоговой панели
	
	int text_speech_size, // размер диалогового текста
	text_name_size, // размер текста имени персонажа
	symbols_count; // максимальное количество символов, находящихся на одной строке в диалоговом окне
	
	fstream script; //поток для чтения.
	
	person *current_person, // текущий персонаж, который произносит реплику
	character[3];// главный герой.
	
	Clock clock_for_printing; // таймер для равномерной печати текста в диалоговом окне
	
	RectangleShape panel_shape; // форма панели
	
	Vector2f center_bar_position; // постоянная позиция панели диалогов
	Vector2f left_person_position; // левая позиция для персонажей
	Vector2f right_person_position; // правая позиция для персонажей
	
	Vector2f bar_position; // позиция диалогового окна
	Vector2f current_left_positoin; // позиция главного игрока
	Vector2f speech_position; // позиция текста реплики
	Vector2f name_position; // позиция текста имени
	
	Text current_speech; // текстовая переменная, хранящая текущую речь персонажа
	Text person_name; // тектовая переменная, хранящая имя текущего персонажа
	
	Color bar_color, // цвет и прозрачность диалоговой панели
	text_color; // цвет текста
	
//	~~~~~ФУНКЦИИ~~~~~
	void update(bool notInventary); // обновление
	void parsing(string str); // разбиение текста на подтексты
	void render(); // отрисовка объектов интерфейса
	
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
		center_bar_position = bar_position = Vector2f((WIDTH - panel_shape.getSize().x) / 2, (HEIGHT - panel_shape.getSize().y) - (WIDTH - panel_shape.getSize().x) / 2);
		left_person_position = current_left_positoin = Vector2f(center_bar_position.x + panel_shape.getSize().x * 0.2f, center_bar_position.y);
		panel_shape.setPosition(center_bar_position);
		speech_position = Vector2f(center_bar_position.x + panel_shape.getSize().x / 2 - text_speech_size / 2, center_bar_position.y + panel_shape.getSize().y / 2 - text_speech_size / 2);
		name_position = Vector2f(current_left_positoin.x , bar_position.y);
		
		// установка цвета
		bar_color = Color(255, 255, 255, 0);
		text_color = Color(0, 0, 0, 0);
		
		// создание и загрузка текста и шрифтов
		current_speech.setFont(main_font);
		current_speech.setCharacterSize(text_speech_size);
		current_speech.setFillColor(text_color);
		person_name.setFont(main_font);
		person_name.setCharacterSize(text_name_size);
		person_name.setFillColor(text_color);
		
		// вычисление количества символов на одну строку
		symbols_count = WIDTH * 1.5f / text_speech_size;
		// задержка между выводом двух соседних символов в секундах
		printing_delay = 0.05f;
		// скорость анимации
		anim_speed = 15;
		
		// обнуление строки текущей реплики
		current_text = name_text = "";
		
		// установка начальных значений булевым переменным
		APPEARING = DISAPPEARING = false;
		isActive = false;
		thinking = speaking = false;
		
		// открытие сценария из текстового документа
		script.open("Scripts/Script.txt");
		if(!script) cout<<"Error!!! File not open."<<'\n';
		else cout<<"File opened succsessfully."<<'\n';
		
		
		// ~~~~НАСТРОЙКИ_ПЕРСОНАЖЕЙ~~~~
		current_person = &character[0];
		
		character[0].name = "виктор";
		character[0].say_txt.loadFromFile("Sprites/victor_say.png");
		character[0].think_txt.loadFromFile("Sprites/victor_think.png");
		character[0].setPosition(current_left_positoin);
		
		character[1].name = "дима";
		character[1].setPosition(current_left_positoin);
		
		character[2].name = "элеонора";
		character[2].setPosition(current_left_positoin);
	}
};

void panel::update(bool notInventary){
	// проверка на нажатие левой кнопки мыши
	if (Mouse::isButtonPressed(Mouse::Left) && !notInventary){
		if (left_click){
			// если диалоговое окно открыто
			if(isActive){
				// если в данный момент текст не печатается
				if (!printing){
					thinking = speaking = false;
					speech_position.x = center_bar_position.x + panel_shape.getSize().x / 2 - text_speech_size / 2;
					getline(script, script_text); // получение строки из текстового документа
					// если строка нулевая, закрыть окно
					if (script_text.length() == 0) {
						isActive = false;
						DISAPPEARING = true;
						return;
					}
					parsing(script_text); // разделение строки на отдельные части
					current_text = ""; // обнуление текущей строки
					printing_delay = 0.05f; // задержка между выводом двух отдельных символов
					printing = true; // запуск печати
					
					
					// активация и деактивация текущего персонажа
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
	} else left_click = true;
	
	if (printing) {
		if (!thinking) speaking = true;
	}	
	
	if (Mouse::isButtonPressed(Mouse::Right)){
		(*current_person).isActive = !(*current_person).isActive;
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
	
	
	// обновление характеристик элементов интерфейса.
	panel_shape.setPosition(bar_position);
	
	
	panel_shape.setFillColor(bar_color);
	current_speech.setFillColor(text_color);
	person_name.setFillColor(text_color);
	
	current_speech.setPosition(speech_position);
	person_name.setPosition(name_position);
	
	current_speech.setString(String::fromUtf8(current_text.begin(), current_text.end()));
	person_name.setString(String::fromUtf8(name_text.begin(), name_text.end()));
}

// функция отрисовки объектов.
void panel::render(){
	window.draw((*current_person).shape);
	window.draw(panel_shape);
	window.draw(current_speech);
	window.draw(person_name);
}

// разделение строки на отдельные подстроки с учётом определённых характеристик
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

// анимация исчезновения панели.
void panel::anim_disappearing(){
	if(bar_color.a > 0){
		// изменение позиции
		bar_position.y += anim_speed * deltaTime;
		speech_position.y += anim_speed * deltaTime;
		name_position.y += anim_speed * deltaTime;
		//изменение цвета
		text_color.a = bar_color.a--;
	} else DISAPPEARING = false;
}

// анимация появления панели.
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

// анимация набора текста.
void panel::anim_text(){
	static int i = 0; // индекс символа в полной строке
	static int line_breaks_count = 0; // количество переводов на новую строки
	static bool isBreaking = false; // перенесена ли строка хотя бы раз
	
	time_for_printing = (double)clock_for_printing.getElapsedTime().asMicroseconds() / 1000000; // время, прощедшее с момента печати последнего символа, в секундах
	if (time_for_printing >= printing_delay) {
		
		current_text += script_text[i];
		
		// перевод на новую строку
		if ((line_breaks_count> symbols_count) && (script_text[i] == ' ')) {
			current_text += '\n';
			line_breaks_count = 0;
			isBreaking = true;
		}
		
		// обновление таймера
		clock_for_printing.restart();
		i += 1;
		line_breaks_count += 1;
		// центрирование текста
		if (!isBreaking) current_speech.setOrigin(Vector2f(text_speech_size * current_text.length() / 5.5f, text_speech_size));
	}
	
	// если количество символов в строке закончилось
	if (i >= script_text.length()){
		i = 0;
		line_breaks_count = 0;
		printing = isBreaking = false;
	}
}




