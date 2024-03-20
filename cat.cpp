#include "Cat.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>

Cat::Cat(float p_x, float p_y, SDL_Texture* p_tex, float p_velocity, Mix_Chunk* p_sound)
	:x(p_x), y(p_y), tex(p_tex), CatVelX(p_velocity), currentVelX(0), isRight(1), isJumping(0), gravity(0.5),
	JumpForce(13), CatVelY(0), doubleJumped(0), jumped(0), doubleJumpForce(12), jumpSound(p_sound)
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
			currentVelX -= CatVelX;
			isRight = false;
			break;
		case SDLK_RIGHT:
			currentVelX += CatVelX;
			isRight = true;
			break;
		case SDLK_UP:
			if (!isJumping && !jumped)
			{
				CatVelY = -JumpForce;
				isJumping = true;
				jumped = true;
			}
			else if (isJumping && !doubleJumped)
			{
				CatVelY = -doubleJumpForce;
				doubleJumped = true;
			}
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			currentVelX += CatVelX;
			break;
		case SDLK_RIGHT:
			currentVelX -= CatVelX;
			break;
		}
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
	x += currentVelX;
}

float Cat::getCurrentVel()
{
	return currentVelX;
}

bool Cat::getIsRight()
{
	return isRight;
}

void Cat::jump()
{
	CatVelY += gravity;
	y += CatVelY;
	if (y >= 611)
	{
		y = 611;
		CatVelY = 0;
		jumped = false;
		isJumping = false;
		doubleJumped = false;
	}
}

bool Cat::getIsJumping()
{
	return isJumping;
}

void Cat::collideWithWall()
{
	if (x <= 398) x = 398;
	if (x >= 820) x = 820;
}

void Cat::restartPos()
{
	x = 630;
	y = 611;
}