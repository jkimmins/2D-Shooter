#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>
class Sprite
{
protected:

	SDL_Renderer* renderer;
	SDL_Texture* image;
	// x/y position and width/height of this sprite
	SDL_Rect position;
	
	bool destroyed;

public:
	//Constructor
	Sprite(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h);

	//Destructor
	~Sprite(); 
	virtual void Draw();

	//Setters
	void SetX(int _x) { position.x = _x; }
	void SetY(int _y) { position.y = _y; }

	//Getters
	int GetX() { return position.x; }
	int GetY() { return position.y; }
	int GetW() { return position.w; }
	int GetH() { return position.h; }
	SDL_Rect& GetRect() { return position; }

	bool getDestroyed() { return destroyed; }
	void setDestroyed(bool _value) { destroyed = _value; }

	bool IsColliding(Sprite* _sprite);

};

#endif