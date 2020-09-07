

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
#include "../../../blast/blast_modifier_queue.h"

#include "../../../choice/choice_time.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../lvl_script.h"
#include "../../../UI/console_output/dsp_string.h"
#include "../../lvl_1/msg_events/ev_enter_name.h"		// INTRUDER

static Event ev_WakeUp2(Ev_Wake_Up_2, 30);

static std::string _1 = "Welcome Back Employee"; 
static std::string _2 = "Usually People Tend To Quit On Their First Day";
static std::string _3 = "If They Manage To Survive That Is...";
 //Hey, It's...You! "You Work Here Right?";
 //"I Can't Recall Your Name Somehow";
 //"I Don't Have Time To Talk....";
//
static std::string _4 = "That Said, If You Want To Keep Working Here,";
static std::string _5 = "You Will Have To Use Our Mandatory \"Tools\"";
static std::string _6 = "Here They Are";
static std::string _7 = "Try Them Both";
static std::string _8 = "Very Useful Right?";
static std::string _9 = "As I Said, These \"Great\" Tools Are MANDATORY";
// These Tools Have Been Around For A While Now. That's How Things Are Done Here. Better Get Used To It.
static std::string _10 = "If You Don't Use Them, Well...";
static std::string _11 = "Things Might Go Bad For You, I'm Afraid...";
//static std::string _11 = "We'll Make Sure That You Do :)";
static std::string _12 = "Anyway, That's All For Me Here";

// Histoire, le boss à reçu une mauvaise performance review et ça se peut qu'il se fasse mettre à la porte, ou du moins remplacé par Jerry
// Next Level On apprend qu'il s'est fait remplacé par Jerry, Qui est bcp trop intense, et qui a réussie à monter grâce à sa détermination
// Mais Jerry à des standards trop élevés (LVL Fast)

static std::string _13= "A Few Training Rooms Await You Next";
static std::string _14 = "Fell Free To Complete Them";

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
		P1.Set_Position({ 6,1 });
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
		P1.Set_Sym(AllPlyrSym[4]); P1.Set_Position({ 6,1 }); P1.Dr_Player();

		ListsOfChainToModify::Annihilate_All_Links();	// Links
		ev_WakeUp2.Activate();
		ev_WakeUp2.Start(0);	// 1000 / 2 = 500.		2 secondes
		MsgQueue::Register(ENABLE_BLAST);
		MsgQueue::Register(FREE_PLAYER);	// pour debug
	}
	else
	{
		Lvl2_S1_Refresher();
		while (ev_WakeUp2.delay.Tick())
			switch (ev_WakeUp2.Get_Current_Step())
			{
			case 1:

				for (int c = 0; c < linkGrid->Get_Cols(); c++)	// active une rangée de blockers
				{
					gGrids.Activate_Blocker({ c,3 });
				}

				ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, 150);
				ev_WakeUp2.Advance(350);
				break;

			case 2:
				ConsoleRender::Add_String(_1, Boss_Txt_Crd(_1), gBossClr, 50, true);
				ev_WakeUp2.Advance(500);
				break;

			case 3:

				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(400);
				break;

			case 4:
				//Ev_Enter_Name();
				ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(300);
				break;

			case 5:
				ConsoleRender::Add_String(_2, Boss_Txt_Crd(_2), gBossClr, 50, true);
				ConsoleRender::Add_String(_3, Boss_Txt_Crd(_3, 1), gBossClr, 50, true);
				ev_WakeUp2.Advance(500);
				break;

			case 6:
				ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(500);
				break;

			case 7:
				ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5 , 1), gBossClr, 175);
				ev_WakeUp2.Advance(250);
				break;

			case 8:
				ConsoleRender::Add_String(_4, Boss_Txt_Crd(_4), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5,1), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(500);
				break;

			case 9:
				ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6, 1), gBossClr, 250);
				ev_WakeUp2.Advance(900);
				break;

			case 10:
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { 3,5 });
				ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { 9,5 });
				ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7, 2), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(550);
				break;

			case 11:
				gGrids.Make_Chain_Of_Walls({ 3,9 }, DOWN, wallGridVer->Get_Rows() - 9);	// Mur que le joueurs va tirés avec les items
				gGrids.Make_Chain_Of_Walls({ 9,9 }, DOWN, wallGridVer->Get_Rows() - 9);	// Mur que le joueurs va tirés avec les items
				ev_WakeUp2.Advance(500);
				break;

			case 12:
				for (int c = 0; c < linkGrid->Get_Cols(); c++)	// active une rangée de blockers
				{
					gGrids.Activate_Blocker({ c,3 }, true);
				}
				ev_WakeUp2.Advance(1200);
				break;

			case 13:
				ev_WakeUp2.Advance(0);
				ev_WakeUp2.delay.Start_Timer(10000, 1, true);
				break;

			case 14:
				if (!ItemsOnGrid::size && !BlastModifierQueue::What_Is_Size())
				{
					ConsoleRender::Add_String(_5, Boss_Txt_Crd(_5), gBossClr, 50, true);
					ConsoleRender::Add_String(_6, Boss_Txt_Crd(_6, 1), gBossClr, 50, true);
					ConsoleRender::Add_String(_7, Boss_Txt_Crd(_7, 2), gBossClr, 50, true);
					ConsoleRender::Add_String(_8, Boss_Txt_Crd(_8, 3), gBossClr, TXT_SPD_DR);
					ev_WakeUp2.delay.Stop();
					ev_WakeUp2.Advance(400);
				}
				break;

			case 15:
				Press_R_To_Refresh();
				ConsoleRender::Add_String(_8, Boss_Txt_Crd(_8, 3), gBossClr, 0, true);
				ConsoleRender::Add_String(_9, Boss_Txt_Crd(_9), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(500);
				break;

			case 16:
				ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10, 1), gBossClr, 250);
				ev_WakeUp2.Advance(300);
				break;

			case 17:

				ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11, 2), gBossClr, TXT_SPD_DR);
				ev_WakeUp2.Advance(400);
				break;

			case 18:
				ConsoleRender::Add_String(_9, Boss_Txt_Crd(_9), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_10, Boss_Txt_Crd(_10, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_11, Boss_Txt_Crd(_11, 2), gBossClr, TXT_SPD_ER, true);
				//ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, 400);
				ev_WakeUp2.Advance(600);
				break;


			case 19:
				//ConsoleRender::Add_String(TXT_CONST.DOTDOTDOT, Boss_Txt_Crd(TXT_CONST.DOTDOTDOT, 2), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12), gBossClr, 250);
				ev_WakeUp2.Advance(500);
				break;

			case 20:
				ConsoleRender::Add_String(_13, Boss_Txt_Crd(_13,1), gBossClr, 250);
				Press_R_To_Refresh();
				ev_WakeUp2.Advance(500);
				break;

			case 21:
				ConsoleRender::Add_String(_14, Boss_Txt_Crd(_14,2), gBossClr, 250);
				ev_WakeUp2.Advance(300);
				break;

			case 22:
				ev_WakeUp2.Advance(1000);
				break;

			case 23:
				ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_13, Boss_Txt_Crd(_13, 1), gBossClr, TXT_SPD_ER, true);
				ConsoleRender::Add_String(_14, Boss_Txt_Crd(_14, 2), gBossClr, TXT_SPD_ER, true);
				ev_WakeUp2.Advance(0);
				break;

			case 24:
				// ON NE CANCEL PAS L'EVENT
				break;

			//case 25:
			//	ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12), gBossClr, TXT_SPD_DR);
			//	ev_WakeUp2.Advance(400);
			//	break;

			//case 26:
			//	ConsoleRender::Add_String(_13, Boss_Txt_Crd(_13, 1), gBossClr, TXT_SPD_DR);
			//	ev_WakeUp2.Advance(200);
			//	break;

			//case 27:
			//	ConsoleRender::Add_String(_12, Boss_Txt_Crd(_12), gBossClr, TXT_SPD_ER, true);
			//	ConsoleRender::Add_String(_13, Boss_Txt_Crd(_13, 1), gBossClr, TXT_SPD_ER, true);

			//	ev_WakeUp2.Cancel();
			//	break;


			//	/* Cheat laid ici, branching dialogue de bouette*/
			//case 28:
			//	ev_WakeUp2.Advance(400);
			//	break;

			//case 29:
			//	ev_WakeUp2.Advance(400);
			//	break;

			//case 30:
			//	ev_WakeUp2.Advance(0);
			//	break;
			}

	}
}