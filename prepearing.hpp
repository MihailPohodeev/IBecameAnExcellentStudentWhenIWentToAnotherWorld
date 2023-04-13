#include "panel.hpp"

namespace constructor{
	
	Clock clock;
	void background_movement(RectangleShape &back);
    
    // ����� ����
    void menu(){
    	
    	Text title; // ��������� � ����
    	
    	title.setString("I became an excelent student \n when I visited another world");
    	title.setCharacterSize((WIDTH + HEIGHT) / 45);
    	title.setFont(main_font);
		title.setFillColor(Color(255, 255, 255, 255));
		title.setOrigin(Vector2f(((string)title.getString().toAnsiString()).length() / 2.1f * title.getCharacterSize() / 3.f, title.getCharacterSize() / 2));
		title.setOutlineColor(Color(0,0,0,255));
		title.setOutlineThickness(thick_size);
		title.setPosition(Vector2f(WIDTH / 2, HEIGHT / 6));
    	
    	Button start = Button(WIDTH / 5, HEIGHT / 10);
    	Button settings = Button(WIDTH / 5, HEIGHT / 10);
    	Button exit = Button(WIDTH / 5, HEIGHT / 10);
    	
    	start.isActive = true;
    	settings.isActive = true;
    	exit.isActive = true;
    	
    	start.setText("������ ����");
		settings.setText("���������");
		exit.setText("�����");
		
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
	    
	    // ��������������� ������� ����
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
	        
	        // ��� ������� ������ "�����"
	        if (start.onClick()) {
	        	if (!startIsClick){
	        		title.setString("��������...");
	        		title.setOrigin(Vector2f(((string)title.getString().toAnsiString()).length() * title.getCharacterSize() / 4.f, title.getCharacterSize() / 2));
		        	start_game = true;
		        	anim = !anim;
		        	startIsClick = true;
				}
			} else startIsClick = false;
	        
	        // ��� ������� ������ "���������"
	        if ((settings.onClick() || Keyboard::isKeyPressed(Keyboard::Space))) {
	        	if (!isClick){
					anim = !anim;
					to_settings = true;
	        		isClick = true;
	        	}
			} else isClick = false;
			
			// ��� ������� ������ "�����"
			if (exit.onClick()) window.close();
			
			disappearing(anim, start, settings, exit); 
			
			if(to_settings && !exit.isActive && exit.alpha == 0){
				break;
			}
			
			if (start_game && !exit.isActive && exit.alpha == 0){
				break;
			}
	        
	        // ��������� ��������
		    window.clear();
		    window.setView(view);
		    window.draw(background);
			start.update();
			settings.update();
			exit.update();
			window.draw(title);
	        window.display();
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
    	}
	}
	
	
	
	
	// ����� ��������
    void settings(){
		
		Texture back_texture;
	    RectangleShape background;
	    back_texture.loadFromFile("Sprites/background.jpg");
	    if (!back_texture.loadFromFile("Sprites/background.jpg")) cout<<"background picture loading failed"<<'\n';
	    else cout<<"background picture loaded succsessfully"<<'\n';
	    
	    Text screen_size;
		screen_size.setFont(main_font);
		screen_size.setString("���������� ������");
		screen_size.setCharacterSize((WIDTH + HEIGHT) / 50);
		screen_size.setOutlineColor(Color(0, 0, 0, 255));
		screen_size.setOutlineThickness(thick_size);
		screen_size.setPosition(Vector2f(WIDTH / 6, HEIGHT / 5));
		
		Text fullscreen;
		fullscreen.setFont(main_font);
		fullscreen.setString("������������� �����");
		fullscreen.setCharacterSize((WIDTH + HEIGHT) / 70);
		fullscreen.setOutlineColor(Color(0, 0, 0, 255));
		fullscreen.setOutlineThickness(thick_size);
		fullscreen.setPosition(Vector2f(WIDTH / 6, HEIGHT * 2 / 5));
		
		Text vsync;
		vsync.setFont(main_font);
		vsync.setString("������������ �������������");
		vsync.setCharacterSize((WIDTH + HEIGHT) / 70);
		vsync.setOutlineColor(Color(0, 0, 0, 255));
		vsync.setOutlineThickness(thick_size);
		vsync.setPosition(Vector2f(WIDTH / 6, HEIGHT * 3 / 5));
		
		Button save = Button(WIDTH / 6, HEIGHT / 12);
		Button back = Button(WIDTH / 6, HEIGHT / 12);
		save.setText("���������");
		back.setText("�����");
		save.setTextSize((WIDTH + HEIGHT) / 2 * 0.03f);
		back.setTextSize((WIDTH + HEIGHT) / 2 * 0.03f);
		save.setPosition(WIDTH * 3 / 8, HEIGHT * 9 / 10);
		back.setPosition(WIDTH  * 5 / 8, HEIGHT * 9 / 10);
		save.isActive = true;
		back.isActive = true;
		
	    check_mark isWindowed;
	    check_mark isV_sync;
	    
	    isWindowed.setPosition(Vector2f(WIDTH * 5 / 8, HEIGHT * 2 / 5));
	    isV_sync.setPosition(Vector2f(WIDTH * 5 / 8, HEIGHT * 3 / 5));
	    
	    // ���������� ���� ��� ���������� ������
	    drop_down_menu screen;
	    screen.setPosition(Vector2f(WIDTH * 5/8, HEIGHT / 5));
	    
	    // ��������������� ������� ����
    	background_init(back_texture, background);
    	
    	while (window.isOpen())
    	{
    		clock.restart();
    		
	    	Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == Event::Closed)
	                window.close();
	        }
	        
	        mouse_position = Mouse::getPosition(window);
	        
	        screen.update();
	        isWindowed.update();
	        isV_sync.update();
	        
	        if (back.onClick()){
	        	to_settings = false;
	        	break;
			}
	        
	        // ��������� ��������
		    window.clear();
		    window.setView(view);
		    window.draw(background);
		    window.draw(screen_size);
		    window.draw(fullscreen);
		    window.draw(vsync);
		    save.update();
		    back.update();
		    isWindowed.render();
		    isV_sync.render();
		    screen.render();
	        window.display();
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
    	}
	}
	
	
	
	
	// ����� �������� ����
	void game(){
		
		panel main_bar; // ������ ��������
		inventory invent; // ���������
		Clock fps_clock; // ���� ��� �������� ���������� ������ � �������
		Text fps_text; // ����� ����������� fps
		double fps = 0;
		int old_act = main_bar.act;
	
		
		Texture back_texture; // �������� ������� ���� � ���������
		Texture classroom_texture; // �������� ������� ���� � ���������
		Texture black; // �������� ������� ����
		
	    RectangleShape background; // ����� ������� ����
	    
	    // �������� �����������
	    if (!back_texture.loadFromFile("Sprites/background.jpg")) cout<<"background picture loading failed"<<'\n';
	    else cout<<"background picture loaded succsessfully"<<'\n';
	    if (!classroom_texture.loadFromFile("Sprites/classroom.jpg")) cout<<"classroom picture loading failed"<<'\n';
	    else cout<<"classroom picture loaded succsessfully"<<'\n';
	    if (!black.loadFromFile("Sprites/black.png")) cout<<"background picture loading failed"<<'\n';
	    else cout<<"background picture loaded succsessfully"<<'\n';
	    
	    fps_text.setFont(main_font);
	    fps_text.setCharacterSize(14);
	    
	    // ��������������� ������� ����
	    background_init(back_texture, background);
//	    window.setFramerateLimit(60);
	    
		while (window.isOpen())
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
			
			
			// ��������� ������� ����
			mouse_position = Mouse::getPosition(window);
			
			main_bar.update(invent.isActive);
			invent.update();
			background_movement(background);
			
			if (old_act != main_bar.act){
				// ���������� ������� ����
				main_bar.isDark = true;
				// ������������ ������ ��������
				main_bar.DISAPPEARING = true;
			}
			if ((main_bar.dark_alpha >= 254) && (main_bar.act > 0) && (!main_bar.isActive)){
				if (main_bar.act == 1) background_init(back_texture, background);
				else if (main_bar.act == 2) {
					background_init(classroom_texture, background);
					for (int i = 0; i < 3; i++) main_bar.character[i].isSitting = true;
				}
				main_bar.isDark = false;
			}
			
	        window.clear();
	        window.setView(view);
	        window.draw(background);
			main_bar.render();
			invent.render();
			window.draw(fps_text);
	        window.display();
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
	        
	        // ���������� �������� fps
	        if ((double)fps_clock.getElapsedTime().asMilliseconds() / 1000 < 1.f) fps++;
	        else {
	        	fps_text.setString(to_string(fps));
	        	fps = 0;
	        	fps_clock.restart();
			}
			old_act = main_bar.act;
	    }	
	}
	
	// ������� �������� ������� ����
	void background_movement(RectangleShape &back){
		static bool left = true;
		if (left){
			back.move(-WIDTH * 0.005f * deltaTime, 0);
			if (back.getPosition().x < (WIDTH - back.getSize().x)){
				left = false;
			}
		}
		if (!left){
			back.move(WIDTH * 0.005f * deltaTime, 0);
			if (back.getPosition().x > 0){
				left = true;
			}
		}
	}
	
	void level2(){
		
		level2_nmspc::main_player hero;
		level2_nmspc::dialog_bar bar;
		
		while (window.isOpen())
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
	        
	        hero.update();
	        bar.update();
	        
	        window.clear();
	        hero.render();
	        bar.render();
	        window.display();
	        
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
		}
		
		
		
	}
}
