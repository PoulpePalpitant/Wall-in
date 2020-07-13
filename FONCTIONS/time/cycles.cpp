
#include "bot_move_cycle.h"
#include "spawn_cycle.h"
#include "cycles.h"
#include "../items/item_spawner.h"

 bool stopSpwCycle = true;
 bool stopMoveCycle = true;
 bool stopItmSpwCycle = true;

void UPD_Cycles_Stuff()
{
	if (!stopSpwCycle)
		UPD_Spawn_Cycle();		// Update le cycle de spawn 
	if (!stopMoveCycle)
		UPD_Bot_Move_Cycle();	// Update le cycle de bots
	if (!stopItmSpwCycle)
		ItemSpawner::UPD_Item_Spawn_Timers();	// Update timers des spawners
		
}



void Do_Stuff_this_Cycle()
{
	if(!stopSpwCycle)
		Spawn_Bots_This_Cycle();		// Spawn les Bots, ou pas!
	if(!stopMoveCycle)
		Move_Bots_This_Cycle();			// Move les bots, ou pas!
}