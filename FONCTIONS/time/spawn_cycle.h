#pragma once 

#include <time.h>
#include "movement_timer.h"

extern bool gSpawnThisCycle;
extern int gSpawnCycle;							// L'intervalle de spawn cycle. La distance entre le current et le next
extern time_t gCurrentSpawnCycle;	// Le spawn cycle actuel
extern time_t gNextSpawnCycle;		// Le prochain spawn cycle
extern int gSpawnCycleTot;						// Le nombre total de spawn cycle ayant u lieu

extern MovementTimer gSpwBotTimer;



void UPD_Spawn_Cycle();			// Refresh Timer des spawns
bool Spawn_Bots_This_Cycle();	// Spawn les bots, ou pas!