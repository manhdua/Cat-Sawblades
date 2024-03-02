#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
		cout << "Window failed\nError: " << SDL_GetError() << '\n';

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		cout << "Renderer failed\nError: " << SDL_GetError() << '\n';
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 100;
	src.h = 100;

	SDL_Rect dst;
	//vi tri
	dst.x = 100;
	dst.y = 100;
	//scale
	dst.w = 500;
	dst.h = 500;

	
	//(renderer, texture, src, dst)
	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);
	if (texture == NULL)
		cout << "Texture failed\nError: " << SDL_GetError() << '\n';

	return texture;
}