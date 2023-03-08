#include "panel.hpp"

namespace constructor{
	
	Clock clock;
    
    void menu(){
    	
    	Text title;
    	
    	title.setString("I became an excelent student \n when I visited another world");
    	title.setCharacterSize((WIDTH + HEIGHT) / 30);
    	title.setFont(main_font);
		title.setFillColor(Color(255, 255, 255, 255));
		title.setOrigin(Vector2f(((string)title.getString().toAnsiString()).length() / 2.1f * title.getCharacterSize() / 3.f, title.getCharacterSize() / 2));
		title.setPosition(Vector2f(WIDTH / 2, HEIGHT / 6));
    	
    	Button start = Button(WIDTH / 5, HEIGHT / 10);
    	Button settings = Button(WIDTH / 5, HEIGHT / 10);
    	Button exit = Button(WIDTH / 5, HEIGHT / 10);
    	
    	start.setText("начать игру");
		settings.setText("параметры");
		exit.setText("выход");
		
		start.setTextSize((WIDTH + HEIGHT) / 2 * 0.03f);
		settings.setTextSize((WIDTH + HEIGHT) / 2 * 0.03f);
		exit.setTextSize((WIDTH + HEIGHT) / 2 * 0.03f);
		
		start.setPosition(WIDTH / 2, HEIGHT / 2);
    	settings.setPosition(WIDTH / 2, start.getPosition().y + start.getSize().y * 1.5f);
		exit.setPosition(WIDTH / 2, settings.getPosition().y + settings.getSize().y * 1.5f);
		
		Texture back_texture;
	    RectangleShape background;
	    back_texture.loadFromFile("Sprites/background.jpg");
	    if (!back_texture.loadFromFile("Sprites/background.jpg")) cout<<"background picture loading failed"<<'\n';
	    else cout<<"background picture loaded succsessfully"<<'\n';
	    
	    // масштабирование заднего фона
    	background_init(back_texture, background);
		
		bool anim = true,
		isClick = false,
		startIsClick = false;
    	
    	while (window.isOpen())
    	{
	    	Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
	        
	        clock.restart();
	        
	        mouse_position = Mouse::getPosition(window);
	        
	        if (start.onClick()) {
	        	if (!startIsClick){
		        	start_game = true;
		        	anim = !anim;
		        	startIsClick = true;
				}
			} else startIsClick = false;
	        
	        if ((settings.onClick() || Keyboard::isKeyPressed(Keyboard::Space))) {
	        	if (!isClick){
					anim = !anim;
	        		isClick = true;
	        	}
			} else isClick = false;
			
			if (exit.onClick()) window.close();
			
			disappearing(anim, start, settings, exit); 
			
			if (start_game && !exit.isActive && !exit.alpha) break;
	        
	        // отрисовка объектов
		    window.clear();
		    window.draw(background);
			start.update();
			settings.update();
			exit.update();
			window.draw(title);
	        window.display();
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
	        
    	}
	}
	
	
	
	
	void game(){
		
	panel main_bar; // панель диалогов
	inventory invent; // инвентарь
	Clock fps_clock;
	Text fps_text; // текст отображения fps
	double fps = 0;
	
	Texture back_texture;
    RectangleShape background;
    back_texture.loadFromFile("Sprites/background.jpg");
    if (!back_texture.loadFromFile("Sprites/background.jpg")) cout<<"background picture loading failed"<<'\n';
    else cout<<"background picture loaded succsessfully"<<'\n';
    
    fps_text.setFont(main_font);
    fps_text.setCharacterSize(14);
    
    // масштабирование заднего фона
    background_init(back_texture, background);
    
	while (window.isOpen())
    {
        clock.restart();
        
		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
		// получение позиции мыши
		mouse_position = Mouse::getPosition(window);
		
		main_bar.update(invent.isActive);
		invent.update();
		
        window.clear();
        window.draw(background);
		main_bar.render();
		invent.render();
		window.draw(fps_text);
        window.display();
        
        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
        
        // обновление счётчика fps
        if ((double)fps_clock.getElapsedTime().asMilliseconds() / 1000 < 1.f) fps++;
        else {
        	fps_text.setString(to_string(fps));
        	fps = 0;
        	fps_clock.restart();
		}
    }
		
	}
	
}
