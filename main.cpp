﻿#include <SDL.h>
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
#include "mainMenu.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

bool paused = true;
bool showDeathMenu = false;
bool showMainMenu = true;

bool checkCollision(float Ax, float Ay, float Bx, float By);
void restartGame(Cat& p_cat, vector<Sawblade>& p_sawblade, int& p_score);
string randomMusic();

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
	backgroundMusic = Mix_LoadMUS("audio/bgmusic/mainmenu.wav");
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

	//deathMenu
	SDL_Texture* deathmenuTexture = window.loadTexture("image/deathmenu.png");
	SDL_Texture* tryAgainTexture = window.loadTexture("image/tryAgain.png");
	SDL_Texture* quitTexture = window.loadTexture("image/quit.png");
	Deathmenu deathmenu(290, 200, deathmenuTexture, tryAgainTexture, quitTexture);

	//mainMenu
	SDL_Texture* mainmenuTexture = window.loadTexture("image/mainmenu.png");
	SDL_Texture* playTexture = window.loadTexture("image/play.png");
	SDL_Texture* optionTexture = window.loadTexture("image/option.png");
	SDL_Texture* quitMainTexture = window.loadTexture("image/quitmain.png");
	mainMenu mainmenu(0, 0, mainmenuTexture, playTexture, optionTexture, quitMainTexture);

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

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		
		if (mouseX >= 402 && mouseX <= 592 && mouseY >= 430 && mouseY <= 496)
		{
			deathmenu.changeToTryAgain();
		}
		else if (mouseX >= 735 && mouseX <= 848 && mouseY >= 433 && mouseY <= 489)
		{
			deathmenu.changeToQuit();
		}
		else deathmenu.changeToNormal();
		//
		if (mouseX >= 432 && mouseX <= 848 && mouseY >= 233 && mouseY <= 304)
		{
			mainmenu.changeToPlay();
		}
		else if (mouseX >= 432 && mouseX <= 848 && mouseY >= 366 && mouseY <= 436)
		{
			mainmenu.changeToOption();
		}
		else if (mouseX >= 432 && mouseX <= 848 && mouseY >= 495 && mouseY <= 566)
		{
			mainmenu.changeToQuit();
		}
		else mainmenu.changeToNormal();
		
		if (!Mix_PlayingMusic())
		{
			backgroundMusic = Mix_LoadMUS(randomMusic().c_str());
			Mix_PlayMusic(backgroundMusic, 0);
		}

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			Cat.handleEvent(event);

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (showMainMenu)
				{
					if (mouseX >= 432 && mouseX <= 848 && mouseY >= 233 && mouseY <= 304)
					{
						showMainMenu = false;
						paused = false;
						Mix_HaltMusic();
						backgroundMusic = Mix_LoadMUS(randomMusic().c_str());
						Mix_PlayMusic(backgroundMusic, 0);
					}

					if (mouseX >= 432 && mouseX <= 848 && mouseY >= 495 && mouseY <= 566)
					{
						gameRunning = false;
					}
				}
				
				if (showDeathMenu)
				{
					if (mouseX >= 402 && mouseX <= 592 && mouseY >= 430 && mouseY <= 496)
					{
						paused = false;
						showDeathMenu = false;
						restartGame(Cat, sawblades, playerScore);
					}

					if (mouseX >= 735 && mouseX <= 848 && mouseY >= 433 && mouseY <= 489)
					{
						gameRunning = false;
					}
				}
			}
		}
		
		int avgFPS = countedFrame / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
			avgFPS = 0;
		
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
			//spawn sawblade
			delay++;
			if (delay == SpawnSpeed)
			{
				delay = 0;
				sawblades.push_back(Sawblade(rand() % 200 + 500, 30, redSawbladeTexture, greenSawbladeTexture, 5, rand() % 201 - 100, rand() % 100 + 1));
			}
			
			window.clear();
			window.renderEntity(background);
			window.renderCat(Cat); //render texture
			window.renderText(smallerFont, { 0, 0, 0 }, "Score: " + to_string(playerScore), 420, 60);
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
		}
		if (showDeathMenu)
		{
			window.renderDeathmenu(deathmenu);
			window.renderText(scoreFont, { 0, 0, 0 }, to_string(playerScore), 470, 280);
			window.renderText(scoreFont, { 0, 0, 0 }, to_string(maxScore), 460, 330);
		}
		if (showMainMenu)
		{
			window.renderMainMenu(mainmenu);
		}
		
		window.display();
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

string randomMusic()
{
	return "audio/bgmusic/" + to_string(rand() % 6 + 1) + ".wav";
}