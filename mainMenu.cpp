#include "mainMenu.hpp"
#include <SDL.h>
#include <SDL_image.h>

mainMenu::mainMenu(float p_x, float p_y, SDL_Texture* p_tex, SDL_Texture* p_play, SDL_Texture* p_option)
	:x(p_x), y(p_y), tex(p_tex), playTex(p_play), optionTex(p_option), normalTex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 1920;
	currentFrame.h = 1080;
}

float mainMenu::getX()
{
	return x;
}

float mainMenu::getY()
{
	return y;
}

SDL_Texture* mainMenu::getTex()
{
	return tex;
}

SDL_Rect mainMenu::getCurrentFrame()
{
	return currentFrame;
}

void mainMenu::changeToPlay()
{
	tex = playTex;
}

void mainMenu::changeToOption()
{
	tex = optionTex;
}

void mainMenu::changeToNormal()
{
	tex = normalTex;
}