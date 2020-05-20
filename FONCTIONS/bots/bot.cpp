
#include "bot.h"

extern CustomBot gCustomBot = {};	// Permet de faire des bots customs 

// Change la couleur du BOT selon sa progression
// ----------------------------------------------

void Bot::Upd_Progression_Color(Colors& Color, int NumStepsLeft, int Max_Steps)
{
	int Halfway = Max_Steps / 2;	// Le bot est à moitié chemin >:| 
	int HURRY = 10;					// Il reste 10 bot moves!!

	if (NumStepsLeft == Halfway)
		Color = Colors::LIGHT_YELLOW;
	else if (NumStepsLeft == HURRY)
		Color = Colors::LIGHT_RED;
}
