
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

#include "../../events/global_events/ev_lvl_unlocked.h"

void Lvl_1_Initializer()
{
	gLvlTime = 0;		

	if (gSkipStory)
	{
		// Pour un quick start avec warning
		//gCurrentStage = 2;
		//gSkipStory = false;
		
		// Pour un normal quick start
		gCurrentStage = 3; 


		//gCurrentStage = 1;	// Skip tout les tutorials
		//Ev_Bot_Tutorial();	// TEST EVENT TUTORIAL AVEC JERRY
		//gSkipStory = false;


		MsgQueue::Register(STAGE_ADVANCE);	

		// TEST DU SPAWN SCRIPT ICI
		// **************************
		int checkpointTest = 9;/*17 = max*/
		if(gCurrentPuzzle[gCurrentLevel - 1] < checkpointTest)
			gCurrentPuzzle[gCurrentLevel - 1] = checkpointTest;	// Start à partir de ce checkpoint
	}
	else
	{

		//Ev_Wake_Up();		// TEST EVENT WAKEUP
		gCurrentStage = 0;
		MsgQueue::Register(SPAWN_PLAYER);	
	}

	gSpwBotTimer.Start_Timer(1700, 1 , true); //  DEFUALT
	//gSpwBotTimer.Start_Timer(7000, 1 , true); // DEBUG


	gBotMoveTimer.Start_Timer(10000, 1, true);		// DEFUALT
	//gBotMoveTimer.Start_Timer(50200, 1, true);	// DEBUG


	Resize_Grids_To_Level(gGrids, 1);			
	bots_to_spawn::Reset_To_Default();			
	
	P1.Set_Hp(3);	// 3 de vie le gros
	P1.Set_Position({ linkGrid->Get_Cols() / 2, linkGrid->Get_Rows() - 1 });
	
	if (!P1.Set_On_Grid())		
		throw "player pas sur le grid";
	
	MsgQueue::Register(LVL_INITIALIZED);
	MsgQueue::Register(DISABLE_BLAST);	
}