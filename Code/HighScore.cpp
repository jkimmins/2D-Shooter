#include "HighScore.h"
#include <string>
#include <SDL_ttf.h>

HighScore::HighScore(SDL_Renderer* _renderer, int _highScore)
{
	renderer = _renderer;
	highScore = _highScore;
}

//Function for declaring variables used to draw text to the screen
void HighScore::Draw(int _highScore)
{
	TTF_Font* font = TTF_OpenFont("Coalition_v2.ttf", 24); //this opens a font style and sets a size
	std::string score_text = "High Score: " + std::to_string(_highScore);
	SDL_Color scoreColor = { 255, 255, 255, 0 };
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, score_text.c_str(), scoreColor);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, scoreSurface);
	SDL_FreeSurface(scoreSurface);
	SDL_Rect renderQuad = { 310, 10, 250, 100 };
	SDL_RenderCopy(renderer, text, NULL, &renderQuad);
	SDL_DestroyTexture(text);
}