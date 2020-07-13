

#include "dispatch_msg_to_lvl_1.h"
#include "../../events/msg_dispatcher.h"
#include "lvl_1_initializer.h"
#include "../../console/sweet_cmd_console.h"

/* Level1  events !*/
#include "events/ev_change_window.h"
#include "events/ev_spawn_life.h"

/* Msg events*/
#include "msg_events/ev_new_goal.h"
#include "msg_events/EV_Hello.h"
#include "msg_events/ev_wasd.h"


#include "../../player/player.h"	// don't...

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
		MsgQueue::Register(START_BOTS);				// Here they come baby
		break;	// fack

	case WAITING_TIME:
		break;

		/*Player*/
	case LOCK_PLAYER: 
		break;

	case PLAYER_SPAWNED: 
		Ev_Dr_Wasd();							// Affiche les touches clavier du mouvement
		//MsgQueue::Register(FINAL_PUSH);
		break;

		/* Items*/
	case ITEM_PICKUP:
		Ev_Dr_New_Goal();		// - NEW GOAL -
		break;

	case SPAWN_SPECIAL_ITEM: 
		Ev_Spawn_Mysterious_Item();			// Si tu trigger un event qui était déjà actif ici, ça va faire deux updates en 1 seul cycle! -	BAD -
		break;

		/*Bots*/
	case START_BOTS:
		Ev_Er_New_Goal();  break;		// efface le Texte du new goal
		break;
	}
}
