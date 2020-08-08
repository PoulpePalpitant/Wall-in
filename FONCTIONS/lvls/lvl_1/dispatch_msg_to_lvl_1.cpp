

#include "dispatch_msg_to_lvl_1.h"
#include "../../events/msg_dispatcher.h"
#include "lvl_1_initializer.h"
#include "../../console/sweet_cmd_console.h"
#include "../lvl_script.h"

/* Level1  events !*/
#include "events/ev_change_window.h"
#include "events/ev_spawn_life.h"
#include "events/ev_dot_chase.h"
#include "events/ev_bot_tutorial.h"
#include "events/ev_build_start_walls.h"
#include "../../events/global_events/ev_update_heart.h"

/* Msg events*/
#include "msg_events/ev_new_goal.h"
#include "msg_events/EV_Hello.h"
#include "msg_events/ev_wasd.h"
#include "msg_events/ev_waking_up.h"
#include "msg_events/ev_arr_keys.h"
#include "msg_events/ev_day_1.h"

#include "../../events/global_events/feedback/ev_draw_map.h"

#include "../../player/player.h"	// don't...
#include "../../grid/AllGrids.h"

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
			Ev_Dr_Day_1();
		}
		if (gCurrentStage == 4)
		{
			P1.Set_Position({6,6});
			P1.Dis_Player_Sym();
			//Build_Lvl_1_Walls();
			// Ceci est temporaire pour débugger plus rapidement le bot script
			//Ev_Dr_Arr_Keys();
			//Ev_Dr_Wasd();
			Just_Dr_Heart();
			MsgQueue::Register(FREE_PLAYER);
			MsgQueue::Register(START_BOTS); // Here they come baby
		}
		//MsgQueue::Register(START_BOTS);	stage 3, après le tuto?			// Here they come baby
		break;	// fack

	case WAITING_TIME:
		break;

		/*Player*/
	case LOCK_PLAYER: 
		break;

	case PLAYER_SPAWNED: 
		if(gCurrentStage == 0)
			Ev_Dr_Wasd();							// Affiche les touches clavier du mouvement
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
		Ev_Dr_New_Goal();		// - NEW GOAL -
		Ev_Spawn_Life();
		//Erase_Map_Borders_1();
		break;

	case SPAWN_SPECIAL_ITEM: 
		Ev_Spawn_Mysterious_Item();			// Si tu trigger un event qui était déjà actif ici, ça va faire deux updates en 1 seul cycle! -	BAD -
		break;

		/*Bots*/
	case START_BOTS:
		break;
	}
}
