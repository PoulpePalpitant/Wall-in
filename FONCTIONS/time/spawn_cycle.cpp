
#include "timerOP.h"
#include "../spawns/spawn_bot.h"

#include "spawn_cycle.h"


bool gSpawnThisCycle;
int gSpawnCycleTot;						// Le nombre total de spawn cycle ayant u lieu
//int gSpawnCycleTot = 120;						// Le nombre total de spawn cycle ayant u lieu

SpeedTimer gSpwBotTimer;

void Reset_Spw_Cycle()				// Reset le nombre de spw cycle à 0
{
	gSpawnCycleTot = 0;
}

void UPD_Spawn_Cycle()			// Refresh Timer des spawns
{
	while (gSpwBotTimer.Tick())
	{
		gSpawnThisCycle = true;
		gSpawnCycleTot++;						// Le nombre de cycle de spawn depuis le début de la game
	}
}

bool Spawn_Bots_This_Cycle()
{
	if (gSpawnThisCycle)
	{
		Spawn_Bots();
		gSpawnThisCycle = false;
		return true;
	}

	return false;	// no spawnerino
}

