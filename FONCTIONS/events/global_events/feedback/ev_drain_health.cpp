
#include "ev_drain_health.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../UI/console_output/draw_queue.h"
#include "../../../blast/blast_ammo_animator.h"

using namespace DrawBlastAmmo;

static Event ev_DrainHealth(Ev_Drain_Health); // Def //
DrawerQueue Q_ev_DrainHealth(8, 9);		

static unsigned char dr = 179;
static unsigned char er = TXT_CONST.SPACE;

void Ev_Drain_Health()
{
	//static unsigned char dr = TXT_CONST.SPACE_FILL;
	static Coord crd; 
	static int y; 
	static int step;

	if (!ev_DrainHealth.Is_Active())
	{
		ev_DrainHealth.Activate();
		ev_DrainHealth.Start(0);	// On ne tick pas ce timer
	}
	else
	{
			for (int i = 0; i < Q_ev_DrainHealth.Get_Total(); i++)
			{
				while (Q_ev_DrainHealth.queue[i].timer.Tick())
				{

					step = Q_ev_DrainHealth.queue[i].currStep;
					crd = Q_ev_DrainHealth.queue[i].XY;
					y = crd.y;				// ne changera pas

					
					if (step < MAX_BAR_SIZE + 1)
					{
						ConsoleRender::Add_Char({ crd.x,crd.y + step }, er);
						
						if(step < MAX_BAR_SIZE / 2)
							Q_ev_DrainHealth.Step(i, 55000);
						else
							Q_ev_DrainHealth.Step(i, 25000);
					}
					else
						Q_ev_DrainHealth.Remove(i);

					//if(step < MAX_BAR_SIZE + 1)
					//	ConsoleRender::Add_Char({ crd.x,crd.y + step }, dr, LIGHT_RED);
					//else
					//	ConsoleRender::Add_Char({ crd.x,crd.y + step - MAX_BAR_SIZE }, er);

					//if(step > MAX_BAR_SIZE * 2 )
					//	Q_ev_DrainHealth.Remove(i);
					//else
					//	Q_ev_DrainHealth.Step(i, 100000);


					//switch (Q_ev_DrainHealth.queue[i].currStep)
					//{
					//case 1:
					//	ConsoleRender::Add_Char(crd, line);
					//	Q_ev_DrainHealth.Step(i, 100000);
					//	break;
					//case 2:
					//	ConsoleRender::Add_Char({ y,crd.y - 1 }, line);	//																 
					//	ConsoleRender::Add_Char({ y,crd.y + 1 }, line);	//																 
					//	Q_ev_DrainHealth.Step(i, 80000);
					//	break;

					//case 3:
					//	ConsoleRender::Add_Char(crd, tear);			// Modifie le milieu								    			 
					//	Q_ev_DrainHealth.Step(i, 40000);
					//	break;

					//case 4:
					//	ConsoleRender::Add_Char({ y,crd.y - 1 }, TXT_CONST.SPACE);		// efface										
					//	ConsoleRender::Add_Char({ y,crd.y + 1 }, TXT_CONST.SPACE);
					//	ConsoleRender::Add_Char({ y,crd.y - 2 }, line);	// draw										
					//	ConsoleRender::Add_Char({ y,crd.y + 2 }, line);
					//	ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// Modifie le milieu
					//	Q_ev_DrainHealth.Step(i, 25000);
					//	break;

					//case 5:
					//	ConsoleRender::Add_Char({ y,crd.y - 2 }, TXT_CONST.SPACE);	// erase																							
					//	ConsoleRender::Add_Char({ y,crd.y + 2 }, TXT_CONST.SPACE);
					//	ConsoleRender::Add_Char({ y,crd.y - 3 }, line, GRAY); // draw
					//	ConsoleRender::Add_Char({ y,crd.y + 3 }, line, GRAY);
					//	Q_ev_DrainHealth.Step(i, 15000);
					//	break;

					//case 6:
					//	ConsoleRender::Add_Char({ y,crd.y - 3 }, TXT_CONST.SPACE);
					//	ConsoleRender::Add_Char({ y,crd.y + 3 }, TXT_CONST.SPACE);
					//	ConsoleRender::Add_Char({ y,crd.y - 4 }, tear, GRAY);
					//	ConsoleRender::Add_Char({ y,crd.y + 4 }, tear, GRAY);
					//	Q_ev_DrainHealth.Step(i, 10000);
					//	break;

					//case 7:
					//	ConsoleRender::Add_Char({ y,crd.y - 4 }, TXT_CONST.SPACE);
					//	ConsoleRender::Add_Char({ y,crd.y + 4 }, TXT_CONST.SPACE);
					//	Q_ev_DrainHealth.Step(i);
					//	Q_ev_DrainHealth.Remove(i);
					//	break;
					//}
				}
			}
			
			if (!Q_ev_DrainHealth.Get_Total())
				ev_DrainHealth.Cancel();

	}
}

void Add_Ev_Drain_Health()	// Fait une animation de splash quand tu tir sur la bordure
{
	static Coord crd;
	crd = Get_Ori();
	Q_ev_DrainHealth.Add(crd);

	for (int i = 1; i < MAX_BAR_SIZE; i++)
		ConsoleRender::Add_Char({ crd.x,crd.y + i }, dr, LIGHT_RED);

	Ev_Drain_Health();  
}



