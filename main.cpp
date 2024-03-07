#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_mixer.h>
using namespace std;

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Cat.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		cout << "SDL_Init failed\nError: " << SDL_GetError() << '\n';

	if (!IMG_Init(IMG_INIT_PNG))
		cout << "IMG_Init failed\nError: " << IMG_GetError() << '\n';
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		cout << "SDL_mixer failed\nError: " << Mix_GetError() << '\n';

	// title , resolution
	RenderWindow window("Cat & Sawblades", SCREEN_WIDTH, SCREEN_HEIGHT);

	bool gameRunning = true;

	SDL_Event event;
	
	Mix_Chunk* jump = NULL;
	jump = Mix_LoadWAV("audio/jump.wav");

	//tao texture
	SDL_Texture* catTexture = window.loadTexture("image/cat.png");
	Cat Cat(500, 300, catTexture, 4, jump);

	SDL_Texture* backgroundTexture = window.loadTexture("image/bg.png");
	Entity background(0, 0, backgroundTexture);

	int frameTime = 0;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			Cat.handleEvent(event);
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
		
		window.clear();
		window.renderEntity(background);
		window.renderCat(Cat); //render texture
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