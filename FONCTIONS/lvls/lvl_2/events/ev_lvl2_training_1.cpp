

#include "ev_lvl2_training_1.h"
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

#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../lvl_script.h"


static Event ev_Lvl2_Training_1(Ev_Lvl2_Training_1, 7);

static void Block_Prison(bool Remove = false)
{
	GrdCoord crd = P1.Get_Grd_Coord();

	for (int c = -1; c < 2; c++)
		for (int r = -1; r < 2; r++)
		{
			if(!(c == 0 && r == 0))
				gGrids.Activate_Blocker({ crd.c + c,crd.r + r }, Remove);
		}
}

static void Refresher()	/// Refresher du stage
{
	if (gRefreshStage || P1.Get_HP() < 1)
	{
		//ItemsOnGrid::Remove_All();	// enl�ve tout les items spawn�
		//ListsOfChainToModify::Annihilate_All_Links();	// Links
		//botList.Destroy_All_Bots();	// Bots
		//P1.Er_Player();
		Clear_Map();
		Press_R_To_Refresh();
		Press_X_To_Proceed(3);
		P1.Set_Position({ 2,2 }); P1.Reset_Hp_And_Heart(1);
		P1.Dr_Player();
		Block_Prison(); // Prison de blockers autours du joueur
		ev_Lvl2_Training_1.Go_To_X_Step(2);
		gRefreshStage = false;
	}
}

void Ev_Lvl2_Training_1()			// Le joueur apprend comment tirer sur les modifiers
{
	if (!ev_Lvl2_Training_1.Is_Active())
	{
		Press_R_To_Refresh();
		Press_X_To_Proceed(3);
		Clear_All_Renders();
		Clear_Map();	// hope
		blastP1.Cancel();			 // Cancel le blast
		P1.Set_Hp(1);
		//clrscr

		Erase_Right_Text();	// backup
		ev_Lvl2_Training_1.Activate();
		ev_Lvl2_Training_1.Start(1000);	
		MsgQueue::Register(LOCK_PLAYER);
	}
	else
	{
		Refresher();
		while (ev_Lvl2_Training_1.delay.Tick())
			switch (ev_Lvl2_Training_1.Get_Current_Step())
			{
			case 1:
				if (Resize_Grids_To_Level(gGrids, gCurrentLevel, gCurrentStage))
				{
					ev_Lvl2_Training_1.Advance(0);	// 1000 / 2 = 500.		2 secondes
					MsgQueue::Register(ENABLE_BLAST);
					MsgQueue::Register(FREE_PLAYER);
					gRefreshStage = true;	// lazy shortcut pour tout refresh
				}
				else
					ev_Lvl2_Training_1.delay.Start_Timer(1000);

				break;

			case 2:
				Just_Dr_Map_Borders();
				ev_Lvl2_Training_1.delay.Stop();
				ev_Lvl2_Training_1.Advance(1000);	// 1000 / 2 = 500.		2 secondes
				break;

			case 3:
				gGrids.Make_Chain_Of_Walls({ 12,2 }, RIGHT, wallGridHor->Get_Cols() - 12);	// Mur que le joueurs va tir�s avec les items
				ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 11,2 });
				ev_Lvl2_Training_1.Advance(350);
				break;

			case 4 :
				Spawn_A_Bot(UP, 12);	Spawn_A_Bot(DOWN, 12);
				Spawn_A_Bot(UP, 15);	Spawn_A_Bot(DOWN, 15);
				Spawn_A_Bot(UP, 14);	Spawn_A_Bot(DOWN, 14);
				Spawn_A_Bot(UP, 13);	Spawn_A_Bot(DOWN, 13);
				ev_Lvl2_Training_1.Advance(875);
				break;

			case 5:
				Erase_Map_Borders_1();
				Block_Prison(true);	// Le joueur doit tir�!
				ev_Lvl2_Training_1.Advance(10000);
				break;

			case 6:
				ev_Lvl2_Training_1.Advance(0);
				ev_Lvl2_Training_1.delay.Start_Timer(10000,1,true);
				break;

				// EVENT N'EST PAS CANCELL�!
			}

	}
}