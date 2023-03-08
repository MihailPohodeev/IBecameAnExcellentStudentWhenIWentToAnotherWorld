#include "panel.hpp"

namespace constructor{
	
	Clock clock;
    
    void menu(){
    	
    	Button start = Button(WIDTH / 5, HEIGHT / 10);
    	Button settings = Button(WIDTH / 5, HEIGHT / 10);
    	Button exit = Button(WIDTH / 5, HEIGHT / 10);
    	
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
	        window.display();
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
	        
    	}
	}
	
	
	
	
	void game(){
		
	panel main_bar; // панель диалогов
	inventory invent; // инвентарь
	
	Texture back_texture;
    RectangleShape background;
    back_texture.loadFromFile("Sprites/background.jpg");
    if (!back_texture.loadFromFile("Sprites/background.jpg")) cout<<"background picture loading failed"<<'\n';
    else cout<<"background picture loaded succsessfully"<<'\n';
    
    // масштабирование заднего фона
    background_init(back_texture, background);
    
	while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
		clock.restart();
		
		// получение позиции мыши
		mouse_position = Mouse::getPosition(window);
		
		main_bar.update(invent.isActive);
		invent.update();
		
		
		
		
        window.clear();
        window.draw(background);
		main_bar.render();
		invent.render();
        window.display();
        
        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
    }
		
	}
	
}
