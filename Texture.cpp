#include "Texture.h"
#include "stb_image.h"
Texture::Texture()
{
	mTexture = nullptr;
}
Texture::~Texture()
{}

bool Texture::init(const std::string& path)
{
	return false;
}
void Texture::cleanup()
{}

SDL_Texture* Texture::getTexture()
{
	return mTexture;
}
