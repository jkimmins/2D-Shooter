#ifndef LIVES_H
#define LIVES_H
#include "Sprite.h"
#include <string>

class Lives
{
protected:

	SDL_Renderer* renderer;
public:
	//Constructor 
	Lives(SDL_Renderer* _renderer, int _lives);
	~Lives() {}

	//Draws high score to the screen
	void Draw(int _lives);
};

#endif