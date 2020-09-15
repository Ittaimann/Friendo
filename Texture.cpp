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
    int req_format = STBI_rgb;
    int width, height, orig_format;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &orig_format, req_format);
    if (data == NULL) {
        SDL_Log("Loading image failed: %s", stbi_failure_reason());
        exit(1);
    }

    // Set up the pixel format color masks for RGB(A) byte arrays.
    // Only STBI_rgb (3) and STBI_rgb_alpha (4) are supported here!
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    int shift = (req_format == STBI_rgb) ? 8 : 0;
    rmask = 0xff000000 >> shift;
    gmask = 0x00ff0000 >> shift;
    bmask = 0x0000ff00 >> shift;
    amask = 0x000000ff >> shift;
#else // little endian, like x86
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = (req_format == STBI_rgb) ? 0 : 0xff000000;
#endif

    int depth, pitch;
    if (req_format == STBI_rgb) {
        depth = 24;
        pitch = 3 * width; // 3 bytes per pixel * pixels per row
    }
    else { // STBI_rgb_alpha (RGBA)
        depth = 32;
        pitch = 4 * width;
    }

    SDL_Surface* surf = SDL_CreateRGBSurfaceFrom((void*)data, width, height, depth, pitch,
        rmask, gmask, bmask, amask);

    if (surf == NULL) {
        SDL_Log("Creating surface failed: %s", SDL_GetError());
        stbi_image_free(data);
        exit(1);
    }

    mTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    stbi_image_free(data);
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
