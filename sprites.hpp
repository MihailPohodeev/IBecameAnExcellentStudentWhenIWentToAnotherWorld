#include "inventory.hpp"

namespace victor_standard{
	
	Texture say_txt, // спрайты персонажа
	think_txt,
	sitting;
	
	IntRect say[2], // позиции анимации "разговора" на атласе
	think[4], // позиции "раздумья" на атласе
	siting_think[4], // позиции "раздумья сидя" на атсасе
	writing[4], // анимация письма
	idle_rect[2]; // позиции анимации "спокойствия" на атласе
	
	void initialization(){
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
	}
}
