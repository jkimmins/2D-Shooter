#include "Player.h"
#include "Bullet.h"
#include <vector>

Player::Player(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h):
	Sprite(_renderer, _file, _x, _y, _w, _h)
{

}

void Player::Move(SDL_Renderer* &_renderer, std::vector<Bullet*> &_bullets, int &_timer)
{
	//Get keyboard input
	const Uint8* key = SDL_GetKeyboardState(NULL);
	float playerSpeed = 5;

	//Move player
	if (key[SDL_SCANCODE_RIGHT])
	{
		position.x += 5;
	}
	if (key[SDL_SCANCODE_LEFT])
	{
		position.x -= 5;
	}
	if (key[SDL_SCANCODE_UP])
	{
		position.y -= 5;
	}
	if (key[SDL_SCANCODE_DOWN])
	{
		position.y += 5;
	}
	//Shoot
	if (key[SDL_SCANCODE_SPACE] && _timer < 0)
	{
		_timer = 10;
		_bullets.push_back(new Bullet(_renderer, "laserBlue01.png", Player::GetX(), (Player::GetY() + (Player::GetH() / 2)), 10, 5));
	}

	//Check for collision with edge of screen
	if (position.x < 0)
	{
		//Move back
		position.x += 10;
	}
	else if (position.x + 50 > 1280)
	{
		//Move back
		position.x -= 10;
	}
	else if (position.y < 0)
	{
		//Move back
		position.y += 10;
	}
	else if (position.y + 50 > 720)
	{
		//Move back
		position.y -= 10;
	}
}