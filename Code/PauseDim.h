#pragma once
#include "Sprite.h"
#include <string>

class PauseDim : public Sprite
{
public:
	// constructor 
	PauseDim(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h);
	~PauseDim() {}
};
