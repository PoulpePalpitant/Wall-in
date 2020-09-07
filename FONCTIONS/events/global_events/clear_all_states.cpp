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
#include "feedback/ev_draw_map.h"
#include "../../player/player.h"
//#include "../../grid/AllGrids.h"

void Clear_All_States(bool eraseLinks, bool stopTimers)	// Gros reset button()	
{
	// PRIME RESETS
	blastP1.Cancel();			 // Cancel le blast
	MsgQueue::Unregister_All();	// Tout les msg é
	Event::Cancel_All();		// Tout les events
	Reset_Input_Flags();				// Flags
	gSkipStory = gDayStarted = gRefreshStage = false;	// Other important flags
	ChoiceTime::Stop_Choice_Time();	// flag spécial
	
	if(stopTimers)
		SpeedTimer::Stop_All_Timers(); // STOP TOUT LES TIMERS du monde, sauf la gameloop bien entendu

	// VIDE LA RENDER QUEUE


	//Vide tout les drawers et les queues : item spawns, warnings, wall drawers etc.
	WarningDrawerList::Remove_All();
	DrawModifierQueue::addNew.Remove_All();  // empty drawer qui ajoute des mod
	DrawModifierQueue::consume.Remove_All(); // empty le drawer qui consume des mod

	//BlastModifierQueue::queue.EMPTY_QUEUE(); // empty la queue de modifiers
	BlastModifierQueue::Reset();

	if (eraseLinks)	// efface les links et walls
	{
		ListsOfChainToModify::Annihilate_All_Links();	// Links
		DrawWalls::Remove_All();
	}



	botList.Destroy_All_Bots();	// Bots
	ItemsOnGrid::Remove_All();	// enlève tout les items spawné
	Reset_Spw_Cycle();			// Reset le nombre de spw cycle à 0

	//MsgQueue::Register(HIDE_MOD_QUEUE);
	MsgQueue::Register(LOCK_PLAYER);
	MsgQueue::Register(STOP_BOT_SPAWNS);
	MsgQueue::Register(DISABLE_ITEM_SPAWN);
	MsgQueue::Register(RESET_SPW_TOT);
	//P1.Reset_State();			// 
}
void Clear_Map()// Tout ce qui à une influence sur l'interface graphique 
{
	P1.Er_Player();
	ListsOfChainToModify::Annihilate_All_Links();	// Links
	botList.Destroy_All_Bots();	// Bots
	ItemsOnGrid::Remove_All();	// enlève tout les items spawné
	BlastModifierQueue::Reset();
	//BlastModifierQueue::queue.EMPTY_QUEUE(); // empty la queue de modifiers			// CECI CRASH
	//MsgQueue::Register(HIDE_MOD_QUEUE);
	ChoiceTime::Stop_Choice_Time();	// flag spécial
	Erase_Map_Borders_1();
}

void Clear_All_Renders()
{
	ConsoleRender::Empty_All();
}