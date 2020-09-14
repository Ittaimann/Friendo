#pragma once
#include<SDL.h>
#include<string>

// single texture to load and get
class Texture
{
public:
	Texture();
	~Texture();

	bool init(const std::string& path);
	void cleanup();

	SDL_Texture* getTexture();
private:
	SDL_Texture* mTexture;
};

