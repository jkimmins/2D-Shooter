#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h"
#include <string>

//Class inherits from 'Sprite'
class Bullet : public Sprite
{
private:
	//Timer sets cooldown for player shooting
	int timer;

public:

	//Constructor 
	Bullet(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h);
	~Bullet() {}

	//Function for moving
	void Move();
};

#endif