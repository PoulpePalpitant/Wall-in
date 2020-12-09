
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
	gLvlTime = 0;		

	if (gSkipStory)
	{
		// Pour un normal quick start
		//gCurrentStage = 0; // wakup
		//gCurrentStage = 1; // warning
		gCurrentStage = 2; // Normal
		MsgQueue::Register(STAGE_ADVANCE);	

		// TEST DU SPAWN SCRIPT ICI
		// **************************
		int checkpointTest = 7;/*17 = max*/
		if (gCurrentPuzzle[gCurrentLevel - 1] < checkpointTest)
			gCurrentPuzzle[gCurrentLevel - 1] = checkpointTest;	// Start à partir de ce checkpoint
	}
	else
	{
		gCurrentStage = 0;
		Ev_Build_Labyrinth(); // start le level avec ceci :
	}


	gSpwBotTimer.Start_Timer(1700, 1, true); //  DEFUALT
	gBotMoveTimer.Start_Timer(10000, 1, true);		// DEFUALT


	//gSpwBotTimer.Start_Timer(7000, 1 , true); // TEST
	//gBotMoveTimer.Start_Timer(10200, 1, true);	// TEST


	Resize_Grids_To_Level(gGrids, 2);					
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