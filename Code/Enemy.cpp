#include "Enemy.h"
#include <time.h>

Enemy::Enemy(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h) :
	Sprite(_renderer, _file, _x, _y, _w, _h)
{

}

void Enemy::Update(int &_lives)
{
	//Moves the enemy
	position.x -= speed;

	//Move back to the right side of the screen
	if (position.x < 0)
	{
		position.x += 1280;
		_lives -= 1;
	}
}