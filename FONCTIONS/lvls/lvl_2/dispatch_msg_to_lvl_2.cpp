

#include "dispatch_msg_to_lvl_2.h"
#include "../../events/msg_dispatcher.h"
#include "lvl_2_initializer.h"
#include "../../console/sweet_cmd_console.h"
#include "../lvl_script.h"
#include "../../structure_manager/structure_manager.h"
#include "../../bots/botlist.h"
#include "../../time/spawn_cycle.h"

/* Level  events !*/
#include "../../events/global_events/ev_update_heart.h"
#include "events/ev_build_labyrinth.h"
#include "events/ev_lvl2_training.h"
#include "events/ev_lvl2_training_1.h"
#include "events/ev_lvl2_training_2.h"
#include "events/ev_lvl2_training_3.h"
#include "../../events/global_events/ev_spwn_player.h"
#include "../../events/global_events/ev_lvl_unlocked.h"
#include "../../events/global_events/ev_back_to_menu.h"	 


/* Msg events*/
#include "msg_events/ev_waking_up_2.h"
#include "../../events/global_events/ev_level_title.h"


// others
#include "../../events/global_events/feedback/ev_draw_map.h"
#include "../../player/player.h"	// don't...
#include "../../grid/AllGrids.h"
#include "../../events/global_events/ev_progress_bar.h"
#include "../../events/global_events/ev_thank_you.h"
#include "../../grid/managegrids.h"
#include "../../items/item_spawner.h"

static bool seenLevelTitle = false;


// C'EST ICI QUE ÇA SE PASSE
void Dispatch_Msg_To_Lvl_2()
{
	// The bare minimum!
	switch (gCurrentMsg)
	{
	case PLS_INTIALIZE_LVL: Lvl_2_Initializer();	break;			// Initialize plein de choses	/* Remarque ce n'est pas un observateur, car c'est pas vraiment un event, en fin je crois */

	case STAGE_ADVANCE:
		Event::Cancel_All();		// Tout les events en cours sont annulés
		clrscr();

		if (gCurrentPuzzle[gCurrentLevel - 1] == 0)
		{
			if (!seenLevelTitle)
			{
				Ev_Dr_Level_Title();
				seenLevelTitle = 1;
				return;
			}

			//Just_Dr_Map_Borders();
			P1.Er_Player();
			gCurrPuzzleStep = 0;	// SAFETY				
			Set_Ev_Spawn_Player(3);													
		}
		else
		{
			Checkpoint_Delay();// Delay Next spawn

			if (gCurrentPuzzle[gCurrentLevel - 1] + 1 != NUM_PUZZLES[gCurrentLevel - 1])	// Veut dire qu'on est rendu au final hour qui est le dernier checkpoint.
				Set_Ev_Spawn_Player(3);														// Je sais, c'est très clair
		}

		/*safety*/
		ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
		botList.Destroy_All_Bots();

		P1.Set_Hp(1);
		Ev_Progress_Bar();
		Init_Puzzle();

		MsgQueue::Register(START_BOTS); // Here they come baby
		gSkipTutorial = false;
		gDayStarted = true;

		// Pour debug
		//gGrids.Dr_Spawngrid();
		break;


	case LOAD_CHECKPOINT:						// Restart le level, met en ajustant le Checkpoint
		Clear_All_States();	// Thats a fucking quick reset brah
		clrscr();
		gSkipTutorial = true;	// clear state clear aussi ça, qui est agaçant
		MsgQueue::Register(PLS_INTIALIZE_LVL);
		break;

	case PROCEED:
		MsgQueue::Register(PLS_INTIALIZE_LVL);
		clrscr();

		if (gLastLvlUnlocked == -1)
			Go_Back_To_Menu();
		else
			Ev_Lvl_Unlocked();
		break;
	}
}
