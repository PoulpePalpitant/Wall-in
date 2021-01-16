

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
#include "msg_events/ev_waking_up.h"
#include "msg_events/ev_arr_keys.h"
#include "msg_events/ev_day_1.h"
#include "msg_events/ev_health_is_ammo.h"

// others
#include "../../events/global_events/feedback/ev_draw_map.h"
#include "../../player/player.h"	// don't...
#include "../../grid/AllGrids.h"
#include "../../events/global_events/ev_progress_bar.h"
#include "../../events/global_events/ev_thank_you.h"
#include "../../events/global_events/ev_lvl_unlocked.h"


// C'EST ICI QUE ÇA SE PASSE
void Dispatch_Msg_To_Lvl_1()
{
	// The bare minimum!
	switch (gCurrentMsg)
	{
	case PLS_INTIALIZE_LVL: Lvl_1_Initializer();	break;			// Initialize plein de choses	/* Remarque ce n'est pas un observateur, car c'est pas vraiment un event, en fin je crois */

	case LVL_INITIALIZED: 
		break;

	case CHANGE_WINSIZE:
	//	OBS_Change_Window();
		break;		// Test le changement de window

	case STAGE_ADVANCE:
		if (gCurrentStage == 3)
		{
			Cancel_All_That_Buggy_Shit();
			clrscr();
			ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
			botList.Destroy_All_Bots();
			gSkipStory = true;
			Clear_All_Renders();

			//Ev_Dr_Day_1();
			MsgQueue::Register(STAGE_ADVANCE);
		}
		if (gCurrentStage == 4)
		{
			if (gSkipStory)
			{
				/*safety*/
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
				botList.Destroy_All_Bots();


				if (gCurrentPuzzle[gCurrentLevel - 1] == 0)	// Si aucun checkpoint n'été atteint
				{
					P1.Set_Position({ 6,5 });
					Just_Dr_Arr_Keys(); 
					Just_Dr_Wasd();
					P1.Er_Player();
					Just_Dr_Map_Borders();
					gCurrPuzzleStep = 0;	// SAFETY
					MsgQueue::Register(SPAWN_PLAYER); // OLDWAY
				}
				else
				{
					Checkpoint_Delay();// Delay Next spawn

					if (gCurrentPuzzle[gCurrentLevel - 1] != NUM_PUZZLES[gCurrentLevel - 1] - 1)	// Veut dire qu'on est rendu au final hour qui est le dernier checkpoint.
						Set_Ev_Spawn_Player(3);														// Je sais, c'est très clair



					// Pour debug
					//gGrids.Dr_Spawngrid();

				}
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
		MsgQueue::Register(PLS_INTIALIZE_LVL);
		clrscr();	
		gSkipStory = true;	// clear state clear aussi ça, qui est agaçant
		break;

	case PROCEED: 
		if (gCurrentStage == 4)
		{
			gCurrentPuzzle[gCurrentLevel - 1] = 0;	// Restart le checkpoint
			MsgQueue::Register(PLS_INTIALIZE_LVL);	
			clrscr();
			
			if (P1.Get_State() != DEAD)	// hey, Niveau suivant!!
			{
				// Ferme le jeu
				//Ev_Thks_For_Playing();

				// Prochain level
				Ev_Lvl_Unlocked();
			}
		}
		else
			MsgQueue::Register(STAGE_ADVANCE);
		break;	

	case VICTORY:
		break;


	case WAITING_TIME:
		break;

		/*Player*/
	case LOCK_PLAYER: 
		break;

	case PLAYER_SPAWNED: 
		if (gCurrentStage == 0)
		{
			Ev_Dr_Wasd();							// Affiche les touches clavier du mouvement
			MsgQueue::Register(SPAWN_SPECIAL_ITEM);	// Spawn la vie
		}
		break;

		/* Items*/
	case ITEM_PICKUP:
		if (gCurrentStage <= 1)
		{
			Draw_Tuto_Progression(1);
			Ev_Spawn_Life2();
			Ev_Learn_Border_Limit();			// Learn to shoot
		}
		
		if (gDayStarted == true && gCurrentPuzzle[0] == 2) {
			Ev_Health_Is_Ammo();
		}

		break;

	case SPAWN_SPECIAL_ITEM: 
		Ev_Spawn_Mysterious_Item2();			// Si tu trigger un event qui était déjà actif ici, ça va faire deux updates en 1 seul cycle! -	BAD -
		break;

		/*Bots*/
	case START_BOTS:
		break;
	}
}
