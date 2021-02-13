
#include "ev_stop_Jerry_1.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../bots/botmeta.h"
#include "../../../spawns/ev_spawn_Jerry.h"

Event ev_Dr_StopJerry(Ev_Dr_Stop_Jerry, 3);
static std::string _1 = "- STOP THEM -"; ;
static std::string _2 = "Remaining : ";
static Coord crdCount;		// La coord du numéro à updater

static int deadCount;	// Nombre de Jerry dead

void Upd_Jerry_Count()
{
	crdCount = Up_Txt_3(_2);
	crdCount.x += 12;
	
	if(jerCount - deadJerrys == 9)
		ConsoleRender::Add_String("9 ", crdCount, LIGHT_GREEN, TXT_SPD_FAST);	// Lazy interface stuff
	else
		if (jerCount - deadJerrys == 99)
			ConsoleRender::Add_String("99 ", crdCount, LIGHT_GREEN, TXT_SPD_FAST);	// Lazy interface stuff
		else
			ConsoleRender::Add_String(std::to_string(jerCount - deadJerrys), crdCount, LIGHT_GREEN, TXT_SPD_FAST);	// Update le nombre
}

void Stop_Ev_Dr_Stop_Jerry()	// Stopping the jerrys
{
	ev_Dr_StopJerry.Cancel();
	jerryTime = false;
	deadCount = 0;
}

void Ev_Dr_Stop_Jerry()			// Le joueur doit arrêter Jerry plusieurs fois
{
	if (!ev_Dr_StopJerry.Is_Active())
	{
		 deadCount = 0;

		ConsoleRender::Add_String(_1, Up_Txt_1(_1), BRIGHT_WHITE, TXT_SPD_FAST);
		ConsoleRender::Add_String(_2, Up_Txt_3(_2), WHITE, TXT_SPD_FAST);
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
				ev_Dr_StopJerry.delay.Start_Timer(1000000, 1, true);
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
	ConsoleRender::Add_String(_1, Up_Txt_1(_1), WHITE, TXT_SPD_FAST, true);	// ERASE
	ConsoleRender::Add_String(_2 + "   ", Up_Txt_3(_2 + "   "), WHITE, TXT_SPD_FAST, true);
}