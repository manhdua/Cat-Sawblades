#include "Sawblade.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include "Cat.hpp"

Sawblade::Sawblade(float p_x, float p_y, SDL_Texture* p_red, SDL_Texture* p_green, float p_bulletSpeed, float p_dx, float p_dy)
	:x(p_x), y(p_y), tex(p_red), greenTex(p_green), active(1)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	
	float magnitude = sqrt(p_dx * p_dx + p_dy * p_dy);
	velX = p_dx / magnitude * p_bulletSpeed;
	velY = p_dy / magnitude * p_bulletSpeed;
}

int Sawblade::getX()
{
	return (int)x;
}

int Sawblade::getY()
{
	return (int)y;
}

SDL_Texture* Sawblade::getTex()
{
	return tex;
}

SDL_Rect Sawblade::getCurrentFrame()
{
	return currentFrame;
}

void Sawblade::move()
{
	x += velX;
	y += velY;
	if (x <= 398) velX = -velX;
	if (x >= 820) velX = -velX;
	if (y >= 611) velY = -velY;

	
}

bool Sawblade::isActive()
{
	return active;
}

void Sawblade::deactivate()
{
	active = false;
}

void Sawblade::changeToGreen()
{
	tex = greenTex;
}