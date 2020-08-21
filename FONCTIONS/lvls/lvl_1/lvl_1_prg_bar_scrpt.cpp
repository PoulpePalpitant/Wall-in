

#include "../../time/spawn_cycle.h"
#include "../../events/global_events/ev_progress_bar.h"

#include "lvl_1_prg_bar_scrpt.h"

// GENERAL  

void Lvl_1_Prg_Bar_Script()
{
	int skip;
	switch (gSpawnCycleTot) // Pour aller dans la switch et déterminé quel va être le break
	{
	case 15:skip = 3; break;
	case 39:skip = 4; break;
	case 49:skip = 6;
		//case 100: /*(FINAL_PUSH)*/ skip = 5;	

		if (skip)
			gSpwBotTimer.Add_Count(skip);
	}
}