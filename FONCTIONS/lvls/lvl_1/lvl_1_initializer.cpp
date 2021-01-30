
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
#include "events/ev_bot_tutorial2.h"
#include "msg_events/ev_day_1.h"
#include "msg_events/ev_waking_up.h"
#include "../../spawns/valid_spwn_intervals.h"

#include "../../events/global_events/ev_lvl_unlocked.h"

void Lvl_1_Initializer()
{
	if (gSkipTutorial)
	{
		gCurrentStage = 3; 
		MsgQueue::Register(STAGE_ADVANCE);	

		// TEST DU SPAWN SCRIPT ICI
		// **************************
		int checkpointTest = 0;/*17 = max*/
		if(gCurrentPuzzle[gCurrentLevel - 1] < checkpointTest)
			gCurrentPuzzle[gCurrentLevel - 1] = checkpointTest;	// Start à partir de ce checkpoint
	}
	else
	{
		gCurrentStage = 0;
		MsgQueue::Register(SPAWN_PLAYER);	
	}

	gSpwBotTimer.Start_Timer(1700, 1 , true);	
	gBotMoveTimer.Start_Timer(10000, 1, true);	


	Resize_Grids_To_Level(gGrids, 1);			
	bots_to_spawn::Reset_To_Default();			
	
	P1.Set_Hp(3);	// 3 de vie le gros
	P1.Set_Position({ linkGrid->Get_Cols() / 2, linkGrid->Get_Rows() - 1 });
	
	MsgQueue::Register(LVL_INITIALIZED);
	MsgQueue::Register(DISABLE_BLAST);	
}