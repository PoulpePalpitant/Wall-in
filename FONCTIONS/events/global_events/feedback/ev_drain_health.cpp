
#include "ev_drain_health.h"

#include "../../../UI/map.h"
#include "../../../blast/blast.h"
#include "../../../UI/console_output/render_list.h"
#include "../../events.h"
#include "../../../UI/console_output/draw_queue.h"
#include "../../../blast/blast_ammo_animator.h"
#include "../../../player/player.h"

using namespace DrawBlastAmmo;

static Event ev_DrainHealthWarning(Ev_Drain_Health_Warning); // Def //
static Event ev_HpDrainMsg(Ev_Hp_Drain_Msg,2); // Def //
DrawerQueue Q_ev_DrainHealthWarning(8, 9);		

static unsigned char dr = 179;
static unsigned char er = TXT_CONST.SPACE;




static std::string drained = "- LOW HP -";

void Ev_Drain_Health_Warning()
{
	//static unsigned char dr = TXT_CONST.SPACE_FILL;
	static Coord crd; 
	static int y; 
	static int step;
	
	if (!ev_DrainHealthWarning.Is_Active())
	{
		// Re do it! But with another color probably
		if (ev_HpDrainMsg.Is_Active()) {
			ev_HpDrainMsg.Cancel();
		}

		ev_DrainHealthWarning.Activate();
		ev_DrainHealthWarning.Start(0);	// On ne tick pas ce timer
	}
	else
	{
			for (int i = 0; i < Q_ev_DrainHealthWarning.Get_Total(); i++)
			{
				while (Q_ev_DrainHealthWarning.queue[i].timer.Tick())
				{

					step = Q_ev_DrainHealthWarning.queue[i].currStep;
					crd = Q_ev_DrainHealthWarning.queue[i].XY;
					y = crd.y;				// ne changera pas

					
					if (step < MAX_BAR_SIZE + 1)
					{
						ConsoleRender::Add_Char({ crd.x,crd.y + step }, er);
						
						if(step < MAX_BAR_SIZE / 2)
							Q_ev_DrainHealthWarning.Step(i, 55000);
						else
							Q_ev_DrainHealthWarning.Step(i, 25000);
					}
					else
					{

						Q_ev_DrainHealthWarning.Remove(i);
					}
				}
			}
			
			if (!Q_ev_DrainHealthWarning.Get_Total())
				ev_DrainHealthWarning.Cancel();

	}
}

void Add_Ev_Drain_Health()	
{
	static Coord crd;
	crd = Get_Ori();

	// Je veux juste une animation de ça à la fois
	if (ev_DrainHealthWarning.Is_Active())
	{
		ev_DrainHealthWarning.Cancel();
		Q_ev_DrainHealthWarning.Remove(0);
		Stop_Ev_Hp_Drain_Msg();
	}

	Q_ev_DrainHealthWarning.Add(crd);

	for (int i = 1; i < MAX_BAR_SIZE; i++)
		ConsoleRender::Add_Char({ crd.x,crd.y + i }, dr, LIGHT_RED);

	Ev_Drain_Health_Warning();  
}

void Ev_Hp_Drain_Msg()
{
	static Colors clr;
	static int y = Heart_Txt_Crd_Left("").y;

	if (!ev_HpDrainMsg.Is_Active())
	{
		if (P1.Get_HP() == 2)
			clr = YELLOW;
		else
			if (P1.Get_HP() == 1)
				clr = LIGHT_RED;
			else
				clr = GREEN;

		ConsoleRender::Add_String(drained, { Heart_Txt_Crd_Left(drained).x + 14, y }, clr);
		ConsoleRender::Add_String(drained, {Heart_Txt_Crd_Right(drained).x - 14, y}, clr);

		ev_HpDrainMsg.Activate();
		ev_HpDrainMsg.Start(700);
	}
	else
		while (ev_HpDrainMsg.delay.Tick())
		{

			ConsoleRender::Add_String(drained, { Heart_Txt_Crd_Left(drained).x + 14,  y }, clr ,0,1);
			ConsoleRender::Add_String(drained, { Heart_Txt_Crd_Right(drained).x - 14, y }, clr,0,1);
			ev_HpDrainMsg.Cancel();
		}
}
void Stop_Ev_Hp_Drain_Msg()		// C'était pas assé clair finalement
{
	static int y = Heart_Txt_Crd_Left("").y;

	ev_HpDrainMsg.Cancel();
	ConsoleRender::Add_String(drained, { Heart_Txt_Crd_Left(drained).x + 14, y }, WHITE, 0, 1);
	ConsoleRender::Add_String(drained, { Heart_Txt_Crd_Right(drained).x - 14,y }, WHITE, 0, 1);
}