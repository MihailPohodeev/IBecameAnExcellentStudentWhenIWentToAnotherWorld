#include "interrogation.hpp"

namespace constructor{
	
	Clock clock;
	void background_movement(RectangleShape &back);
    
    object card;// объект удостоверения личности
    Texture objcts_txt; // текстура объектов
	
    
    // поочерёдная отрисовка спрайтов в зависимости от позиций
    void DrawSprites(RectangleShape *rect, double *pos, int count){

		int length = count;
		while(length--)
		{
			bool swapped = false;
			
			for(int i = 0; i < length; i++)
			{
				if(pos[i] > pos[i + 1])
				{
					swap(pos[i], pos[i + 1]);
					swap(rect[i], rect[i + 1]);
					swapped = true;
				}
			}
			
			if(swapped == false)
				break;
		}
		for (int i = 0 ; i < count; i++){
			window.draw(rect[i]);
		}
	}
    
    // метод меню
    void menu(){
    	
    	objcts_txt.loadFromFile("Sprites/objects.png");
    	card.description = "Удостоверение личности, кого-то похожего на вампира. В графе \"Имя\" написано \"Вит Калиновский\"";
    	card.shape.setTexture(&objcts_txt);
    	card.shape.setTextureRect(IntRect(1, 23, 18, 13));
    	
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
    	exit.setPosition(WIDTH / 2, start.getPosition().y + start.getSize().y * 1.5f);
		
		Texture back_texture;
	    RectangleShape background;
	    back_texture.loadFromFile("Sprites/background.png");
	    
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
//	        if ((settings.onClick() || Keyboard::isKeyPressed(Keyboard::Space))) {
//	        	if (!isClick){
//					anim = !anim;
//					to_settings = true;
//	        		isClick = true;
//	        	}
//			} else isClick = false;
			
			// при нажатии кнопки "выход"
			if (exit.onClick()) window.close();
			
			disappearing(anim, start, exit, exit); 
			
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
//			settings.update();
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
	    back_texture.loadFromFile("Sprites/background.png");
	    if (!back_texture.loadFromFile("Sprites/background.png")) cout<<"background picture loading failed"<<'\n';
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
		scene_menu SceneMenu;
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
		character[3].shape.setSize(Vector2f(WIDTH * 0.32f, HEIGHT * 0.6f));
		character[3].setOrigin(Vector2f(character[3].shape.getSize().x / 2, character[3].shape.getSize().y));
		character[3].say_txt.loadFromFile("Sprites/Prepod_say.png");
		character[3].say[0] = IntRect(2, 40, 190, 215);
		character[3].say[1] = IntRect(192, 40, 190, 215);
		character[3].idle_rect[0] = IntRect(2, 40, 190, 215);
		character[3].idle_rect[1] = IntRect(568, 40, 190, 215);
		
		
		main_bar.current_person = &character[0];
		
		IntRect finalRect = IntRect(6, 672, 225, 190);
		
		main_bar.isDark = false;
		main_bar.dark_alpha = 0;		
		
		Texture back_texture; // текстура заднего фона в корридоре
		Texture classroom_texture; // текстура заднего фона в аудитории
		Texture black; // текстура чёрного фона
		
	    RectangleShape background; // форма заднего фона
	    
	    // загрузка изображений
	    if (!back_texture.loadFromFile("Sprites/background.png")) cout<<"background picture loading failed"<<'\n';
	    else cout<<"background picture loaded succsessfully"<<'\n';
	    if (!classroom_texture.loadFromFile("Sprites/classroom.jpg")) cout<<"classroom picture loading failed"<<'\n';
	    else cout<<"classroom picture loaded succsessfully"<<'\n';
	    if (!black.loadFromFile("Sprites/black.png")) cout<<"background picture loading failed"<<'\n';
	    else cout<<"background picture loaded succsessfully"<<'\n';
	    
	    fps_text.setFont(main_font);
	    fps_text.setCharacterSize(14);
	    
	    // масштабирование заднего фона
	    background_init(black, background);
	    window.setFramerateLimit(60);
	    
	    music.setLoop(true);
	    music.play();
	    music.setVolume(50.f);
	    
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
			
			SceneMenu.update();
			if (!SceneMenu.isActive){
				main_bar.update(false, character, 4);
				background_movement(background);
			
				
				
				if ((main_bar.dark_alpha >= 254) && (main_bar.act > 0) && (!main_bar.isActive)){				
					if (main_bar.act == 1) background_init(back_texture, background);
					else if (main_bar.act == 2) {
						character[3].shape.setSize(Vector2f(WIDTH * 0.4f, HEIGHT * 0.8f));
						character[3].setOrigin(Vector2f(character[3].shape.getSize().x, character[3].shape.getSize().y));
						character[3].shape.setPosition(main_bar.panel_shape.getPosition().x + main_bar.panel_shape.getSize().x, character[3].shape.getPosition().y);
						background_init(classroom_texture, background);
						for (int i = 0; i < 3; i++) character[i].isSitting = true;
					}
					main_bar.isDark = false;
				}
				
				if (main_bar.act == 3) {					
					
					character[0].shape.setTextureRect(finalRect);
				
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
							main_bar.script.close();
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
			}
			
	        window.clear();
	        window.setView(view);
	        window.draw(background);
			main_bar.render();
			window.draw(dark);
//			window.draw(fps_text);
			SceneMenu.render();
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
		music.setVolume(50.f);
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
		identity_card.setPosition(WIDTH * 0.6f, HEIGHT * 0.85f);
		
		trigger window_view = trigger(WIDTH / 10, HEIGHT / 5);
		window_view.setPosition(WIDTH * 0.15f, HEIGHT * 0.7f);
		
		// объект персонажа и диалоговой панели
		level2_nmspc::main_player hero; // персонаж
		level2_nmspc::dialog_bar bar; // диалоговое окно
		level2_nmspc::npc emris; // нпс
		inventory _inventory; // инвентарь
		scene_menu sceneMenu; // меню
		
		emris.setPosition(Vector2f(WIDTH * 1.2f, HEIGHT));
		
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
		
		background_image.loadFromFile("Sprites/background2.png");
		window_view_image.loadFromFile("Sprites/window_view.png");
		
		background_init(background_image, background);	
		
		emris.texture.loadFromFile("Sprites/emris_atlas.png");
		emris.shape.setTexture(&emris.texture);
			
		emris.left_walking[0] = IntRect(0, 10, 43, 88);
		emris.left_walking[1] = IntRect(45, 10, 43, 88);
		emris.left_walking[2] = IntRect(90, 10, 43, 88);
		emris.left_walking[3] = IntRect(135, 10, 43, 88);
		emris.left_walking[4] = IntRect(180, 10, 43, 88);
		emris.left_walking[5] = IntRect(215, 10, 43, 88);
			
		emris.right_walking[0] = IntRect(0, 100, 43, 88);
		emris.right_walking[1] = IntRect(45, 100, 43, 88);
		emris.right_walking[2] = IntRect(90, 100, 43, 88);
		emris.right_walking[3] = IntRect(135, 100, 43, 88);
		emris.right_walking[4] = IntRect(180, 100, 43, 88);;
		emris.right_walking[5] = IntRect(215, 100, 43, 88);
			
		emris.up_walking[0] = IntRect(0, 200, 43, 88);
		emris.up_walking[1] = IntRect(44, 200, 43, 88);
		emris.up_walking[2] = IntRect(88, 200, 43, 88);
		emris.up_walking[3] = IntRect(132, 200, 43, 88);
		emris.up_walking[4] = IntRect(176, 200, 43, 88);;
		emris.up_walking[5] = IntRect(215, 200, 43, 88);
			
		emris.down_walking[0] = IntRect(0, 290, 43, 88);
		emris.down_walking[1] = IntRect(44, 290, 43, 88);
		emris.down_walking[2] = IntRect(88, 290, 43, 88);
		emris.down_walking[3] = IntRect(132, 290, 43, 88);
		emris.down_walking[4] = IntRect(176, 290, 43, 88);;
		emris.down_walking[5] = IntRect(215, 290, 43, 88);
			
		emris.idle[0] = IntRect(260, 200, 43, 88);
		emris.idle[1] = IntRect(260, 290, 43, 88);
		emris.idle[2] = IntRect(260, 100, 43, 88);
		emris.idle[3] = IntRect(260, 10, 43, 88);	
		
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
				
				_inventory.trigger_notification("Добавлено: Удостоверение личности", card, 1);
				
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
					}
				}
				
				if (emris.getPosition().x > (hero.getPosition().x + (WIDTH - hero.getPosition().x) / 2)) emris.dir = LEFT;
				else if (emris.getPosition().y > hero.getPosition().y) emris.dir = UP;
				else if (emris.getPosition().x > hero.getPosition().x + hero.getSize().x * .75f) emris.dir = LEFT;
				else {
					bar.isActive = true;
					emris.dir = STOP;
					hero.last_dir = RIGHT;
					emris.last_dir = LEFT;
				}
				emris.update(hero);
			}
			
			// акт 5
			else if (bar.script_act == 5){
				
				if (alpha < 255){
					alpha += anim_speed *  25 * deltaTime;
					if (alpha >= 255){
						level2_start = false;
						level2_5_start = true;
						bar.script.close();
					}
				}
				
			}
			
			
			dark_front.setFillColor(Color(0, 0, 0, (char)alpha));
			
			
			
			if(!sceneMenu.isActive){
				hero.update();
		        bar.update();
		        if (!bar.isActive) _inventory.update();
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
				emris.render();
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
		character[1].say_txt.loadFromFile("Sprites/Emris_say.png");
		character[1].say[0] = IntRect(230, 0, 115, 256);
		character[1].say[1] = IntRect(345, 0, 115, 256);
		character[1].idle_rect[0] = IntRect(0, 0, 115, 256);
		character[1].idle_rect[1] = IntRect(345, 0, 115, 256);
		
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
	        		main_bar.script.close();
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
	        
	        main_bar.update(false, character, 3);
	        
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
	restart:	
	
		Music music;
		music.openFromFile("Music/Halt_-This-Instant__v1__1.ogg");
		music.setVolume(50.f);
		music.setLoop(true);
		music.play();
		
		scene_menu	SceneMenu;
		
		interrogation *main_bar = new interrogation();
		(*main_bar).script.open("Scripts/Script5.txt");
		
		(*main_bar).nessesary_obj = 4;
		(*main_bar).interrog_act = 5;
		(*main_bar).true_act = 1;
		
		(*main_bar)._inventory.add_item_object(card);
		
		person character[2];
		object rec;
		rec.shape.setTexture(&objcts_txt);
    	rec.shape.setTextureRect(IntRect(13, 2, 19, 17));
    	rec.description = "\"Зендей Слипанов, раса: Великан\" ...знал жертву заочно по рассказам друзей...";
		(*main_bar).rec = rec;
		
		character[0].name = "виктор";
		character[0].say_txt.loadFromFile("Sprites/victor_say.png");
		character[0].think_txt.loadFromFile("Sprites/victor_think.png");
		character[0].sitting.loadFromFile("Sprites/atlas_sitting.png");
		character[0].setPosition((*main_bar).current_left_positoin);
		
		character[1].name = "зендей";
		character[1].setPosition((*main_bar).current_right_positoin);
		
		(*main_bar).current_person = &character[1];
		
		RectangleShape background; // форма заднего фона
		Texture texture;
		texture.loadFromFile("Sprites/prison.png");
		
		background_init(texture, background);
		
		while (window.isOpen() && level5_start)
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
	        
	        mouse_position = Mouse::getPosition(window);
			SceneMenu.update();
					
			if (!SceneMenu.isActive){
				background_movement(background);
				
				(*main_bar).update(false, character, 2);
				
				if ((*main_bar).act == 9) {
					(*main_bar).isActive = false;
					(*main_bar).DISAPPEARING = true;
					if((*main_bar).alpha <= 1){
						level5_start = false;
						level5_5_start = true;
					}
				}
				if((*main_bar).lifes == 0) goto restart;
			}
			
			window.clear();
	        window.setView(view);
	        window.draw(background);
	        (*main_bar).render();
	        SceneMenu.render();
	        window.display();
	        
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
		}
	}
	
	// Сценарий 2
	// уровень 5_5 диалог в офисе
	void level5_5(){
		
		panel main_bar;
		scene_menu SceneMenu;
		
		main_bar.script.open("Scripts/Script5_5.txt");
		
		person character[2];
		
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
		
		main_bar.current_person = &character[0];
		
		RectangleShape background; // форма заднего фона
		Texture texture;
		texture.loadFromFile("Sprites/hallway.png");
		
		background_init(texture, background);
		
		main_bar.isDark = false;
		main_bar.isDarkness = false;
		
		while (window.isOpen() && level5_5_start)
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
	        
	        mouse_position = Mouse::getPosition(window);
	        SceneMenu.update();
	        
	        if(!SceneMenu.isActive){
		        
				background_movement(background);
		        
		        main_bar.update(false, character, 2);
		        if(main_bar.act == 1){
		        	main_bar.isActive = false;
		        	main_bar.DISAPPEARING = true;
		        	main_bar.isDarkness = true;
		        	main_bar.isDark = true;
		        	if (main_bar.alpha < 3){
		        		level5_5_start = false;
		        		level6_start = true;
		        	}
				}
			}
	        
	        window.clear();
	        window.setView(view);
	        window.draw(background);
			main_bar.render();
			SceneMenu.render();
	        window.display();
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
		}
	}
	
	object _map;
	object note;
	
	// уровень в квартире
	void level6(){
		
		bool isDialogActive = false;
		
		scene_menu SceneMenu;
		
		level2_nmspc::main_player hero; // персонаж
		panel bar; // диалоговое окно
		level2_nmspc::npc emris; // нпс эмрис
		level2_nmspc::npc anna; // нпс анна
		inventory _inventory; // инвентарь
		
		trigger anna_trig = trigger(anna.getSize().x * 1.5f, anna.getSize().x * 0.5f);
		anna_trig.setOrigin(Vector2f(anna.getSize().x * 1.5f, anna.getSize().x * 0.25f));
		trigger note_trig = trigger(WIDTH * 0.1f, HEIGHT* 0.1f);
		trigger map_trig = trigger(WIDTH * 0.1f, HEIGHT* 0.1f);
		
		note_trig.setPosition(WIDTH * 0.3, HEIGHT * 0.7f);
		map_trig.setPosition(WIDTH * 0.6, HEIGHT * 0.7f);
		
		bar.isDarkness = false;
		bar.allowed = false;
		bar.script.open("Scripts/Script6.txt");
		
		_map.shape.setTexture(&objcts_txt);
    	_map.shape.setTextureRect(IntRect(0, 39, 32, 25));
    	_map.description = "Карта с несколькими обозначенными местами. Точно известно, что все эти места заброшены.";
    	note.shape.setTexture(&objcts_txt);
    	note.shape.setTextureRect(IntRect(13, 2, 19, 17));
		note.description = "Записка : \"Ушел к своему обычному месту. Не скучай и не волнуйся. Лен.\"";

		
		person character[3];
		
		character[0].name = "виктор";
		character[0].say_txt.loadFromFile("Sprites/victor_say.png");
		character[0].think_txt.loadFromFile("Sprites/victor_think.png");
		character[0].sitting.loadFromFile("Sprites/atlas_sitting.png");
		character[0].setPosition(bar.current_left_positoin);
		
		character[1].name = "эмрис";
		character[1].setPosition(bar.current_right_positoin);
		character[1].say_txt.loadFromFile("Sprites/Emris_say.png");
		character[1].say[0] = IntRect(230, 0, 115, 256);
		character[1].say[1] = IntRect(345, 0, 115, 256);
		character[1].idle_rect[0] = IntRect(0, 0, 115, 256);
		character[1].idle_rect[1] = IntRect(345, 0, 115, 256);		
		
		character[2].name = "анна";
		character[2].setPosition(bar.current_right_positoin);
		character[2].say_txt.loadFromFile("Sprites/Anna_Say.png");
		character[2].say[0] = IntRect(10, 8, 144, 248);
		character[2].say[1] = IntRect(154, 8, 144, 248);
		character[2].idle_rect[0] = IntRect(10, 8, 144, 248);
		character[2].idle_rect[1] = IntRect(442, 8, 144, 248);
		
		RectangleShape dark_back; //  форма для затемнения заднего фона во время диалогов
		RectangleShape dark_front; // форма для затемнения экрана
		Clock timer_for_darkness; // таймер затемнения
		
		int text_size = (HEIGHT + WIDTH) / 2 * 0.025f;
		Text hint;
		hint.setFont(main_font);
		hint.setCharacterSize(text_size);
		hint.setString("");
		hint.setFillColor(Color(255, 255, 255, 255));
		hint.setOutlineThickness(thick_size / 2);
		hint.setOutlineColor(Color(0, 0, 0, 255));
		hint.setPosition(WIDTH / 2 - ((string)(hint.getString())).length() * (HEIGHT + WIDTH) / 4 * 0.018f, HEIGHT - (HEIGHT + WIDTH) / 2 * 0.04f);
		
		Text start_text;
		start_text.setFont(main_font);
		start_text.setCharacterSize((WIDTH + HEIGHT) / 75);
		start_text.setString("...тем же вечером");
		start_text.setFillColor(Color(255, 255, 255, 255));
		start_text.setPosition(WIDTH * 0.7f, HEIGHT * 0.9f);
		
		dark_front.setSize(Vector2f(WIDTH, HEIGHT * 1.5f));
		dark_front.setPosition(0, 0);
		dark_front.setFillColor(Color(0, 0, 0, 255));
		dark_back.setSize(Vector2f(WIDTH, HEIGHT * 1.5f));
		dark_back.setPosition(0, 0);
		dark_back.setFillColor(Color(0, 0, 0, 255));
		float dark_alpha = 255;
		float dark_back_alpha = 0;
		
		bar.current_person = &character[0];
		
		hero.setPosition(Vector2f(1, HEIGHT * 0.75f));
		emris.setPosition(Vector2f(-50, HEIGHT * 0.85f));
		anna.setPosition(Vector2f(WIDTH - 100, HEIGHT * 0.8f));
		
		hero.allowed = false;
		hero.stand = true;
		
		bool get_map = false, get_note = false;
		
		emris.texture.loadFromFile("Sprites/emris_atlas.png");
		emris.shape.setTexture(&emris.texture);
			
		emris.left_walking[0] = IntRect(0, 10, 43, 88);
		emris.left_walking[1] = IntRect(45, 10, 43, 88);
		emris.left_walking[2] = IntRect(90, 10, 43, 88);
		emris.left_walking[3] = IntRect(135, 10, 43, 88);
		emris.left_walking[4] = IntRect(180, 10, 43, 88);
		emris.left_walking[5] = IntRect(215, 10, 43, 88);
			
		emris.right_walking[0] = IntRect(0, 100, 43, 88);
		emris.right_walking[1] = IntRect(45, 100, 43, 88);
		emris.right_walking[2] = IntRect(90, 100, 43, 88);
		emris.right_walking[3] = IntRect(135, 100, 43, 88);
		emris.right_walking[4] = IntRect(180, 100, 43, 88);;
		emris.right_walking[5] = IntRect(215, 100, 43, 88);
			
		emris.up_walking[0] = IntRect(0, 200, 43, 88);
		emris.up_walking[1] = IntRect(44, 200, 43, 88);
		emris.up_walking[2] = IntRect(88, 200, 43, 88);
		emris.up_walking[3] = IntRect(132, 200, 43, 88);
		emris.up_walking[4] = IntRect(176, 200, 43, 88);;
		emris.up_walking[5] = IntRect(215, 200, 43, 88);
			
		emris.down_walking[0] = IntRect(0, 290, 43, 88);
		emris.down_walking[1] = IntRect(44, 290, 43, 88);
		emris.down_walking[2] = IntRect(88, 290, 43, 88);
		emris.down_walking[3] = IntRect(132, 290, 43, 88);
		emris.down_walking[4] = IntRect(176, 290, 43, 88);;
		emris.down_walking[5] = IntRect(215, 290, 43, 88);
			
		emris.idle[0] = IntRect(260, 200, 43, 88);
		emris.idle[1] = IntRect(260, 290, 43, 88);
		emris.idle[2] = IntRect(260, 100, 43, 88);
		emris.idle[3] = IntRect(260, 10, 43, 88);
		
		RectangleShape back;
		back.setSize(Vector2f(WIDTH, HEIGHT));
		
		while (window.isOpen() && level6_start)
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
	    	
	    	mouse_position = Mouse::getPosition(window);
	        SceneMenu.update();
	        Texture back_txt;
	        back_txt.loadFromFile("Sprites/flat.png");
	        background_init(back_txt, back);
	    	
	    	if(!SceneMenu.isActive){
				if (timer_for_darkness.getElapsedTime().asSeconds() >= 4){
			    	
			    	if (dark_alpha > 0){
			    		dark_alpha -= anim_speed * 5 * deltaTime;
			    		if (dark_alpha <= 0) dark_alpha = 0;
					}
					dark_front.setFillColor(Color(0, 0, 0, (char)dark_alpha));
				
					if(bar.act == 0){
			    		if (hero.getPosition().x < WIDTH / 3) {
							hero.dir = RIGHT;
							emris.dir = RIGHT;
						}
			    		else{
			    			emris.dir = STOP;
			    			hero.dir = STOP;
			    			hero.allowed = true;
			    			bar.act = 1;
						}
					}
					else if (bar.act == 1){
						bar.allowed = true;
						isDialogActive = true;
					}
					else if (bar.act == 2){
						if (anna_trig.intersects(hero.collision_rect)){
							bar.allowed = true;
							if (bar.APPEARING || bar.isActive){
								hero.allowed = false;
								isDialogActive = true;
							}
						}
						else{
							bar.DISAPPEARING = true;
							bar.allowed = false;
							hero.allowed = true;
							isDialogActive = false;
						}
					}
					else if (bar.act == 3){
						
						if (anna.getPosition().x < WIDTH * 1.5f) anna.dir = RIGHT;
						else anna.dir = STOP;
						
						if (note_trig.intersects(hero.collision_rect) && !get_note && get_map){
							hint.setString("для взаимодействия нажмите клавишу E");
							hint.setPosition(WIDTH / 2 - ((string)(hint.getString())).length() * (HEIGHT + WIDTH) / 4 * 0.018f, HEIGHT - (HEIGHT + WIDTH) / 2 * 0.04f);
							if (Keyboard::isKeyPressed(Keyboard::E)){
								get_note = true;
							}
						}
						else if (map_trig.intersects(hero.collision_rect) && !get_map){
							hint.setString("для взаимодействия нажмите клавишу E");
							hint.setPosition(WIDTH / 2 - ((string)(hint.getString())).length() * (HEIGHT + WIDTH) / 4 * 0.018f, HEIGHT - (HEIGHT + WIDTH) / 2 * 0.04f);
							if (Keyboard::isKeyPressed(Keyboard::E)){
								get_map = true;
							}
						}
						else{
							hint.setString("");
						}
						
						if (get_note && get_map) {
							hint.setString("");
							bar.act = 4;
						}
						
						bar.DISAPPEARING = true;
						bar.allowed = false;
						hero.allowed = true;
						isDialogActive = false;
					}
					else if (bar.act == 4){
						if (anna.getPosition().x > WIDTH * 0.7f) anna.dir = LEFT;
						else {
							anna.dir = STOP;
							if (anna_trig.intersects(hero.collision_rect)){
								bar.allowed = true;
								if (bar.APPEARING || bar.isActive){
									hero.allowed = false;
									isDialogActive = true;
								}
							}
						}
					}
					else if(bar.act == 5){
						bar.isDark = true;
						bar.isDarkness = true;
						bar.isActive = false;
						bar.DISAPPEARING = true;
						if (bar.alpha <= 1){
							level6_start = false;
							level7_start = true;
						}
					}
				}
				
				if (get_map){
					if (get_note) _inventory.trigger_notification("Добавлено: Загадочная записка", note, 0);
					else _inventory.trigger_notification("Добавлено: Карта местности", _map, 1);
				}
				
				
				if(!isDialogActive){
					hero.update();
					emris.update(hero);
					anna.update(hero);
					
					if (dark_back_alpha > 0 && bar.isActive) {
						dark_back_alpha -= anim_speed * 10 * deltaTime;
						if (dark_back_alpha <= 0) dark_back_alpha = 0;
					}
				}
				else{
					if (dark_back_alpha < 128) {
						dark_back_alpha += anim_speed * 10 * deltaTime;
						if (dark_back_alpha >= 128) dark_back_alpha = 128;
					}
					
					_inventory.isActive = false;
				}
				
				dark_back.setFillColor(Color(0, 0, 0, (char)dark_back_alpha));
				
				_inventory.update();
			    bar.update(false, character, 3);
				
				anna_trig.setPosition(anna.getPosition().x, anna.getPosition().y);
			}
			
			RectangleShape shapes[] = {hero.shape, emris.shape, anna.shape};
			double position[] = {hero.getPosition().y, emris.getPosition().y, anna.getPosition().y};
			
	    	window.clear();
	        window.setView(view);
	        window.draw(back);
	        DrawSprites(shapes, position, 3);
	        window.draw(hint);
	        _inventory.render();
	        window.draw(dark_back);
	        bar.render();
	        window.draw(dark_front);
	        if (timer_for_darkness.getElapsedTime().asSeconds() < 3) window.draw(start_text);
	        anna_trig.render();
	        note_trig.render();
	        map_trig.render();
	        window.display();
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
		}
		
	}
	
	void level7(){
	restart:	
	
		Music music;
		music.openFromFile("Music/Halt_-This-Instant__v1__1.ogg");
		music.setVolume(50.f);
		music.setLoop(true);
		music.play();
		
		scene_menu	SceneMenu;
		
		interrogation *main_bar = new interrogation();
		(*main_bar).script.open("Scripts/Script7.txt");
		
		(*main_bar).nessesary_obj = 4;
		(*main_bar).interrog_act = 5;
		(*main_bar).true_act = 3;
		
		(*main_bar)._inventory.add_item_object(card);
		
		(*main_bar)._inventory.add_item_object(card);
		(*main_bar)._inventory.add_item_object(_map);
		(*main_bar)._inventory.add_record_object(note);
		
		person character[3];
		
		(*main_bar).rec = note;
		
		character[0].name = "виктор";
		character[0].say_txt.loadFromFile("Sprites/victor_say.png");
		character[0].think_txt.loadFromFile("Sprites/victor_think.png");
		character[0].sitting.loadFromFile("Sprites/atlas_sitting.png");
		character[0].setPosition((*main_bar).current_left_positoin);
		
		character[1].name = "эмрис";
		character[1].setPosition((*main_bar).current_right_positoin);
		character[1].say_txt.loadFromFile("Sprites/Emris_say.png");
		character[1].say[0] = IntRect(230, 0, 115, 256);
		character[1].say[1] = IntRect(345, 0, 115, 256);
		character[1].idle_rect[0] = IntRect(0, 0, 115, 256);
		character[1].idle_rect[1] = IntRect(345, 0, 115, 256);	
		
		character[2].name = "анна";
		character[2].setPosition((*main_bar).current_right_positoin);
		character[2].say_txt.loadFromFile("Sprites/Anna_Say.png");
		character[2].say[0] = IntRect(10, 8, 144, 248);
		character[2].say[1] = IntRect(154, 8, 144, 248);
		character[2].idle_rect[0] = IntRect(10, 8, 144, 248);
		character[2].idle_rect[1] = IntRect(442, 8, 144, 248);
		
		(*main_bar).current_person = &character[0];
		(*main_bar).withoutObject = true;
		
		RectangleShape background; // форма заднего фона
		Texture texture;
		texture.loadFromFile("Sprites/flat.png");
		
		RectangleShape black;
		black.setSize(Vector2f(WIDTH, HEIGHT));
		black.setFillColor(Color(0,0,0,0));
		float alpha_black = 0.0f;
		
		
		background_init(texture, background);
		
		while (window.isOpen() && level7_start)
	    {
	        clock.restart();
	        
			Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }
	        
	        mouse_position = Mouse::getPosition(window);
			SceneMenu.update();
					
			if (!SceneMenu.isActive){
				background_movement(background);
				
				(*main_bar).update(false, character, 3);
				
				if ((*main_bar).act == 9) {
					(*main_bar).isActive = false;
					(*main_bar).DISAPPEARING = true;
					if((*main_bar).alpha <= 1){
						if (alpha_black > 0) {
							alpha_black -= deltaTime * 15 * anim_speed;
							if (alpha_black <= 0){
								alpha_black = 0;
//								level7_start = false;
							}
						}
					}
				}
				if((*main_bar).lifes == 0) goto restart;				
			}
			
			black.setFillColor(Color(0, 0, 0, (char)alpha_black));
			
			window.clear();
	        window.setView(view);
	        window.draw(background);
	        (*main_bar).render();
	        window.draw(black);
	        SceneMenu.render();
	        window.display();
	        
	        
	        deltaTime = (double)clock.getElapsedTime().asMicroseconds() / 1000000;
		}
	}
}




















