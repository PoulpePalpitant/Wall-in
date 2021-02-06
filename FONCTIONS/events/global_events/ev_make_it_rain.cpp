
#include "ev_make_it_rain.h"

#include "../msg_dispatcher.h"
#include "../events.h"
#include "../../UI/console_output/render_list.h"
#include "../../grid/AllGrids.h"
#include "../../console/sweet_cmd_console.h"

static int MAX_STEPS = 5;

static Event ev_MakeItRain(Ev_Make_It_Rain, MAX_STEPS);
DrawerQueue Q_ev_MakeItRain(1550 , MAX_STEPS);		// Queue de 50, avec 5 MAX_STEPS

static Coord xy;	// dollars positions
const int rainSpd = 110000;	// viteese d'apparition des dollars	
static const int fadeSpd = 2300;		// vitesse de dispartition des dollars (linéaire)


void Ev_Make_It_Rain()				 // Affiche un écran qui gratifiant		
{
	if (!ev_MakeItRain.Is_Active())
	{
		ev_MakeItRain.Activate();
		ev_MakeItRain.Start(0);
		ev_MakeItRain.delay.Start_Timer(100000, 1, true);
	}
	else
	{
		while(ev_MakeItRain.delay.Tick())
		for (int i = 0; i < Q_ev_MakeItRain.Get_Total(); i++)
		{
			while (Q_ev_MakeItRain.queue[i].timer.Tick())
			{
				switch (Q_ev_MakeItRain.queue[i].currStep)
				{
				case 1:
					// le xy sera celui du drawer queue
					Q_ev_MakeItRain.queue[i].XY.x = rand() % gConWidth;
					Q_ev_MakeItRain.queue[i].XY.y = rand() % gConHeight;
					if (Q_ev_MakeItRain.queue[i].XY.y <= 3)
						Q_ev_MakeItRain.queue[i].XY.y += 3;
					else
						if (Q_ev_MakeItRain.queue[i].XY.y >= gConHeight - 3)
							Q_ev_MakeItRain.queue[i].XY.y -= 3;

					ConsoleRender::Add_Char(Q_ev_MakeItRain.queue[i].XY, TXT_CONST.CASH, LIGHT_GREEN);
					Q_ev_MakeItRain.Step(i, fadeSpd);
					break;
				case 2:
					ConsoleRender::Add_Char(Q_ev_MakeItRain.queue[i].XY, TXT_CONST.SPACE);
 					Q_ev_MakeItRain.queue[i].XY.y--;
					ConsoleRender::Add_Char(Q_ev_MakeItRain.queue[i].XY, TXT_CONST.CASH, LIGHT_GREEN);
					Q_ev_MakeItRain.Step(i, fadeSpd - fadeSpd / 4);
					break;

				case 3:
					ConsoleRender::Add_Char(Q_ev_MakeItRain.queue[i].XY, TXT_CONST.SPACE);
					Q_ev_MakeItRain.queue[i].XY.y--;
					ConsoleRender::Add_Char(Q_ev_MakeItRain.queue[i].XY, TXT_CONST.CASH, GREEN);
					Q_ev_MakeItRain.Step(i, fadeSpd - fadeSpd / 3);
					break;

				case 4:
					ConsoleRender::Add_Char(Q_ev_MakeItRain.queue[i].XY, TXT_CONST.SPACE);
					Q_ev_MakeItRain.queue[i].XY.y--;
					ConsoleRender::Add_Char(Q_ev_MakeItRain.queue[i].XY, TXT_CONST.CASH, GRAY);
					Q_ev_MakeItRain.Step(i, fadeSpd);
					break;

				case 5:
					ConsoleRender::Add_Char(Q_ev_MakeItRain.queue[i].XY, TXT_CONST.SPACE);
					Q_ev_MakeItRain.Step(i);
					Q_ev_MakeItRain.Remove(i);
					break;

				}

			}
		}
	}
}
