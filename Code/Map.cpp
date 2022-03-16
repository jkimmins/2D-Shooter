#include "Map.h"

Map::Map(SDL_Renderer* _renderer, std::string _imagefile, float _speed, int _w, int _h)
{
	w = _w;		// store incoming parameters that we'll need later
	speed = _speed;
	x = 0;		// start x at 0

	image = new Sprite(_renderer, _imagefile, 0, 0, _w, _h); // construct Sprite
}

void Map::Update()
{
	x -= speed; // scroll along

	if (x < -w) // jump back by 'w' if scrolled too far
		x += w;
}

void Map::Draw()
{
	//draw two copies of image, one at 'x' one at 'x + w'
	image->SetX((int)x);
	image->Draw();

	image->SetX((int)x + w);
	image->Draw();
}