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
#include "../../choice/choice_time.h"
#include "ev_warning.h"
#include "../../items/item_list.h"
#include "../../blast/mod_queue_animator.h"
#include "../../blast/mod_queue_animator_add.h"
#include "../../blast/mod_queue_animator_consume.h"
#include "../../blast/blast_modifier_queue.h"
#include "../../blast/blast.h"
//#include "../../player/player.h"
//#include "../../grid/AllGrids.h"

void Clear_All_States(bool eraseLinks)	// Gros reset button()	
{
	// PRIME RESETS
	blastP1.Cancel();			 // Cancel le blast
	MsgQueue::Unregister_All();	// Tout les msg é
	Event::Cancel_All();		// Tout les events
	Reset_All_Flags();				// Flags
	gSkipStory = gDayStarted = false;	// important flags
	ChoiceTime::Stop_Choice_Time();	// flag spécial
	SpeedTimer::Stop_All_Timers(); // STOP TOUT LES TIMERS du monde, sauf la gameloop bien entendu

	//Vide tout les drawers et les queues : item spawns, warnings, wall drawers etc.
	WarningDrawerList::Remove_All();
	DrawModifierQueue::addNew.Remove_All();  // empty drawer qui ajoute des mod
	DrawModifierQueue::consume.Remove_All(); // empty le drawer qui consume des mod
	BlastModifierQueue::queue.EMPTY_QUEUE(); // empty la queue de modifiers

	if (eraseLinks)	// efface les links et walls
	{
		ListsOfChainToModify::Annihilate_All_Links();	// Links
	}



	botList.Destroy_All_Bots();	// Bots
	ItemsOnGrid::Remove_All();	// enlève tout les items spawné
	Reset_Spw_Cycle();			// Reset le nombre de spw cycle à 0

	MsgQueue::Register(LOCK_PLAYER);
	MsgQueue::Register(STOP_BOT_SPAWNS);
	MsgQueue::Register(RESET_SPW_TOT);
	//P1.Reset_State();			// 
}

