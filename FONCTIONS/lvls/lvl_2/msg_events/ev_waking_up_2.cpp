

#include "ev_waking_up_2.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../player/player.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../inputs/action_input.h"
#include "../../../structure_manager/modify_chain.h"
#include "../../../events/global_events/ev_to_proceed.h"
#include "../../../items/item_spawner.h"

#include "../../../choice/choice_time.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../lvl_script.h"
#include "../../../UI/console_output/dsp_string.h"

static Event ev_WakeUp2(Ev_Wake_Up_2, 30);

static std::string _1 = "Hey, Welcome Back!"; 
static std::string _2 = "Usually People Tend To Quit On Their First Day";
static std::string _3 = "If They Manage To Survive That Is...";
static std::string _4 = ". . .";
static std::string _5 = ".";
static std::string _6 = "Let Me introduce You To You New Tools";
static std::string _7 = "They Are All Very Useful Tool As I'm";
static std::string _8 = "Sure You Will Notice By Yourself";
static std::string _9 = "It Is Company Policy That You Use Them Anyway";
static std::string _10 ="If You Don't Well...";
static std::string _11 = "We'll Keep Sending Them Haha, There Is No Escape.";
static std::string _12 = "So That's All For Me Here";
static std::string _13= "Complete Your Trainings And...";
static std::string _14 = "Try Not To Die.";
static std::string _15 = "Good Luck!";
static std::string _16 = "brr";
static std::string _17 = "asdasd";
static std::string _18 = "asdasd";
static std::string _19 = "asdasd";

// CHOICE STRINGS
static std::string yes_1 = "Huuh...";				// Accept de faire le tutorial
static std::string subyes_1 =  "(Start Tutorial)";	// Accept de faire le tutorial
static std::string yes_2 = "Actually, Maybe Not.";
static std::string subyes_2 = "(You Swallow your Ego)";
static std::string no_1 = "Yes!";					// refuse de faire le tutorial
static std::string subno_1 = "(You Are Confident)";	// refuse de faire le tutorial
static std::string no_2 = "Absolutely!";
static std::string subno_2 = "(You Know What You're Doing)";


void Lvl2_S1_Refresher()	/// Refresher du niveau 2, stage 1
{
	if (gRefreshStage)
	{
		ListsOfChainToModify::Annihilate_All_Links();	// Links
		ItemsOnGrid::Remove_All();	// enlève tout les items spawné
		gGrids.Make_Chain_Of_Walls({ 3,9 }, DOWN, wallGridVer->Get_Rows() - 9);	// Mur que le joueurs va tirés avec les items
		gGrids.Make_Chain_Of_Walls({ 9,9 }, DOWN, wallGridVer->Get_Rows() - 9);	// Mur que le joueurs va tirés avec les items
		ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,5 });
		ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 9,5 });
		P1.Er_Player();
		P1.Set_Position({ 2,2 });
		P1.Dr_Player();
		gRefreshStage = false;
	}


}

void Ev_Wake_Up_2()			// Accueil Le joueur quand il sort de son répit
{
	if (!ev_WakeUp2.Is_Active())
	{
		Press_X_To_Proceed(3);
		Just_Dr_Map_Borders();
		ListsOfChainToModify::Annihilate_All_Links();	// Links
		ev_WakeUp2.Activate();
		ev_WakeUp2.Start(500);	// 1000 / 2 = 500.		2 secondes
		MsgQueue::Register(ENABLE_BLAST);
	}
	else
	{
		Lvl2_S1_Refresher();
		while (ev_WakeUp2.delay.Tick())
			switch (ev_WakeUp2.Get_Current_Step())
			{
			case 1:
				gGrids.Make_Chain_Of_Walls({3,9},DOWN, wallGridVer->Get_Rows() - 9);	// Mur que le joueurs va tirés avec les items
				gGrids.Make_Chain_Of_Walls({9,9},DOWN, wallGridVer->Get_Rows() - 9);	// Mur que le joueurs va tirés avec les items
				for (int c = 0; c < linkGrid->Get_Cols(); c++)
				{
					gGrids.Activate_Blocker({ c,3 });
				}

				Press_R_To_Refresh();
				ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, 150);
				ev_WakeUp2.Advance(350);
				break;

			case 2:
				ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, 50, true);
				ev_WakeUp2.Advance(700);
				break;

			case 3:
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,5 });
				ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 9,5 });
				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(800);
				break;

			case 4:
				ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(340);
				break;

			case 5:
				ev_WakeUp2.Advance(0);
				break;

			case 6:
				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, 50, true);
				ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, 50, true);
				ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(400);
				break;

			case 7:
				ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(800);
				break;

			case 8:
				ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5), gBossClr, 175);
				ev_WakeUp2.Advance(600);
				break;

			case 9:
				ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6, 1), gBossClr, 250);
				ev_WakeUp2.Advance(900);
				break;

			case 10:
				ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7, 2), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(350);
				break;

			case 11:
				ev_WakeUp2.Advance(0);
				break;

			case 12:
				ConsoleRender::Add_String(_14, Boss_Txt_Crd(_14), gBossClr, 50, true);
				ConsoleRender::Add_String(_15, Boss_Txt_Crd(_15, 1), gBossClr, 50, true);
				ConsoleRender::Add_String(_16, Boss_Txt_Crd(_16, 2), gBossClr, 50, true);
				ConsoleRender::Add_String(_17, Boss_Txt_Crd(_17, 3), gBossClr, 50, true);
				ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(900);
				break;

			case 13:
				ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6, 2), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(300);
				break;

			case 14:
				ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7), gBossClr, 250);
				ev_WakeUp2.Advance(400);
				break;

			case 15:
				ev_WakeUp2.Advance(0);
				break;

			case 16:
				ev_WakeUp2.Advance(500);
				break;

			case 17:
				ConsoleRender::Add_String(_8, Boss_Txt_Crd(_8), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(400);
				break;

			case 18:
				ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, 400);
				ev_WakeUp2.Advance(600);
				break;


			case 19:
				ConsoleRender::Add_String(_8, Boss_Txt_Crd(_8), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_9, Boss_Txt_Crd(_9), gBossClr, 250);
				ev_WakeUp2.Advance(700);
				break;

			case 20:
				ev_WakeUp2.Advance(0);
				break;

			case 21:
				ev_WakeUp2.Advance(300);
				break;

			case 22:
				ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(400);
				break;

			case 23:
				ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(300);
				break;

			case 24:
				ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(400);
				break;

			case 25:
				ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(400);
				break;

			case 26:
				ConsoleRender::Add_String(_13, Boss_Txt_Crd(_13, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(200);
				break;

			case 27:
				ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_13, Boss_Txt_Crd(_13, 1), gBossClr, TXT_SPD_ER, true);

				ev_WakeUp2.Cancel();
				break;


				/* Cheat laid ici, branching dialogue de bouette*/
			case 28:
				ev_WakeUp2.Advance(400);
				break;

			case 29:
				ev_WakeUp2.Advance(400);
				break;

			case 30:
				ev_WakeUp2.Advance(0);
				break;
			}

	}
}