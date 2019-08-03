#pragma once
#include "SDL2/SDL.h"
#include "Constants.cpp"
#include "BasicGameObject.h"
#include <math.h>
#include "InitSdl.h"
#include "ScorePanel.h"
#include "Audio.h"

class BallLogic : public BasicGameObject
{
public:
	
    BallLogic(int ballSize);
	~BallLogic();

	int checkColision(const SDL_Rect & firstPlayer);
	int checkGOAL(ScorePanel &);
private:
	int checkWallColision();
	int checkPlayersColision(const SDL_Rect & player);
	int ResetBall();
private:
	Audio ballSounds;
};

