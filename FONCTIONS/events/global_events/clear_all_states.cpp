#include "clear_all_states.h"

#include "../../inputs/action_input.h"
#include "../../lvls/lvl_script.h"
#include "../../UI/console_output/render_list.h"
#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../structure_manager/structure_manager.h"
#include "../../bots/botlist.h"
#include "../../time/cycles.h"
#include "../../time/movement_timer.h"
//#include "../../player/player.h"

//#include "../../grid/AllGrids.h"

void Clear_All_States(bool eraseLinks)	// Gros reset button()	
{
	// Reset all
	//vide les drawers suivants : item spawns, warnings

	MsgQueue::Unregister_All();	// Tout les msg 
	Event::Cancel_All();		// Tout les events
	Reset_All_Flags();			// Flags
	SpeedTimer::Stop_All_Timers(); // STOP TOUT LES TIMERS du monde, sauf la gameloop bien entendu

	//P1.Reset_State();			// 
	if (eraseLinks)	// efface les links
	{
		ListsOfChainToModify::Annihilate_All_Links();	// Links
	}
	botList.Destroy_All_Bots();	// Bots
	Reset_Spw_Cycle();				// Reset le nombre de spw cycle à 0
	MsgQueue::Register(LOCK_PLAYER);
	MsgQueue::Register(STOP_BOT_SPAWNS);
	MsgQueue::Register(RESET_SPW_TOT);
}

