
#include "lvl_1_initializer.h"

#include "../../events/msg_dispatcher.h"
#include "../../time/spawn_cycle.h"
#include "../../time/bot_move_cycle.h"
#include "../../player/player.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../time/timerOP.h"
#include "../../grid/managegrids.h"

void Lvl_1_Initializer()
{
	gLvlTime = 0;		// Reset Le timer du niveau
	
	// DONT TOUCH	***********************************************************************************
//**** WIN SIZE: 85/48			ou 713x807

	// DONT TOUCH	************************************************************************************
		// Vitesse des BOTS
		//BOT_Move_Cycle = 400;	// pas touché!
		// Vitesse des bots		// 200 = good speed pour les autres niveaux, ici 225-250 devrait être bon, check ton event qui rétablit la vitesse dans ce niv: ce sera la vrai bonne valeur 

	/**//* RAPPEL *//**/

	// Pour l'initialisation d'un niveau, il faut mettre les cycles de spawn et de BOTmove en même temps
	// et Activer le spawn et le bot move pour le cycle courant
	gSpawnCycle = 10000;	//test								// 10000 pour la vitesse du timer op, 1000 pour la vitesse de la fonction clock() que j'ai fabriqué
	gCurrentSpawnCycle = 20000;		// Premier Spawn!!!
	gNextSpawnCycle = gCurrentSpawnCycle + gSpawnCycle;
	gSpawnThisCycle = false;
	
	//test
	gBotMoveCycle = 400;
	gCurrentBotMoveCycle = gCurrentSpawnCycle;					// On bouge les bots quand y va avoir des bots de spawné
	gNextBotMoveCycle = gCurrentBotMoveCycle + gBotMoveCycle;
	gMoveBotsThisCycle = true;

	P1.Set_Position({ linkGrid->Get_Cols() / 2, 4 + linkGrid->Get_Rows() / 2 });
	P1.Set_Hp(3);	// 3 de vie le gros

	bots_to_spawn::Reset_To_Default();			// reset les valeurs par défaut pour le prochain spawn
	Resize_Grids_To_Level(gGrids, 1);			// Resize tout les grids pour ce niveau :)

	gLvlTime = 0;

	MsgQueue::Register(LVL_INITIALIZED);	// It has to be done
}