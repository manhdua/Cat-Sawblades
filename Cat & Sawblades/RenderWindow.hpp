#pragma once
#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp(); //Destroy a window
	void clear(); //Clear the current rendering target with the drawing color.
	void render(Entity& p_entity); //Copy a portion of the texture to the current rendering target. - use referene to optimize
	void display(); //Update the screen with any rendering performed since the previous call.
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};