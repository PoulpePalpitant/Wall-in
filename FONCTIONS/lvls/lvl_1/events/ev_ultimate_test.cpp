
#include "ev_ultimate_test.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../bots/botmeta.h"
#include "../../../spawns/ev_spawn_Jerry.h"

Event ev_UltimateTest(Ev_Ultimate_Test, 3);
static std::string _1 = "- STOP EVERYTHING -"; ;
static std::string _2 = "(Or Die Horribly)";
static Coord crdCount;		// La coord du numéro à updater

static int deadCount;	// Nombre de Jerry dead

static void Upd_Jerry_Count()
{
	crdCount = Up_Txt_3(_2);
	crdCount.x += 7;
	
	if(jerCount - deadJerrys == 9)
		ConsoleRender::Add_String("9 ", crdCount, LIGHT_GREEN, 50);	// Lazy interface stuff
	else
		ConsoleRender::Add_String(std::to_string(jerCount - deadJerrys), crdCount, LIGHT_GREEN, 50);	// Update le nombre
}

void Stop_Ev_Dr_Stop_Jerry()	// Stopping the jerrys
{
	ev_UltimateTest.Cancel();
	jerryTime = false;
	deadCount = 0;
}

void Ev_Ultimate_Test()			// Le joueur doit arrêter Jerry plusieurs fois
{
	//crd.x = P1.Get_XY().x; crd.y -= 3;
	if (!ev_UltimateTest.Is_Active())
	{
		 deadCount = 0;

		ConsoleRender::Add_String(_1, Up_Txt_1(_1), BRIGHT_WHITE, 50);
		ConsoleRender::Add_String(_2, Up_Txt_3(_2), WHITE, 50);
		ev_UltimateTest.Activate();
		ev_UltimateTest.Start(1500);	// 1000 / 2 = 500.		2 secondes
	}
	else
	{
		while (ev_UltimateTest.delay.Tick())
		{
			switch (ev_UltimateTest.Get_Current_Step())
			{
			case 1:
				Upd_Jerry_Count();
				ev_UltimateTest.Advance(0);	// Delay 
				ev_UltimateTest.delay.Start_Timer(1000000, 1, true);
				break;

			case 2:
				// Si 1 Jerry Meurt on réduit le compte et on update le nombre
				if (deadJerrys > deadCount)
				{
					deadCount = deadJerrys;
					Upd_Jerry_Count();		// Update le tit nombre

					if (!jerryTime)
					{
						ev_UltimateTest.Cancel();
						Er_Stop_Jerry();	// efface l'objectif
					}
				}
			}
		}
	}
}

void Er_Stop_Jerry()
{
	ConsoleRender::Add_String(_1, Up_Txt_1(_1), WHITE, 50, true);	// ERASE
	ConsoleRender::Add_String(_2, Up_Txt_3(_2), WHITE, 60, true);
}