
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
#include "msg_events/ev_waking_up.h"
#include "../../spawns/valid_spwn_intervals.h"

void Lvl_1_Initializer()
{
	gLvlTime = 0;		// Reset Le timer du niveau

	if (gSkipStory)
	{
		// Pour un quick start avec warning
		gCurrentStage = 4;
		gSkipStory = false;
		
		// Pour un normal quick start
		//gCurrentStage = 3; // super fast


		//gCurrentStage = 2;	// Skip tout les tutorials
		//Ev_Bot_Tutorial();	// start tuto avec jerry
		//gSkipStory = false;
		
		
		MsgQueue::Register(STAGE_ADVANCE);	// Start le stage à partir du msgdispatcher du nlvl 1. 
	}
	else
	{
		gCurrentStage = 0;
		MsgQueue::Register(SPAWN_PLAYER);	// spawn le player 
	}

	gSpwBotTimer.Start_Timer(500 , 1 , true); // DEFUALT
	//gSpwBotTimer.Start_Timer(7000, 1 , true); // TEST
	gBotMoveTimer.Start_Timer(6200, 1, true); //DEFAULT
	//gBotMoveTimer.Start_Timer(50200, 1, true);	// TEST
	
	//ItemSpawner::Add_To_Pool(ItemType::BUFFER, 30, 0);
	//ItemSpawner::Add_To_Pool(ItemType::BLOCKER, 20, 50);
	//ItemSpawner::Add_To_Pool(ItemType::CORRUPTED, 10, 0);
	//ItemSpawner::Add_To_Pool(ItemType::HEALTH, 500, 0);


	Resize_Grids_To_Level(gGrids, 1);			// Resize tout les grids pour ce niveau :)
	bots_to_spawn::Reset_To_Default();			// reset les valeurs par défaut pour le prochain spawn
	
	P1.Set_Hp(3);	// 3 de vie le gros
	P1.Set_Position({ linkGrid->Get_Cols() / 2, linkGrid->Get_Rows() - 1 });
	
	if (!P1.Set_On_Grid())		// Doit être sur le grid pour le niveau
		throw "player pas sur le grid";
	
	MsgQueue::Register(LVL_INITIALIZED);// It has to be done
	MsgQueue::Register(DISABLE_BLAST);	// It has to be done
}