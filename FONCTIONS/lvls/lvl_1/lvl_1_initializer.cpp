
#include "../../time/spawn_cycle.h"
#include "../../time/bot_move_cycle.h"
#include "../../player/player.h"
#include "../../spawns/bots_to_spawn.h"
#include "lvl_1_initializer.h"
#include "../../time/timerOP.h"


void Lvl_1_Initializer()
{
	gLvlTime = 0;		// Reset Le timer du niveau
	
	// DONT TOUCH	***********************************************************************************
//**** WIN SIZE: 85/48			ou 713x807

	// DONT TOUCH	************************************************************************************
		// Vitesse des BOTS
		//BOT_Move_Cycle = 400;	// pas touch�!
		// Vitesse des bots		// 200 = good speed pour les autres niveaux, ici 225-250 devrait �tre bon, check ton event qui r�tablit la vitesse dans ce niv: ce sera la vrai bonne valeur 

	/**//* RAPPEL *//**/

	// Pour l'initialisation d'un niveau, il faut mettre les cycles de spawn et de BOTmove en m�me temps
	// et Activer le spawn et le bot move pour le cycle courant
	gSpawnCycle = 10000;	//test								// 10000 pour la vitesse du timer op, 1000 pour la vitesse de la fonction clock() que j'ai fabriqu�
	gCurrentSpawnCycle = 20000;		// Premier Spawn!!!
	gNextSpawnCycle = gCurrentSpawnCycle + gSpawnCycle;
	gSpawnThisCycle = false;
	
	
	//test
	gBotMoveCycle = 4000;
	gCurrentBotMoveCycle = gCurrentSpawnCycle;					// On bouge les bots quand y va avoir des bots de spawn�
	gNextBotMoveCycle = gCurrentBotMoveCycle + gBotMoveCycle;
	gMoveBotsThisCycle = true;


	P1.Set_Hp(3);	// 3 de vie le gros

	bots_to_spawn::Reset_To_Default();			// reset les valeurs par d�faut pour le prochain spawn
}