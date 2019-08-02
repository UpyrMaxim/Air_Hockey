#include "BallLogic.h"



BallLogic::BallLogic(int ballSize = BALL_SIZE) : BasicGameObject(ballSize)
{
	x_pos = (WINDOW_W - Dest.w) / 2;
	y_pos = (WINDOW_H + SCORE_PANEL_H) / 2 + SCORE_PANEL_H;
	x_vel = 0;
	y_vel = 0;
	changePosition();
	ballSounds.AddWavChunk("Rebound", "audio/Rebound.wav");
	ballSounds.AddWavChunk("Hit", "audio/Hit.wav");
	ballSounds.AddWavChunk("Goal", "audio/Goal.wav");
}


BallLogic::~BallLogic()
{
}

int BallLogic::checkColision(const SDL_Rect & firstPlayer)
{
	checkWallColision();
	checkPlayersColision(firstPlayer);
	x_pos += x_vel / FPS;
	y_pos += y_vel / FPS;
	return 0;
}

int BallLogic::checkGOAL(ScorePanel & ScorePanel)
{
	float gatesStartX = WINDOW_W / 3;
	float gatesEndX = gatesStartX * 2;

	if (Dest.x > gatesStartX & Dest.x < gatesEndX)
	{
		if (Dest.y <= SCORE_PANEL_H + BALL_SIZE / 2)
		{
			ScorePanel.makePlayerGoal("PlayerScore", static_cast<int>(PlayerType::Player));
			ResetBall();
		}

		if (Dest.y >= WINDOW_H - BALL_SIZE - BUFFER_DISTANCE)
		{
			ScorePanel.makePlayerGoal("AIScore", static_cast<int>(PlayerType::AI));
			ResetBall();
		}
		
	}
	return 0;
}

int BallLogic::checkWallColision()
{
	if (x_pos <= BUFFER_DISTANCE)
	{
		x_pos = BUFFER_DISTANCE;
		x_vel = -x_vel * ATTENUATION_COEFFICIENT;
		ballSounds.playChunk("Rebound");
	}
	if (y_pos <= BUFFER_DISTANCE + SCORE_PANEL_H)
	{
		y_pos = BUFFER_DISTANCE + SCORE_PANEL_H;
		y_vel = -y_vel * ATTENUATION_COEFFICIENT;
		ballSounds.playChunk("Rebound");
	}
	if (x_pos >= WINDOW_W - Dest.w - BUFFER_DISTANCE)
	{
		x_pos = WINDOW_W - Dest.w - BUFFER_DISTANCE;
		x_vel = -x_vel * ATTENUATION_COEFFICIENT;
		ballSounds.playChunk("Rebound");
	}
	if (y_pos >= WINDOW_H - Dest.h - BUFFER_DISTANCE)
	{
		y_pos = WINDOW_H - Dest.h - BUFFER_DISTANCE;
		y_vel = -y_vel * ATTENUATION_COEFFICIENT;
		ballSounds.playChunk("Rebound");
	}
	return 0;
}

int BallLogic::checkPlayersColision(const SDL_Rect & player)
{
	if ( sqrt(
			   (x_pos + Dest.w / 2 - player.x - player.w / 2) * (x_pos + Dest.w / 2 - player.x - player.w / 2) + 
			   (y_pos + Dest.h /2 - player.y - player.h / 2) * (y_pos + Dest.h/2 - player.y - player.h / 2)
	         ) < BALL_SIZE / 2 + PLAYER_SIZE / 2)
	{
		if (abs(static_cast<int>(x_pos) - player.x) < BUFFER_DISTANCE) {
			x_vel = 0;
			y_vel = y_pos < player.y ? -SPEED: SPEED;

			x_pos += x_vel / FPS;
			y_pos += y_vel / FPS;
			return 0;
		}
		if (abs(static_cast<int>(y_pos) - player.y) < BUFFER_DISTANCE) {
			y_vel = 0;
			x_vel = x_pos < player.x ? -SPEED: SPEED ;

			x_pos += x_vel / FPS;
			y_pos += y_vel / FPS;
			return 0;
		}
		float coefX = abs(x_pos - player.x) / Dest.w;
		float coefY = abs(y_pos - player.y) / Dest.h;
		x_vel = x_pos < player.x ? -SPEED * coefX : SPEED * coefX;
		y_vel = y_pos < player.y ? -SPEED * coefY : SPEED * coefY;

		ballSounds.playChunk("Hit");
	}
	x_pos += x_vel / FPS;
	y_pos += y_vel / FPS;
	return 0;
}

int BallLogic::ResetBall()
{
	x_pos = (WINDOW_W - Dest.w) / 2;
	y_pos = (WINDOW_H + SCORE_PANEL_H) / 2 + SCORE_PANEL_H;
	x_vel = 0;
	y_vel = 0;
	ballSounds.playChunk("Goal");
	changePosition();
	return 0;
}

