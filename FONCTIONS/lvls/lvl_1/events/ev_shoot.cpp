

#include "ev_shoot.h"

#include "../../lvl_script.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../grid/AllGrids.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../player/player.h"

static Event ev_AdventureHere(Ev_Learn_To_Shoot, 5);
static GrdCoord dotChase;	// Le player va chase un tit point, ceci sera sa position
static Coord XY;			// À un certain point, il y avoir plusieurs dots, ceci sera leur coord de reférence

void Ev_Learn_To_Shoot()// Trace un chemin vers une fausse porte de sortie
{
	if (!ev_AdventureHere.Is_Active())
	{
		dotChase = { 2, 6 };		// Premier Dot
		
		if (P1.Get_Grd_Coord().c == 2 || P1.Get_Grd_Coord().r == 6)
			dotChase = { 0, 4 };

		ConsoleRender::Add_Char(linkGrid->link[dotChase.c][dotChase.r].Get_XY(), 250, LIGHT_GREEN);
		ev_AdventureHere.Activate();
		ev_AdventureHere.Start(600);
		ev_AdventureHere.delay.Start_Timer(10000, 1, true);	// va checker à l'infinie pour vérifier si le joueur se trouve sur la position

		MsgQueue::Register(FREE_PLAYER);
		MsgQueue::Register(STAGE_ADVANCE);
	}
	else	// doin stuff 
	{
		while (ev_AdventureHere.delay.Tick())
		{
			static int step; step = ev_AdventureHere.Get_Current_Step();

			if (step == 1)
			{
				if (Are_Equal(P1.Get_Grd_Coord(), dotChase))	// Si le player se déplace sur le dot
				{
					XY = linkGrid->link[linkGrid->Get_Cols() - 6][dotChase.r].Get_XY();
					XY.x += DELTA_X;
					ev_AdventureHere.delay.Stop();	// Stop le infinite check
					ev_AdventureHere.Go_To_Next_Step();
					ev_AdventureHere.delay.Start_Timer(7500, 7);	// Stop le infinite check

				}
			}

			switch (step)	// STEP 20 à +
			{
			case 2:
				XY.x += DELTA_X;
				ConsoleRender::Add_Char(XY, 250);
				ev_AdventureHere.Advance(6000, 2);
				break;

			case 3:
				XY.y -= DELTA_Y;
				ConsoleRender::Add_Char(XY, 250);
				ev_AdventureHere.Advance(6000);
				break;

			case 4:
				XY.y -= DELTA_Y;
				ConsoleRender::Add_Char(XY, 219, LIGHT_AQUA);
				ev_AdventureHere.Advance(6000);
				break;

			case 5:					
				XY.y -= DELTA_Y;
				XY.x -= 7;
				ConsoleRender::Add_String("Adventure here", XY, WHITE);
				ev_AdventureHere.Advance(0);
				ev_AdventureHere.delay.Start_Timer(50000, 1, true);	// va checker à l'infinie pour vérifier si le joueur se trouve sur la position
				break;
				// si bump la bordure stop it

			}

		}
	}
}

