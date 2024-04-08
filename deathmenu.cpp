#include "Deathmenu.hpp"
#include <SDL.h>
#include <SDL_image.h>

Deathmenu::Deathmenu(float p_x, float p_y, SDL_Texture* p_tex, SDL_Texture* p_tryAgain, SDL_Texture* p_quit, SDL_Texture* p_option)
	:x(p_x), y(p_y), tex(p_tex), tryAgainTex(p_tryAgain), quitTex(p_quit), normalTex(p_tex), optionTex(p_option)
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

void Deathmenu::changeToTryAgain()
{
	tex = tryAgainTex;
}

void Deathmenu::changeToQuit()
{
	tex = quitTex;
}

void Deathmenu::changeToNormal()
{
	tex = normalTex;
}

void Deathmenu::changeToOption()
{
	tex = optionTex;
}