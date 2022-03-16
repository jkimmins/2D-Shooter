#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <time.h>
#include "Player.h"
#include "Enemy.h"
#include "Title.h"
#include "PlayButton.h"
#include "QuitButton.h"
#include "Map.h"
#include "Bullet.h"
#include "Score.h"
#include "HighScore.h"
#include "Lives.h"
#include "Explosion.h"

// function prototypes
void GameLoop(SDL_Window* window, SDL_Renderer* renderer, bool &_quit);
void MainMenu(SDL_Window* window, SDL_Renderer* renderer, bool &_quit);
void GameOver(SDL_Window* window, SDL_Renderer* renderer, bool &_quit, int _score, int _hScore);

int main(int, char**)
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool quit = false;
	srand(time(NULL));

	// try initialising SDL, log error and pause if fail
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
		system("pause");
		return 0;
	}
	TTF_Init();



	// try to create the window, log error and pause if fail
	window = SDL_CreateWindow("Space Defender", 100, 100, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	// try to create the renderer, log error and pause if fail
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// this function call goes into the actual game loop
	MainMenu(window, renderer, quit);
	GameLoop(window, renderer, quit);

	// clean up, free any memeory we have used
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;
}

void GameLoop(SDL_Window* window, SDL_Renderer* renderer, bool &_quit)
{
	//Declare and initialise variables
	SDL_Event e;
	const Uint8* key = SDL_GetKeyboardState(NULL);
	bool paused = false;
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	std::vector<Explosion*> explosions;
	int timer = 0;
	int score = 0;
	int currentLives = 100;
	int hScore = NULL;

	//Open high score file and read value
	std::ifstream file("HighScore.txt");
	if (!file.is_open())
	{
		std::cout << "Could not open file!" << '\n';
	}
	file >> hScore;
	file.close();
	

	// create background and player
	Player* player = new Player(renderer, "playerShip3_blue.png", 0, 0, 50, 50);
	Map* map = new Map(renderer, "scene.png", 0.5f, 1280, 720);
	Score* scoreText = new Score(renderer, score);
	HighScore* highScoreText = new HighScore(renderer, hScore);
	Lives* lives = new Lives(renderer, currentLives);
	
	while (!_quit) { // this is the main game loop

		while (SDL_PollEvent(&e)) // allow closing SDL window to quit
		{
			if (e.type == SDL_QUIT)
				_quit = true;
		}

		//When the player is reduced to 0 lives
		if (currentLives <= 0)
		{
			//Save high score
			hScore == score;
			std::ofstream file("HighScore.txt");
			if (!file.is_open())
			{
				std::cout << "Could not open file!" << '\n';
			}
			file << hScore;
			file.close();
			//Delete objects
			delete map;
			delete player;
			for (int i = 0; i < enemies.size(); ++i)
			{
				delete enemies[i];
			}
			for (int i = 0; i < bullets.size(); ++i)
			{
				delete bullets[i];
			}
			delete scoreText;
			delete highScoreText;
			delete lives;
			//Open game over screen
			GameOver(window, renderer, _quit, score, hScore);
		}

		//Clear the renderer
		SDL_RenderClear(renderer);
		timer--;

		
		//Player movement
		player->Move(renderer, bullets, timer);

		//Spawn enemies
		if (enemies.size() < 20)
		{
			enemies.push_back(new Enemy(renderer, "ufoRed.png", 1280, (rand() % 671), 50, 50));
		}

		//Update enemies
		for (int x = 0; x < enemies.size(); x++)
		{
			enemies[x]->Update(currentLives);
		}

		//Update explosions
		for (int x = 0; x < explosions.size(); x++)
		{
			explosions[x]->Update();
		}

		//Move bullets
		for (int i = 0; i < bullets.size(); ++i)
		{
			bullets[i]->Move();
		}

		//Draw sprites
		map->Draw();
		map->Update();
		player->Draw();
		for (int i = 0; i < enemies.size(); ++i)
		{
			enemies[i]->Draw();
		}
		for (int i = 0; i < bullets.size(); ++i)
		{
			bullets[i]->Draw();
		}
		for (int i = 0; i < explosions.size(); ++i)
		{
			explosions[i]->Draw();
		}

		//When a bullet hits an enemy set destroy to true and spawn an explosion
		for (int x = 0; x < enemies.size(); x++)
		{
			for (int i = 0; i < bullets.size(); i++)
			{
				if (enemies[x]->IsColliding(bullets[i]))
				{
					enemies[x]->setDestroyed(true);
					bullets[i]->setDestroyed(true);
					explosions.push_back(new Explosion(renderer, "explosion.png", enemies[x]->GetX(), enemies[x]->GetY(), 50, 50));

				}
			}
		}

		//Destroy objects that have been set to be destroyed
		for (int x = 0; x < enemies.size(); x++)
		{
			if (enemies[x]->getDestroyed())
			{
				std::vector<Enemy*>::iterator itr = (enemies.begin() + x);
				enemies.erase(itr);
				score += 100;
			}
		}

		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->getDestroyed())
			{
				std::vector<Bullet*>::iterator itr = (bullets.begin() + i);
				bullets.erase(itr);
			}
		}

		for (int i = 0; i < explosions.size(); i++)
		{
			if (explosions[i]->getDestroyed())
			{
				std::vector<Explosion*>::iterator itr = (explosions.begin() + i);
				explosions.erase(itr);
			}
		}

		//Set highscore to score if score is higher than highscore
		if (score >= hScore)
		{
			hScore = score;
		}

		scoreText->Draw(score);
		highScoreText->Draw(hScore);
		lives->Draw(currentLives);
		SDL_RenderPresent(renderer);
	}

	//Delete objects
	delete map;
	delete player;
	for (int i = 0; i < enemies.size(); ++i)
	{
		delete enemies[i];
	}
}

//Main menu function
void MainMenu(SDL_Window* window, SDL_Renderer* renderer, bool &_quit)
{
	//Set up variables and create objects
	bool choice = true;
	int x, y;
	SDL_Event e;
	Title* title = new Title(renderer, "Title.png", 280, 50, 720, 300);
	Title* instructions = new Title(renderer, "Instructions.png", 0, 620, 1280, 100);
	PlayButton* play = new PlayButton(renderer, "Play.png", 540, 300, 200, 100);
	QuitButton* quitButton = new QuitButton(renderer, "Quit.png", 540, 500, 200, 100);
	title->Draw();
	instructions->Draw();
	play->Draw();
	quitButton->Draw();
	//Wait for player to press a button
	while (choice == true)
	{
		SDL_PollEvent(&e);
		SDL_GetMouseState(&x, &y);
		//Start game
		if (e.type == SDL_MOUSEBUTTONDOWN && x >= 540 && x <= 740 && y >= 300 && y <= 400)
		{
			delete title;
			delete instructions;
			delete play;
			delete quitButton;
			choice = false;
		}
		//Quit
		if (e.type == SDL_MOUSEBUTTONDOWN && x >= 540 && x <= 740 && y >= 500 && y <= 600)
		{
			_quit = true;
			choice = false;
		}
		SDL_RenderPresent(renderer);
	}
}

//Function for gameover screen
void GameOver(SDL_Window* window, SDL_Renderer* renderer, bool &_quit, int _score, int _hScore)
{
	//Set up variables and create classes
	bool choice = true;
	int x, y;
	SDL_Event e;
	Title* background = new Title(renderer, "GameOverBKG.png", 0, 0, 1280, 720);
	Title* gameOver = new Title(renderer, "GameOver.png", 280, 50, 720, 300);
	PlayButton* play = new PlayButton(renderer, "Play.png", 540, 300, 200, 100);
	QuitButton* quitButton = new QuitButton(renderer, "Quit.png", 540, 500, 200, 100);
	Score* scoreText = new Score(renderer, _score);
	HighScore* highScoreText = new HighScore(renderer, _hScore);
	background->Draw();
	gameOver->Draw();
	play->Draw();
	scoreText->Draw(_score);
	highScoreText->Draw(_hScore);
	quitButton->Draw();

	//Play again
	while (choice == true)
	{
		SDL_PollEvent(&e);
		SDL_GetMouseState(&x, &y);
		if (e.type == SDL_MOUSEBUTTONDOWN && x >= 540 && x <= 740 && y >= 300 && y <= 400)
		{
			delete background;
			delete gameOver;
			delete play;
			delete quitButton;
			choice = false;
			GameLoop(window, renderer, _quit);
		}
		//Quit
		if (e.type == SDL_MOUSEBUTTONDOWN && x >= 540 && x <= 740 && y >= 500 && y <= 600)
		{
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			TTF_Quit();
			SDL_Quit();
			_quit = true;
			choice = false;
		}
		SDL_RenderPresent(renderer);
	}
}
