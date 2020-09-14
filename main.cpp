//Using SDL and standard IO
#include <SDL.h>
#include <iostream>
#include "SDLInit.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool loadMedia(SDL_Surface*& HelloWorld) // gross lets make sure this aint it
{
    //Loading success flag
    bool success = true;

    //Load splash image
    HelloWorld = SDL_LoadBMP("Assets/hello_world.bmp");
    if (HelloWorld == nullptr)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

int main(int argc, char* argv[])
{
    SDLInit instance;
    bool result = instance.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    bool quit = false;
    SDL_Event e;
    SDL_Surface* HelloWorld = nullptr;
    if (!loadMedia(HelloWorld))
    {
        std::cout << "FUCK" << std::endl;
    }
    else
    {
        while (result && !quit)
        {
            //Software based rendering, replace with hardware alternative
            SDL_BlitSurface(HelloWorld, NULL, instance.getScreenSurface(), NULL);
            //Update the surface
            SDL_UpdateWindowSurface(instance.getWindow());
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
        }
    }
    SDL_FreeSurface(HelloWorld);
    HelloWorld = nullptr;
    instance.cleanup();
    return 0;
}   

