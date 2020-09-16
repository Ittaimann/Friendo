//Using SDL and standard IO
#include <SDL.h>
#include <iostream>
#include "SDLInit.h"
#include "Texture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
    SDLInit instance;
    bool result = instance.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    bool quit = false;
    SDL_Event e;
    SDL_Surface* HelloWorld = nullptr;
    Texture testTexure;
    testTexure.init(instance.getRenderer(),"./Assets/hello_world.bmp");
    while (result && !quit)
    {
        SDL_RenderClear(instance.getRenderer());

        //Render texture to screen
        SDL_RenderCopy(instance.getRenderer(), testTexure.getTexture(), NULL, NULL);

        //Update screen
        SDL_RenderPresent(instance.getRenderer());

        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }
    
    instance.cleanup();
    return 0;
}   

