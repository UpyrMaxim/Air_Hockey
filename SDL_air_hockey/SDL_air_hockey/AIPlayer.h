#pragma once
#include "BasicGameObject.h"
#include "Constants.cpp"

class AIPlayer : public BasicGameObject
{
public:
	AIPlayer(int size);
	~AIPlayer();

	int checkColision(const SDL_Rect & ball);
private:
	int checkWallColision();
	int changeDirectionToBall(const SDL_Rect & player);
};

