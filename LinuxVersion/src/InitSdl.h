#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>
#include <map>
#include <memory>

struct sdl_deleter
{
	void operator()(SDL_Window *p) const 
	{ 
		SDL_DestroyWindow(p);
	}
	void operator()(SDL_Renderer *p) const
	{ 
		SDL_DestroyRenderer(p); 
	}
	void operator()(SDL_Texture *p) const
	{ 
		SDL_DestroyTexture(p); 
	}
	void operator()(SDL_Surface *p) const
	{
		SDL_FreeSurface(p);
	}
};

class InitSdl
{
public:
	// init smth
	InitSdl(long SDL_PROPERTIES);
	int initWindow(const char * windowTitle, long initialX, long initialY, long width, long height, long flags);
	int initRender(long flags);
	int setTextureByFile(const char * textureName, const char * imageName, bool  deleteWhiteColor = false);
	int setTextureBySurface(const char * textureName,SDL_Surface & surface);
	// get smth
	SDL_Window * getWindow();
	SDL_Renderer * getRenderer();
	int getInitStatus();
	SDL_Texture * getTexture(const char *);

	~InitSdl();
private:
	std::unique_ptr<SDL_Window, sdl_deleter> window;
	std::unique_ptr<SDL_Renderer, sdl_deleter> renderer;
	std::map<const char *, std::unique_ptr<SDL_Texture, sdl_deleter>> texturesMap;
	int status;
};

