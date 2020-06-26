
#include "../../lvls/lvl_script.h"

#include "../../events/msg_dispatcher.h"
#include "../../inputs/action_input.h"
#include "Ev_Game_Title.h"
#include "Ev_Start_Game.h"


void Ev_Start_Game()		// On comprend ici que tout les autres events du niveau seront ignoré durant ce cyclsi on change le currentLevel
{
	gCurrentLevel = 1;
	gChoiceTime = false;
	MsgQueue::Register(PLS_INTIALIZE_LVL);	// Nxt Level
	startGame.Deactivate();	// Désactive l'event		DOIT RETIRER CETTE EVENT DE LA LISTE, OH YEAH	
}

void OBS_Start_Game()	// L'observateur de l'événement
{
	//if(//Seledcted button == Start)
	// do stuff

	startGame.Activate();	// Active l'event
}


Event startGame(Ev_Start_Game);