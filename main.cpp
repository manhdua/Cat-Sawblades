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
#include "Deathmenu.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

bool paused = false;
bool showDeathMenu = false;

bool checkCollision(float Ax, float Ay, float Bx, float By);
void restartGame(Cat& p_cat, vector<Sawblade>& p_sawblade, int& p_score);

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
	TTF_Font* scoreFont = NULL;
	font = TTF_OpenFont("dogicapixel.ttf", 32);
	smallerFont = TTF_OpenFont("dogicapixel.ttf", 16);
	scoreFont = TTF_OpenFont("Have Idea.ttf", 32);

	// title , resolution
	RenderWindow window("Cat & Sawblades", SCREEN_WIDTH, SCREEN_HEIGHT);

	bool gameRunning = true;

	SDL_Event event;

	//audio
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music* backgroundMusic = NULL;
	backgroundMusic = Mix_LoadMUS("audio/bg.wav");
	Mix_PlayMusic(backgroundMusic, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 10);

	Mix_Chunk* jump = NULL;
	jump = Mix_LoadWAV("audio/jump.wav");

	Mix_Chunk* click = NULL;
	click = Mix_LoadWAV("audio/click.wav");

	//tao texture
	SDL_Texture* catTexture = window.loadTexture("image/cat.png");
	Cat Cat(630, 611, catTexture, 5, jump);

	SDL_Texture* redSawbladeTexture = window.loadTexture("image/redsawblade.png");
	SDL_Texture* greenSawbladeTexture = window.loadTexture("image/greensawblade.png");

	SDL_Texture* backgroundTexture = window.loadTexture("image/bg.png");
	Entity background(0, 0, backgroundTexture);

	SDL_Texture* deathmenuTexture = window.loadTexture("image/deathmenu.png");
	Deathmenu deathmenu(290, 200, deathmenuTexture);

	vector<Sawblade> sawblades;

	LTimer fpsTimer;
	LTimer capTimer;

	int frameTime = 0;
	int delay = 0;
	int playerScore = 0;
	int maxScore = 0;
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
		
		if (playerScore > maxScore) maxScore = playerScore;

		if (!paused)
		{
			window.clear();
			window.renderEntity(background);
			window.renderCat(Cat); //render texture
			window.renderText(font, { 0, 0, 0 }, to_string(playerScore), 640, 150);
			window.renderText(smallerFont, { 255, 255, 255 }, "FPS: " + to_string(avgFPS), 10, 10);

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
						Mix_PlayChannel(-1, click, 0);
					}

					if (sawblade.getY() < 30) sawblade.deactivate();

					if (checkCollision(Cat.getX(), Cat.getY(), sawblade.getX(), sawblade.getY()))
					{
						sawblade.deactivate();
						showDeathMenu = true;
						paused = true;
					}
					sawblade.move();
					window.renderSawblade(sawblade);
				}
			}
			window.display();

			if (showDeathMenu)
			{
				window.renderDeathmenu(deathmenu);
				showDeathMenu = false;

				window.renderText(scoreFont, {0, 0, 0}, to_string(playerScore), 470, 280);
				window.renderText(scoreFont, { 0, 0, 0 }, to_string(maxScore), 460, 330);
			}
			window.display();
		}
	}
	
	Mix_FreeChunk(jump);
	Mix_FreeMusic(backgroundMusic);
	Mix_CloseAudio();
	window.cleanUp();
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();

	return 0;
}

bool checkCollision(float Ax, float Ay, float Bx, float By)
{
	if (Ax + 32 < Bx || Bx + 32 < Ax || Ay + 32 < By || By + 32 < Ay)
		return false;
	return true;
}

void restartGame(Cat& p_cat, vector<Sawblade>& p_sawblade, int& p_score)
{
	p_cat.restartPos();
	for (int i = 0; i < p_sawblade.size(); i++)
	{
		p_sawblade[i].deactivate();
	}
	p_score = 0;
}