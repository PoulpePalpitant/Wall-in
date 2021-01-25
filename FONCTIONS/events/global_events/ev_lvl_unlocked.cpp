#include "ev_lvl_unlocked.h"

#include "../../UI/map.h"
#include "../../UI/console_output/render_list.h"
#include "../events.h"
#include "../msg_dispatcher.h"
#include "../../lvls/lvl_script.h"
#include "../../inputs/action_input.h"
#include "clear_all_states.h"
#include "../../time/timerOP.h"
#include "../../events/global_events/ev_back_to_menu.h"
#include "../../lvls/lvl_script.h"

static Event ev_LvlUnlocked(Ev_Lvl_Unlocked, 10);


static std::string msg = "- NEW LEVEL UNLOCKED -";
static std::string msg2 = "- FINAL LEVEL UNLOCKED -";
static std::string txt;

static Coord crd;
static int numDist = 8;
static const int spd = 5000;


void Ev_Lvl_Unlocked()
{
	static int X, Y;

	if (!ev_LvlUnlocked.Is_Active())
	{
		crd.y = 40;
		crd.x = Find_Ctr_X(1 + (1 + numDist * gLastLvlUnlocked)) - 4;
		crd.x += (numDist + 1) * gLastLvlUnlocked - 1;

		if (gLastLvlUnlocked < 3)
			txt = msg;
		else
			txt = msg2;

		ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
		MsgQueue::Unregister_All();	
		Go_Back_To_Menu();

		ev_LvlUnlocked.Activate();
		ev_LvlUnlocked.Start(1000);
	}
	else
		while (ev_LvlUnlocked.delay.Tick())
		{
			X = crd.x;
			Y = crd.y;

			switch (ev_LvlUnlocked.Get_Current_Step())
			{
			case 0:
				ConsoleRender::Add_String(std::to_string(gLastLvlUnlocked), { X,Y }, GRAY);
				ConsoleRender::Add_Char({ X + 2,Y + 2 }, 250, GRAY);
				ConsoleRender::Add_Char({ X + 2,Y - 2 }, 250, GRAY);
				ConsoleRender::Add_Char({ X - 2,Y + 2 }, 250, GRAY);
				ConsoleRender::Add_Char({ X - 2,Y - 2 }, 250, GRAY);
				ev_LvlUnlocked.Advance(spd);
				break;

			case 1:
				ConsoleRender::Add_Char({ X + 2,Y + 2 }, '\\', WHITE);
				ConsoleRender::Add_Char({ X + 2,Y - 2 }, '/', WHITE);
				ConsoleRender::Add_Char({ X - 2,Y + 2 }, '/', WHITE);
				ConsoleRender::Add_Char({ X - 2,Y - 2 }, '\\', WHITE);
				ConsoleRender::Add_Char({ X + 1,Y + 1 }, 250, GRAY);
				ConsoleRender::Add_Char({ X + 1,Y - 1 }, 250, GRAY);
				ConsoleRender::Add_Char({ X - 1,Y + 1 }, 250, GRAY);
				ConsoleRender::Add_Char({ X - 1,Y - 1 }, 250, GRAY);
				ev_LvlUnlocked.Advance(spd);
				break;

			case 2:
				ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', GRAY);
				ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/', GRAY);
				ConsoleRender::Add_Char({ X - 1,Y + 1 }, '/', GRAY);
				ConsoleRender::Add_Char({ X - 1,Y - 1 }, '\\', GRAY);
				ConsoleRender::Add_Char({ X + 2,Y + 2 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X + 2,Y - 2 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X - 2,Y + 2 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X - 2,Y - 2 }, TXT_CONST.SPACE, GRAY);
				ev_LvlUnlocked.Advance(spd + 2000);
				break;

			case 3:
				ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', WHITE);
				ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/', WHITE);
				ConsoleRender::Add_Char({ X - 1,Y + 1 }, '/', WHITE);
				ConsoleRender::Add_Char({ X - 1,Y - 1 }, '\\', WHITE);
				ev_LvlUnlocked.Advance(spd + 2000);
				break;

			case 4:
				ConsoleRender::Add_Char({ X,Y }, 250, GRAY);
				ConsoleRender::Add_Char({ X + 1,Y + 1 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X + 1,Y - 1 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X - 1,Y + 1 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X - 1,Y - 1 }, TXT_CONST.SPACE, GRAY);
				ev_LvlUnlocked.Advance(spd);
				break;

			case 5:
				ConsoleRender::Add_Char({ X,Y }, '-', WHITE);
				ev_LvlUnlocked.Advance(spd);
				break;

			case 6:
				ConsoleRender::Add_String(std::to_string(gLastLvlUnlocked), { X,Y }, GREEN);
				ConsoleRender::Add_Char({ X - 2,Y }, 250, GRAY);
				ConsoleRender::Add_Char({ X + 2,Y }, 250, GRAY);
				ConsoleRender::Add_Char({ X - 1,Y }, '-', WHITE);
				ConsoleRender::Add_Char({ X + 1,Y }, '-', WHITE);
				ev_LvlUnlocked.Advance(spd);
				break;

			case 7:
				ConsoleRender::Add_Char({ X - 1,Y }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ X + 1,Y }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ X - 2,Y }, '-', GRAY);
				ConsoleRender::Add_Char({ X + 2,Y }, '-', GRAY);
				ev_LvlUnlocked.Advance(spd);
				break;

			case 8:
				ConsoleRender::Add_String(std::to_string(gLastLvlUnlocked), { X,Y }, LIGHT_GREEN);
				ConsoleRender::Add_Char({ X - 2,Y }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ X + 2,Y }, TXT_CONST.SPACE);
				ev_LvlUnlocked.Advance(spd);
				
			case 9:
				ConsoleRender::Add_String(txt, {crd.x - Half_String(txt), crd.y - 3 }, LIGHT_YELLOW, TXT_SPD_DR);
				gLastLvlUnlocked = 0;
				ev_LvlUnlocked.Cancel();
			}
		}
}