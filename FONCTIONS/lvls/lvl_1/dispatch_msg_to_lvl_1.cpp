

#include "dispatch_msg_to_lvl_1.h"
#include "../../events/msg_dispatcher.h"
#include "lvl_1_initializer.h"
#include "../../console/sweet_cmd_console.h"

/* Level1  events !*/
#include "events/ev_change_window.h"
#include "msg_events/EV_Hello.h"
#include "events/ev_spawn_life.h"

#include "../../player/player.h"


// C'EST ICI QUE ÇA SE PASSE
void Dispatch_Msg_To_Lvl_1()
{
	// The bare minimum!
	switch (gCurrentMsg)
	{
	case PLS_INTIALIZE_LVL: Lvl_1_Initializer();	break;			// Initialize plein de choses	/* Remarque ce n'est pas un observateur, car c'est pas vraiment un event, en fin je crois */

	case LVL_INITIALIZED: P1.Spawn_Player(P1.Get_Grd_Coord(), true); // Cinématique d'apparition du joueur
		MsgQueue::Register(CHANGE_WINSIZE);
		MsgQueue::Register(SPECIAL_ITEM_SPAWNED);
		break;	// n'empêche même pas de register des messges ici :(

	case CHANGE_WINSIZE:OBS_Change_Window(); break;		// Test le changement de window

	case STAGE_ADVANCE:break;	// fack

	case WAITING_TIME:break;
	case LOCK_PLAYER: break;
	case ITEM_PICKUP:break;
	case SPECIAL_ITEM_SPAWNED: Ev_Spawn_Life(); break;
	}
}
