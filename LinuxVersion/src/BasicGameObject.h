#pragma once
#include "SDL2/SDL.h"
#include "Constants.cpp"

class BasicGameObject
{
public:
	BasicGameObject(int size);
	virtual ~BasicGameObject();
	int changePosition();
	SDL_Rect getDest();
protected:
	float x_pos;
	float y_pos;
	float x_vel;
	float y_vel;

	SDL_Rect Dest;
};
