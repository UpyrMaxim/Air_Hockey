#include "AIPlayer.h"
#include <iostream>


AIPlayer::AIPlayer(int size = PLAYER_SIZE) : BasicGameObject(size)
{
	x_pos = (WINDOW_W - Dest.w) / 2;
	y_pos = (SCORE_PANEL_H * 2 + Dest.h);
	x_vel = SPEED;
	y_vel = SPEED;
}

AIPlayer::~AIPlayer()
{
}

int AIPlayer::checkColision(const SDL_Rect & ball)
{
	changeDirectionToBall(ball);
	checkWallColision();
	return 0;
}

int AIPlayer::checkWallColision()
{
	x_pos += x_vel / FPS;
	y_pos += y_vel / FPS;

	if (x_pos <= BUFFER_DISTANCE)
		x_pos = BUFFER_DISTANCE;
	if (y_pos <= BUFFER_DISTANCE + SCORE_PANEL_H)
		y_pos = BUFFER_DISTANCE + SCORE_PANEL_H;
	if (x_pos >= WINDOW_W - Dest.w - BUFFER_DISTANCE)
		x_pos = WINDOW_W - Dest.w - BUFFER_DISTANCE;
	if (y_pos >= (WINDOW_H - SCORE_PANEL_H) / 2 + SCORE_PANEL_H - Dest.h - BUFFER_DISTANCE)
		y_pos = (WINDOW_H - SCORE_PANEL_H) / 2 + SCORE_PANEL_H - Dest.h - BUFFER_DISTANCE;
	return 0;
}

int AIPlayer::changeDirectionToBall(const SDL_Rect & ball)
{
	int target_x = ball.x - Dest.w / 2;
	int target_y = ball.y - Dest.h / 2;
	float delta_x = target_x - x_pos;
	float delta_y = target_y - y_pos;
	float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

	x_vel = delta_x * SPEED / distance;
	y_vel = delta_y * SPEED / distance;
	
	return 0;
}
