#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <string>
#include <SDL_ttf.h>
using namespace std;

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Cat.hpp"
#include "Sawblade.hpp"
#include "LTimer.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

bool checkCollision(float Ax, float Ay, float Bx, float By)
{
	if (Ax + 32 < Bx || Bx + 32 < Ax || Ay + 32 < By || By + 32 < Ay)
		return false;
	return true;
}

int main(int argc, char* args[])
{
	srand(time(0));
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		cout << "SDL_Init failed\nError: " << SDL_GetError() << '\n';

	if (!IMG_Init(IMG_INIT_PNG))
		cout << "IMG_Init failed\nError: " << IMG_GetError() << '\n';
	
	TTF_Init();
	TTF_Font* font = NULL;
	TTF_Font* smallerFont = NULL;
	font = TTF_OpenFont("dogicapixel.ttf", 32);
	smallerFont = TTF_OpenFont("dogicapixel.ttf", 16);

	// title , resolution
	RenderWindow window("Cat & Sawblades", SCREEN_WIDTH, SCREEN_HEIGHT);

	bool gameRunning = true;

	SDL_Event event;
	
	Mix_Chunk* jump = NULL;
	jump = Mix_LoadWAV("audio/jump.wav");

	//tao texture
	SDL_Texture* catTexture = window.loadTexture("image/cat.png");
	Cat Cat(500, 300, catTexture, 5, jump);

	SDL_Texture* redSawbladeTexture = window.loadTexture("image/redsawblade.png");
	SDL_Texture* greenSawbladeTexture = window.loadTexture("image/greensawblade.png");

	SDL_Texture* backgroundTexture = window.loadTexture("image/bg.png");
	Entity background(0, 0, backgroundTexture);

	vector<Sawblade> sawblades;

	LTimer fpsTimer;
	LTimer capTimer;

	int frameTime = 0;
	int delay = 0;
	int playerScore = 0;
	int countedFrame = 0;
	int SpawnSpeed = 100;

	fpsTimer.start();

	while (gameRunning)
	{
		capTimer.start();

		
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			Cat.handleEvent(event);
		}
		
		int avgFPS = countedFrame / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
			avgFPS = 0;
		
		delay++;
		if (delay == SpawnSpeed)
		{
			delay = 0;
			sawblades.push_back(Sawblade(rand() % 200 + 500, 30, redSawbladeTexture, greenSawbladeTexture, 5, rand() % 201 - 100, rand() % 100 + 1));
		}
		Cat.collideWithWall();
		Cat.jump();
		if (Cat.getIsRight())
		{
			Cat.move();
			if (Cat.getCurrentVel() != 0) Cat.moveRightAnimation(frameTime);
		}
		else
		{
			Cat.move();
			if (Cat.getCurrentVel() != 0) Cat.moveLeftAnimation(frameTime);
		}
		
		countedFrame++;
		int frameTicks = capTimer.getTicks();
		if (frameTicks < TICKS_PER_FRAME)
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		
		window.clear();
		window.renderEntity(background);
		window.renderCat(Cat); //render texture
		window.renderText(font, {0, 0, 0}, to_string(playerScore), 640, 150);
		window.renderText(smallerFont, {255, 255, 255}, "FPS: " + to_string(avgFPS), 10, 10);
		
		for (auto& sawblade : sawblades)
		{
			if (sawblade.isActive())
			{
				if (Cat.getY() < sawblade.getY() && abs(Cat.getX() - sawblade.getX()) < 5)
				{
					sawblade.changeToGreen();
				}
				
				if (sawblade.getChangedToGreen() && Cat.getY() == 611)
				{
					sawblade.deactivate();
					playerScore++;
				}

				if (sawblade.getY() < 30) sawblade.deactivate();

				if (checkCollision(Cat.getX(), Cat.getY(), sawblade.getX(), sawblade.getY()))
					gameRunning = false;
				sawblade.move();
				window.renderSawblade(sawblade);
			}
		}
		window.display();
	}
	
	Mix_FreeChunk(jump);
	jump = NULL;
	window.cleanUp();
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();

	return 0;
}