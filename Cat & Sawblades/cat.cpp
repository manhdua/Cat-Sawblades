#include "Cat.hpp"
#include <SDL.h>
#include <SDL_image.h>

Cat::Cat(float p_x, float p_y, SDL_Texture* p_tex, float p_velocity)
	:x(p_x), y(p_y), tex(p_tex), CatVel(p_velocity), currentVel(0)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

float Cat::getX()
{
	return x;
}

float Cat::getY()
{
	return y;
}

SDL_Texture* Cat::getTex()
{
	return tex;
}

SDL_Rect Cat::getCurrentFrame()
{
	return currentFrame;
}

void Cat::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			currentVel -= CatVel;
			break;
		case SDLK_RIGHT:
			currentVel += CatVel;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			currentVel += CatVel;
			break;
		case SDLK_RIGHT:
			currentVel -= CatVel;
			break;
		}
	}
}

void Cat::move()
{
	x += currentVel;
}

