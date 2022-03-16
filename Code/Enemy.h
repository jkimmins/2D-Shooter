#ifndef ENEMY_H
#define ENEMY_H
#include "Sprite.h"
#include "Bullet.h"
#include <string>

//Class inherits from 'Sprite'
class Enemy : public Sprite
{
private:
	int speed = 5;

public:
	//Constructor 
	Enemy(SDL_Renderer* _renderer, std::string _imagefile, int _x, int _y, int _w, int _h);
	~Enemy() {}

	//Updates position and checks to see if it's touching a bullet
	void Update(int &_lives);
};

#endif