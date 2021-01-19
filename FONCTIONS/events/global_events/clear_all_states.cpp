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
#include "../../spawns/valid_spwn_intervals.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../items/item_spw_drawer.h"
#include "feedback/ev_drain_health.h"
#include "../../blast/mod_queue_animator.h"

//#include "../../grid/AllGrids.h"

void Clear_All_States(bool eraseLinks, bool stopTimers)	// Gros reset button()	
{
	// PRIME RESETS
	
	Clear_All_Renders();			// VIDE LA RENDER QUEUE

	if (stopTimers)
		SpeedTimer::Stop_All_Timers(); // STOP TOUT LES TIMERS du monde, sauf la gameloop bien entendu

	blastP1.Clear_Blast();	// stop and clear
	MsgQueue::Unregister_All();	// Tout les msg é
	Event::Cancel_All();		// Tout les events
	Reset_Input_Flags();				// Flags
	gSkipStory = gDayStarted = gRefreshStage = false;	// Other important flags
	ChoiceTime::Stop_Choice_Time();	// flag spécial

	if (eraseLinks)	// efface les links et walls
	{
		DrawWalls::Remove_All();
		ListsOfChainToModify::Annihilate_All_Links();	// Links
		DrawWalls::Draw_Them_Walls();
	}

	//Vide tout les drawers et les queues : item spawns, warnings, wall drawers etc.
	WarningDrawerList::Remove_All();
	DrawModifierQueue::addNew.Remove_All();  // empty drawer qui ajoute des mod
	DrawModifierQueue::consume.Remove_All(); // empty le drawer qui consume des mod
	DrawItemSpawnList::Remove_All();	// hardcore
	DrawModifierQueue::isShown = false;
	
	BlastModifierQueue::Reset();

	P1.Get_Teleporter().Remove_Teleport_Location();	// Prévient des abus

	// Bot stuff
	botList.Destroy_All_Bots();	// Bots
	ValidSpwnIntervals::Reset_For_Next_Cycle();	// Doit ré-initialiser les listes à chaque cycle de spawn
	bots_to_spawn::Reset_To_Default();			// reset les valeurs par défaut pour le prochain spawn

	ItemsOnGrid::Remove_All();	// enlève tout les items spawné
	Reset_Spw_Cycle();			// Reset le nombre de spw cycle à 0



	MsgQueue::Register(HIDE_MOD_QUEUE);
	MsgQueue::Register(LOCK_PLAYER);
	MsgQueue::Register(STOP_BOT_SPAWNS);
	MsgQueue::Register(DISABLE_ITEM_SPAWN);
	MsgQueue::Register(RESET_SPW_TOT);
	//P1.Reset_State();			// 
}
void Clear_Map()// Tout ce qui à une influence sur l'interface graphique 
{
	blastP1.Clear_Blast();	// stop and clear
	P1.Er_Player();
	ListsOfChainToModify::Annihilate_All_Links();	// Links
	botList.Destroy_All_Bots();	// Bots
	ItemsOnGrid::Remove_All();	// enlève tout les items spawné
	DrawModifierQueue::addNew.Remove_All();  // empty drawer qui ajoute des mod
	DrawModifierQueue::consume.Remove_All(); // empty le drawer qui consume des mod
	DrawItemSpawnList::Remove_All();	// hardcore
	BlastModifierQueue::Reset();
	//BlastModifierQueue::queue.EMPTY_QUEUE(); // empty la queue de modifiers			// CECI CRASH
	//MsgQueue::Register(HIDE_MOD_QUEUE);
	ChoiceTime::Stop_Choice_Time();	// flag spécial
	Set_Dr_Map_1();
	Stop_Ev_Hp_Drain_Msg();
}

void Clear_All_Renders()
{
	ConsoleRender::Empty_All();
}