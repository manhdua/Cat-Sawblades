#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Cat.hpp"

class Sawblade
{
public:
	Sawblade(float p_x, float p_y, SDL_Texture* p_red, SDL_Texture* p_green, float bulletSpeed, float p_dx, float p_dy);
	int getX();
	int getY();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	void move();
	bool isActive();
	void deactivate();
	void changeToGreen();
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;

	float velX, velY;
	bool active;
	SDL_Texture* greenTex;
};