#include "ScorePanel.h"



ScorePanel::ScorePanel(InitSdl * MainObj)
{
	mainObj = MainObj;
	playerScore = -1;
	AIScore = -1;

	makePlayerGoal("AIScore", static_cast<int>(PlayerType::AI));
	makePlayerGoal("PlayerScore", static_cast<int>(PlayerType::Player));
}

int ScorePanel::makePlayerGoal(const char * player, int playerType)
{
	int fontsize = 50;
	SDL_Color text_color = { 0,0,0 };
	std::string fontpath = "OpenSans-Regular.ttf";
	std::string text = std::to_string(playerType ? ++AIScore : ++playerScore);
	TTF_Font* font = TTF_OpenFont(fontpath.c_str(), fontsize);
	SDL_Texture* ftexture;

	if (font == NULL){
		SDL_Log("Failed the load the font!\n SDL_TTF Error: : %s", TTF_GetError());
		return 1;
	}

	// now create a surface from the font
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);

	// render the text surface
	if (text_surface == NULL) 
	{
		SDL_Log("Failed to render text surface!\n SDL_TTF Error: : %s", TTF_GetError());
		return 1;
	}
	ftexture = SDL_CreateTextureFromSurface(mainObj->getRenderer(), text_surface);
	mainObj->setTextureBySurface(player, *text_surface);
	SDL_FreeSurface(text_surface);
	return 0;
}



ScorePanel::~ScorePanel()
{
}
