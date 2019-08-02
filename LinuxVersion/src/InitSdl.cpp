#include "InitSdl.h"


InitSdl::InitSdl(long SDL_PROPERTIES)
{
	if (SDL_Init(SDL_PROPERTIES) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		status = 1;
	}

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		status = 2;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	status = 0;
}
int InitSdl::initWindow(const char * windowTitle, long initialX, long initialY, long width, long height, long flags)
{
	// Create an application window with the following settings:
	window = std::unique_ptr<SDL_Window,sdl_deleter>(SDL_CreateWindow(
		windowTitle,		   // window title
		initialX,			   // initial x position
		initialY,			   // initial y position
		width,                 // width, in pixels
		height,                // height, in pixels
		flags                  // flags - see below
	),sdl_deleter());

	if (!window.get())
	{
		SDL_Log("Unable to initialize Window: %s", SDL_GetError());
		return 1;
	}
	return 0;
}

int InitSdl::initRender(long flags)
{
	if (!window.get())
	{
		SDL_Log("Need to create window!");
		return 2;
	}
	renderer = std::unique_ptr<SDL_Renderer, sdl_deleter>(SDL_CreateRenderer(window.get(), -1, flags),sdl_deleter());
	if (!renderer.get())
	{
		SDL_Log("Unable to initialize renderer: %s", SDL_GetError());
		return 1;
	}
	return 0;
}

int InitSdl::setTextureByFile(const char * textureName, const char * imageName, bool deleteWhiteColor)
{
	auto surface = std::unique_ptr<SDL_Surface, sdl_deleter>(SDL_LoadBMP(imageName),sdl_deleter());
	if (!surface.get())
	{
		SDL_Log("Unable to initialize SDL_Surface: %s", SDL_GetError());
		return 1;
	}
	if (deleteWhiteColor) {
		Uint32 colorkey = SDL_MapRGB(surface.get()->format, 255, 255, 255);
		SDL_SetColorKey(surface.get(), SDL_TRUE, colorkey);
	}
	return setTextureBySurface(textureName, *surface.get());
}

int InitSdl::setTextureBySurface(const char * textureName, SDL_Surface & surface)
{
	if (!renderer.get())
	{
		SDL_Log("Need to initialize renderer");
		return 1;
	}
	texturesMap[textureName] = std::unique_ptr<SDL_Texture, sdl_deleter>(SDL_CreateTextureFromSurface(renderer.get(), &surface), sdl_deleter());
	return 0;
}

SDL_Window * InitSdl::getWindow()
{
	return window.get();
}

SDL_Renderer * InitSdl::getRenderer()
{
	return renderer.get();
}

int InitSdl::getInitStatus()
{
	return status;
}

SDL_Texture * InitSdl::getTexture(const char *name)
{
	return texturesMap[name].get();
}

InitSdl::~InitSdl()
{
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}
