#ifndef SCORE_H
#define SCORE_H
#include "Sprite.h"
#include <string>

class Score
{
protected:

	SDL_Renderer* renderer; // SDL renderer used for drawing
	int score;
public:
	//Constructor 
	Score(SDL_Renderer* _renderer, int _score);
	~Score() {}

	//Draws score
	void Draw(int _score);
};

#endif
