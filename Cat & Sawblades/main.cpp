#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

#include "RenderWindow.hpp"
#include "Entity.hpp"

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
	SDL_Texture* grassTexture = window.loadTexture("image/grass.png");

	Entity platform(0, 0, grassTexture);

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
		}

		window.clear();
		window.render(platform); //render texture
		window.display();
	}
	
	window.cleanUp();
	SDL_Quit();

	return 0;
}