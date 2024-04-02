#pragma once
#include <SDL.h>
#include <SDL_image.h>

class mainMenu
{
public:
	mainMenu(float p_x, float p_y, SDL_Texture* p_tex, SDL_Texture* p_play, SDL_Texture* p_option);

	//Lay gia tri x va y
	float getX();
	float getY();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	void changeToPlay();
	void changeToOption();
	void changeToNormal();
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	SDL_Texture* playTex;
	SDL_Texture* optionTex;
	SDL_Texture* normalTex;
};