#include "PlayerLogic.h"



PlayerLogic::PlayerLogic(int size = PLAYER_SIZE) : BasicGameObject(size)
{
	x_pos = (WINDOW_W - Dest.w) / 2;
	y_pos = (WINDOW_H - SCORE_PANEL_H - Dest.h);
	x_vel = SPEED;
	y_vel = SPEED;
}


PlayerLogic::~PlayerLogic()
{
}

int PlayerLogic::checkColision()
{
	int mouse_x, mouse_y;
	int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	int target_x = mouse_x - Dest.w / 2;
	int target_y = mouse_y - Dest.h / 2;
	float delta_x = target_x - x_pos;
	float delta_y = target_y - y_pos;
	float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

	if (distance < BUFFER_DISTANCE)
	{
		x_vel = y_vel = 0;
	}
	else
	{
		x_vel = delta_x * SPEED / distance;
		y_vel = delta_y * SPEED / distance;
	}
	x_pos += x_vel / FPS;
	y_pos += y_vel / FPS;

	if (x_pos <= BUFFER_DISTANCE)
		x_pos = BUFFER_DISTANCE;
	if (y_pos <= WINDOW_H / 2 + BUFFER_DISTANCE)
		y_pos = WINDOW_H / 2 + BUFFER_DISTANCE;
	if (x_pos >= WINDOW_W - Dest.w - BUFFER_DISTANCE)
		x_pos = WINDOW_W - Dest.w - BUFFER_DISTANCE;
	if (y_pos >= WINDOW_H - Dest.h - BUFFER_DISTANCE)
		y_pos = WINDOW_H - Dest.h - BUFFER_DISTANCE;
	return 0;
}