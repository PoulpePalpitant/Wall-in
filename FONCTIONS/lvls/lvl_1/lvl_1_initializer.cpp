
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
#include "events/ev_bot_tutorial.h"
#include "msg_events/ev_day_1.h"

void Lvl_1_Initializer()
{
	gLvlTime = 0;		// Reset Le timer du niveau

	if (gSkipStory)
	{
		//gCurrentStage = 3;
		//MsgQueue::Register(STAGE_ADVANCE);	// Start le stage � partir du msgdispatcher du nlvl 1. 

		gCurrentStage = 2;	// Skip tout les tutorials
		Ev_Bot_Tutorial();	// start tuto avec jerry
	}
	else
	{
		gCurrentStage = 0;
		MsgQueue::Register(SPAWN_PLAYER);	// spawn le player 
	}

	gSpwBotTimer.Start_Timer(500 , 1 , true);
	gBotMoveTimer.Start_Timer(7000, 1, true);
	
	//ItemSpawner::Add_To_Pool(ItemType::BUFFER, 1000, 0);
	//ItemSpawner::Add_To_Pool(ItemType::BLOCKER, 1000, 50);
	//ItemSpawner::Add_To_Pool(ItemType::CORRUPTED, 1000, 0);


	Resize_Grids_To_Level(gGrids, 1);			// Resize tout les grids pour ce niveau :)
	bots_to_spawn::Reset_To_Default();			// reset les valeurs par d�faut pour le prochain spawn
	
	P1.Set_Hp(3);	// 3 de vie le gros
	P1.Set_Position({ linkGrid->Get_Cols() / 2, 7 + linkGrid->Get_Rows() / 2 });
	
	if (!P1.Set_On_Grid())		// Doit �tre sur le grid pour le niveau
		throw "player pas sur le grid";
	
	MsgQueue::Register(LVL_INITIALIZED);// It has to be done
	MsgQueue::Register(DEACTIVATE_BLAST);	// It has to be done
	//MsgQueue::Register(START_BOTS);	// It has to be done
	
}