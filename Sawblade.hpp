#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Sawblade
{
public:
	Sawblade(float p_x, float p_y, SDL_Texture* p_tex, float bulletSpeed, float p_dx, float p_dy);
	float getX();
	float getY();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	void move();
	bool isActive();
	void deactivate();
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;

	float velX, velY;
	bool active;
};