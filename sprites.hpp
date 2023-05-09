#include "scene_menu.hpp"

namespace level2_nmspc{
	
	class character{
	
	protected:
		
		// форма персонажа
		RectangleShape collider;
		
		// имя персонажа
		string name;
		
		double x, y; // координаты персонажа
		double speed; // скорость движения персонажа		
		
	public:
		
		bool drawShadow;
		
		RectangleShape shape;
		RectangleShape shadow;
		
		int up_barrier, down_barrier, right_barrier, left_barrier;
		
		// направление движения
		direction dir;
		direction last_dir;
		
		bool movement; // доступно ли движение
		
		FloatRect collision_rect;
		
		Vector2f getPosition();
		Vector2f getSize();
		void setPosition(Vector2f pos);
		
		void _update(); // обновление
		void render(); // отрисовка
		
		character(){
			shape.setSize(Vector2f(WIDTH / 6, HEIGHT / 2));
			shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y));
			
			shadow.setFillColor(Color(0, 0, 0, 64));
			shadow.setSize(Vector2f(shape.getSize().x * 0.7f, shape.getSize().y / 6));
			shadow.setOrigin(Vector2f(shadow.getSize().x * 0.35f, shadow.getSize().y * 0.8f));
			
			collider.setSize(Vector2f(shape.getSize().x, shape.getSize().y / 10));
			collider.setOrigin(Vector2f(collider.getSize().x / 2, collider.getSize().y));
			
			dir = STOP;
			last_dir = LEFT;
			x = WIDTH * 0.5f;
			y = HEIGHT * 0.8f;
			speed = WIDTH / 6.5f;
			movement = true;
			drawShadow = true;
			
			up_barrier = HEIGHT / 4;
			down_barrier = HEIGHT;
			right_barrier = WIDTH;
			left_barrier = 0;
		}
		
	};
	
	// обновление
	void character::_update(){
		if (movement){
			if (dir == RIGHT){
				if (x < right_barrier){
					x += speed * deltaTime;
				}
				last_dir = RIGHT;
			}
			else if (dir == LEFT){
				if (x > left_barrier){
					x -= speed * deltaTime;
				}
				last_dir = LEFT;
			}
			else if (dir == UP){
				if (y > up_barrier){
					y -= speed * deltaTime;
				}
				last_dir = UP;
			}
			else if (dir == DOWN){
				if (y < down_barrier){
					y += speed * deltaTime;
				}
				last_dir = DOWN;
			}
		}
		
		collision_rect = collider.getGlobalBounds();
		
		shape.setPosition(x, y);
		shadow.setPosition(x, y);
		collider.setPosition(x, y);
	}
	
	// отрисовка
	void character::render(){
		if (drawShadow) window.draw(shadow);
		window.draw(shape);
		if (debugging) window.draw(collider);
	}
	
	Vector2f character::getSize(){
		return shape.getSize();
	}
	
	// получить позицию персонажа
	Vector2f character::getPosition(){
		return Vector2f(x, y);
	}
	
	// установить позицию персонажа
	void character::setPosition(Vector2f pos){
		 x = pos.x;
		 y = pos.y;
	}
	
	
	
	class npc : public character{
	
		Clock anim_timer;
	
	public:
		
		Texture texture;
		
		IntRect right_walking[6];
		IntRect left_walking[6];
		IntRect up_walking[6];
		IntRect down_walking[6];
		IntRect idle[4];
		IntRect getting_up[4];
		
		bool near_by_player;
		
		void update(character &player);
		void animation();
		
		npc(){
			near_by_player = false;
			
			shape.setSize(Vector2f(WIDTH / 6, HEIGHT / 2));
			shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y));
			
		}
		
	};
	
	void npc::update(character &player){
		
		// установка значения близости персонажа к игроку
		if (sqrt(pow(x - player.getPosition().x, 2) + pow(y - player.getPosition().y, 2)) <= shape.getSize().x * 1.5f) 
			near_by_player = true;
		else
			near_by_player = false;
			
		_update();
		animation();
	}
	
	// анимация неигрового персонажа
	void npc::animation(){
		
		double anim_time = (double)anim_timer.getElapsedTime().asMicroseconds() / 1000000;
		
		if (anim_time > 1.f){
			anim_timer.restart();
			anim_time = (double)anim_timer.getElapsedTime().asMicroseconds() / 1000000;
		}
		
		if (dir == LEFT){
			shape.setTextureRect(left_walking[(int)(anim_time * 6)]);
		}
		else if(dir == RIGHT){
			shape.setTextureRect(right_walking[(int)(anim_time * 6)]);
		}
		else if (dir == UP){
			shape.setTextureRect(up_walking[(int)(anim_time * 6)]);
		}
		else if (dir == DOWN){
			shape.setTextureRect(down_walking[(int)(anim_time * 6)]);
		}
		else{
			shape.setTextureRect(idle[last_dir - 1]);
		}		
	}
	
	
	// главный игрок
	class main_player : public character{
		
		
	
		Texture texture;
		
		IntRect right_walking[6];
		IntRect left_walking[6];
		IntRect up_walking[6];
		IntRect down_walking[6];
		IntRect idle[4];
		IntRect getting_up[4];
		
		
		double anim_time;
		
		
	
	public:
		
		Clock anim_timer;
		
		bool standing,
		stand,
		allowed; // разрешено ли управление с клавиатуры
		
		void update();
		void animation();
		
		main_player(){
			
			up_barrier = HEIGHT * 0.6f;
			down_barrier = HEIGHT;
			right_barrier = WIDTH * 0.72f;
			left_barrier = WIDTH * 0.15f;
			
			name = "виктор";
			standing = stand = false;
			allowed = true;
			
			texture.loadFromFile("Sprites/player_atlas.png");
			shape.setTexture(&texture);
			
			left_walking[0] = IntRect(0, 10, 43, 88);
			left_walking[1] = IntRect(45, 10, 43, 88);
			left_walking[2] = IntRect(90, 10, 43, 88);
			left_walking[3] = IntRect(135, 10, 43, 88);
			left_walking[4] = IntRect(180, 10, 43, 88);
			left_walking[5] = IntRect(215, 10, 43, 88);
			
			right_walking[0] = IntRect(0, 100, 43, 88);
			right_walking[1] = IntRect(45, 100, 43, 88);
			right_walking[2] = IntRect(90, 100, 43, 88);
			right_walking[3] = IntRect(135, 100, 43, 88);
			right_walking[4] = IntRect(180, 100, 43, 88);;
			right_walking[5] = IntRect(215, 100, 43, 88);
			
			up_walking[0] = IntRect(0, 200, 43, 88);
			up_walking[1] = IntRect(44, 200, 43, 88);
			up_walking[2] = IntRect(88, 200, 43, 88);
			up_walking[3] = IntRect(132, 200, 43, 88);
			up_walking[4] = IntRect(176, 200, 43, 88);;
			up_walking[5] = IntRect(215, 200, 43, 88);
			
			down_walking[0] = IntRect(0, 290, 43, 88);
			down_walking[1] = IntRect(44, 290, 43, 88);
			down_walking[2] = IntRect(88, 290, 43, 88);
			down_walking[3] = IntRect(132, 290, 43, 88);
			down_walking[4] = IntRect(176, 290, 43, 88);;
			down_walking[5] = IntRect(215, 290, 43, 88);
			
			idle[0] = IntRect(260, 200, 43, 88);
			idle[1] = IntRect(260, 290, 43, 88);
			idle[2] = IntRect(260, 100, 43, 88);
			idle[3] = IntRect(260, 10, 43, 88);
			
			getting_up[0] = IntRect(60, 390, 90, 90);
			getting_up[1] = IntRect(140, 390, 90, 90);
			getting_up[2] = IntRect(220, 390, 90, 90);
			
			shape.setSize(Vector2f(WIDTH / 4, WIDTH / 4));
			shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y * 0.8f));
			shape.setTextureRect(getting_up[0]);
		}
	};
	
	void main_player::update(){
		
		double axisX = Joystick::getAxisPosition(0, Joystick::X) / 100;
		double axisY = Joystick::getAxisPosition(0, Joystick::Y) / 100;
		
		if (abs(axisX) < 0.05f) axisX = 0;
		if (abs(axisY) < 0.6f) axisY = 0;
		
		if (standing && movement && allowed){
			if (Keyboard::isKeyPressed(Keyboard::W) || axisY < 0){
				dir = UP;
			}
			else if (Keyboard::isKeyPressed(Keyboard::S) || axisY > 0){
				dir = DOWN;
			}
			else if (Keyboard::isKeyPressed(Keyboard::A) || axisX < 0){
				dir = LEFT;
			}
			else if (Keyboard::isKeyPressed(Keyboard::D) || axisX > 0){
				dir = RIGHT;
			}
			else{
				dir = STOP;
			}
		}
		_update();
		animation();
	}
	
	void main_player::animation(){
		
		anim_time = (double)anim_timer.getElapsedTime().asMicroseconds() / 1000000;
		
		if (anim_time > 1.f){
			anim_timer.restart();
			anim_time = (double)anim_timer.getElapsedTime().asMicroseconds() / 1000000;
		}
		
		if (!standing && stand){
			shape.setTextureRect(getting_up[(int)(anim_time * 3)]);
			if (anim_time > 0.9f) {
				standing = true;
				shape.setSize(Vector2f(WIDTH / 6, HEIGHT / 2));
				shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y));
				
				collider.setSize(Vector2f(shape.getSize().x / 2, shape.getSize().y / 10));
				collider.setOrigin(Vector2f(collider.getSize().x / 2, collider.getSize().y));
			}
		}
		else if(standing){
			if (movement){
				if (dir == LEFT){
					shape.setTextureRect(left_walking[(int)(anim_time * 6)]);
				}
				else if(dir == RIGHT){
					shape.setTextureRect(right_walking[(int)(anim_time * 6)]);
				}
				else if (dir == UP){
					shape.setTextureRect(up_walking[(int)(anim_time * 6)]);
				}
				else if (dir == DOWN){
					shape.setTextureRect(down_walking[(int)(anim_time * 6)]);
				}
				else{
					shape.setTextureRect(idle[last_dir - 1]);
				}
			}
			else{
				shape.setTextureRect(idle[last_dir - 1]);
			}
		}
		
	}
}
