
#include "bot_move_cycle.h"
#include "spawn_cycle.h"
#include "cycles.h"


void UPD_Cycles()
{
	UPD_Spawn_Cycle();		// Update le cycle de spawn 
	UPD_Bot_Move_Cycle();	// Update le cycle de bots
}

void Do_Stuff_this_Cycle()
{
	Spawn_Bots_This_Cycle();		// Spawn les Bots, ou pas!
	Move_Bots_This_Cycle();			// Move les bots, ou pas!
}