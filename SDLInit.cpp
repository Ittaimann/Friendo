#include <iostream>
#include "SDLInit.h"
SDLInit::SDLInit()
{
    mWindow = nullptr;
    mScreenSurface = nullptr;
}
SDLInit::~SDLInit()
{

}

// initialize the sdl.
bool SDLInit::init(const int width, const int height)
{
	bool result = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout<<"SDL could not initialize, SDL_ERROR: "<< SDL_GetError()<<std::endl;
        result = false;
    }
    else
    {
        // create the window
        mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (mWindow == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            result = false;
        }
        else
        {
            //Get window surface
            mScreenSurface = SDL_GetWindowSurface(mWindow);
        }
    }
	return result;
}

void SDLInit::cleanup()
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

SDL_Window* SDLInit::getWindow()
{
    return mWindow;
}
SDL_Surface* SDLInit::getScreenSurface()
{
    return mScreenSurface;
}
