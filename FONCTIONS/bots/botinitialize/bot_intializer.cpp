

#include "../botlist.h"
#include "../../grid/AllGrids.h"
#include "../../grid/spawngrid.h"

#include "bot_intializer.h"


//// L'UNIQUE BOT INITIALIZER
////extern BotInitializer botInitializer;
//
//Bot* Create_New_Bot(BotType type, SpwCrd& spGrdCrd, bool isBotCustomised)	// NOT A MEMBBER OF CLASS BOT!!!
//{
//	// Pointeur vers le nouveau Bot créé
//	static Bot* newBot; newBot = NULL;				// Avec les thread, les variables static risquent de causé problème?
//	
//	if(!spawnGrid->Is_Inbound(spGrdCrd.border, spGrdCrd.spwNum))	// That ain't a valid spawn location braah
//		return newBot;
//	
//	//CRÉATION DU BOT
//	newBot = botList.Add_Bot(type, spGrdCrd, isBotCustomised);	// passage par référencex3...
//
//	return newBot;
//}
//
//
//




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






