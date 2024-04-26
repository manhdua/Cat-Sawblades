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
#include "mainMenu.hpp"
#include "globals.hpp" //global variables

vector<Sawblade> sawblades;
int mouseX, mouseY;
RenderWindow window("Cat & Sawblades", SCREEN_WIDTH, SCREEN_HEIGHT);

bool checkCollision(float Ax, float Ay, float Bx, float By);
void restartGame(Cat& p_cat);
string randomMusic();
void UpdateAudio(Mix_Chunk* p_jump, Mix_Chunk* p_click, Mix_Music* p_bgm);
void UpdateTexture(Deathmenu &p_deathmenu, mainMenu &p_mainmenu);
void OpenMenu();
void HandleMainMenuInput(Mix_Music* p_bgm);
void HandleDeathMenuInput(Cat p_Cat);
void HandleOptionMenuInput();
void FreeMemory(Mix_Music* p_bgm, Mix_Chunk* p_jump, Mix_Chunk* p_click);
void SpawnSawblade(SDL_Texture* redSawbladeTexture, SDL_Texture* greenSawbladeTexture);
void IncreaseSpawnNumber();

int main(int argc, char* args[])
{
	srand(time(0));
	
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		cout << "SDL_Init failed\nError: " << SDL_GetError() << '\n';
	if (!IMG_Init(IMG_INIT_PNG))
		cout << "IMG_Init failed\nError: " << IMG_GetError() << '\n';

	// Khởi tạo font
	TTF_Init();
	TTF_Font* smallerFont = NULL;
	TTF_Font* scoreFont = NULL;
	smallerFont = TTF_OpenFont("dogicapixel.ttf", 16);
	scoreFont = TTF_OpenFont("Have Idea.ttf", 32);

	// Render window

	//Khởi tạo audio và file âm thanh
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
	Mix_Music* backgroundMusic = NULL;
	backgroundMusic = Mix_LoadMUS("audio/bgmusic/mainmenu.wav");
	Mix_PlayMusic(backgroundMusic, -1);
	Mix_VolumeMusic(BGMVolume);
	
	Mix_Chunk* jump = NULL;
	jump = Mix_LoadWAV("audio/jump.wav");
	Mix_Chunk* click = NULL;
	click = Mix_LoadWAV("audio/click.wav");
	
	Mix_VolumeChunk(jump, SFXVolume);
	Mix_VolumeChunk(click , SFXVolume);

	//Khởi tạo các texture
	SDL_Texture* catTexture = window.loadTexture("image/cat.png");
	Cat Cat(630, 611, catTexture, 5, jump);

	SDL_Texture* redSawbladeTexture = window.loadTexture("image/redsawblade.png");
	SDL_Texture* greenSawbladeTexture = window.loadTexture("image/greensawblade.png");

	SDL_Texture* backgroundTexture = window.loadTexture("image/bg.png");
	Entity background(0, 0, backgroundTexture);

	SDL_Texture* deathmenuTexture = window.loadTexture("image/deathmenu.png");
	SDL_Texture* tryAgainTexture = window.loadTexture("image/tryAgain.png");
	SDL_Texture* quitTexture = window.loadTexture("image/quit.png");
	SDL_Texture* optionMenuTexture = window.loadTexture("image/optionMenu.png");
	Deathmenu deathmenu(290, 200, deathmenuTexture, tryAgainTexture, quitTexture, optionMenuTexture);

	SDL_Texture* mainmenuTexture = window.loadTexture("image/mainmenu.png");
	SDL_Texture* playTexture = window.loadTexture("image/play.png");
	SDL_Texture* optionTexture = window.loadTexture("image/option.png");
	SDL_Texture* quitMainTexture = window.loadTexture("image/quitmain.png");
	mainMenu mainmenu(0, 0, mainmenuTexture, playTexture, optionTexture, quitMainTexture);

	//Setup Cap FPS
	LTimer fpsTimer;
	LTimer capTimer;
	fpsTimer.start();

	while (gameRunning)
	{
		capTimer.start();

		UpdateAudio(jump, click, backgroundMusic);
		UpdateTexture(deathmenu, mainmenu);

		//Xử lí input người chơi
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			Cat.handleEvent(event);
			
			if (event.type == SDL_QUIT) gameRunning = false;

			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE) OpenMenu();
			}

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (showMainMenu && !showOptionMenu) HandleMainMenuInput(backgroundMusic);
				if (showDeathMenu) HandleDeathMenuInput(Cat);
				if (showOptionMenu) HandleOptionMenuInput();
			}
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

		int avgFPS = countedFrame / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
			avgFPS = 0;

		countedFrame++;
		int frameTicks = capTimer.getTicks();
		if (frameTicks < TICKS_PER_FRAME)
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		
		if (playerScore > maxScore) maxScore = playerScore;
		IncreaseSpawnNumber();

		if (!paused)
		{	
			//Render
			window.clear();
			window.renderEntity(background);
			window.renderCat(Cat);
			window.renderText(smallerFont, { 0, 0, 0 }, "Score: " + to_string(playerScore), 420, 60);
			window.renderText(smallerFont, { 255, 255, 255 }, "FPS: " + to_string(avgFPS), 10, 10);

			SpawnSawblade(redSawbladeTexture, greenSawbladeTexture);
			for (auto& sawblade : sawblades)
			{
				if (sawblade.isActive())
				{
					if (Cat.getY() < sawblade.getY() && abs(Cat.getX() - sawblade.getX()) < 7)
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
		
		if (showOptionMenu)
		{
			deathmenu.changeToOption();
			window.renderDeathmenu(deathmenu);
			window.renderText(scoreFont, { 255, 255, 255 }, to_string(BGMVolume) + "%", 470, 295);
			window.renderText(scoreFont, { 255, 255, 255 }, to_string(SFXVolume) + "%", 470, 345);
		}
		window.display();
	}
	FreeMemory(backgroundMusic, jump, click);
	return 0;
}

bool checkCollision(float Ax, float Ay, float Bx, float By)
{
	if (Ax + 32 < Bx || Bx + 32 < Ax || Ay + 32 < By || By + 32 < Ay)
		return false;
	return true;
}

void restartGame(Cat& p_cat)
{
	p_cat.restartPos();
	for (int i = 0; i < sawblades.size(); i++)
	{
		sawblades[i].deactivate();
	}
	playerScore = 0;
	SpawnNumber = 1;
}

string randomMusic()
{
	return "audio/bgmusic/" + to_string(rand() % 6 + 1) + ".wav";
}

void UpdateAudio(Mix_Chunk* p_jump, Mix_Chunk* p_click, Mix_Music* p_bgm)
{
	Mix_VolumeMusic(BGMVolume);
	Mix_VolumeChunk(p_jump, SFXVolume);
	Mix_VolumeChunk(p_click, SFXVolume);

	if (!Mix_PlayingMusic())
	{
		p_bgm = Mix_LoadMUS(randomMusic().c_str());
		Mix_PlayMusic(p_bgm, 0);
	}
}

void UpdateTexture(Deathmenu &p_deathmenu, mainMenu &p_mainmenu)
{
	if (mouseX >= 402 && mouseX <= 592 && mouseY >= 430 && mouseY <= 496)
	{
		p_deathmenu.changeToTryAgain();
	}
	else if (mouseX >= 735 && mouseX <= 848 && mouseY >= 433 && mouseY <= 489)
	{
		p_deathmenu.changeToQuit();
	}
	else p_deathmenu.changeToNormal();
	
	if (mouseX >= 432 && mouseX <= 848 && mouseY >= 233 && mouseY <= 304)
	{
		p_mainmenu.changeToPlay();
	}
	else if (mouseX >= 432 && mouseX <= 848 && mouseY >= 366 && mouseY <= 436)
	{
		p_mainmenu.changeToOption();
	}
	else if (mouseX >= 432 && mouseX <= 848 && mouseY >= 495 && mouseY <= 566)
	{
		p_mainmenu.changeToQuit();
	}
	else p_mainmenu.changeToNormal();
}

void OpenMenu()
{
	if (!showOptionMenu)
	{
		showOptionMenu = true;
	}
	else
	{
		showOptionMenu = false;
	}
}

void HandleMainMenuInput(Mix_Music* p_bgm)
{
	if (mouseX >= 432 && mouseX <= 848 && mouseY >= 233 && mouseY <= 304)
	{
		showMainMenu = false;
		paused = false;
		Mix_HaltMusic();
		p_bgm = Mix_LoadMUS(randomMusic().c_str());
		Mix_PlayMusic(p_bgm, 0);
	}

	if (mouseX >= 432 && mouseX <= 848 && mouseY >= 495 && mouseY <= 566)
	{
		gameRunning = false;
	}

	if (mouseX >= 432 && mouseX <= 848 && mouseY >= 366 && mouseY <= 436)
	{
		showOptionMenu = true;
	}
}

void HandleDeathMenuInput(Cat p_Cat)
{
	if (mouseX >= 402 && mouseX <= 592 && mouseY >= 430 && mouseY <= 496)
	{
		paused = false;
		showDeathMenu = false;
		restartGame(p_Cat);
	}

	if (mouseX >= 735 && mouseX <= 848 && mouseY >= 433 && mouseY <= 489)
	{
		gameRunning = false;
	}
}

void HandleOptionMenuInput()
{
	if (mouseX >= 932 && mouseX <= 966 && mouseY >= 220 && mouseY <= 254)
	{
		showOptionMenu = false;
	}

	if (mouseX >= 539 && mouseX <= 573 && mouseY >= 295 && mouseY <= 334 && BGMVolume != 100)
	{
		BGMVolume += 10;
	}

	if ((mouseX >= 587 && mouseX <= 621 && mouseY >= 295 && mouseY <= 334 && BGMVolume != 0))
	{
		BGMVolume -= 10;
	}

	if ((mouseX >= 539 && mouseX <= 574 && mouseY >= 341 && mouseY <= 382 && SFXVolume != 100))
	{
		SFXVolume += 10;
	}

	if ((mouseX >= 589 && mouseX <= 619 && mouseY >= 341 && mouseY <= 382 && SFXVolume != 0))
	{
		SFXVolume -= 10;
	}
}

void FreeMemory(Mix_Music* p_bgm, Mix_Chunk* p_jump, Mix_Chunk* p_click)
{
	Mix_FreeChunk(p_jump);
	Mix_FreeChunk(p_click);
	Mix_FreeMusic(p_bgm);
	Mix_CloseAudio();
	window.cleanUp();
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
}

void SpawnSawblade(SDL_Texture* redSawbladeTexture, SDL_Texture* greenSawbladeTexture)
{
	delay++;
	if (delay == SpawnSpeed)
	{
		delay = 0;
		for (int i = 0; i < SpawnNumber; i++)
		{
			sawblades.push_back(Sawblade(rand() % 200 + 500, 30, redSawbladeTexture, greenSawbladeTexture, 5, rand() % 201 - 100, rand() % 20 + 80));
		}
	}
}

void IncreaseSpawnNumber()
{
	if (playerScore == 20) SpawnNumber = 2;
	if (playerScore == 40) SpawnNumber = 3;
	if (playerScore == 60) SpawnNumber = 4;
	if (playerScore == 80) SpawnNumber = 5;
	if (playerScore == 100) SpawnNumber = 6;
}