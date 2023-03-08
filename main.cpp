#include "prepearing.hpp"

int main()
{
	setlocale(LC_ALL, "Russian");    
    main_font.loadFromFile("Fonts/Chava-Regular.ttf");
    // текстура заднего фона

    constructor::menu();
    if (start_game) constructor::game();

//	constructor::game();
	
    return 0;
}
