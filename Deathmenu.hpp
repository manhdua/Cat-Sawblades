#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Deathmenu
{
public:
	Deathmenu(float p_x, float p_y, SDL_Texture* p_tex, SDL_Texture* p_tryAgain, SDL_Texture* p_quit, SDL_Texture* p_option);

	//Lay gia tri x va y
	float getX();
	float getY();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	void changeToTryAgain();
	void changeToQuit();
	void changeToNormal();
	void changeToOption();
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	SDL_Texture* tryAgainTex;
	SDL_Texture* quitTex;
	SDL_Texture* normalTex;
	SDL_Texture* optionTex;
};