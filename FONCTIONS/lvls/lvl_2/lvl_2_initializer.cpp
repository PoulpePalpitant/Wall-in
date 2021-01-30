
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

	// TEST DU SPAWN SCRIPT ICI
	// **************************
	int checkpointTest = 0;/* 23 = max*/
	if (gCurrentPuzzle[gCurrentLevel - 1] < checkpointTest)
		gCurrentPuzzle[gCurrentLevel - 1] = checkpointTest;	// Start à partir de ce checkpoint


	gSpwBotTimer.Start_Timer(1700, 1, true); //  DEFUALT
	gBotMoveTimer.Start_Timer(10000, 1, true);		// DEFUALT

	Resize_Grids_To_Level(gGrids, 2);
	ValidSpwnIntervals::Initialize_Valid_Spawn_List();
	bots_to_spawn::Reset_To_Default();

	MsgQueue::Register(STAGE_ADVANCE);
	MsgQueue::Register(LVL_INITIALIZED);
	MsgQueue::Register(ENABLE_BLAST);
	MsgQueue::Register(DISABLE_ITEM_SPAWN);

}