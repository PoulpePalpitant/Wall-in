

#include "../../../UI/console_output/render_list.h"
#include "../../../console/sweet_cmd_console.h"
#include "../../../events/events.h"
#include "ev_new_goal.h"
#include "../../../player/player.h"


static Event ev_Dr_NewGoal(Ev_Dr_New_Goal , 2);
static Event ev_Er_NewGoal(Ev_Er_New_Goal);
static Coord crd;
static std::string _1 = "- NEW GOAL -"; ;
static std::string _2 = "Do Something With Your Life";


void Ev_Dr_New_Goal()			// Accueil Le joueur quand il sort de son répit
{
	//crd.x = P1.Get_XY().x; crd.y -= 3;
	if (!ev_Dr_NewGoal.Is_Active())
	{
		crd.y = 3;
		ev_Dr_NewGoal.Activate();
		ev_Dr_NewGoal.Start(300);	// 1000 / 2 = 500.		2 secondes
	}
	else
	{
		while (ev_Dr_NewGoal.delay.Tick())
			switch (ev_Dr_NewGoal.Get_Current_Step())
			{
			case 1:
				ConsoleRender::Add_String(_1, { Find_Ctr_X((int)std::size(_1)),crd.y }, BRIGHT_WHITE, 50);
				ev_Dr_NewGoal.Advance(600);	// Delay 
				break;

			case 2:
				ConsoleRender::Add_String(_2, { Find_Ctr_X((int)std::size(_2)),crd.y + 2 }, WHITE, 80);
				ev_Dr_NewGoal.Advance(0);	// finito
				break;

			}
	}
}
void Ev_Er_New_Goal()
{
	if (!ev_Er_NewGoal.Is_Active())
	{
		crd.y = 3;
		ev_Er_NewGoal.Activate();
		ev_Er_NewGoal.Start(100);
	}
	else
		while (ev_Er_NewGoal.delay.Tick())
		{
			ConsoleRender::Add_String(_1, { Find_Ctr_X((int)std::size(_1)),crd.y }, BRIGHT_WHITE, 50, true);	// ERASE
			ConsoleRender::Add_String(_2, { Find_Ctr_X((int)std::size(_2)),crd.y + 2 }, WHITE, 60, true);
			ev_Er_NewGoal.Advance(0);
		}
}