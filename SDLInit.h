#pragma once
#include <SDL.h>

class SDLInit
{
public:
	// constructor
	SDLInit();
	//destructor
	~SDLInit();
	//actual init
	bool init(const int width, const int height);
	void cleanup();

	SDL_Window* getWindow();
	SDL_Surface* getScreenSurface();
	SDL_Renderer* getRenderer(); // This seems like it might need to be a singleton?

private:
	SDL_Window* mWindow;
	SDL_Surface* mScreenSurface;
	SDL_Renderer* mRenderer;
};

