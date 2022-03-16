#ifndef PLAY_BUTTON__H
#define PLAY_BUTTON__H
#include "Sprite.h"
#include <string>

//Class inherits from 'Sprite'
class PlayButton : public Sprite
{
public:
	//Constructor 
	PlayButton(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h);
	~PlayButton() {}
};

#endif
