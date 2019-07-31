#include "SDL.h"
#include "InitSdl.h"
#include "SDL_mixer.h"
#include "BallLogic.h"
#include "PlayerLogic.h"
#include "Constants.cpp"
#include "AIPlayer.h"
#include "ScorePanel.h"
#include "Audio.h"


int initGame(InitSdl &);

int main(int argc, char *argv[]) 
{
	SDL_Rect Arena;
	Arena.x = 0;
	Arena.y = SCORE_PANEL_H;
	Arena.w = WINDOW_W;
	Arena.h = WINDOW_H - SCORE_PANEL_H;

	SDL_Rect ScorePanelRect;
	ScorePanelRect.x = 0;
	ScorePanelRect.y = 0;
	ScorePanelRect.w = WINDOW_W;
	ScorePanelRect.h = SCORE_PANEL_H;

	SDL_Rect AIScore;
	AIScore.x = 350;
	AIScore.y = 10;
	AIScore.w = 50;
	AIScore.h = 30;

	SDL_Rect PlayerScore;
	PlayerScore.x = 180;
	PlayerScore.y = 10;
	PlayerScore.w = 50;
	PlayerScore.h = 30;

	SDL_Rect Score;
	InitSdl AirHockeyMain(SDL_INIT_AUDIO );
	Audio AudioObject("audio/Battle in the winter.mp3");
	bool success = !initGame(AirHockeyMain);
	if (success)
	{

		BallLogic BallObject(BALL_SIZE);
		PlayerLogic PlayerObject(PLAYER_SIZE);
		AIPlayer AIPlayerObject(PLAYER_SIZE);
		ScorePanel ScorePanelObject(&AirHockeyMain);
		AudioObject.playBackgroundMusic();
		int close_requested = 0;
		// animation loop
		while (!close_requested)
		{
			// process events
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					close_requested = 1;
				}
			}

			PlayerObject.checkColision();
			PlayerObject.changePosition();

			AIPlayerObject.checkColision(BallObject.getDest());
			AIPlayerObject.changePosition();

			BallObject.checkColision(BallObject.getDest().y > (WINDOW_H + SCORE_PANEL_H) / 2 ?
				PlayerObject.getDest() : AIPlayerObject.getDest());
			BallObject.changePosition();
			BallObject.checkGOAL(ScorePanelObject);

			// clear the window
			SDL_RenderClear(AirHockeyMain.getRenderer());

			// draw the window
			SDL_RenderCopy(AirHockeyMain.getRenderer(), AirHockeyMain.getTexture("Arena"), NULL, &Arena);
			SDL_RenderCopy(AirHockeyMain.getRenderer(), AirHockeyMain.getTexture("ScorePanel"), NULL, &ScorePanelRect);
			SDL_RenderCopy(AirHockeyMain.getRenderer(), AirHockeyMain.getTexture("Player"), NULL, &PlayerObject.getDest());
			SDL_RenderCopy(AirHockeyMain.getRenderer(), AirHockeyMain.getTexture("AI"), NULL, &AIPlayerObject.getDest());
			SDL_RenderCopy(AirHockeyMain.getRenderer(), AirHockeyMain.getTexture("PlayerScore"), NULL, &PlayerScore);
			SDL_RenderCopy(AirHockeyMain.getRenderer(), AirHockeyMain.getTexture("AIScore"), NULL, &AIScore);
			SDL_RenderCopy(AirHockeyMain.getRenderer(), AirHockeyMain.getTexture("Ball"), NULL, &BallObject.getDest());
			SDL_RenderPresent(AirHockeyMain.getRenderer());

			SDL_Delay(1000 / FPS);
		}
		return 0;
	}
	return 1;
}

int initGame(InitSdl & AirHockeyMain)
{

	if (
		AirHockeyMain.getInitStatus() ||
		AirHockeyMain.initWindow("Air Hockey", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_W, WINDOW_H,
			SDL_WINDOW_OPENGL) ||
		AirHockeyMain.initRender(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ||
		AirHockeyMain.setTextureByFile("Arena", "img/Arena.bmp") ||
		AirHockeyMain.setTextureByFile("Ball", "img/Ball.bmp", true) ||
		AirHockeyMain.setTextureByFile("Player", "img/Player.bmp", true) ||
		AirHockeyMain.setTextureByFile("AI", "img/AI.bmp",true) ||
		AirHockeyMain.setTextureByFile("ScorePanel", "img/ScorePanel.bmp")) {
		std::cerr << "Smth was wrong! Check the log files" << std::endl;
		return 1;
	}

	return 0;
}
