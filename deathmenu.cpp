#include "Deathmenu.hpp"
#include <SDL.h>
#include <SDL_image.h>

Deathmenu::Deathmenu(float p_x, float p_y, SDL_Texture* p_tex)
	:x(p_x), y(p_y), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 700;
	currentFrame.h = 350;
}

float Deathmenu::getX()
{
	return x;
}

float Deathmenu::getY()
{
	return y;
}

SDL_Texture* Deathmenu::getTex()
{
	return tex;
}

SDL_Rect Deathmenu::getCurrentFrame()
{
	return currentFrame;
}