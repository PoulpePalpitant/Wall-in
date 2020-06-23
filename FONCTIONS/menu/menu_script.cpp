#pragma once


#include "../time/cycles.h"
#include "../time/spawn_cycle.h"
#include "../grid/managegrids.h"
#include "../lvls/lvl_initializer.h"

#include "menu_initializer.h"
#include "menu_upd_events.h"
#include "menu_script.h"


void Menu_Script()
{
	if (gLvlInitializer)
	{
		Resize_Grids_To_Level(gGrids, 0);	// Resize tout les grids pour ce niveau :)
		Menu_Initializer();				// Initialize plein de choses
		//		UI_Display_StatsName();	// Display les trackers
		gLvlInitializer = false;
	}
	else
	{
		Menu_Upd_Events();		// Update les events du niveau
	}


}