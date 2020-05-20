

#include "../bot.h"

// INITIALISE LES STATS DU BOT
// ---------------------------

void Bot::Init_Bot_Stats(CustomBot* customBot)											// Le type du Bot doit être initialisé d'abord
{
	switch (type)		// Le type du nouveau bot
	{
	case BotType::SUPERSONIC:  health = 1; speed = 2; break;	// suprafast
	case BotType::GHOSTER:  health = 1;break;		// who a you?
	case BotType::REGULAR: health = 1; break;		// 1 de vie c'est bien e n masse
	case BotType::TOUGH: health = 3; break;			// supra stronk

	}
}
