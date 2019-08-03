#pragma once
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_log.h"
#include <map>
#include <memory>

struct mix_deleter
{
	void operator()(Mix_Chunk *p) const
	{
		Mix_FreeChunk(p);
	}
	void operator()(Mix_Music *p) const
	{
		Mix_FreeMusic(p);
	}
};

class Audio
{
public:
	Audio();
	Audio(const char* soundName);
	~Audio();
	int AddWavChunk(const char * chunkName, const char * fileName);
	int SetBackgroundMusic(const char * musicName);
	int removeChunk(const char * chunkName);
	int haltMusic();
	int playBackgroundMusic();
	int playChunk(const char * chunkName);
private:
	std::map<const char *, std::unique_ptr<Mix_Chunk, mix_deleter>> chunksMap;
	std::unique_ptr<Mix_Music, mix_deleter > backgroundMusic;
};

