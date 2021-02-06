

#include "../bot.h"

// INITIALISE LES STATS DU BOT
// ---------------------------


// Il n'y a qu'un seul type de bots finalement
void Bot::Init_Bot_Stats(CustomBotStats& customBot)								
{
	switch (type)		
	{
	case BotType::REGULAR: hp = 1;speed = 1; break;			
	}
}
