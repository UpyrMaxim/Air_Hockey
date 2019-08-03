#pragma once
#include "SDL2/SDL.h"
#include "Constants.cpp"
#include "BasicGameObject.h"
class PlayerLogic : public BasicGameObject
{
public:
	PlayerLogic(int size);
	~PlayerLogic();
	int checkColision();
};

