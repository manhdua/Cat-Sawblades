#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
using namespace std;

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
		cout << "Window failed\nError: " << SDL_GetError() << '\n';

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

void RenderWindow::renderEntity(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;;
	src.y = p_entity.getCurrentFrame().y;;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	//vi tri
	dst.x = p_entity.getX();
	dst.y = p_entity.getY();
	//scale
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h;

	
	//(renderer, texture, src, dst)
	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::renderCat(Cat& p_cat)
{
	SDL_Rect src;
	src.x = p_cat.getCurrentFrame().x;;
	src.y = p_cat.getCurrentFrame().y;;
	src.w = p_cat.getCurrentFrame().w;
	src.h = p_cat.getCurrentFrame().h;

	SDL_Rect dst;
	//vi tri
	dst.x = p_cat.getX();
	dst.y = p_cat.getY();
	//scale
	dst.w = p_cat.getCurrentFrame().w * 2;
	dst.h = p_cat.getCurrentFrame().h * 2;


	//(renderer, texture, src, dst)
	SDL_RenderCopy(renderer, p_cat.getTex(), &src, &dst);
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

void RenderWindow::renderSawblade(Sawblade& p_cat)
{
	SDL_Rect src;
	src.x = p_cat.getCurrentFrame().x;;
	src.y = p_cat.getCurrentFrame().y;;
	src.w = p_cat.getCurrentFrame().w;
	src.h = p_cat.getCurrentFrame().h;

	SDL_Rect dst;
	//vi tri
	dst.x = p_cat.getX();
	dst.y = p_cat.getY();
	//scale
	dst.w = p_cat.getCurrentFrame().w * 2;
	dst.h = p_cat.getCurrentFrame().h * 2;


	//(renderer, texture, src, dst)
	SDL_RenderCopy(renderer, p_cat.getTex(), &src, &dst);
}

void RenderWindow::renderText(TTF_Font* p_font, const std::string& text, float x, float y)
{
	SDL_Color color = {0, 0, 0}; //pure black
	SDL_Surface* surface = TTF_RenderText_Solid(p_font, text.c_str(), color);
	if (surface == NULL) {
		cout << "Surface failed\nError: " << TTF_GetError() << '\n';
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		std::cerr << "Texture failed\nError: " << SDL_GetError() << '\n';
		return;
	}
	SDL_Rect textRect = {x, y, surface->w, surface->h};
	SDL_RenderCopy(renderer, texture, NULL, &textRect);
}