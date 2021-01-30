

#include "dispatch_msg_to_lvl_3.h"
#include "../../events/msg_dispatcher.h"
#include "lvl_3_initializer.h"
#include "../../console/sweet_cmd_console.h"
#include "../lvl_script.h"
#include "../../structure_manager/structure_manager.h"
#include "../../bots/botlist.h"
#include "../../time/spawn_cycle.h"

/* Level  events !*/
#include "../../events/global_events/ev_update_heart.h"
#include "../../events/global_events/ev_spwn_player.h"
#include "../../events/global_events/ev_lvl_unlocked.h"
#include "../../events/global_events/ev_back_to_menu.h"

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
void Dispatch_Msg_To_Lvl_3()
{
	// The bare minimum!
	switch (gCurrentMsg)
	{
	case PLS_INTIALIZE_LVL: Lvl_3_Initializer();	break;			// Initialize plein de choses	/* Remarque ce n'est pas un observateur, car c'est pas vraiment un event, en fin je crois */

	case STAGE_ADVANCE:
		Event::Cancel_All();		// Tout les events en cours sont annulés
		clrscr();
		ListsOfChainToModify::Annihilate_All_Links();
		botList.Destroy_All_Bots();

		if (gCurrentPuzzle[gCurrentLevel - 1] == 0)	// Si le checkpoint actuel est autre que ZÉRO
		{

			if (!seenLevelTitle)
			{
				Ev_Dr_Level_Title();
				seenLevelTitle = 1;
				return;
			}

			P1.Er_Player();
			gCurrPuzzleStep = 0;	// SAFETY
			MsgQueue::Register(SPAWN_PLAYER);
		}
		else
		{
			Checkpoint_Delay();// Delay Next spawn

			if (gCurrentPuzzle[gCurrentLevel - 1] + 1 != NUM_PUZZLES[gCurrentLevel - 1])	// Veut dire qu'on est rendu au final hour qui est le dernier checkpoint.
				Set_Ev_Spawn_Player(3);														// Je sais, c'est très clair
		}



		// Pour debug
		//gGrids.Dr_Spawngrid();

		P1.Set_Hp(1);

		Ev_Progress_Bar();
		Init_Puzzle();


		MsgQueue::Register(START_BOTS); // Here they come baby
		gSkipTutorial = false;
		gDayStarted = true;
		break;

	case LOAD_CHECKPOINT:
		Clear_All_States();
		clrscr();
		gSkipTutorial = true;
		MsgQueue::Register(PLS_INTIALIZE_LVL);
		break;

	case PROCEED:
		if (gCurrentStage == 1)
		{
			if (P1.Get_State() != DEAD)
			{
				gCurrentStage++;
				gCurrentPuzzle[3 - 1] = 0;
				Ev_Thks_For_Playing();	// Le jeu est finit
			}
		}
		else
			Go_Back_To_Menu();

	}
}
