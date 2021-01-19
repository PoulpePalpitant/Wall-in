
#include "ev_tp_animation.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../UI/console_output/draw_queue.h"
#include "../../../player/player.h"


static Event ev_TeleportAnimation(Ev_Teleport_Animation); // Def //
DrawerQueue Q_ev_TeleportAnimation(8, 9);

void Ev_Teleport_Animation()
{
	static Coord crd; 
	static int X,Y; 

	if (!ev_TeleportAnimation.Is_Active())
	{
		ev_TeleportAnimation.Activate();
		ev_TeleportAnimation.Start(0);	// On ne tick pas ce timer
	}
	else
	{
			for (int i = 0; i < Q_ev_TeleportAnimation.Get_Total(); i++)
			{
				while (Q_ev_TeleportAnimation.queue[i].timer.Tick())
				{

					crd = Q_ev_TeleportAnimation.queue[i].XY;
					X = crd.x;				
					Y = crd.y;

					switch (Q_ev_TeleportAnimation.queue[i].currStep)
					{
					case 1:
						ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', GRAY);
						ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/', GRAY);
						ConsoleRender::Add_Char({ X - 1,Y + 1 }, '/', GRAY);
						ConsoleRender::Add_Char({ X - 1,Y - 1 }, '\\', GRAY);
						Q_ev_TeleportAnimation.Step(i, 100000);
						break;

					case 2:
						ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', LIGHT_GREEN);
						ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/',  LIGHT_GREEN);
						ConsoleRender::Add_Char({ X - 1,Y + 1 }, '/',  LIGHT_GREEN);
						ConsoleRender::Add_Char({ X - 1,Y - 1 }, '\\', LIGHT_GREEN);
						Q_ev_TeleportAnimation.Step(i, 80000);
						break;

					case 3:
						ConsoleRender::Add_Char({ X + 1,Y + 1 },TXT_CONST.SPACE, LIGHT_GREEN);
						ConsoleRender::Add_Char({ X + 1,Y - 1 },TXT_CONST.SPACE, LIGHT_GREEN);
						ConsoleRender::Add_Char({ X - 1,Y + 1 },TXT_CONST.SPACE, LIGHT_GREEN);
						ConsoleRender::Add_Char({ X - 1,Y - 1 },TXT_CONST.SPACE, LIGHT_GREEN);
						ConsoleRender::Add_Char({ X + 2,Y + 2 }, '\\',GREEN);
						ConsoleRender::Add_Char({ X + 2,Y - 2 }, '/', GREEN);
						ConsoleRender::Add_Char({ X - 2,Y + 2 }, '/', GREEN);
						ConsoleRender::Add_Char({ X - 2,Y - 2 }, '\\',GREEN);
						Q_ev_TeleportAnimation.Step(i, 40000);
						break;

					case 4:
						ConsoleRender::Add_Char({ X + 2,Y + 2 }, '\\', LIGHT_GREEN);
						ConsoleRender::Add_Char({ X + 2,Y - 2 }, '/',  LIGHT_GREEN);
						ConsoleRender::Add_Char({ X - 2,Y + 2 }, '/',  LIGHT_GREEN);
						ConsoleRender::Add_Char({ X - 2,Y - 2 }, '\\', LIGHT_GREEN);
						Q_ev_TeleportAnimation.Step(i, 25000);
						break;

					case 5:
						ConsoleRender::Add_Char({ X + 2,Y + 2 },TXT_CONST.DOT,LIGHT_GREEN);
						ConsoleRender::Add_Char({ X + 2,Y - 2 },TXT_CONST.DOT,LIGHT_GREEN);
						ConsoleRender::Add_Char({ X - 2,Y + 2 },TXT_CONST.DOT,LIGHT_GREEN);
						ConsoleRender::Add_Char({ X - 2,Y - 2 },TXT_CONST.DOT,LIGHT_GREEN);
						Q_ev_TeleportAnimation.Step(i, 15000);
						break;

					case 6:
						ConsoleRender::Add_Char({ X + 2,Y + 2 }, TXT_CONST.DOT, GRAY);
						ConsoleRender::Add_Char({ X + 2,Y - 2 }, TXT_CONST.DOT, GRAY);
						ConsoleRender::Add_Char({ X - 2,Y + 2 }, TXT_CONST.DOT, GRAY);
						ConsoleRender::Add_Char({ X - 2,Y - 2 }, TXT_CONST.DOT, GRAY);
						Q_ev_TeleportAnimation.Step(i, 10000);
						break;

					case 7:
						ConsoleRender::Add_Char({ X + 2,Y + 2 }, TXT_CONST.SPACE, GRAY);
						ConsoleRender::Add_Char({ X + 2,Y - 2 }, TXT_CONST.SPACE, GRAY);
						ConsoleRender::Add_Char({ X - 2,Y + 2 }, TXT_CONST.SPACE, GRAY);
						ConsoleRender::Add_Char({ X - 2,Y - 2 }, TXT_CONST.SPACE, GRAY);
						Q_ev_TeleportAnimation.Step(i);
						Q_ev_TeleportAnimation.Remove(i);
						break;
					}
				}
			}
			
			if (!Q_ev_TeleportAnimation.Get_Total())
				ev_TeleportAnimation.Cancel();

	}
}

void Add_Tp_Animation()		// Fait une animation quand le joueur se Tp
{
	GrdCoord tpCoord = P1.Get_Teleporter().Get_Coord();

	Q_ev_TeleportAnimation.Add(linkGrid->link[tpCoord.c][tpCoord.r].Get_XY());
	Ev_Teleport_Animation();
}

