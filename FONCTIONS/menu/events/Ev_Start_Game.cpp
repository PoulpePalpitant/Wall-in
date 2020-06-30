
#include "../../lvls/lvl_script.h"

#include "../../events/msg_dispatcher.h"
#include "../../inputs/action_input.h"
#include "Ev_Game_Title.h"
#include "Ev_Start_Game.h"


void Ev_Start_Game()		// On comprend ici que tout les autres events du niveau seront ignor� durant ce cyclsi on change le currentLevel
{
	gCurrentLevel = 1;
	gChoiceTime = false;
	MsgQueue::Register(PLS_INTIALIZE_LVL);	// Nxt Level
	ev_startGame.Deactivate();	// D�sactive l'event		DOIT RETIRER CETTE EVENT DE LA LISTE, OH YEAH	
}

void OBS_Start_Game()	// L'observateur de l'�v�nement
{
	//if(//Seledcted button == Start)
	// do stuff

	ev_startGame.Activate();	// Active l'event
}


Event ev_startGame(Ev_Start_Game);