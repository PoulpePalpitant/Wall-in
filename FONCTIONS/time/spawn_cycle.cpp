
#include "timerOP.h"
#include "../spawns/spawn_bot.h"

#include "spawn_cycle.h"


int gSpawnCycle;							// L'intervalle de spawn cycle. La distance entre le current et le next
bool gSpawnThisCycle;
time_t gCurrentSpawnCycle ;
time_t gNextSpawnCycle ;
int gSpawnCycleTot;						// Le nombre total de spawn cycle ayant u lieu


void UPD_Spawn_Cycle()			// Refresh Timer des spawns
{
	if (/*gameClockTEST.Get_Time()*/gLvlTime >= gNextSpawnCycle)
	{
		gSpawnThisCycle = true;
		gCurrentSpawnCycle = gNextSpawnCycle;	// j'ai pt pas besoin de Current_Spawn_Cycle
		gNextSpawnCycle = gCurrentSpawnCycle + gSpawnCycle;
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

