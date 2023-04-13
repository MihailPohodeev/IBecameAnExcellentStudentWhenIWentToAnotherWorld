#include "prepearing.hpp"

int main()
{
	setlocale(LC_ALL, "Russian");    
    main_font.loadFromFile("Fonts/Chava-Regular.ttf");
    // текстура заднего фона

	while(window.isOpen()){
//	    constructor::menu();
//	    if (to_settings) constructor::settings();
//	    if (start_game) constructor::game();
//		constructor::level2();
		constructor::game();
	}
	
    return 0;
}
