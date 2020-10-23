
#include "ev_wasd.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"


static Event ev_Dr_Wasd(Ev_Dr_Wasd, 2);
static Event ev_Er_Wasd(Ev_Er_Wasd);
static Coord crd;
static std::string _1 = "M O V E";
static std::string _2 = "[W]";
static std::string _3 = "[A] [S] [D]";
//static std::string _2 = "[W]";
//static std::string _3 = "[A]";
//static std::string _4 = "[S]";
//static std::string _5 = "[D]";


void Ev_Dr_Wasd()			// Accueil Le joueur quand il sort de son r�pit
{
	if (!ev_Dr_Wasd.Is_Active())
	{
		crd = { (Find_Ctr_X((int)std::size(_1)) / 2) / 2, (gConHeight / 2) / 2};
		ev_Dr_Wasd.Activate();
		ev_Dr_Wasd.Start(600);	// 1000 / 2 = 500.		2 secondes
	}
	else
	{
		while (ev_Dr_Wasd.delay.Tick())
			switch (ev_Dr_Wasd.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String(_1, crd, BRIGHT_WHITE, TXT_SPD_DR);
				ev_Dr_Wasd.Advance(1000);	// Delay 
				break;
				
			case 2:
				ConsoleRender::Add_String(_2, { crd.x + 2, crd.y + 2 }, WHITE, TXT_SPD_DR);	// x -3, y + 2
				ConsoleRender::Add_String(_3, { crd.x - 2 ,crd.y + 3 }, WHITE, TXT_SPD_DR);	// x -3, y + 2
				ev_Dr_Wasd.Advance(0);	// finito
				break;
			}
	}
}

void Just_Dr_Wasd()// Draw fast
{
	static Coord crd = { (Find_Ctr_X((int)std::size(_1)) / 2) / 2, (gConHeight / 2) / 2 };
	ConsoleRender::Add_String(_1, crd, BRIGHT_WHITE);
	ConsoleRender::Add_String(_2, { crd.x + 2, crd.y + 2 }, WHITE);	
	ConsoleRender::Add_String(_3, { crd.x - 2 ,crd.y + 3 }, WHITE);	
}

void Just_Er_Wasd()// erase fast
{
	static Coord crd = { (Find_Ctr_X((int)std::size(_1)) / 2) / 2, (gConHeight / 2) / 2 };
	ConsoleRender::Add_String(_1, crd, WHITE, true);
	ConsoleRender::Add_String(_2, { crd.x + 2, crd.y + 2 }, WHITE, true);
	ConsoleRender::Add_String(_3, { crd.x - 2 ,crd.y + 3 }, WHITE, true);
}

void Ev_Er_Wasd()
{
	if (!ev_Er_Wasd.Is_Active())
	{
		ev_Er_Wasd.Activate();
		ev_Er_Wasd.Start(0);
	}
	else
		while (ev_Er_Wasd.delay.Tick())
		{
			ConsoleRender::Add_String(_1, crd, WHITE, 80, true);						// ERASE
			ConsoleRender::Add_String(_2, { crd.x + 2, crd.y + 2 }, WHITE, TXT_SPD_DR, true);
			ConsoleRender::Add_String(_3, { crd.x - 2 ,crd.y + 3 }, WHITE, TXT_SPD_DR, true);
			ev_Er_Wasd.Advance(0);
		}
}