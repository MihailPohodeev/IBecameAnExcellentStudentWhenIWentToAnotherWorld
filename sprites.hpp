#include "inventory.hpp"

namespace level2_nmspc{
	
	class character{
	
	protected:
		
		// форма персонажа
		RectangleShape shape;
		
		// имя персонажа
		string name;
		
		double x, y; // координаты персонажа
		double speed; // скорость движения персонажа
		
		int up_barrier, down_barrier, right_barrier, left_barrier;
		
		// перечислимый тип направления
		enum direction {STOP, UP, DOWN, RIGHT, LEFT};
		direction dir;
		
		
	public:
		
		void _update(); // обновление
		void render(); // отрисовка
		
		character(){
			shape.setSize(Vector2f(WIDTH / 8, HEIGHT / 3));
			shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y));
			dir = RIGHT;
			x = WIDTH * 0.5f;
			y = HEIGHT * 0.8f;
			speed = 100;
			
			up_barrier = HEIGHT * 2 / 3;
			down_barrier = HEIGHT;
			right_barrier = WIDTH;
			left_barrier = 0;
		}
		
	};
	
	// обновление
	void character::_update(){
		if (dir == RIGHT){
			if (x < right_barrier){
				x += speed * deltaTime;
			}
		}
		else if (dir == LEFT){
			if (x > left_barrier){
				x -= speed * deltaTime;
			}
		}
		else if (dir == UP){
			if (y > up_barrier){
				y -= speed * deltaTime;
			}
		}
		else if (dir == DOWN){
			if (y < down_barrier){
				y += speed * deltaTime;
			}
		}
		
		shape.setPosition(x, y);
	}
	
	// отрисовка
	void character::render(){
		window.draw(shape);
	}
	
	
	
	
	class main_player : public character{
	
		Texture texture;
		
		IntRect right_walking[6];
		IntRect left_walking[6];
		IntRect up_walking[6];
		IntRect down_walking[6];
		
		Clock anim_timer;
		
		double anim_time;
		
		
	
	public:
		
		void update();
		void animation();
		
		main_player(){
			name = "виктор";
			
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
		}
	};
	
	void main_player::update(){
		if (Keyboard::isKeyPressed(Keyboard::W)){
			dir = UP;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)){
			dir = DOWN;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)){
			dir = LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)){
			dir = RIGHT;
		}
		else{
			dir = STOP;
		}
		_update();
		animation();
	}
	
	void main_player::animation(){
		
		anim_time = (double)anim_timer.getElapsedTime().asMicroseconds() / 1000000;
		
		if (anim_time > 1.f){
			anim_timer.restart();
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
	}
}
