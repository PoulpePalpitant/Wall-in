
#include "bot_move_cycle.h"
#include "spawn_cycle.h"
#include "cycles.h"


 bool stopSpwCycle = true;
 bool stopMoveCycle = true;

void UPD_Bots_Cycles()
{
	if (!stopSpwCycle)
		UPD_Spawn_Cycle();		// Update le cycle de spawn 
	if (!stopMoveCycle)
		UPD_Bot_Move_Cycle();	// Update le cycle de bots

}

void Do_Stuff_this_Cycle()
{
	if(!stopSpwCycle)
		Spawn_Bots_This_Cycle();		// Spawn les Bots, ou pas!
	if(!stopMoveCycle)
		Move_Bots_This_Cycle();			// Move les bots, ou pas!
}