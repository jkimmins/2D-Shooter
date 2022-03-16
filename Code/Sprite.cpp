#include "Sprite.h"
#include <SDL_image.h>

Sprite::Sprite(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h)
{
	SDL_Surface* imgFile = IMG_Load(_file.c_str());
	image = SDL_CreateTextureFromSurface(_renderer, imgFile);
	SDL_FreeSurface(imgFile);

	// iniitial position & w/h of sprite, based in incoming parameters
	position.x = _x;
	position.y = _y;
	position.w = _w;
	position.h = _h;

	renderer = _renderer;

	destroyed = false;
}

//Destructor destroys texture
Sprite::~Sprite()
{
	if (image)
		SDL_DestroyTexture(image);
}

//Draws sprite to the screen
void Sprite::Draw()
{
	if (image)
	{
		SDL_RenderCopy(renderer, image, NULL, &position);
	}
}

//Checks if two sprites are colliding and returns a boolean
bool Sprite::IsColliding(Sprite* _sprite)
{
	return SDL_HasIntersection(&position, &_sprite->GetRect());
}