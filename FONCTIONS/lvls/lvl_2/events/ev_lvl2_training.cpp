

#include "ev_lvl2_training.h"
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
#include "../../../spawns/ev_spawn_Jerry.h"	// pour spawner jerry
#include "../../../choice/choice_time.h"

#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../lvl_script.h"

// WELCOME TO THE SPECIAL TRAINING ROOMS. "Jerry Was Bored Of Wasting His Time Giving This Training To Every Single Employee That Comes Around". "So He Decided  
// To Make The Process Automated, As He Has Other Things To Do, Like Proving That He Can Be The Best Employee This Company Has Ever Had, By Making Automated Training Rooms"
// "If You manage To Succeed Here, IT IS GUARANTEED, That You Will Somewhat Be Prepared To Not Die During Your Duty.  - Signed: Me. Jerry -

// P.S. Please Leave A Review Before You Exit

// Sorry, "Cap Locks" Was On. I Have Designed This Training To Increase Your Inner Employee Potential. 
// 

static Coord crd;	// Ui
static int line;
static std::string title = { "A Huge Flashing Sign Is In The Middle Of The Room" };
static std::string title_2 = { "You Can't Ignore It. It's Just Too Tempting To Read!" };
static Choice read = { {},"Read It","(I Love Signs)" };
static Choice noRead = { {},"Ignore It", "(I Don't Trust Signs)"};
static Choice stopRead = { {},"Stop Reading It","(It Has Been Done)" };
static Choice tryToIgnore = { {},"Try To Ignore It","(You Can Escape Its Power!)" };
static std::string choiceMade;

static int lineDelay = 0;
static float drawSpeed = 0;
static int yStart = 0;	// on start 16 ligne plus haut
//std::string jeryyMsg_1 = "WELCOME TO MY SPECIAL TRAINING ROOMS";										// I JERRY, decided to make these training rooms to better our employees at the use of our brand new technology
//std::string jeryyMsg_2 = "\"I (JERRRY) Was Bored Of Wasting My Time Giving This Training ";			 // I, JERRY, Designed These Rooms All Night To Train The New Employees
//std::string jeryyMsg_3 = "To Every Single Employee That Comes Around Here.";							// In The Art Of Using The Tools
//std::string jeryyMsg_4 = "So I Decided To Build Automatic Training Rooms";							// That Were Given To Us To Help Us In Our Job
//std::string jeryyMsg_5 = "As I Have Other Things To Do...";				// 
//std::string jeryyMsg_6 = "Like Proving That I Can Be The Best Employee This Company Has Ever Had";	// Like becoming the best at his job
//std::string jeryyMsg_7 = "By Building Automated Training Rooms.";										//providing
//std::string jeryyMsg_8 = "If You Manage To Succeed Here, IT IS GUARANTEED, That";
//std::string jeryyMsg_9 = " You Will Be \"Somewhat\" Prepared To Not Die During Your Duty.\"";
//std::string jeryyMsg_10 = "- Signed: Me. Jerry -";
std::string jeryyMsg_1 = "WELCOME TO MY SPECIAL TRAINING ROOMS";	// 
std::string jeryyMsg_2 = "\"I, JERRY, Designed These Rooms To Train New Employees"; // 
std::string jeryyMsg_3 = "In The Art Of Not Dying";	// 
std::string jeryyMsg_4 = "And Also Using The \"BLOCKER\" and \"BUFFER\" tools.";	// 
std::string jeryyMsg_5 = " "; 
std::string jeryyMsg_6 = " ";
std::string jeryyMsg_7 = "I Also Made This Beautiful Sign Here";	
std::string jeryyMsg_8 = "";
std::string jeryyMsg_9 = "Thank You :)";
std::string jeryyMsg_10 = "- Signed: Me. Jerry -";

static Event ev_Lvl2_Training(Ev_Lvl2_Training, 30);

static void Block_Prison(bool Remove = false)
{
	for (int r = 1; r < 5; r+=2)	// 2 couloirs
	{
		for (int c = 0; c < linkGrid->Get_Cols() - 3; c++)
			gGrids.Activate_Blocker({ c ,r }, Remove);	// 1 couloir de la mort!!!			
	}
	//gGrids.Activate_Blocker({ 0,0 }, 0);	// ferme le corridor
	gGrids.Activate_Blocker({ 0,1 }, 0);	// ferme le corridor
	gGrids.Activate_Blocker({ 0,2 }, 0);	// ferme le corridor
	gGrids.Activate_Blocker({ 0,3 }, 0);	// ferme le corridor
	//gGrids.Activate_Blocker({ 0,4 }, 0);	// ferme le corridor
	gGrids.Activate_Blocker({ linkGrid->Get_Cols() - 3,0 }, 0);	
	gGrids.Activate_Blocker({ linkGrid->Get_Cols() - 3,4 }, 0);

}

static void Refresher()	/// Refresher du stage
{
	if (gRefreshStage || P1.Get_HP() < 1)
	{
		//ItemsOnGrid::Remove_All();	// enlève tout les items spawné
		//ListsOfChainToModify::Annihilate_All_Links();	// Links
		//botList.Destroy_All_Bots();	// Bots
		//P1.Er_Player();
		Clear_Map();
		Press_R_To_Refresh();
		Press_X_To_Proceed(3);
		P1.Set_Position({ linkGrid->Get_Cols() -5, 2 }); P1.Reset_Hp_And_Heart(1);
		P1.Dr_Player();
		Block_Prison(); // Prison de blockers autours du joueur
		ev_Lvl2_Training.Go_To_X_Step(2);
		gRefreshStage = false;
	}
}

void Ev_Lvl2_Training()			// Le joueur apprend comment tirer sur les modifiers
{
	if (!ev_Lvl2_Training.Is_Active())
	{
		Clear_All_Renders();
		Clear_Map();	// hope
		clrscr();
		blastP1.Cancel();			 // Cancel le blast
		P1.Set_Hp(1);

		Erase_Right_Text();	// backup
		ev_Lvl2_Training.Activate();
		ev_Lvl2_Training.Start(1000);	
		MsgQueue::Register(LOCK_PLAYER);
	}
	else
	{
		Refresher();
		while (ev_Lvl2_Training.delay.Tick())
			switch (ev_Lvl2_Training.Get_Current_Step())
			{
			case 1:
				if (Resize_Grids_To_Level(gGrids, gCurrentLevel, gCurrentStage))
				{
					MsgQueue::Register(ENABLE_BLAST);
					MsgQueue::Register(FREE_PLAYER);
					//ev_Lvl2_Training.Go_To_X_Step(8);
					ev_Lvl2_Training.delay.Start_Timer(1000);
					ev_Lvl2_Training.Advance(0);	// 1000 / 2 = 500.		2 secondes
					gRefreshStage = true;	// lazy shortcut pour tout refresh
					clrscr();
				}
				else
					ev_Lvl2_Training.delay.Start_Timer(1000);

				break;

			case 2:
				ConsoleRender::Add_String(GOAL_STOP, Up_Txt_2(GOAL_STOP), BRIGHT_WHITE, TXT_SPD_DR);
				Just_Dr_Map_Borders();
				ev_Lvl2_Training.delay.Stop();
				ev_Lvl2_Training.Advance(1000);	// 1000 / 2 = 500.		2 secondes
				break;

			case 3:
				// Place quelques blockers autours 
				/*ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 1,0 }, 0,1);
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 2,0 }, 0,1);
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 3,0 }, 0,1);*/
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 1,1 }, 0, 1);
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 2,1 }, 0, 1);
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 3,1 }, 0, 1);
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 1,3 }, 0,1);
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 2,3 }, 0,1);
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 3,3 }, 0,1);
				//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 1,4 }, 0, 1);
				//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 2,4 }, 0, 1);
				//ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 3,4 }, 0, 1);
				ItemSpawner::Spawn_This_Item(ItemType::BLOCKER, { linkGrid->Get_Cols() - 2,2 });	// un derrière le joueur
				//ItemSpawner::Spawn_This_Item(ItemType::BUFFER, { linkGrid->Get_Cols() - 4,2 });	// just en face du joueur
				ev_Lvl2_Training.Advance(500);
				break;

			case 4:
				Spawn_A_Jerry(UP, 0, SPWN_DLAY + 10);
				ev_Lvl2_Training.Advance(300);
				break;

			case 5:
				Spawn_A_Jerry(DOWN, 0, SPWN_DLAY + 19);
				Spawn_A_Jerry(UP, 1, SPWN_DLAY   + 19);
				Spawn_A_Jerry(DOWN, 2, SPWN_DLAY + 19);
				Spawn_A_Jerry(UP, 3, SPWN_DLAY   + 19);
				Spawn_A_Jerry(DOWN, 4, SPWN_DLAY + 19);
				Spawn_A_Jerry(UP, 5, SPWN_DLAY   + 19);

				Set_Dr_Map_1();
				ev_Lvl2_Training.Advance(10000);
				break;

			case 6:
				ev_Lvl2_Training.Advance(0);
				ev_Lvl2_Training.delay.Start_Timer(10000,1,true);
				break;

			case 8:
				// Ajuste les coord ici
				noRead.crd.r = read.crd.r = linkGrid->Get_Rows() - 2;
				read.crd.c = ((linkGrid->Get_Cols() - 1) / 2) / 2 ;noRead.crd.c = read.crd.c * 3;

				// Player au centre
				P1.Set_Position({ read.crd.c * 2,read.crd.r });
				P1.Dr_Player();
				Just_Dr_Map_Borders();

				ConsoleRender::Add_String(title, { Find_Ctr_Grid(title), map.Get_Box_Limit(UP) + 2 }, BRIGHT_WHITE, 100); // title
				ChoiceTime::Add_Choice(read.name, read.subname, read.crd);
				ChoiceTime::Add_Choice(noRead.name, noRead.subname, noRead.crd);
				ev_Lvl2_Training.Advance(0);
				ev_Lvl2_Training.delay.Start_Timer(2000, 1, true);	// infinite check here
				break;

			case 9:
				if (!ChoiceTime::Is_Choice_Time())
				{
					ConsoleRender::Add_String(title, { Find_Ctr_Grid(title), map.Get_Box_Limit(UP) + 2 }, BRIGHT_WHITE, 50, true); // title
					ev_Lvl2_Training.delay.Stop();
					ev_Lvl2_Training.Advance(500);
				}
				break;

			case 10:
				choiceMade = ChoiceTime::Get_Choice_Made();

				if(choiceMade == read.name)
					ev_Lvl2_Training.Advance(1000);
				else
				{
					ConsoleRender::Add_String(title_2, { Find_Ctr_Grid(title_2), map.Get_Box_Limit(UP) + 2 }, BRIGHT_WHITE, 50); // title_2
					ev_Lvl2_Training.Advance(1000);
					gRefreshStage = true;
					Refresher();
				}

				break;

				// fuck le message de jerry
				// MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRYS
			case 11:
				//Set_Dr_Map_1();
				line = Up_Txt_1(TXT_CONST.EMPTY).y - 4;
				ConsoleRender::Add_String(jeryyMsg_1, { Up_Txt_1(jeryyMsg_1).x,line - yStart - 1 }, BRIGHT_WHITE, drawSpeed);
				ev_Lvl2_Training.Advance(lineDelay);
				break;

			case 12:
				line++;
				ConsoleRender::Add_String(jeryyMsg_2, { Up_Txt_1(jeryyMsg_2).x,line - yStart}, GRAY, drawSpeed);
				ev_Lvl2_Training.Advance(lineDelay);
				break;

			case 13:
				line++;
				ConsoleRender::Add_String(jeryyMsg_3, { Up_Txt_1(jeryyMsg_3).x,line - yStart }, GRAY, drawSpeed);
				ev_Lvl2_Training.Advance(lineDelay);
				break;

			case 14:
				line++;
				ConsoleRender::Add_String(jeryyMsg_4, { Up_Txt_1(jeryyMsg_4).x,line - yStart }, GRAY, drawSpeed);
				ev_Lvl2_Training.Advance(lineDelay);
				break;

			case 15:
				line++;
				ConsoleRender::Add_String(jeryyMsg_5, { Up_Txt_1(jeryyMsg_5).x,line - yStart }, GRAY, drawSpeed);
				ev_Lvl2_Training.Advance(lineDelay);
				break;

			case 16:
				line++;
				ConsoleRender::Add_String(jeryyMsg_6, { Up_Txt_1(jeryyMsg_6).x,line - yStart }, GRAY, drawSpeed);
				ev_Lvl2_Training.Advance(lineDelay);
				break;

			case 17:
				line++;
				ConsoleRender::Add_String(jeryyMsg_7, { Up_Txt_1(jeryyMsg_7).x,line - yStart }, GRAY, drawSpeed);
				ev_Lvl2_Training.Advance(lineDelay);
				break;

			case 18:
				line++;
				ConsoleRender::Add_String(jeryyMsg_8, { Up_Txt_1(jeryyMsg_8).x,line - yStart }, GRAY, drawSpeed);
				ev_Lvl2_Training.Advance(lineDelay);
				break;

			case 19:
				line++;
				ConsoleRender::Add_String(jeryyMsg_9, { Up_Txt_1(jeryyMsg_9).x,line - yStart }, GRAY, drawSpeed);
				ev_Lvl2_Training.Advance(lineDelay);
				break;

			case 20:
				line++;
				ConsoleRender::Add_String(jeryyMsg_10,{ Up_Txt_1(jeryyMsg_10).x,line - yStart + 1 }, LIGHT_AQUA, drawSpeed);
				ev_Lvl2_Training.Advance(0);
				break;

			case 21:	// final				
				// Ajuste les coord ici
				stopRead.crd.r = noRead.crd.r;
				stopRead.crd.c = ((linkGrid->Get_Cols() - 1) / 2);

				ChoiceTime::Add_Choice(stopRead.name, stopRead.subname, stopRead.crd);
				ev_Lvl2_Training.Advance(0);
				ev_Lvl2_Training.delay.Start_Timer(2000, 1, true);	// infinite check here
				break;

			case 22: // final
				if (!ChoiceTime::Is_Choice_Time())
				{
					ev_Lvl2_Training.Advance(1000);
					clrscr();
					gRefreshStage = true;
					Refresher();
					break;
				}
				// MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRY MESSAGE DE JERRYS

				// EVENT N'EST PAS CANCELLÉ!
			}

	}
}