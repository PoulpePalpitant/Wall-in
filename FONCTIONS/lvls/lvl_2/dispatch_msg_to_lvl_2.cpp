

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


/* Msg events*/
#include "msg_events/ev_day_2.h"
#include "msg_events/ev_waking_up_2.h"


// others
#include "../../events/global_events/feedback/ev_draw_map.h"
#include "../../player/player.h"	// don't...
#include "../../grid/AllGrids.h"
#include "../../events/global_events/ev_progress_bar.h"
#include "../../events/global_events/ev_thank_you.h"
#include "../../grid/managegrids.h"
#include "../../items/item_spawner.h"

// C'EST ICI QUE ÇA SE PASSE
void Dispatch_Msg_To_Lvl_2()
{
	// The bare minimum!
	switch (gCurrentMsg)
	{
	case PLS_INTIALIZE_LVL: Lvl_2_Initializer();	break;			// Initialize plein de choses	/* Remarque ce n'est pas un observateur, car c'est pas vraiment un event, en fin je crois */

	case STAGE_ADVANCE:
		if (gCurrentStage < 6)
		{
			Event::Cancel_All();		// Tout les events en cours sont annulés
			clrscr();
		}
		switch (gCurrentStage)
		{
		case 1:Ev_Wake_Up_2();
			break;
		
		case 2: 
			Ev_Dr_Day_2();
			break;
		
		case 3:
			P1.Set_Hp(3);
			if (gSkipStory)
			{
				/*safety*/
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
				botList.Destroy_All_Bots();

				if (gCurrentPuzzle[gCurrentLevel - 1] == 0)	// Si le checkpoint actuel est autre que ZÉRO
				{
					P1.Set_Position({ 6,6 });
					P1.Er_Player();
					Just_Dr_Map_Borders();
					gCurrPuzzleStep = 0;	// SAFETY
					MsgQueue::Register(SPAWN_PLAYER);
				}
				else
				{

					Checkpoint_Delay();// Delay Next spawn

					if (gCurrentPuzzle[gCurrentLevel - 1] != NUM_PUZZLES[gCurrentLevel - 1])	// Veut dire qu'on est rendu au final hour qui est le dernier checkpoint.
						Set_Ev_Spawn_Player(3);														// Je sais, c'est très clair
				}



				// Pour debug
				gGrids.Dr_Spawngrid();
			}

			P1.Reset_Hp_And_Heart(3);
			Ev_Progress_Bar2();
			Init_Puzzle();

			MsgQueue::Register(START_BOTS); // Here they come baby
			gSkipStory = false;
			gDayStarted = true;
		}

		break;

	case LOAD_CHECKPOINT:						// Restart le level, met en ajustant le Checkpoint
		Clear_All_States();	// Thats a fucking quick reset brah
		clrscr();
		gSkipStory = true;	// clear state clear aussi ça, qui est agaçant
		MsgQueue::Register(PLS_INTIALIZE_LVL);
		break;

	case PROCEED: 
		if (gCurrentStage == 2)	// Le stage ou à lieu le main game
		{
			gCurrentPuzzle[gCurrentLevel - 1] = 0;	// Restart le checkpoint
			MsgQueue::Register(PLS_INTIALIZE_LVL);
			clrscr();
			
			if (P1.Get_State() != DEAD)	// hey, Niveau suivant!!
			{
				gCurrentStage = 0;
				gCurrentLevel = 3;
				Ev_Thks_For_Playing();

				Ev_Lvl_Unlocked();

			}
		}
		else
			MsgQueue::Register(STAGE_ADVANCE);
		break;	

		/* Items*/
	case ITEM_PICKUP:
		if (gCurrentStage <= 1)
		{
			break;break;
		}
		break;
	}
}
