#ifndef QUIT_BUTTON_H
#define QUIT_BUTTON__H
#include "Sprite.h"
#include <string>

//Class inherits from 'Sprite'
class QuitButton : public Sprite
{
public:
	//Constructor 
	QuitButton(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h);
	~QuitButton() {}
};

#endif
