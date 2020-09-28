

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
#include "../../../blast/blast_modifier_queue.h"
#include "../../../spawns/ev_spawn_Jerry.h"	// pour spawner jerry


static Event ev_Lvl2_Training_3(Ev_Lvl2_Training_3, 13);
static bool leftOrRight = true;

static void Block_Prison(bool Remove = false)
{
	GrdCoord crd = { 0,0 };

	for (int c = crd.c; c < linkGrid->Get_Cols(); c++)
		gGrids.Activate_Blocker({ c,crd.r }, Remove);

	crd.r++;
	gGrids.Activate_Blocker({ 0,crd.r }, Remove);

	crd.r++;
	for (int c = crd.c; c < linkGrid->Get_Cols(); c++)
		gGrids.Activate_Blocker({ c,crd.r }, Remove);
}

static void Refresher()	/// Refresher du stage
{
	if (gRefreshStage || P1.Get_HP() < 1)
	{
		Clear_Map();
		P1.Set_Position({ 1,1 }); P1.Reset_Hp_And_Heart(1);
		P1.Dr_Player();
		gGrids.Make_Chain_Of_Walls({ 2, 1 }, LEFT, 1);	// Mur que le joueur va transfert
		Block_Prison(); // Prison de blockers autours du joueur
		Press_R_To_Refresh();
		Press_X_To_Proceed(3);
		Just_Dr_Map_Borders();

		BlastModifierQueue::Add_Modifier(BLOCKER);
		BlastModifierQueue::Add_Modifier(BLOCKER);
		ev_Lvl2_Training_3.Go_To_X_Step(2);
		gRefreshStage = false;
	}
}
// V2
void Ev_Lvl2_Training_3()			// Le joueur apprend comment tirer sur les modifiers
{

	if (!ev_Lvl2_Training_3.Is_Active())
	{
		Clear_All_Renders();
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
					ConsoleRender::Add_String(GOAL_STOP, Up_Txt_2(GOAL_STOP), BRIGHT_WHITE, TXT_SPD_DR);
				}
				else
					ev_Lvl2_Training_3.delay.Start_Timer(1000);

				break;

			case 2:
				ev_Lvl2_Training_3.delay.Stop();
				ev_Lvl2_Training_3.Advance(500);
				break;

			case 3:
				Spawn_A_Jerry(UP, 1);
				ev_Lvl2_Training_3.Advance(5000);	// 1000 / 2 = 500.		2 secondes
				break;

			case 4:
				Erase_Map_Borders_1();
				ev_Lvl2_Training_3.Advance(800);
				break;

			case 5:
				Spawn_A_Jerry(DOWN, 1);
				ev_Lvl2_Training_3.Advance(500);
				break;

			case 6:
				Spawn_A_Jerry(UP, 1);
				ev_Lvl2_Training_3.Advance(500);
				break;

			case 7:
				Spawn_A_Jerry(DOWN, 1);
				ev_Lvl2_Training_3.Advance(5000);
				break;

			case 8:
				ev_Lvl2_Training_3.Advance(0);
				ev_Lvl2_Training_3.delay.Start_Timer(10000, 1, true);
				break;

				// EVENT N'EST PAS CANCELLÉ!
			}

	}
}


// V1
//void Ev_Lvl2_Training_3()			// Le joueur apprend comment tirer sur les modifiers
//{
//
//	if (!ev_Lvl2_Training_3.Is_Active())
//	{
//		Press_R_To_Refresh();
//		Press_X_To_Proceed(3);Clear_All_Renders();
//		Clear_Map();	// hope
//		blastP1.Cancel();			 // Cancel le blast
//		// Erase blast
//		// stop drawer queues
//
//
//		ev_Lvl2_Training_3.Activate();
//		ev_Lvl2_Training_3.Start(1000);	
//		MsgQueue::Register(LOCK_PLAYER);
//	}
//	else
//	{
//		Refresher();
//		while (ev_Lvl2_Training_3.delay.Tick())
//			switch (ev_Lvl2_Training_3.Get_Current_Step())
//			{
//			case 1:
//				if (Resize_Grids_To_Level(gGrids, gCurrentLevel, gCurrentStage))
//				{
//					ev_Lvl2_Training_3.Advance(0);	// 1000 / 2 = 500.		2 secondes
//					MsgQueue::Register(ENABLE_BLAST);
//					MsgQueue::Register(FREE_PLAYER);
//					gRefreshStage = true;	// lazy shortcut pour tout refresh
//				}
//				else
//					ev_Lvl2_Training_3.delay.Start_Timer(1000);
//
//				break;
//
//			case 2:
//				Just_Dr_Map_Borders();
//				gGrids.Make_Chain_Of_Walls({ 0, 1 }, RIGHT, 1);	// Mur que le joueurs va tirés avec les items
//				gGrids.Make_Chain_Of_Walls({ linkGrid->Get_Cols() - 1, 1 }, LEFT, 1);	// Mur que le joueurs va tirés avec les items
//				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 4,1 }, true, true);
//				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 5,1 }, true, true);
//				ev_Lvl2_Training_3.delay.Stop();
//				ev_Lvl2_Training_3.Advance(500);
//				break;
//
//			case 3:
//				Spawn_A_Bot(UP, 0);
//				Spawn_A_Bot(DOWN, spawnGrid->Get_MaxSpwnCrdX() - 1);
//				ev_Lvl2_Training_3.Advance(5000);	// 1000 / 2 = 500.		2 secondes
//				break;
//
//			case 4 :
//				Erase_Map_Borders_1();
//				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 4,1 }, true, true);
//				//if (!ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,1 }, true))
//					//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 4,1 }, true);
//
//				ev_Lvl2_Training_3.Advance(5000);
//				break;
//
//			case 5:
//				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 5,1 }, true, true);
//				//if (!ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 4,1 }, true))
//					//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 6,1 }, true);
//
//				ev_Lvl2_Training_3.Advance(5000);
//				break;
//
//			case 6:
//				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 2,1 }, true, true);
//				ev_Lvl2_Training_3.Advance(5000);
//				break;
//
//			case 7:
//				Spawn_A_Bot(DOWN, 0);
//				ev_Lvl2_Training_3.Advance(5000);
//				break;
//
//			case 8:
//				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 3,1 }, true, true);
//				ev_Lvl2_Training_3.Advance(5000);
//				break;
//
//			case 9:
//				Spawn_A_Bot(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);
//				ev_Lvl2_Training_3.Advance(5000);
//				break;
//
//			case 10:
//				//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 2,1 }, true);
//				ev_Lvl2_Training_3.Advance(5000);
//				break;
//
//			case 11:
//				Spawn_A_Bot(UP, 0);
//				ev_Lvl2_Training_3.Advance(5000);
//				break;
//
//			case 12:
//				Spawn_A_Bot(UP, spawnGrid->Get_MaxSpwnCrdX() - 1);
//				ev_Lvl2_Training_3.Advance(0);
//				ev_Lvl2_Training_3.delay.Start_Timer(10000,1,true);
//				break;
//
//				// EVENT N'EST PAS CANCELLÉ!
//			}
//
//	}
//}
