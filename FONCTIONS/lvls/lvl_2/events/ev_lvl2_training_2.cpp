

#include "ev_lvl2_training_2.h"
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
#include "../../../spawns/ev_spawn_Jerry.h"	// pour spawner jerry



static Event ev_Lvl2_Training_2(Ev_Lvl2_Training_2, 8);
static bool leftOrRight = true;
static int dlay = 5;
static void Block_Prison(bool Remove = false)
{
	GrdCoord crd = P1.Get_Grd_Coord();

	crd.r--;
	for (int c = crd.c; c < linkGrid->Get_Cols() - 2; c++)
		gGrids.Activate_Blocker({ c,crd.r }, Remove);

	crd.r+= 2;

	for (int c = crd.c; c < linkGrid->Get_Cols() - 5; c++)
		gGrids.Activate_Blocker({ c,crd.r }, Remove);

	crd.c = linkGrid->Get_Cols() - 3;

	for (int r = 1; r < linkGrid->Get_Rows(); r++)
		gGrids.Activate_Blocker({ crd.c ,r }, Remove);

	crd.c = 2;

	for (int r = 2; r < linkGrid->Get_Rows() ; r++)
		gGrids.Activate_Blocker({ crd.c ,r }, Remove);
}

static void Refresher()	/// Refresher du stage
{
	if (gRefreshStage || P1.Get_HP() < 1)
	{
		Clear_Map();
		Press_R_To_Refresh();
		Press_X_To_Proceed(3);
		P1.Set_Position({ 0,1 }); P1.Reset_Hp_And_Heart(1); 
		P1.Dr_Player();
		Block_Prison(); // Prison de blockers autours du joueur
		Just_Dr_Map_Borders();
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 2,1 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 3,1 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,2 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 3,3 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,4 });
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,5 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 3,6 });
		ev_Lvl2_Training_2.Go_To_X_Step(2);
		gRefreshStage = false;
	}
}

void Ev_Lvl2_Training_2()			// Le joueur apprend comment tirer sur les modifiers
{

	if (!ev_Lvl2_Training_2.Is_Active())
	{
		
		Press_R_To_Refresh();
		Clear_All_Renders();
		Clear_Map();	// hope
		blastP1.Cancel();			 // Cancel le blast
		P1.Set_Hp(1);
		
		// Erase blast
		// stop drawer queues

		ev_Lvl2_Training_2.Activate();
		ev_Lvl2_Training_2.Start(1000);	
		MsgQueue::Register(LOCK_PLAYER);
	}
	else
	{
		Refresher();
		while (ev_Lvl2_Training_2.delay.Tick())
			switch (ev_Lvl2_Training_2.Get_Current_Step())
			{
			case 1:
				if (Resize_Grids_To_Level(gGrids, gCurrentLevel, gCurrentStage))
				{
					ev_Lvl2_Training_2.Advance(0);	// 1000 / 2 = 500.		2 secondes
					MsgQueue::Register(ENABLE_BLAST);
					MsgQueue::Register(FREE_PLAYER);
					gRefreshStage = true;	// lazy shortcut pour tout refresh
					ConsoleRender::Add_String(GOAL_STOP, Up_Txt_2(GOAL_STOP), BRIGHT_WHITE, TXT_SPD_DR);
				}
				else
					ev_Lvl2_Training_2.delay.Start_Timer(1000);

				break;

			case 2:
				ev_Lvl2_Training_2.delay.Stop();
				ev_Lvl2_Training_2.Advance(0);	// 1000 / 2 = 500.		2 secondes
				break;

			case 3:
				gGrids.Make_Chain_Of_Walls({ 3, 11 }, UP, 3);	// Mur que le joueurs va tirés avec les items
				ev_Lvl2_Training_2.Advance(500);
				break;

			case 4 :
					Spawn_A_Jerry(LEFT, 7, SPWN_DLAY + dlay);
					Spawn_A_Jerry(RIGHT, 7, SPWN_DLAY + dlay);
					Spawn_A_Jerry(RIGHT, 8, SPWN_DLAY + dlay);
				ev_Lvl2_Training_2.Advance(500);
				break;

			case 5:
				Set_Dr_Map_1();
				Spawn_A_Jerry(LEFT, 8, SPWN_DLAY + dlay);
				Spawn_A_Jerry(RIGHT, 8, SPWN_DLAY + dlay);
				Spawn_A_Jerry(LEFT, 9, SPWN_DLAY + dlay);
				ev_Lvl2_Training_2.Advance(500);
				break;

			case 6:
				Spawn_A_Jerry(LEFT, 9, SPWN_DLAY + dlay);
				Spawn_A_Jerry(RIGHT, 9, SPWN_DLAY + dlay);
				Spawn_A_Jerry(RIGHT, 10, SPWN_DLAY + dlay);
				ev_Lvl2_Training_2.Advance(500);
				break;

			case 7:
				Spawn_A_Jerry(LEFT, spawnGrid->Get_MaxSpwnCrdY() - 1, SPWN_DLAY + dlay);
				ev_Lvl2_Training_2.Advance(0);
				ev_Lvl2_Training_2.delay.Start_Timer(10000,1,true);
				break;

				// EVENT N'EST PAS CANCELLÉ!
			}

	}
}