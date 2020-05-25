

#include "bot_intializer.h"
#include "../botlist.h"


// L'UNIQUE BOT INITIALIZER
//extern BotInitializer botInitializer;

Bot* Create_New_Bot(BotType type, GrdCoord& spGrdCrd, bool isBotCustomised)	// NOT A MEMBBER OF CLASS BOT!!!
{
	// Pointeur vers le nouveau Bot créé
	static Bot* newBot = NULL;				// Avec les thread, les variables static risquent de causé problème?

	//CRÉATION DU BOT
	newBot = botList.Add_Bot(type, spGrdCrd, isBotCustomised);	// passage par référencex3...

	return newBot;
}


//void Bot::Create_Spawn_Warning(Direction botDir, Cptr warnCycles = SPWN_DLAY)
//{
//	switch (BotType)
//	{
//	case BotType::REGULAR:
//		break;
//	case BotType::TOUGH:
//		break;
//	case BotType::SUPERSONIC:
//		break;
//	case BotType::GHOSTER:
//		break;
//	default:
//		break;
//	}
//
//
//	this->spwnWarning = new SpawnWarning(botDir, warnCycles);
//}






