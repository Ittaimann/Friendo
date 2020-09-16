#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
	mTexture = nullptr;
}

Texture::~Texture()
{
    cleanup();
}

bool Texture::init(SDL_Renderer* renderer,const std::string& path)
{
    //todo: work on understanding stbi and maybe reading meta data from 
    // images. as well as the rest of this 
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &orig_format, req_format);
    if (data == NULL) {
        SDL_Log("Loading image failed: %s", stbi_failure_reason());
        return false; // fucking crash
    }
    //nani the fuck
    int depth, pitch;
    if (req_format == STBI_rgb) {
        depth = 24;
        pitch = 3 * width; // 3 bytes per pixel * pixels per row
    }
    else { // STBI_rgb_alpha (RGBA)
        depth = 32;
        pitch = 4 * width;
    }

    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormatFrom((void*)data, width, height, depth, pitch, SDL_PIXELFORMAT_RGBA32);

    if (surf == NULL) {
        SDL_Log("Creating surface failed: %s", SDL_GetError());
        stbi_image_free(data);
        return false; // fucking crash
    }

    mTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf); // free sdl surface data
    stbi_image_free(data); // free image data
    return true;
}

void Texture::cleanup()
{
    
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
}

SDL_Texture* Texture::getTexture()
{
	return mTexture;
}
