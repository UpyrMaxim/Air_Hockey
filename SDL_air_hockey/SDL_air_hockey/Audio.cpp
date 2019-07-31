#include "Audio.h"



Audio::Audio(const char * soundName)
{
	SetBackgroundMusic(soundName);
}


Audio::Audio()
{
}

Audio::~Audio()
{
}

int Audio::AddWavChunk(const char * chunkName, const char * wavFileName)
{
	std::unique_ptr<Mix_Chunk, mix_deleter> chunk = std::unique_ptr<Mix_Chunk, mix_deleter>(Mix_LoadWAV(wavFileName), mix_deleter());
	if (!chunk.get()) {
		SDL_Log("Mix_LoadWAV(\"%s\"): %s\n", chunkName, Mix_GetError());
	}
	chunksMap[chunkName] = std::move(chunk);
	return 0;
}

int Audio::SetBackgroundMusic(const char * musicName)
{
	std::unique_ptr<Mix_Music, mix_deleter> backgroundSound = std::unique_ptr<Mix_Music, mix_deleter>(Mix_LoadMUS(musicName), mix_deleter());
	if (!backgroundSound.get()) {
		SDL_Log("Mix_LoadMUS(\"%s\"): %s\n", musicName,Mix_GetError());
		return 1;
	}
	backgroundMusic = std::move(backgroundSound);
	return 0;
}

int Audio::removeChunk(const char * chunkName)
{
	chunksMap.erase(chunkName);
	return 0;
}

int Audio::haltMusic()
{
	Mix_HaltMusic();
	return 0;
}

int Audio::playBackgroundMusic()
{
	Mix_PlayMusic(backgroundMusic.get(), -1);
	return 0;
}

int Audio::playChunk(const char * chunkName)
{
	if (chunksMap[chunkName].get()) {
		Mix_PlayChannel(-1, chunksMap[chunkName].get(), 0);
	} else {
		SDL_Log("chunk with name \"%s\") not found\n", chunkName);
	}
	return 0;
}
