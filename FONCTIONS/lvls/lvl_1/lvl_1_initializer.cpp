
#include "lvl_1_initializer.h"

#include "../../events/msg_dispatcher.h"
#include "../../time/spawn_cycle.h"
#include "../../time/bot_move_cycle.h"
#include "../../player/player.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../time/timerOP.h"
#include "../../grid/managegrids.h"
#include "../../items/item_spawner.h"
#include "../lvl_script.h"

void Lvl_1_Initializer()
{
	gLvlTime = 0;		// Reset Le timer du niveau
	gCurrentStage = 0;	// stage 1 baby

	gSpwBotTimer.Start_Timer(500 , 1 , true);
	gBotMoveTimer.Start_Timer(8000, 1, true);
	
	//ItemSpawner::Add_To_Pool(ItemType::BUFFER, 1000, 0);
	//ItemSpawner::Add_To_Pool(ItemType::BLOCKER, 1000, 50);
	//ItemSpawner::Add_To_Pool(ItemType::CORRUPTED, 1000, 0);


	Resize_Grids_To_Level(gGrids, 1);			// Resize tout les grids pour ce niveau :)
	bots_to_spawn::Reset_To_Default();			// reset les valeurs par défaut pour le prochain spawn
	
	P1.Set_Hp(3);	// 3 de vie le gros
	P1.Set_Position({ linkGrid->Get_Cols() / 2, 7 + linkGrid->Get_Rows() / 2 });
	
	if (!P1.Set_On_Grid())		// Doit être sur le grid pour le niveau
		throw "player pas sur le grid";
	
	MsgQueue::Register(LVL_INITIALIZED);// It has to be done
	MsgQueue::Register(SPAWN_PLAYER);	// It has to be done
	MsgQueue::Register(LOCK_PLAYER);	// It has to be done

	//MsgQueue::Register(START_BOTS);	// It has to be done
	
}