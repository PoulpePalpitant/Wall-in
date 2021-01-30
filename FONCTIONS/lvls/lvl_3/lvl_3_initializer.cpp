
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
	// Pour un normal quick start
	gCurrentStage = 1; // Normal

	// TEST DU SPAWN SCRIPT ICI
	// **************************
	int checkpointTest = 0;/* 20 = max*/

	if (gCurrentPuzzle[gCurrentLevel - 1] < checkpointTest)
		gCurrentPuzzle[gCurrentLevel - 1] = checkpointTest;	// Start à partir de ce checkpoint

	gSpwBotTimer.Start_Timer(2000, 1, true);		

	gBotMoveTimer.Start_Timer(10000, 1, true);		

	Resize_Grids_To_Level(gGrids, 3);
	ValidSpwnIntervals::Initialize_Valid_Spawn_List();
	bots_to_spawn::Reset_To_Default();

	P1.Set_Hp(3);

	MsgQueue::Register(STAGE_ADVANCE);
	MsgQueue::Register(LVL_INITIALIZED);
	MsgQueue::Register(ENABLE_BLAST);
	MsgQueue::Register(DISABLE_ITEM_SPAWN);

}