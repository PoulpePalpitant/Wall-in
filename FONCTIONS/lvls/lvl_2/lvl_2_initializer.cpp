
#include "lvl_2_initializer.h"

#include "../../events/msg_dispatcher.h"
#include "../../time/spawn_cycle.h"
#include "../../time/bot_move_cycle.h"
#include "../../player/player.h"
#include "../../spawns/bots_to_spawn.h"
#include "../../time/timerOP.h"
#include "../../grid/managegrids.h"
#include "../../items/item_spawner.h"
#include "../../spawns/valid_spwn_intervals.h"
#include "../lvl_script.h"
#include "events/ev_build_labyrinth.h"



void Lvl_2_Initializer()
{
	gLvlTime = 0;		// Reset Le timer du niveau

	if (gSkipStory)
	{
		// Pour un normal quick start
		gCurrentStage = 5; // Normal
		//gCurrentStage = 0; // wakup
		//gCurrentStage = 1; // TEST #1
		//gCurrentStage = 2; // TEST #2
		//gCurrentStage = 3; // TEST #3
		//gCurrentStage = 4; // warning


		MsgQueue::Register(STAGE_ADVANCE);	// Start le stage à partir du msgdispatcher du nlvl 1. 
	}
	else
	{
		//gCurrentStage = 1;	// Pour choisir le niveau que tu veux pour starter	: 0 = wakeup
		//MsgQueue::Register(STAGE_ADVANCE);	// Start le stage à partir du msgdispatcher du nlvl 1. 


		gCurrentStage = 0;
		Ev_Build_Labyrinth(); // start le level avec ceci :)
		MsgQueue::Register(SPAWN_PLAYER);	// spawn le player 
	}

	gSpwBotTimer.Start_Timer(SPW_BOT_SPD_LVL2, 1 , true); // DEFUALT
	//gSpwBotTimer.Start_Timer(7000, 1 , true); // TEST
	gBotMoveTimer.Start_Timer(6200, 1, true); //DEFAULT
	//gBotMoveTimer.Start_Timer(50200, 1, true);	// TEST
	
	ItemSpawner::Add_To_Pool(ItemType::BUFFER, BUFFER_SPEED_LVL2, 2);
	ItemSpawner::Add_To_Pool(ItemType::BLOCKER, BLOCKER_SPEED_LVL2, 2);
	//ItemSpawner::Add_To_Pool(ItemType::HEALTH, 1000, 0);
	ItemSpawner::Add_To_Pool(ItemType::HEALTH, 20, 15);
	//ItemSpawner::Add_To_Pool(ItemType::CORRUPTED, 10, 0);

	ValidSpwnIntervals::Initialize_Valid_Spawn_List(); // MUST BE DONE BEFORE WHEN WE START EACH LEVEL BRAH

	Resize_Grids_To_Level(gGrids, 2);			// Resize tout les grids pour ce niveau :)
	bots_to_spawn::Reset_To_Default();			// reset les valeurs par défaut pour le prochain spawn
	
	P1.Set_Hp(3);	// 3 de vie le gros
	P1.Set_Position({ linkGrid->Get_Cols() / 2, linkGrid->Get_Rows() - 1 });
	
	if (!P1.Set_On_Grid())		// Doit être sur le grid pour le niveau
		throw "player pas sur le grid";
	
	MsgQueue::Register(LVL_INITIALIZED);// It has to be done
	MsgQueue::Register(ENABLE_BLAST);	// quicker quick start
	
	MsgQueue::Register(DISABLE_ITEM_SPAWN); // items!

}