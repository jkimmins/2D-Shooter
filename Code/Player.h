#ifndef PLAYER_H
#define PLAYER_H
#include "Sprite.h"
#include "Bullet.h"
#include <string>
#include <vector>

//Class inherits from 'Sprite'
class Player : public Sprite
{

public:

	//Constructor 
	Player(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h);
	~Player() {}
	//Respond to player input
	void Move(SDL_Renderer* &_renderer, std::vector<Bullet*> &_bullets, int &_timer);
};

#endif
