
#include "../../time/cycles.h"
#include "lvl_1_spwn_script.h"
#include "../../grid/managegrids.h"
#include "../lvl_initializer.h"
#include "lvl_1_initializer.h"

#include "lvl_1_events_checker.h"
#include "lvl_1_script.h"

void Level_1_Script()
{
	if (gLvlInitializer)
	{
		Resize_Grids_To_Level(gGrids, 1);	// Resize tout les grids pour ce niveau :)
		Lvl_1_Initializer();				// Initialize plein de choses
		// INITIALIZE STUFF
		//		UI_Display_StatsName();	// Display les trackers
		gLvlInitializer = false;
	}
	else
	{
		UPD_Cycles();			// Update tout les cycles
		Lvl_1_Spwn_Script();	// Détermine quel sera la prochaine wave de spawn
		Lvl_1_Event_Checker();	// Vérification de si y'a un event qui est trigger
		Do_Stuff_this_Cycle();	// Fais spawner les bots, et les bougent ensuite
	}

}