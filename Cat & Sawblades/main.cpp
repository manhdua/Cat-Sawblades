#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Cat.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "SDL_Init failed\nError: " << SDL_GetError() << '\n';

	if (!IMG_Init(IMG_INIT_PNG))
		cout << "IMG_Init failed\nError: " << SDL_GetError() << '\n';

	// title , resolution
	RenderWindow window("Cat & Sawblades", SCREEN_WIDTH, SCREEN_HEIGHT);

	bool gameRunning = true;

	SDL_Event event;
	
	//tao texture
	SDL_Texture* grassTexture = window.loadTexture("image/cat.png");

	Cat main(50, 50, grassTexture, 1);

	int frameTime = 0;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			main.handleEvent(event);
		}
		
		if (main.getIsRight())
		{
			if (main.getCurrentVel() == 0) main.idleRightAnimation(frameTime);
			else
			{
				main.move();
				main.moveRightAnimation(frameTime);
			}
		}
		else
		{
			if (main.getCurrentVel() == 0) main.idleLeftAnimation(frameTime);
			else
			{
				main.move();
				main.moveLeftAnimation(frameTime);
			}
		}
		
		window.clear();
		window.renderCat(main); //render texture
		window.display();
	}
	
	window.cleanUp();
	SDL_Quit();

	return 0;
}