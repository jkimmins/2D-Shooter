#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "Sprite.h"
#include <string>

//Class inherits from 'Sprite'
class Explosion : public Sprite
{
private:
	int time = 10;

public:
	//Constructor 
	Explosion(SDL_Renderer* _renderer, std::string _imagefile, int _x, int _y, int _w, int _h);
	~Explosion() {}

	//Update function for explosion
	void Update();
};

#endif