#pragma once
#include <SDL.h>
#include <SDL_image.h>

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp(); //Destroy a window
	void clear(); //Clear the current rendering target with the drawing color.
	void render(SDL_Texture* p_tex); //Copy a portion of the texture to the current rendering target.
	void display(); //Update the screen with any rendering performed since the previous call.
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};