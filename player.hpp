#include "sprites.hpp"

class person{
public:
	RectangleShape shape; // форма персонажа
	
	Texture say_txt, // спрайты персонажа
	think_txt,
	sitting;
	
	string name; // имя персонажа
	
	bool isSpeaking, // говорит ли персонаж
	isThinking, // думает ли персонаж
	isActive, // активен ли персонаж
	oldActive, // переменная для проверки изменения текущей активности персонажа
	anim_playing,
	isSitting, // сидит ли персонаж
	printing; // печатается ли текст
	
	Vector2f shape_origin[2], // позиции игрока для анимирования
	position;
	
	IntRect say[2], // позиции анимации "разговора" на атласе
	think[4], // позиции "раздумья" на атласе
	siting_think[4], // позиции "раздумья сидя" на атсасе
	writing[4], // анимация письма
	idle_rect[2]; // позиции анимации "спокойствия" на атласе
	
	Clock anim_clock;
	
	int anim_count, // счётчик кадров анимации
	moving_coefficient; // коэффициент смещения персонажа при анимации
	
	double alpha; // альфа-канал персонажа
	
	// анимация разговора
	void change_atlas();
	
	void update();
	void saying();
	void thinking();
	void idle();
	
	void sitting_writing(); // анимация записи
	void sitting_thinking(); // анимация размышления
	
	// установить стандартную позицию
	void setPosition(Vector2f pos);
	
	void anim_disappearing();
	void anim_appearing();
	
	person(){
		shape.setSize(Vector2f(WIDTH * 0.2f, HEIGHT * 0.65f));
		shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y));
		
		shape.setTexture(&think_txt);
		
		isSitting = false;
		
		moving_coefficient = 5;
		
		say[0] = IntRect(100, 1, 500, 1023);
		say[1] = IntRect(600, 1, 500, 1023);
		
		idle_rect[0] = IntRect(80, 10, 500, 1023);
		idle_rect[1] = IntRect(85, 10, 500, 1023);
		
		think[0] = IntRect(550, 1040, 500, 1023);
		think[1] = IntRect(1045, 1040, 500, 1023);
		think[2] = IntRect(2060, 1040, 500, 1023);
		think[3] = IntRect(1045, 1040, 500, 1023);
		
		siting_think[0] = IntRect(3, 456, 260, 208);
		siting_think[1] = IntRect(269, 456, 260, 208);
		siting_think[2] = IntRect(3, 456, 260, 208);
		siting_think[3] = IntRect(535, 456, 260, 208);
		
		writing[0] = IntRect(4, 235, 260, 208);
		writing[1] = IntRect(260, 235, 260, 208);
		writing[2] = IntRect(4, 235, 260, 208);
		writing[3] = IntRect(518, 235, 260, 208);
		
		shape_origin[0] = shape.getOrigin();
		shape_origin[1] = Vector2f(shape.getOrigin().x + moving_coefficient, shape.getOrigin().y);
		
		isThinking = isSpeaking = isActive = oldActive = anim_playing = false;
		
		alpha = 0;
	}
	
};

void person::update(){
	
	if (!isSitting){
		if (isSpeaking && printing) saying();
		else if (isThinking) thinking();
		else idle();
	}
	else {
		if(isThinking) sitting_thinking();
	}

	if (isActive != oldActive) anim_playing = true;
	
	if (anim_playing){
		if (isActive) anim_appearing();
		else anim_disappearing();
	}

	oldActive = isActive;
	
	shape.setFillColor(Color(255, 255, 255, (char)alpha));
}

// анимация разговора
void person::saying(){
	if ((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 > 0.25f) {
		anim_count++;
		anim_clock.restart();
	}
	shape.setTexture(&say_txt);
	if (anim_count > 1) anim_count = 0;
	shape.setOrigin(shape_origin[anim_count]);
	shape.setTextureRect(say[anim_count]);
}

// анимация размышления
void person::thinking(){
	if ((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 > 1.f) {
		anim_count++;
		anim_clock.restart();
	}
	if (anim_count > 3) anim_count = 0;
	shape.setTexture(&think_txt);
	shape.setTextureRect(think[anim_count]);
}

inline void person::setPosition(Vector2f pos) {
	position = pos;
	shape.setPosition(pos);
}

void person::idle(){
	if ((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 > 1.f) {
		anim_clock.restart();
	}
	shape.setTexture(&say_txt);
	shape.setTextureRect(idle_rect[(int)((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 * 2)]);
}

// анимация размышления сидя
void person::sitting_thinking(){
	if ((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 > 2.f) {
		anim_clock.restart();
	}
	
	shape.setTexture(&sitting);
	shape.setTextureRect(siting_think[(int)((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 / 0.5f)]);
	shape.setSize(Vector2f(WIDTH / 2, HEIGHT / 1.5f));	
	shape.setOrigin(Vector2f(shape.getSize().x / 3, shape.getSize().y));
}

// анимация письма
void person::sitting_writing(){
	if ((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 > 1.f) {
		anim_clock.restart();
	}
	
	shape.setTexture(&sitting);
	shape.setTextureRect(writing[(int)((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 / 0.25f)]);
	shape.setSize(Vector2f(WIDTH / 2, HEIGHT / 1.5f));	
	shape.setOrigin(Vector2f(shape.getSize().x / 3, shape.getSize().y));
	if ((int)((double)anim_clock.getElapsedTime().asMilliseconds() / 1000 / 0.25f) == 5) cout<<"Problem!"<<'\n';
}


// изменить атлас
void person::change_atlas(){
	if (isSitting){
		shape.setTexture(&sitting);
		shape.setSize(Vector2f(WIDTH / 3, HEIGHT / 3));
	}
}

// анимация исчезновения персоажа
void person::anim_disappearing(){
	if (alpha > 0){
		alpha -= anim_speed * 50 * deltaTime;
		shape.move( - anim_speed * 2 * deltaTime, 0);
	}
	else {
		alpha = 0;
		anim_playing = false;
	}
}

// анимация появления
void person::anim_appearing(){
	if (alpha < 255) alpha += anim_speed * 50 * deltaTime;
	if (position.x > shape.getPosition().x) shape.move(anim_speed * 2 * deltaTime, 0);
	if (shape.getPosition().x >= position.x && alpha >= 255){
		alpha = 255;
		anim_playing = false;
	}
}
