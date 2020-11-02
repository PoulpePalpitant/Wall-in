

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
#include "events/ev_spawn_life.h"
#include "events/ev_dot_chase.h"
#include "events/ev_bot_tutorial.h"
#include "events/ev_build_start_walls.h"
#include "../../events/global_events/ev_update_heart.h"
#include "../../events/global_events/ev_spwn_player.h"

/* Msg events*/
#include "msg_events/ev_new_goal.h"
#include "msg_events/EV_Hello.h"
#include "msg_events/ev_wasd.h"
#include "msg_events/ev_waking_up.h"
#include "msg_events/ev_arr_keys.h"
#include "msg_events/ev_day_1.h"

// others
#include "../../events/global_events/feedback/ev_draw_map.h"
#include "../../player/player.h"	// don't...
#include "../../grid/AllGrids.h"
#include "../../events/global_events/ev_progress_bar.h"
#include "../../events/global_events/ev_thank_you.h"


// C'EST ICI QUE ÇA SE PASSE
void Dispatch_Msg_To_Lvl_1()
{
	// The bare minimum!
	switch (gCurrentMsg)
	{
	case PLS_INTIALIZE_LVL: Lvl_1_Initializer();	break;			// Initialize plein de choses	/* Remarque ce n'est pas un observateur, car c'est pas vraiment un event, en fin je crois */

	case LVL_INITIALIZED: 
	//	MsgQueue::Register(CHANGE_WINSIZE);
		break;	// n'empêche même pas de register des messges ici :(

	case CHANGE_WINSIZE:
	//	OBS_Change_Window();
		break;		// Test le changement de window

	case STAGE_ADVANCE:
		if (gCurrentStage == 3)
		{
			ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
			botList.Destroy_All_Bots();
			clrscr();
			Ev_Dr_Day_1();

		}
		if (gCurrentStage == 4)
		{
			if (gSkipStory)
			{
				/*safety*/
				ListsOfChainToModify::Annihilate_All_Links(); // Efface tout les Murs et Les Links				
				botList.Destroy_All_Bots();


				if (gCurrentCheckPoints[gCurrentLevel - 1] == 0)	// Si aucun checkpoint n'été atteint
				{
					P1.Set_Position({ 6,5 });
					Just_Dr_Arr_Keys(); 
					Just_Dr_Wasd();
					P1.Er_Player();
					Just_Dr_Map_Borders();
					Ev_Progress_Bar();
					MsgQueue::Register(SPAWN_PLAYER);
				}
				else
				{
					P1.Set_Position(LVL1_CHECKPOINT_P1_CRD[gCurrentCheckPoints[gCurrentLevel - 1]]);
					gSpawnCycleTot = Get_Lvl_Checkpoint();	// Le lvl va commencer à ce point dans le script
					Checkpoint_Delay();// Delay Next spawn
					Ev_Progress_Bar();	// Besoin d'une version FASTER qui élimine ce qui à été fait avant
					Set_Ev_Spawn_Player(3);

					// Pour debug
					gGrids.Dr_Spawngrid();

				//	MsgQueue::Register(FREE_PLAYER);
				}
			}

			P1.Reset_Hp_And_Heart(3);// Ev_Dr_Heart();
			blastP1.Get_Ammo_Manager().Set_Ammo_For_Checkpoint();	// nombre de shots


			//MsgQueue::Register(ENABLE_BLAST);	// quicker quick start
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
			gCurrentCheckPoints[gCurrentLevel - 1] = 0;	// Restart le checkpoint
			MsgQueue::Register(PLS_INTIALIZE_LVL);	
			clrscr();
			
			if (P1.Get_State() != DEAD)	// hey, Niveau suivant!!
			{
				gCurrentStage = 0;			// START À ZÉRO POUR LE LABYRINTHE
				gCurrentLevel = 2;
				gSkipStory = false;
				Event::Cancel_All();		// Tout les events
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

	case BUMPED_BORDER:
		if (gCurrentLevel == 1 && gCurrentStage == 1)
		{
			if(P1.Get_Grd_Coord().c == linkGrid->Get_Cols() - 1)
				Ev_Wake_Up();		// Le joueur se fait wakeup
			//Ev_Bot_Tutorial();
		}
		break;
		/* Items*/
	case ITEM_PICKUP:
		if (gCurrentStage <= 1)
		{
			Ev_Dr_New_Goal();		// - NEW GOAL -
			Ev_Spawn_Life();
		}
		//Set_Dr_Map_1();
		break;

	case SPAWN_SPECIAL_ITEM: 
		Ev_Spawn_Mysterious_Item();			// Si tu trigger un event qui était déjà actif ici, ça va faire deux updates en 1 seul cycle! -	BAD -
		break;

		/*Bots*/
	case START_BOTS:
		break;
	}
}
