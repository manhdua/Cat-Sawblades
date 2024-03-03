#include "Cat.hpp"
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

Cat::Cat(float p_x, float p_y, SDL_Texture* p_tex, float p_velocity)
	:x(p_x), y(p_y), tex(p_tex), CatVel(p_velocity), currentVel(0), isRight(1)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32; //256 chia 8
	currentFrame.h = 32;
}

float Cat::getX()
{
	return x;
}

float Cat::getY()
{
	return y;
}

SDL_Texture* Cat::getTex()
{
	return tex;
}

SDL_Rect Cat::getCurrentFrame()
{
	return currentFrame;
}

void Cat::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			currentVel -= CatVel;
			isRight = false;
			break;
		case SDLK_RIGHT:
			currentVel += CatVel;
			isRight = true;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			currentVel += CatVel;
			break;
		case SDLK_RIGHT:
			currentVel -= CatVel;
			break;
		}
	}
}

void Cat::idleRightAnimation(int &frameTime)
{
	frameTime++;
	currentFrame.y = 0;
	if (60 / frameTime == 4) //60 la FPS cua game
	{
		frameTime = 0;
		currentFrame.x += 32; //32 la frameWidth
		if (currentFrame.x >= 256) //256 la textureWidth
			currentFrame.x = 0;
	}
}

void Cat::idleLeftAnimation(int& frameTime)
{
	frameTime++;
	currentFrame.y = 128;
	if (60 / frameTime == 4) //60 la FPS cua game
	{
		frameTime = 0;
		currentFrame.x += 32; //32 la frameWidth
		if (currentFrame.x >= 256) //256 la textureWidth
			currentFrame.x = 0;
	}
}

void Cat::moveRightAnimation(int &frameTime)
{
	frameTime++;
	currentFrame.y = 32;
	if (60 / frameTime == 4)
	{
		frameTime = 0;
		currentFrame.x += 32; //32 la frameWidth
		if (currentFrame.x >= 128) //256 la textureWidth
			currentFrame.x = 0;
	}
}

void Cat::moveLeftAnimation(int& frameTime)
{
	frameTime++;
	currentFrame.y = 160;
	if (60 / frameTime == 4)
	{
		frameTime = 0;
		currentFrame.x += 32; //32 la frameWidth
		if (currentFrame.x >= 128) //256 la textureWidth
			currentFrame.x = 0;
	}
}

void Cat::move()
{
	x += currentVel;
}

float Cat::getCurrentVel()
{
	return currentVel;
}

bool Cat::getIsRight()
{
	return isRight;
}