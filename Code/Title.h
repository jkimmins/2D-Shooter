#ifndef TITLE_H
#define TITLE_H
#include "Sprite.h"
#include <string>

//Class inherits from 'Sprite'
class Title : public Sprite
{
public:
	//Constructor 
	Title(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h);
	~Title() {}
};

#endif