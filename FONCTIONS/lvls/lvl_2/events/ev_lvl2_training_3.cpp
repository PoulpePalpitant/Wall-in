

#include "ev_lvl2_training_3.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../player/player.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../inputs/action_input.h"
#include "../../../structure_manager/modify_chain.h"
#include "../../../events/global_events/ev_to_proceed.h"
#include "../../../items/item_spawner.h"
#include "../../../grid/managegrids.h"
#include "../../../spawns/spawn_bot.h"
#include "../../../bots/botlist.h"
#include "../../lvl_script.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"



static Event ev_Lvl2_Training_3(Ev_Lvl2_Training_3, 13);
static bool leftOrRight = true;

static void Block_Prison(bool Remove = false)
{
	GrdCoord crd = { 0,0 };

	for (int c = crd.c; c < linkGrid->Get_Cols(); c++)
		gGrids.Activate_Blocker({ c,crd.r }, Remove);

	crd.r+= 2;

	for (int c = crd.c; c < linkGrid->Get_Cols(); c++)
		gGrids.Activate_Blocker({ c,crd.r }, Remove);
}

static void Refresher()	/// Refresher du stage
{
	if (gRefreshStage || P1.Get_HP() < 3)
	{
		Clear_Map();
		P1.Set_Position({ linkGrid->Get_Cols() / 2,1 }); P1.Reset_Hp();
		P1.Dr_Player();
		Block_Prison(); // Prison de blockers autours du joueur
		ev_Lvl2_Training_3.Go_To_X_Step(2);
		gRefreshStage = false;
	}
}

void Ev_Lvl2_Training_3()			// Le joueur apprend comment tirer sur les modifiers
{

	if (!ev_Lvl2_Training_3.Is_Active())
	{
		Press_R_To_Refresh();
		Press_X_To_Proceed(3);
		Clear_Map();	// hope
		blastP1.Cancel();			 // Cancel le blast
		// Erase blast
		// stop drawer queues


		ev_Lvl2_Training_3.Activate();
		ev_Lvl2_Training_3.Start(1000);	
		MsgQueue::Register(LOCK_PLAYER);
	}
	else
	{
		Refresher();
		while (ev_Lvl2_Training_3.delay.Tick())
			switch (ev_Lvl2_Training_3.Get_Current_Step())
			{
			case 1:
				if (Resize_Grids_To_Level(gGrids, gCurrentLevel, gCurrentStage))
				{
					ev_Lvl2_Training_3.Advance(0);	// 1000 / 2 = 500.		2 secondes
					MsgQueue::Register(ENABLE_BLAST);
					MsgQueue::Register(FREE_PLAYER);
					gRefreshStage = true;	// lazy shortcut pour tout refresh
				}
				else
					ev_Lvl2_Training_3.delay.Start_Timer(1000);

				break;

			case 2:
				Just_Dr_Map_Borders();
				gGrids.Make_Chain_Of_Walls({ 0, 1 }, RIGHT, 1);	// Mur que le joueurs va tirés avec les items
				gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 1 }, LEFT, 1);	// Mur que le joueurs va tirés avec les items
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 4,1 }, true, true);
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 5,1 }, true, true);
				ev_Lvl2_Training_3.delay.Stop();
				ev_Lvl2_Training_3.Advance(500);
				break;

			case 3:
				Spawn_A_Bot(UP, 0);
				Spawn_A_Bot(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 1);
				ev_Lvl2_Training_3.Advance(5000);	// 1000 / 2 = 500.		2 secondes
				break;

			case 4 :
				Erase_Map_Borders_1();
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 4,1 }, true, true);
				//if (!ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,1 }, true))
					//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 4,1 }, true);

				ev_Lvl2_Training_3.Advance(5000);
				break;

			case 5:
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 5,1 }, true, true);
				//if (!ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 4,1 }, true))
					//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 6,1 }, true);

				ev_Lvl2_Training_3.Advance(5000);
				break;

			case 6:
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 2,1 }, true, true);
				ev_Lvl2_Training_3.Advance(5000);
				break;

			case 7:
				Spawn_A_Bot(DOWN, 0);
				ev_Lvl2_Training_3.Advance(5000);
				break;

			case 8:
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 3,1 }, true, true);
				ev_Lvl2_Training_3.Advance(5000);
				break;

			case 9:
				Spawn_A_Bot(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);
				ev_Lvl2_Training_3.Advance(5000);
				break;

			case 10:
				//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 2,1 }, true);
				ev_Lvl2_Training_3.Advance(5000);
				break;

			case 11:
				Spawn_A_Bot(UP, 0);
				ev_Lvl2_Training_3.Advance(5000);
				break;

			case 12:
				Spawn_A_Bot(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);
				ev_Lvl2_Training_3.Advance(0);
				ev_Lvl2_Training_3.delay.Start_Timer(10000,1,true);
				break;

				// EVENT N'EST PAS CANCELLÉ!
			}

	}
}