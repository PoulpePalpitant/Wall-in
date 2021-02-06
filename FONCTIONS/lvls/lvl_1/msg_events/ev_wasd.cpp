
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

void Ev_Dr_Wasd()		
{
	if (!ev_Dr_Wasd.Is_Active())
	{
		crd = { (Find_Ctr_X((int)std::size(_1)) / 2) / 2, (gConHeight / 2) / 2};
		ev_Dr_Wasd.Activate();
		ev_Dr_Wasd.Start(600);	
	}
	else
	{
		while (ev_Dr_Wasd.delay.Tick())
			switch (ev_Dr_Wasd.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String(_1, crd, BRIGHT_WHITE, TXT_SPD_DR);
				ev_Dr_Wasd.Advance(1000);
				break;
				
			case 2:
				ConsoleRender::Add_String(_2, { crd.x + 2, crd.y + 2 }, WHITE, TXT_SPD_DR);
				ConsoleRender::Add_String(_3, { crd.x - 2 ,crd.y + 3 }, WHITE, TXT_SPD_DR);
				ev_Dr_Wasd.Advance(0);	
				break;
			}
	}
}

void Just_Dr_Wasd(bool erase)
{
	static Coord crd = { (Find_Ctr_X((int)std::size(_1)) / 2) / 2, (gConHeight / 2) / 2 };
	ConsoleRender::Add_String(_1, crd, BRIGHT_WHITE,0, erase);
	ConsoleRender::Add_String(_2, { crd.x + 2, crd.y + 2 }, WHITE,0, erase);	
	ConsoleRender::Add_String(_3, { crd.x - 2 ,crd.y + 3 }, WHITE,0, erase);	
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
			Coord crd = { (Find_Ctr_X((int)std::size(_1)) / 2) / 2, (gConHeight / 2) / 2 };
			ConsoleRender::Add_String(_1, crd, WHITE, TXT_SPD_ER, true);						
			ConsoleRender::Add_String(_2, { crd.x + 2, crd.y + 2 }, WHITE, TXT_SPD_ER, true);
			ConsoleRender::Add_String(_3, { crd.x - 2 ,crd.y + 3 }, WHITE, TXT_SPD_ER, true);
			ev_Er_Wasd.Advance(0);
		}
}