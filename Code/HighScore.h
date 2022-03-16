#ifndef HIGH_SCORE__H
#define HIGH_SCORE__H
#include "Sprite.h"
#include <string>

class HighScore
{
protected:

	SDL_Renderer* renderer;
	int highScore;
public:
	//Constructor 
	HighScore(SDL_Renderer* _renderer, int _score);
	~HighScore() {}

	//Draws high score to the screen
	void Draw(int _highScore);
};

#endif
