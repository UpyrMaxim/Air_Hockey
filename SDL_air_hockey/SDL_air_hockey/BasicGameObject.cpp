#include "BasicGameObject.h"

BasicGameObject::BasicGameObject(int size = PLAYER_SIZE)
{
	Dest.w = size;
	Dest.h = size;
}

BasicGameObject::~BasicGameObject()
{
}

int BasicGameObject::changePosition()
{
	Dest.y = static_cast<int>(y_pos);
	Dest.x = static_cast<int>(x_pos);
	return 0;
}


SDL_Rect BasicGameObject::getDest()
{
	return Dest;
}