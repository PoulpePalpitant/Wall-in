
#include "ev_ultimate_test.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../bots/botmeta.h"
#include "../../../spawns/ev_spawn_Jerry.h"
#include "../../../grid/AllGrids.h"
#include "../../../bots/botlist.h"
#include "../../../time/bot_move_cycle.h"
#include "../../../events/global_events/ev_update_heart.h"
#include "../msg_events/ev_stop_Jerry_1.h"
#include "../../../events/global_events/ev_countdown.h"

Event ev_UltimateTest(Ev_Ultimate_Test, 8);
static std::string _1 = "- STOP EVERYTHING -"; ;
static std::string _2 = "(Or Die...";
static std::string _3 = "Yeah For Real)";
static std::string _4 = "(Seconds Before Arrival:    )";
static bool success = false;

static int spw;
static int warnings = 125;/*120*/
const int totalSpw = 80;

bool Ultimate_Test_Time()
{
	return ev_UltimateTest.Is_Active();
}

void Cancel_Ultimate_Test()
{
	ev_UltimateTest.Cancel();
}
bool Ultimate_Test_Succeed()
{
	if (success)
	{
		success = false;
		return true;
	}

	return false;
}

void Ev_Ultimate_Test()			// Le joueur doit arrêter Jerry plusieurs fois
{
	//crd.x = P1.Get_XY().x; crd.y -= 3;
	if (!ev_UltimateTest.Is_Active())
	{
		success = false;
		spw = 3;
		//Set_Jerry_Time((spawnGrid->Get_MaxSpwnCrdY() - 1) * 2);		// Jerry spawn sur tout les spawn verticaux
		Set_Jerry_Time(0);		// Jerry spawn sur tout les spawn verticaux
		Ev_Dr_Stop_Jerry();
		ev_UltimateTest.Activate();
		//ev_UltimateTest.Start(1500);	
		ev_UltimateTest.Start(3000, totalSpw / 4);

	}
	else
	{
		while (ev_UltimateTest.delay.Tick())
		{
			switch (ev_UltimateTest.Get_Current_Step())
			{
			case 1:
				//for (int border = 1; border < 4; border += 2)	// deux bordures verticales			
				//	for (int spw = 0; spw < spawnGrid->Get_MaxSpwnCrdY(); spw++)					
				//		Spawn_A_Jerry((Direction)border, spw, 100);				

				//ev_UltimateTest.Advance(45);	
				//break;

				// v2
				//for (int i = 0; i < 5; i++)
				//{
				//	Spawn_A_Jerry(LEFT, spw, 120);
				//	Spawn_A_Jerry(RIGHT, spw, 120);

				//	if(spw == 3 || spw == 7)
				//		spw++;
				//	spw++;
				//}
				//spw = 3;	// reset

				// v3
				Spawn_A_Jerry(LEFT, 6, warnings);	Spawn_A_Jerry(LEFT, 8, warnings);
				Spawn_A_Jerry(RIGHT, 6, warnings);	Spawn_A_Jerry(RIGHT, 8, warnings);
				Add_Jerrys_To_Stop(4);
				Upd_Jerry_Count();
				ev_UltimateTest.Advance(4000, 5);
				break;

			case 2:
				Add_Jerrys_To_Stop(4);
				Upd_Jerry_Count();			
				ev_UltimateTest.Advance(55);
				break;

			case 3:
				Er_Stop_Jerry();
				Stop_Ev_Dr_Stop_Jerry();
				ev_UltimateTest.Advance(950);
				break;

			case 4:
				ConsoleRender::Add_String(_1, Up_Txt_1(_1), BRIGHT_WHITE, 50);	// stop everything or die
				ConsoleRender::Add_String(_2, { Find_Ctr_X((int)std::size(_2 + _3)),5 }, WHITE, 250);
				ev_UltimateTest.Advance(220);
				break;

			case 5:
				ConsoleRender::Add_String(_3, {(gConWidth / 2 ) - 1, 5 }, WHITE, 250);
				Just_Dr_Heart(3);
				ev_UltimateTest.Advance(320);
				break;

			case 6:
				ConsoleRender::Add_String(_4, { Find_Ctr_X((int)std::size(_4)), 4 }, WHITE, 80);
				Set_CountDown(botList.bot[0].Get_Warnings() / 2, { Find_Ctr_X((int)std::size(_4)) + 25 , 4 }, false);	// /2 c'est pour la vitesse des bots, le count down se fait par secondes à 1000 frames
				Ev_CountDown();
				ev_UltimateTest.Advance(0);
				ev_UltimateTest.delay.Start_Timer(100000, 1, true);
				break;

			case 7:
				if (botList.bot[0].Get_Steps_Count() >= 1)	// Dès que les bot font un step, on réduit leur vitesse!
				{
					Temporary_Bot_Speed_Switch(1400, false);	//false = Conserve la vitesse d'origine
					ev_UltimateTest.delay.Stop();
					ev_UltimateTest.Advance(0);
					ev_UltimateTest.delay.Start_Timer(100000, 1, true);
				}
				break;

			case 8:
				if (!gAllBotMeta.alive)
				{
					if (P1.Get_HP())
						success = true;

					ConsoleRender::Add_String(_1, Up_Txt_1(_1), WHITE, 50, true);	// ERASE
					ConsoleRender::Add_String(_2, { Find_Ctr_X((int)std::size(_2 + _3)),5 }, WHITE, 60, true);
					ConsoleRender::Add_String(_3, { (gConWidth / 2) - 1, 5 }, WHITE, 50, true);
					ConsoleRender::Add_String(_4, { Find_Ctr_X((int)std::size(_4)), 4 }, WHITE, 50, true);
					jerryTime = false;
					ev_UltimateTest.delay.Stop();
					ev_UltimateTest.Advance(0);
				}
			}
		}
	}
}

