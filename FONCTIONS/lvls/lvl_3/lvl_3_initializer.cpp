
#include "lvl_3_initializer.h"

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



void Lvl_3_Initializer()
{
	if (gSkipStory)
	{
		// Pour un normal quick start
		gCurrentStage = 0; // Normal
		MsgQueue::Register(STAGE_ADVANCE);	
		
		// TEST DU SPAWN SCRIPT ICI
		// **************************
		int checkpointTest = 18;/* 23 = max*/

		if (gCurrentPuzzle[gCurrentLevel - 1] < checkpointTest)
			gCurrentPuzzle[gCurrentLevel - 1] = checkpointTest;	// Start à partir de ce checkpoint
	}



	gSpwBotTimer.Start_Timer(2000, 1, true); //  DEFUALT
	gBotMoveTimer.Start_Timer(10000, 1, true);		// DEFUALT


	//gSpwBotTimer.Start_Timer(7000, 1 , true); // TEST
	//gBotMoveTimer.Start_Timer(10200, 1, true);	// TEST


	Resize_Grids_To_Level(gGrids, 3);					
	ValidSpwnIntervals::Initialize_Valid_Spawn_List(); 
	bots_to_spawn::Reset_To_Default();					
	
	P1.Set_Hp(3);	
	P1.Set_Position({ linkGrid->Get_Cols() / 2, linkGrid->Get_Rows() - 1 });
	
	if (!P1.Set_On_Grid())		
		throw "player pas sur le grid";
	
	MsgQueue::Register(LVL_INITIALIZED);
	MsgQueue::Register(ENABLE_BLAST);	
	
	MsgQueue::Register(DISABLE_ITEM_SPAWN);

}