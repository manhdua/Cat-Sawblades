#include "Sawblade.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>

Sawblade::Sawblade(float p_x, float p_y, SDL_Texture* p_tex, float p_bulletSpeed, float p_dx, float p_dy)
	:x(p_x), y(p_y), tex(p_tex), active(1)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	
	float magnitude = sqrt(p_dx * p_dx + p_dy * p_dy);
	velX = p_dx / magnitude * p_bulletSpeed;
	velY = p_dy / magnitude * p_bulletSpeed;
}

float Sawblade::getX()
{
	return x;
}

float Sawblade::getY()
{
	return y;
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
}

bool Sawblade::isActive()
{
	return active;
}

void Sawblade::deactivate()
{
	active = false;
}