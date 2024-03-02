#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Cat
{
public:
	Cat(float p_x, float p_y, SDL_Texture* p_tex, float p_velocity);
	float getX();
	float getY();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	//Entity

	void handleEvent(SDL_Event& e);
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	//Entity

	float velocity;
};