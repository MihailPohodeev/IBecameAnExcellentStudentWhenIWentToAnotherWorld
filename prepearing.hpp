#include "interrogation.hpp"

namespace constructor{
	
	Clock clock;
	void background_movement(RectangleShape &back);
    
    // метод меню
    void menu(){
    	
    	Music music; // музыка
    	music.openFromFile("Music/Friendly_Melody.ogg");
    	
    	Text title; // заголовок в меню
    	
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
	    
	    // масштабирование заднего фона
    	background_init(back_texture, background);
		
		bool anim = true,
		isClick = false,
		startIsClick = false;
		
		music.setLoop(true);
		music.play();
		
		float volume = 100.f; // громкость музыки
    	
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
	        
	        // при нажатии кнопки "старт"
	        if (start.onClick()) {
	        	if (!startIsClick){
	        		title.setString("ЗАГРУЗКА...");
	        		title.setOrigin(Vector2f(((string)title.getString().toAnsiString()).length() * title.getCharacterSize() / 4.f, title.getCharacterSize() / 2));
		        	level1_start = true;
		        	anim = !anim;
		        	startIsClick = true;
				}
			} else startIsClick = false;
	        
	        // при нажатии кнопки "настройки"
	        if ((settings.onClick() || Keyboard::isKeyPressed(Keyboard::Space))) {
	        	if (!isClick){
					anim = !anim;
					to_settings = true;
	        		isClick = true;
	        	}
			} else isClick = false;
			
			// при нажатии кнопки "выход"
			if (exit.onClick()) window.close();
			
			disappearing(anim, start, settings, exit); 
			
			if(to_settings && !exit.isActive && exit.alpha == 0){
				break;
			}
			
			if (level1_start && !exit.isActive && exit.alpha == 0){
				music.setVolume(volume);
				volume -= anim_speed * 5 * deltaTime;
				if (volume <= 0) break;
			}
	        
	        // отрисовка объектов
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
	
	
	
	
	// метод настроек
    void settings(){
		
		Texture back_texture;
	    RectangleShape background;
	    back_texture.loadFromFile("Sprites/background.jpg");
	    if (!back_texture.loadFromFile("Sprites/background.jpg")) cout<<"background picture loading failed"<<'\n';
	    else cout<<"background picture loaded succsessfully"<<'\n';
	    
	    Text screen_size;
		screen_size.setFont(main_font);
		screen_size.setString("РАЗРЕШЕНИЕ ЭКРАНА");
		screen_size.setCharacterSize((WIDTH + HEIGHT) / 50);
		screen_size.setOutlineColor(Color(0, 0, 0, 255));
		screen_size.setOutlineThickness(thick_size);
		screen_size.setPosition(Vector2f(WIDTH / 6, HEIGHT / 5));
		
		Text fullscreen;
		fullscreen.setFont(main_font);
		fullscreen.setString("полноэкранный режим");
		fullscreen.setCharacterSize((WIDTH + HEIGHT) / 70);
		fullscreen.setOutlineColor(Color(0, 0, 0, 255));
		fullscreen.setOutlineThickness(thick_size);
		fullscreen.setPosition(Vector2f(WIDTH / 6, HEIGHT * 2 / 5));
		
		Text vsync;
		vsync.setFont(main_font);
		vsync.setString("вертикальная синхронизация");
		vsync.setCharacterSize((WIDTH + HEIGHT) / 70);
		vsync.setOutlineColor(Color(0, 0, 0, 255));
		vsync.setOutlineThickness(thick_size);
		vsync.setPosition(Vector2f(WIDTH / 6, HEIGHT * 3 / 5));
		
		Button save = Button(WIDTH / 6, HEIGHT / 12);
		Button back = Button(WIDTH / 6, HEIGHT / 12);
		save.setText("сохранить");
		back.setText("назад");
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
	    
	    // выпадающее меню для разрешения экрана
	    drop_down_menu screen;
	    screen.setPosition(Vector2f(WIDTH * 5 / 8, HEIGHT / 5));
	    
	    // масштабирование заднего фона
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
	        
	        // отрисовка объектов
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
	
	
	
	
	// метод процесса игры
	void level1(){
		
		panel main_bar; // панель диалогов
		Clock fps_clock; // часы для просчёта количества кадров в секунду
		Clock final_darkness; // таймер для затемнения
		Text fps_text; // текст отображения fps
		double fps = 0;
		double alpha = 0; // степень прозрачности фона затемнения
		int old_act = main_bar.act;
		
		main_bar.script.open("Scripts/Script.txt");
	
		person character[4];
			
		RectangleShape dark; // затемнение экрана
		dark.setSize(Vector2f(WIDTH, HEIGHT));
		dark.setPosition(0, 0);
		dark.setFillColor(Color(0, 0, 0, 0));
		
		Music music;
		music.openFromFile("Music/A_Likely_Story.ogg");
		float volume = 10.f;
		
		character[0].name = "виктор";
		character[0].say_txt.loadFromFile("Sprites/victor_say.png");
		character[0].think_txt.loadFromFile("Sprites/victor_think.png");
		character[0].sitting.loadFromFile("Sprites/atlas_sitting.png");
		character[0].setPosition(main_bar.current_left_positoin);
		
		character[1].name = "дима";
		character[1].shape.setSize(Vector2f(WIDTH * 0.25f, HEIGHT * 0.65f));
		character[1].setPosition(main_bar.current_right_positoin);
		character[1].say_txt.loadFromFile("Sprites/Dimass_say.png");
		character[1].say[0] = IntRect(13, 0, 160, 256);
		character[1].say[1] = IntRect(333, 0, 160, 256);
		character[1].idle_rect[0] = IntRect(13, 0, 160, 256);
		character[1].idle_rect[1] = IntRect(493, 0, 160, 256);
		
		character[2].name = "элеонора";
		character[2].shape.setSize(Vector2f(WIDTH * 0.28f, HEIGHT * 0.6f));
		character[2].setPosition(main_bar.current_right_positoin);
		character[2].setOrigin(Vector2f(character[2].shape.getSize().x / 2, character[2].shape.getSize().y));
		character[2].say_txt.loadFromFile("Sprites/Eleonora_say.png");
		character[2].say[0] = IntRect(0, 0, 220, 256);
		character[2].say[1] = IntRect(220, 0, 220, 256);
		character[2].idle_rect[0] = IntRect(0, 0, 220, 256);
		character[2].idle_rect[1] = IntRect(685, 0, 220, 256);
		
		character[3].name = "преподаватель";
		character[3].setPosition(main_bar.current_right_positoin);
		
		(main_bar.current_person) = &character[0];
		
		
		Texture back_texture; // текстура заднего фона в корридоре
		Texture classroom_texture; // текстура заднего фона в аудитории
		Texture black; // текстура чёрного фона
		
	    RectangleShape background; // форма заднего фона
	    
	    // загрузка изображений
	    if (!back_texture.loadFromFile("Sprites/background.jpg")) cout<<"background picture loading failed"<<'\n';
	    else cout<<"background picture loaded succsessfully"<<'\n';
	    if (!classroom_texture.loadFromFile("Sprites/classroom.jpg")) cout<<"classroom picture loading failed"<<'\n';
	    else cout<<"classroom picture loaded succsessfully"<<'\n';
	    if (!black.loadFromFile("Sprites/black.png")) cout<<"background picture loading failed"<<'\n';
	    else cout<<"background picture loaded succsessfully"<<'\n';
	    
	    fps_text.setFont(main_font);
	    fps_text.setCharacterSize(14);
	    
	    // масштабирование заднего фона
	    background_init(black, background);
//	    window.setFramerateLimit(60);
	    
	    music.setLoop(true);
	    music.play();
	    music.setVolume(10.f);
	    
		while (window.isOpen() && level1_start)
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
			
			main_bar.update(false, character, 4);
			background_movement(background);
			
			
			if ((main_bar.dark_alpha >= 254) && (main_bar.act > 0) && (!main_bar.isActive)){
				if (main_bar.act == 1) background_init(back_texture, background);
				else if (main_bar.act == 2) {
					background_init(classroom_texture, background);
					for (int i = 0; i < 3; i++) character[i].isSitting = true;
				}
				main_bar.isDark = false;
			}
			
			if (main_bar.act == 3){				
				if (alpha < 253.f){
					volume -= anim_speed * 2 * deltaTime;
					alpha += anim_speed * 5 * deltaTime;
					dark.setFillColor(Color(0, 0, 0, char(alpha)));
					final_darkness.restart();
					if(alpha > 254) alpha = 255;
				}
				else{
					if((int)(((double)final_darkness.getElapsedTime().asMilliseconds() / 1000) / 0.25f) % 2 == 0){
						dark.setFillColor(Color(0, 0, 0, 255));
					}
					else{
						dark.setFillColor(Color(255, 255, 255, 255));
					}
					if ((double)final_darkness.getElapsedTime().asMilliseconds() / 1000 > 1 && volume <= 0){
						level1_start = false;
						level2_start = true;
					}
				}
			}
			else {
				if (old_act != main_bar.act){
					// затемнение заднего фона
					main_bar.isDark = true;
					// исчезновение панели диалогов
					main_bar.DISAPPEARING = true;
				}
			}
			
			music.setVolume(volume);
			
	        window.clear();
	        window.setView(view);
	        window.draw(background);
			main_bar.render();
			window.draw(dark);
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
			old_act = main_bar.act;
	    }	
	}
	
	// плавное движение заднего фона
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
	
	
	
	
	
	// УРОВЕНЬ 2
	void level2(){
		
		Music music;
		music.openFromFile("Music/I-Am-Okay-With-What-I-Am-Doing.ogg");
		music.setVolume(10.f);
		music.setLoop(true);
		music.play();
		
		// текущий акт
		current_act = 0;
		
		// таймер событый
		Clock event_timer;
		double event_time;
		double alpha = 0; // степень затемнения экрана
		
		// текст подсказок
		string hint_text = "";
		int text_size = (HEIGHT + WIDTH) / 2 * 0.025f;
		Text hint;
		hint.setFont(main_font);
		hint.setCharacterSize(text_size);
		hint.setString(hint_text);
		hint.setFillColor(Color(255, 255, 255, 255));
		hint.setOutlineThickness(thick_size / 2);
		hint.setOutlineColor(Color(0, 0, 0, 255));
		hint.setPosition(WIDTH / 2 - hint_text.length() * (HEIGHT + WIDTH) / 4 * 0.018f, HEIGHT - (HEIGHT + WIDTH) / 2 * 0.04f);
		
		// триггер удостоверения личности
		trigger identity_card = trigger(WIDTH / 8, HEIGHT / 10);
		identity_card.setPosition(WIDTH * 0.8f, HEIGHT * 0.6f);
		
		trigger window_view = trigger(WIDTH / 4, HEIGHT / 10);
		window_view.setPosition(WIDTH / 2, HEIGHT / 2);
		
		// объект персонажа и диалоговой панели
		level2_nmspc::main_player hero; // персонаж
		level2_nmspc::dialog_bar bar; // диалоговое окно
		level2_nmspc::npc emris; // нпс
		inventory _inventory; // инвентарь
		scene_menu sceneMenu; // меню
		
		emris.setPosition(Vector2f(WIDTH / 2, HEIGHT * 3 / 4));
		
		hero.movement = false;
		bool cutscene = false;
		
		// настройка заднего фона
		RectangleShape background; // форма заднего фона
		RectangleShape dark_front; // форма для затемнения экрана
		
		dark_front.setSize(Vector2f(WIDTH, HEIGHT * 1.5f));
		dark_front.setPosition(0, 0);
		dark_front.setFillColor(Color(0, 0, 0, 0));
		
		Texture background_image;
		Texture window_view_image;
		
		background_image.loadFromFile("Sprites/background2.jpg");
		window_view_image.loadFromFile("Sprites/window_view.png");
		
		background_init(background_image, background);
		
		object card;// объект удостоверения личности
		card.description = "Удостоверение личности, кого-то похожего на вампира. В графе \"Имя\" написано \"Вит Калиновский\"";
		
		
		while (window.isOpen() && level2_start)
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
	        
	        // получить координаты мыши
	        mouse_position = Vector2i(Mouse::getPosition(window).x + view.getCenter().x - WIDTH / 2, Mouse::getPosition(window).y + view.getCenter().y - HEIGHT / 2);
	        event_time = (double)event_timer.getElapsedTime().asMilliseconds() / 1000;
	        
	        if (!hero.stand && (Mouse::isButtonPressed(Mouse::Left)) || Joystick::isButtonPressed(0, 1)){
	        	hero.anim_timer.restart();
	        	hero.stand = true;
			}
			
			
			
			// ОБРАБОТКА СОБЫТИЙ
			if (hero.standing && hero.stand && (bar.script_act == 0)){
				bar.isActive = true;
				event_timer.restart();
			}
			// акт 1
			else if (bar.script_act == 1){

				if ((event_time < 5.f) && current_act == 0){
					hint_text = "для перемещения персонажа используйте клавиши W,A,S,D.";
					hint.setString(hint_text);
					hint.setPosition(WIDTH / 2 - hint_text.length() * (HEIGHT + WIDTH) / 4 * 0.018f, HEIGHT - (HEIGHT + WIDTH) / 2 * 0.04f);
				}
				else{
					hint.setString("");
				}
				
				if (identity_card.intersects(hero.collision_rect) && (current_act == 0)){
					hint_text = "для взаимодействия нажмите клавишу E";
					hint.setString(hint_text);
					hint.setPosition(WIDTH / 2 - hint_text.length() * (HEIGHT + WIDTH) / 4 * 0.018f, HEIGHT - (HEIGHT + WIDTH) / 2 * 0.04f);
					if(Keyboard::isKeyPressed(Keyboard::E) || Joystick::isButtonPressed(0, 1)){
						current_act = 1;
					}
				}
				
				hero.movement = true;
				if(current_act == 1) {
					bar.isActive = true;
					hero.movement = false;
					event_timer.restart();
				}
				else {
					bar.isActive = false;
				}
				
			}
			// акт 2
			else if (bar.script_act == 2){
				
				_inventory.trigger_notification("Добавлено: Удостоверение личности", card, 1);
				
				if ((event_time < 5.f)){
					hint_text = "чтобы открыть инвентарь, нажмите клавишу Q.";
					hint.setString(hint_text);
					hint.setPosition(WIDTH / 2 - hint_text.length() * (HEIGHT + WIDTH) / 4 * 0.018f, HEIGHT - (HEIGHT + WIDTH) / 2 * 0.04f);
				}
				else hint.setString("");
				
				if (window_view.intersects(hero.collision_rect) && (current_act == 1)){
					hint_text = "для взаимодействия нажмите клавишу E";
					hint.setString(hint_text);
					hint.setPosition(WIDTH / 2 - hint_text.length() * (HEIGHT + WIDTH) / 4 * 0.018f, HEIGHT - (HEIGHT + WIDTH) / 2 * 0.04f);
					
					if (Keyboard::isKeyPressed(Keyboard::E) || Joystick::isButtonPressed(0, 1)){
						current_act = 2;
					}
				}
				
				hero.movement = true;
				if(current_act == 2) {
					bar.isActive = true;
					hero.movement = false;
				}
				else {
					bar.isActive = false;
				}
			}
			
			// акт 3
			else if (bar.script_act == 3){
				if (!cutscene && alpha < 255) {
					alpha += anim_speed * 25 * deltaTime;
					bar.isActive = false;
					if (alpha >= 255){
						alpha = 255;
						background_init(window_view_image, background);
						cutscene = true;
					}
				}
				else {
					alpha -= anim_speed *  25 * deltaTime;
					if (alpha <= 0){
						alpha = 0;
						bar.isActive = true;
					}
				}
				
				hero.movement = false;
			}
			
			// акт 4
			else if (bar.script_act == 4){
				
				if (cutscene && alpha < 255) {
					alpha += anim_speed * 25 * deltaTime;
					bar.isActive = false;
					if (alpha >= 255){
						alpha = 255;
						background_init(background_image, background);
						cutscene = false;
					}
				}
				else {
					alpha -= anim_speed *  25 * deltaTime;
					if (alpha <= 0){
						alpha = 0;
						bar.isActive = true;
					}
				}
			}
			
			// акт 5
			else if (bar.script_act == 5){
				
				if (alpha < 255){
					alpha += anim_speed *  25 * deltaTime;
					if (alpha >= 255){
						level2_start = false;
						level2_5_start = true;
					}
				}
				
			}
			
			
			dark_front.setFillColor(Color(0, 0, 0, (char)alpha));
			
			
			
			if(!sceneMenu.isActive){
				hero.update();
		        bar.update();
		        _inventory.update();
		        if(bar.isActive) _inventory.isActive = false;
	    	}
	    	else {
	    		_inventory.isActive = false;
			}
	    	
	    	sceneMenu.update();
	        
	        
	        window.clear();
	        window.setView(view);
	        window.draw(background);
	        if(!cutscene) {
				hero.render();
//				emris.render();
			}
	        window.draw(hint);
	        bar.render();
			identity_card.render();
			window_view.render();
			_inventory.render();
			window.draw(dark_front);
	        sceneMenu.render();
	        window.display();
	        

	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
		}
	}
	
	// УРОВЕНЬ 2.5
	void level2_5(){
		
		scene_menu sceneMenu;
		
		panel main_bar;
		
		main_bar.script.open("Scripts/Script3.txt");
		
		person character[2];
		
		character[0].name = "виктор";
		character[0].say_txt.loadFromFile("Sprites/victor_say.png");
		character[0].think_txt.loadFromFile("Sprites/victor_think.png");
		character[0].sitting.loadFromFile("Sprites/atlas_sitting.png");
		character[0].setPosition(main_bar.current_left_positoin);
		
		character[1].name = "эмрис";
		character[1].setPosition(main_bar.current_right_positoin);
		character[1].say_txt.loadFromFile("Sprites/dmitriy_atlas.png");
		character[1].say[0] = IntRect(42, 11, 120, 245);
		character[1].say[1] = IntRect(182, 11, 120, 245);
		character[1].idle_rect[0] = IntRect(332, 11, 120, 245);
		character[1].idle_rect[1] = IntRect(42, 11, 120, 245);
		
		view.setCenter(Vector2f(WIDTH / 2, HEIGHT / 2));
//		main_bar.isActive = false;
//		main_bar.APPEARING = true;
		
		main_bar.current_person = &character[0];
		
		while (window.isOpen() && level2_5_start)
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
	        
	        mouse_position = Vector2i(Mouse::getPosition(window).x + view.getCenter().x - WIDTH / 2, Mouse::getPosition(window).y + view.getCenter().y - HEIGHT / 2);
	        
	        sceneMenu.update();
	        
	        if (!sceneMenu.isActive){
	        	main_bar.update(false, character, 2);
	    	}
	        
	        if (main_bar.act == 1){
	        	main_bar.isActive = false;
	        	main_bar.DISAPPEARING = true;
	        	if (main_bar.alpha < 5){
	        		level2_5_start = false;
	        		level3_start = true;
				}
			}
	        
	        window.clear();
	        window.setView(view);
	        main_bar.render();
	        sceneMenu.render();
	        window.display();
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
		}
	}
	
	void level3(){
		
		panel main_bar;
		
		main_bar.script.open("Scripts/Script4.txt");
		
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
		character[2].setPosition(main_bar.current_right_positoin);
		
		main_bar.current_person = &character[0];
		
		while (window.isOpen() && level3_start)
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
	        
	        main_bar.update(false, character, 2);
	        
	        window.clear();
	        window.setView(view);
	        main_bar.render();
	        window.display();
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
		}
		
	}
	
	// подготовка к допросу подозреваемого
	void level4(){
		panel main_bar;
		
		main_bar.script.open("Scripts/Script5.txt");
		
		person character[3];
		
		character[0].name = "виктор";
		character[0].say_txt.loadFromFile("Sprites/victor_say.png");
		character[0].think_txt.loadFromFile("Sprites/victor_think.png");
		character[0].sitting.loadFromFile("Sprites/atlas_sitting.png");
		character[0].setPosition(main_bar.current_left_positoin);
		
		character[1].name = "эмрис";
		character[1].setPosition(main_bar.current_right_positoin);
		character[1].say_txt.loadFromFile("Sprites/Emris_say.png");
		character[1].say[0] = IntRect(345, 0, 115, 256);
		character[1].say[1] = IntRect(460, 0, 115, 256);
		character[1].idle_rect[0] = IntRect(0, 0, 115, 256);
		character[1].idle_rect[1] = IntRect(115, 0, 115, 256);
		
		character[2].name = "зендей";
		character[2].setPosition(main_bar.current_right_positoin);
		
		main_bar.current_person = &character[0];
		
		while (window.isOpen() && level4_start)
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
	        
	        main_bar.update(false, character, 2);
	        
	        window.clear();
	        window.setView(view);
	        main_bar.render();
	        window.display();
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
		}
	}
	
	// уровень 5
	// допрос подозреваемого
	void level5(){
		
		interrogation main_bar;
		
		while (window.isOpen() && level5_start)
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
		
			window.clear();
	        window.setView(view);
	        main_bar.render();
	        window.display();
	        
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
		}
	}
}



















