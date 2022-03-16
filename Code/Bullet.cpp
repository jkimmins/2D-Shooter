#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h) :
	Sprite(_renderer, _file, _x, _y, _w, _h)
{

}

void Bullet::Move()
{
	if (position.x > 1280)
		destroyed = true;

	// add 10 onto bullet x position, moving it along the screen
	position.x += 10;
}