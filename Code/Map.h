#ifndef MAP_H
#define MAP_H
#include "Sprite.h"
#include <string>

class Map
{
protected:
	Sprite* image;  // sprite that this class uses
	float   x;      // current x position
	float   speed;  // scroll speed
	int     w;		// width of image used
public:
	//Constructor 
	Map(SDL_Renderer* _renderer, std::string _imagefile, float _speed, int _w, int _h);
	~Map() {}

	//Updates
	void Update();
	//Draws
	void Draw();
};

#endif