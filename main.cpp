#include "prepearing.hpp"

int main()
{
	RectangleShape logo;
	RectangleShape background;
	logo.setSize(Vector2f(WIDTH / 3, HEIGHT / 2));
	logo.setOrigin(Vector2f(logo.getSize().x / 2, logo.getSize().y / 2));
	logo.setPosition(WIDTH / 2, HEIGHT / 2);
	background.setSize(Vector2f(WIDTH, HEIGHT));
	background.setFillColor(Color(128, 128, 128, 255));
	
	Texture mehmat;
	Texture sfedu;
	
	mehmat.loadFromFile("Sprites/mehmat_logo.png");
	sfedu.loadFromFile("Sprites/sfedu_logo.png");
	
	logo.setTexture(&sfedu);
	
	window.clear();
	window.draw(logo);
	window.display();
	
    // текстура заднего фона

	

	Sleep(2000);
	
	logo.setTexture(&mehmat);
	logo.setSize(Vector2f(WIDTH / 3, WIDTH / 5));
	logo.setOrigin(Vector2f(logo.getSize().x / 2, logo.getSize().y / 2));
	logo.setTextureRect(IntRect(0, 0, mehmat.getSize().x, mehmat.getSize().y));
	window.clear();
	window.draw(background);
	window.draw(logo);
	window.display();
	Sleep(2000);
	
	setlocale(LC_ALL, "Russian");
	main_font.loadFromFile("Fonts/Chava-Regular.ttf");
	
	while(window.isOpen()){
		view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2));
	    constructor::menu();
	  	if (level1_start) constructor::level1();
		if (level2_start) constructor::level2();
		if (level2_5_start) constructor::level2_5();
		if (level3_start) {
			panel main_bar;
			scene_menu SceneMenu;
			
			main_bar.script.open("Scripts/Script4.txt");
			
			Music music;
			music.openFromFile("Music/Halt_-This-Instant__v1__1.ogg");
			music.setVolume(50.f);
			music.setLoop(true);
			music.play();
			
			person character[3];
			
			character[0].name = "виктор";
			character[0].say_txt.loadFromFile("Sprites/victor_say.png");
			character[0].think_txt.loadFromFile("Sprites/victor_think.png");
			character[0].sitting.loadFromFile("Sprites/atlas_sitting.png");
			character[0].setPosition(main_bar.current_left_positoin);
			
			character[1].name = "эмрис";
			character[1].setPosition(main_bar.current_right_positoin);
			character[1].say_txt.loadFromFile("Sprites/Emris_say.png");
			character[1].say[0] = IntRect(230, 0, 115, 256);
			character[1].say[1] = IntRect(345, 0, 115, 256);
			character[1].idle_rect[0] = IntRect(0, 0, 115, 256);
			character[1].idle_rect[1] = IntRect(345, 0, 115, 256);
			
			character[2].name = "зендей";
			character[2].shape.setSize(Vector2f(WIDTH * 0.5f, HEIGHT * 0.7f));
			character[2].shape.setOrigin(Vector2f(character[2].shape.getSize().x / 2, character[2].shape.getSize().y));
			character[2].setPosition(main_bar.current_right_positoin);
			character[2].setPosition(main_bar.current_right_positoin);
			character[2].say_txt.loadFromFile("Sprites/Zenday_say.png");
			character[2].say[0] = IntRect(2, 2, 353, 254);
			character[2].say[1] = IntRect(355, 2, 353, 254);
			character[2].idle_rect[0] = IntRect(2, 2, 353, 254);
			character[2].idle_rect[1] = IntRect(1060, 2, 353, 254);
			character[2].shape_origin[0] = character[2].shape.getOrigin();
			character[2].shape_origin[1] = Vector2f(character[2].shape.getOrigin().x + character[2].moving_coefficient, character[2].shape.getOrigin().y);
			
			main_bar.current_person = &character[0];
			
			RectangleShape background; // форма заднего фона
			Texture texture;
			texture.loadFromFile("Sprites/hallway.png");
			
			background_init(texture, background);
			
			main_bar.isDark = false;
			
			while (window.isOpen() && level3_start)
		    {
		        constructor::clock.restart();
		        
				Event event;
		        while (window.pollEvent(event))
		        {
		            if (event.type == sf::Event::Closed)
		                window.close();
		        }
		        
		        mouse_position = Mouse::getPosition(window);
		        SceneMenu.update();
		        
		        if (!SceneMenu.isActive){
				
					constructor::background_movement(background);
			        
			        main_bar.update(false, character, 3);
			        
					if (main_bar.act == 3){
						main_bar.isActive = false;
						main_bar.DISAPPEARING = main_bar.isDark = true;
						if (main_bar.alpha < 2){
							level3_start = false;
							level5_start = true;
							break;
						}
					}
		    	}
		        
		        window.clear();
		        window.setView(view);
		        window.draw(background);
		        main_bar.render();
		        SceneMenu.render();
		        window.display();
		        
		        deltaTime = (double)constructor::clock.getElapsedTime().asMicroseconds() / 1000000;
			}
		}
		if (level5_start) constructor::level5();
		if (level5_5_start) constructor::level5_5();
		if (level6_start) constructor::level6();
		if (level7_start) constructor::level7();
//		constructor::level2();
	}
	
    return 0;
}
