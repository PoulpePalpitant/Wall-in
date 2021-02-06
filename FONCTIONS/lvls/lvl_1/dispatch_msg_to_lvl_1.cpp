

#include "dispatch_msg_to_lvl_1.h"
#include "../../events/msg_dispatcher.h"
#include "lvl_1_initializer.h"
#include "../../console/sweet_cmd_console.h"
#include "../lvl_script.h"
#include "../../structure_manager/structure_manager.h"
#include "../../bots/botlist.h"
#include "../../time/spawn_cycle.h"

/* Level1  events !*/
#include "events/ev_change_window.h"
#include "events/ev_learn_border_limit.h"
#include "events/ev_spawn_life2.h"
#include "events/ev_dot_chase.h"
#include "events/ev_bot_tutorial2.h"
#include "events/ev_build_start_walls.h"
#include "../../events/global_events/ev_update_heart.h"
#include "../../events/global_events/ev_spwn_player.h"

/* Msg events*/
#include "msg_events/ev_new_goal2.h"
#include "msg_events/EV_Hello.h"
#include "msg_events/ev_wasd.h"
#include "msg_events/ev_arr_keys.h"
#include "msg_events/ev_day_1.h"
#include "../../events/global_events/ev_level_title.h"

// others
#include "../../events/global_events/feedback/ev_draw_map.h"
#include "../../player/player.h"	// don't...
#include "../../grid/AllGrids.h"
#include "../../events/global_events/ev_progress_bar.h"
#include "../../events/global_events/ev_thank_you.h"
#include "../../events/global_events/ev_lvl_unlocked.h"
#include "../../events/global_events/ev_back_to_menu.h"	 
#include  "../../events/global_events/ev_victory_screen.h"

static bool seenLevelTitle = false;

// C'EST ICI QUE ÇA SE PASSE
void Dispatch_Msg_To_Lvl_1()
{
	// The bare minimum!
	switch (gCurrentMsg)
	{
	case PLS_INTIALIZE_LVL: Lvl_1_Initializer();	break;			// Initialize plein de choses	/* Remarque ce n'est pas un observateur, car c'est pas vraiment un event, en fin je crois */

	case STAGE_ADVANCE:
		if (!gSkipTutorial)
		{
			Cancel_All_That_Buggy_Shit();
			clrscr();
			ListsOfChainToModify::Annihilate_All_Links(); 			
			botList.Destroy_All_Bots();
			Clear_All_Renders();
			gSkipTutorial = true;

			MsgQueue::Register(STAGE_ADVANCE);
		}
		else
		{
			/*safety*/
			ListsOfChainToModify::Annihilate_All_Links(); 		
			botList.Destroy_All_Bots();

			if (gCurrentPuzzle[gCurrentLevel - 1] == 0)	// Si aucun checkpoint n'été atteint
			{

				if (!seenLevelTitle)
				{
					Ev_Dr_Level_Title();
					seenLevelTitle = 1;
					return;
				}

				Just_Dr_Arr_Keys();
				Just_Dr_Wasd();
				P1.Er_Player();
				Just_Dr_Map_Borders();
				gCurrPuzzleStep = 0;	
				MsgQueue::Register(SPAWN_PLAYER);
			}
			else
			{
				Checkpoint_Delay();// Delay Next spawn

				if (gCurrentPuzzle[gCurrentLevel - 1] != NUM_PUZZLES[gCurrentLevel - 1] - 1)	// Veut dire qu'on est rendu au final hour qui est le dernier checkpoint.
					Set_Ev_Spawn_Player(3);														// Je sais, c'est très clair

				// Pour debug
				//gGrids.Dr_Spawngrid();

			}


			P1.Set_Hp(1);
			Ev_Progress_Bar();
			Init_Puzzle();

			MsgQueue::Register(START_BOTS); // Here they come baby
			gLevelStarted = true;
		}
		break;

	case LOAD_CHECKPOINT:						
		Clear_All_States();	
		MsgQueue::Register(PLS_INTIALIZE_LVL);
		clrscr();
		gSkipTutorial = true;	// clear state clear aussi ça, qui est agaçant
		break;

	case PROCEED:
		if (Is_Ev_Victory_Screen_Active())
		{
			if (gLastLvlUnlocked == -1)
				Go_Back_To_Menu();
			else
				Ev_Lvl_Unlocked();
		}
		else
			MsgQueue::Register(STAGE_ADVANCE);
		break;

	case PLAYER_SPAWNED:
		if (gCurrentStage == 0)
		{
			Ev_Dr_Wasd();							// Affiche les touches clavier du mouvement
			MsgQueue::Register(SPAWN_SPECIAL_ITEM);	
		}
		break;

		/* Items*/
	case ITEM_PICKUP:
		if (gCurrentStage <= 1)
		{
			Draw_Tuto_Progression(1);
			Ev_Learn_Border_Limit();			
		}
		break;

	case SPAWN_SPECIAL_ITEM:
		Ev_Spawn_Mysterious_Item2();		
		break;

	}
}
