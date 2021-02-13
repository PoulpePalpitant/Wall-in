

#include "spawn_bot.h"
#include "../bots/botlist.h"
#include "bots_to_spawn.h"
#include "find_next_spawn_crd.h"
#include "valid_spwn_intervals.h"
#include "../grid/spawngrid.h"
#include "../bots/botmeta.h"
#include "../time/bot_move_cycle.h"
#include "../events/msg_dispatcher.h"

static void Spawn_Da_Bot_On_Da_Coord(SpwCrd crd)
{
	int botIndex = botList.Find_Available_Bot();	
	if (botIndex == -1)
		throw "There is too many bots, and it's getting buggy over here";
	else
		botList.bot[botIndex].Create_Bot(bots_to_spawn::type, crd, gCustomBot.is, bots_to_spawn::instantSpawn);	
}

static void Prevent_Overspawning()	
{
	if (gAllBotMeta.alive + bots_to_spawn::gNumSpawnTOT >= MAX_NUM_BOTS)				
	{
		int excess = gAllBotMeta.alive + bots_to_spawn::gNumSpawnTOT - MAX_NUM_BOTS;
		bots_to_spawn::gNumSpawnTOT -= excess;
	}
}
static SpwCrd spawn = {};

void Spawn_Bots()
{
	Prevent_Overspawning();	
	bots_to_spawn::Set_Randomness();	// Set le taux de random pour ce spawn cycle

	for (int &i = bots_to_spawn::gNumSpawnTOT; i > 0; i--)
	{
		spawn = Find_Spwn_Coord();			//retourne le spawn
		
		if (spawn.spwNum == -1)			// Le spawn à échoué
			continue;

		Spawn_Da_Bot_On_Da_Coord(spawn);
	}

	ValidSpwnIntervals::Reset_For_Next_Cycle();	// Doit ré-initialiser les listes à chaque cycle de spawn
	bots_to_spawn::Reset_To_Default();			// reset les valeurs par défaut pour le prochain spawn
}


void Spawn_A_Bot(Direction boxSide, int spwNum)	// Spawn un bot en dehors des cycles de spawn d'un niveau
{
	if (!gMoveBotsThisCycle)
		MsgQueue::Register(START_BOT_MOVE);	// Enable les bots pour qu'ils puissent bouger
	
	bots_to_spawn::Add_Spec(boxSide, spwNum );	
	Spawn_Bots();	
}

