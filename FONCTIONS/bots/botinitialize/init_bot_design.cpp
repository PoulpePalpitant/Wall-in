#include "../bot.h"


// INITIALISATION DU DESIGN DU BOT
// -------------------------------

void Bot::Init_Bot_Design(CustomBotStats& customBot)
{
	// Initialisation du "design" du bot( de son symbole )
	this->sym = BOT_DESIGN_1C[dir];

	if (customBot.is)
	{
		clr = customBot.clr;
		fixedColor = customBot.fixedColor;
	}
	else
	{
		switch (type)
		{
		case BotType::REGULAR: clr = WHITE; break;
		}
	}
}