
#include "ev_arr_keys.h"

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"


static Event ev_Dr_ArrKeys(Ev_Dr_Arr_Keys, 2);
static Event ev_Er_ArrKeys(Ev_Er_Arr_Keys);
static Coord crd;
static std::string _1 = "S H O O T";
static std::string _2 = "[^]";
static std::string _3 = "[<] [V] [>]";
static std::string _4 = "(Arrows on Keyboard)";

void Ev_Dr_Arr_Keys()			// Montre les touches clavier pour tirer
{
	if (!ev_Dr_ArrKeys.Is_Active())
	{
		MsgQueue::Register(FREE_PLAYER);

		crd = { (Find_Ctr_X((int)std::size(_1)) / 2) / 2, (gConHeight / 2)  };
		ev_Dr_ArrKeys.Activate();
		ev_Dr_ArrKeys.Start(600/*600*/);	// 1000 / 2 = 500.		2 secondes
	}
	else
	{
		while (ev_Dr_ArrKeys.delay.Tick())
			switch (ev_Dr_ArrKeys.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String(_1, crd, BRIGHT_WHITE, 80);
				ev_Dr_ArrKeys.Advance(1000);	// Delay 
				break;
				
			case 2:
				ConsoleRender::Add_String(_2, { crd.x + 3, crd.y + 2 }, WHITE, 50);	// x -3, y + 2
				ConsoleRender::Add_String(_3, { crd.x - 1 ,crd.y + 3 }, WHITE, 50);	// x -3, y + 2
				ConsoleRender::Add_String(_4, { crd.x - 6 ,crd.y + 5 }, GRAY, 50);	// x -3, y + 2
				
				MsgQueue::Register(ACTIVATE_BLAST);
				ev_Dr_ArrKeys.Advance(0);	// finito
				break;
			}
	}
}

void Ev_Er_Arr_Keys()
{
	if (!ev_Er_ArrKeys.Is_Active())
	{
		ev_Er_ArrKeys.Activate();
		ev_Er_ArrKeys.Start(0);
	}
	else
		while (ev_Er_ArrKeys.delay.Tick())
		{
			ConsoleRender::Add_String(_1, crd, WHITE, 80, true);						// ERASE
			ConsoleRender::Add_String(_2, { crd.x + 2, crd.y + 2 }, WHITE, 50, true);	
			ConsoleRender::Add_String(_3, { crd.x - 2 ,crd.y + 3 }, WHITE, 30, true);
			ev_Er_ArrKeys.Advance(0);
		}
}