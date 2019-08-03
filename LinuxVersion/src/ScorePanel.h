#pragma once
#include "InitSdl.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

enum class PlayerType
{
	Player = 0, AI = 1
};

class ScorePanel
{
public:
	ScorePanel(InitSdl * mainObj);
	int makePlayerGoal(const char * player, int playerType);
	~ScorePanel();
private:
	InitSdl * mainObj;
	int playerScore;
	int AIScore;
};

