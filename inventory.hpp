#include "slot.hpp"

class inventory{
	
	RectangleShape background;
	RectangleShape notification_shape;
	RectangleShape description_shape; // форма для описания предметов
	
	double anim_time, // время для анимации
	alpha, // альфа-канал заднего фона
	max_darkness; // максимальное затемнение заднего фона
	
	slot slots[8]; // массив ячеек
	
	Clock clock; // таймер
	
	Text description; // надпись "инвентарь"
	Text notif_text; // текст уведомления
	
	Button *change_category; // кнопка смены категории инвентаря "записи / предметы";
	
	enum category {RECORDS, ITEMS}; // перечислимый тип контроля текущей категории инветаря
	category current_category;
	
	object items[8]; // массив вещей
	object records[8]; // массив записей
	
	int items_count; // заполненность массива с вещами
	int records_count; // заполненность массива с записями
	int max_line_len; // максимальное количество символов в строке
	
	string cut_text(string str); // функция разбиения текста на строки
	
	bool isClickSlot[8]; // для единоразового нажатия на кнопку слота
	
public:
	
	void add_item_object(object &obj); // добавление объекта в инвентарь
	void add_record_object(object &obj); // добавление записи в инвентарь
	
	bool isActive, // активен ли сейчас интерфейс
	onPress, // для единоразового нажатие кнопки вызова интерфейса
	onClick; // для единоразового нажатия ЛКМ
	
	void trigger_notification(string str, object &obj, bool isItem); // вызвать уведомление
	void update(); // обновление
	void render(); // отрисовка элементов инвентаря
	
	inventory(){
		
		slots[0].setPosition(WIDTH * 1 / 5, HEIGHT * 0.45f);
		slots[1].setPosition(WIDTH * 2 / 5, HEIGHT * 0.45f);
		slots[2].setPosition(WIDTH * 3 / 5, HEIGHT * 0.45f);
		slots[3].setPosition(WIDTH * 4 / 5, HEIGHT * 0.45f);
		slots[4].setPosition(WIDTH * 1 / 5, HEIGHT * 0.7f);
		slots[5].setPosition(WIDTH * 2 / 5, HEIGHT * 0.7f);
		slots[6].setPosition(WIDTH * 3 / 5, HEIGHT * 0.7f);
		slots[7].setPosition(WIDTH * 4 / 5, HEIGHT * 0.7f);
		
		background.setSize(Vector2f(WIDTH, HEIGHT));
		background.setFillColor(Color(0, 0, 0, 0));
		
		notification_shape.setSize(Vector2f(WIDTH / 5, HEIGHT / 8));
		notification_shape.setOrigin(Vector2f(notification_shape.getSize().x, 0));
		notification_shape.setFillColor(Color(255, 255, 255, 200));
		notification_shape.setOutlineThickness(thick_size);
		notification_shape.setOutlineColor(Color(0,0,0,200));
		notification_shape.setPosition(WIDTH + notification_shape.getSize().x + thick_size * 1.0001f, notification_shape.getSize().y * 1.5f);
		
		description_shape.setSize(Vector2f(WIDTH * .72f, HEIGHT * 0.20f));
		description_shape.setOrigin(Vector2f(description_shape.getSize().x / 2, description_shape.getSize().y / 2));
		description_shape.setPosition(WIDTH / 2, description_shape.getSize().y * 0.8f);
		description_shape.setOutlineThickness(thick_size);
		description_shape.setFillColor(Color(255, 255, 255, 0));
		description_shape.setOutlineColor(Color(0, 0, 0, 0));
		
		
		alpha = 0;
		max_darkness = 200;
		items_count = records_count = 0;
		max_line_len = WIDTH / 16;
		
		isActive = false;
		onPress = onClick = false;
		
		current_category = ITEMS;
		change_category = new Button(WIDTH * 0.25f, HEIGHT * 0.1f);
		(*change_category).setPosition(WIDTH / 2, HEIGHT - (*change_category).getSize().y);
		(*change_category).setText("записи");
		(*change_category).setTextSize((WIDTH + HEIGHT) / 2 * 0.03f);
		(*change_category).isActive = false;
		
		description.setFont(main_font);
		description.setFillColor(Color(0, 0, 0, 0));
		description.setCharacterSize((HEIGHT + WIDTH) / 80);
		description.setString("пусто");
		description.setPosition(Vector2f(description_shape.getPosition().x * 0.3f, description_shape.getPosition().y * 0.6f));
		
		notif_text.setFont(main_font);
		notif_text.setFillColor(Color(0, 0, 0, 255));
		notif_text.setCharacterSize((HEIGHT + WIDTH) / 2 * 0.015f);
		notif_text.setPosition(WIDTH * 1.01f, notification_shape.getSize().y / 2 + notification_shape.getPosition().y);
		
	}
};

// обновление
void inventory::update(){
	
	anim_time = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
	
	// активация инвентаря по нажатию кнопки "E"
	if(Keyboard::isKeyPressed(Keyboard::Q) || Joystick::isButtonPressed(0, 0)){
		if(!onPress){
			isActive = !isActive;
			clock.restart();
			onPress = true;
		}
	} else onPress = false;
	
	if(isActive){
		if (alpha < max_darkness){
			alpha += anim_speed * anim_time;
		} 
		else{
			alpha = max_darkness;
			(*change_category).isActive = true;
			for (char i = 0; i < 8; i++) slots[i].isActive = true;
		}
		
		if ((*change_category).onClick()){
			if(!onClick){
				if (current_category == ITEMS){
					current_category = RECORDS;
					(*change_category).setText("предметы");
					cout<<"items\n";
				}
				else{
					current_category = ITEMS;
					(*change_category).setText("записи");
					cout<<"records\n";
				}
				onClick = true;
			}
		}
		else onClick = false;
		
	}
	else {
		(*change_category).isActive = false;
		if (alpha > 0){
			for (char i = 0; i < 8; i++) slots[i].isActive = false;
			alpha -= anim_speed * anim_time;
		} else alpha = 0;
	}	
	
	for (char i = 0; i < 8; i++){
		slots[i].update();
		if (slots[i].onClick()){
			if (!isClickSlot[i]){
				description.setString(cut_text((current_category == RECORDS) ? records[i].description : items[i].description));
				cout<<"Da"<<'\n';
			}
			isClickSlot[i] = true;
		}
		else isClickSlot[i] = false;
	}
	
	background.setFillColor(Color(0, 0, 0, (char)alpha));
	
	description_shape.setFillColor(Color(255, 255, 255, (char)255 * alpha / max_darkness));
	description_shape.setOutlineColor(Color(0, 0, 0, (char)255 * alpha / max_darkness));
	
	description.setFillColor(Color(0, 0, 0, (char)255 * alpha / max_darkness));
}

string inventory::cut_text(string str){
	static int line_len = 0;
	string result = "";
	for(int i = 0; i < str.length(); i++){
		result += str[i];
		if (line_len > max_line_len && str[i] == ' '){
			cout<<line_len<<'\n';
			result += '\n';
			line_len = 0;
		}
		line_len++;
	}
	line_len = 0;
	return result;
}

// анимация уведомления
void inventory::trigger_notification(string str, object &obj, bool isItem){
	static string old_str = "";
	static Clock timer;
	double time_count = (double)timer.getElapsedTime().asMilliseconds() / 1000;
	
	if(str != old_str){
		if (isItem) add_item_object(obj);
		else add_record_object(obj);
		old_str = str;
		timer.restart();
		string new_str = "";
		int new_line = (int)(notification_shape.getSize().x * 0.8f / (notif_text.getCharacterSize() * 1.5f));
		int index = 0;
		for(int i = 0; i < str.length(); i++){
			if ((index >= new_line) && (str[i] == ' ')){
				new_str += '\n';
				index = 0;
			}
			else{
				new_str += str[i];
				index++;
			}
		}
		notif_text.setPosition(notif_text.getPosition().x, notification_shape.getPosition().y + notification_shape.getSize().y / 2 - (notif_text.getCharacterSize() * 1.5f));
		notif_text.setString(new_str);
	}
	
	if (time_count < 8){
		if (notification_shape.getPosition().x + thick_size > WIDTH){
			notification_shape.move(-anim_speed * 15 * deltaTime, 0);
			notif_text.move(-anim_speed * 15 * deltaTime, 0);
			if (notification_shape.getPosition().x + thick_size < WIDTH) notification_shape.setPosition(WIDTH - thick_size * 1.0001f, notification_shape.getPosition().y);
		}
		
	}
	else{
		if (notification_shape.getPosition().x < WIDTH + notification_shape.getSize().x + thick_size){
			notification_shape.move(anim_speed * 15 * deltaTime, 0);
			notif_text.move(anim_speed * 15 * deltaTime, 0);
			if (notification_shape.getPosition().x > WIDTH + notification_shape.getSize().x + thick_size) notification_shape.setPosition(WIDTH + notification_shape.getSize().x + thick_size * 1.0001f, notification_shape.getPosition().y);
		}
	}		
}

void inventory::add_item_object(object &obj){
	obj.shape.setPosition(slots[records_count].getPosition());
	items[items_count] = obj;
	items_count++;
}

void inventory::add_record_object(object &obj){
	obj.shape.setPosition(slots[records_count].getPosition());
	records[records_count] = obj;
	records_count++;
}

// отрисовка элементов меню
void inventory::render(){
//	window.draw(notification_shape);
//	window.draw(notif_text);
	window.draw(background);
	window.draw(description_shape);
	for (int i = 0; i < 8; i++){
		slots[i].render();
		if (alpha > max_darkness * 0.8f){
			if(i < records_count && current_category == RECORDS) window.draw(records[i].shape);
			if(i < items_count && current_category == ITEMS) window.draw(items[i].shape);
		}
	}
	window.draw(description);
	(*change_category).update();
}
























