

#include "../bot.h"

// INITIALISE LES STATS DU BOT
// ---------------------------

void Bot::Init_Bot_Stats(CustomBotStats* customBot)											// Le type du Bot doit être initialisé d'abord
{
	switch (type)		// Le type du nouveau bot
	{
	case BotType::SUPERSONIC:  power = 1; speed = 1; break;	// suprafast	
	case BotType::GHOSTER:  power = 1;break;		// who a you?
	case BotType::REGULAR: power = 1; break;		// 1 de vie c'est bien e n masse
	case BotType::TOUGH: power = 3; break;			// supra stronk

	}
}
