#include "Explosion.h"
#include <time.h>

Explosion::Explosion(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h) :
	Sprite(_renderer, _file, _x, _y, _w, _h)
{

}

//Object is destroyed after a certain amount of frames
void Explosion::Update()
{
	time -= 1;

	if (time <= 0)
	{
		setDestroyed(true);
	}
}