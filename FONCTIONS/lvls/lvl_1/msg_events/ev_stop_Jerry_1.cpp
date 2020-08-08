
#include "ev_stop_Jerry_1.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../bots/botmeta.h"
#include "../../../spawns/ev_spawn_Jerry.h"

static Event ev_Dr_StopJerry(Ev_Dr_Stop_Jerry, 3);
static std::string _1 = "- STOP JERRY -"; ;
static std::string _2 = "(Do It   Times)";
static Coord crdCount;		// La coord du numéro à updater

static int deadCount;	// Nombre de Jerry dead

static void Upd_Jerry_Count()
{
	crdCount = Up_Txt_3(_2);
	crdCount.x += 7;
	ConsoleRender::Add_String(std::to_string(jerCount - deadJerrys), crdCount, LIGHT_GREEN, 50);	// Update le nombre
}


void Ev_Dr_Stop_Jerry()			// Le joueur doit arrêter Jerry plusieurs fois
{
	//crd.x = P1.Get_XY().x; crd.y -= 3;
	if (!ev_Dr_StopJerry.Is_Active())
	{
		 deadCount = 0;

		ConsoleRender::Add_String(_1, Up_Txt_1(_1), BRIGHT_WHITE, 50);
		ConsoleRender::Add_String(_2, Up_Txt_3(_2), WHITE, 50);
		ev_Dr_StopJerry.Activate();
		ev_Dr_StopJerry.Start(1500);	// 1000 / 2 = 500.		2 secondes
	}
	else
	{
		while (ev_Dr_StopJerry.delay.Tick())
		{
			switch (ev_Dr_StopJerry.Get_Current_Step())
			{
			case 1:
				Upd_Jerry_Count();
				ev_Dr_StopJerry.Advance(0);	// Delay 
				ev_Dr_StopJerry.delay.Start_Timer(10000, 1, true);
				break;

			case 2:
				// Si 1 Jerry Meurt on réduit le compte et on update le nombre
				if (deadJerrys > deadCount)
				{
					deadCount = deadJerrys;
					Upd_Jerry_Count();		// Update le tit nombre

					if (!jerryTime)
					{
						ev_Dr_StopJerry.Cancel();
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