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
	void move();
	void moveRightAnimation(int &frameTime);
	void moveLeftAnimation(int& frameTime);
	float getCurrentVel();
	bool getIsRight();
	void jump();
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	//Entity

	float currentVelX;
	float CatVelX;
	bool isRight;
	bool isJumping;

	float gravity;
	float JumpForce;
	float CatVelY;
};