

#include "ev_learn_border_limit.h"

#include "../../lvl_script.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../grid/AllGrids.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../player/player.h"
#include "../../../events/global_events/feedback/ev_draw_map.h"
#include "../../../player/player.h"
#include "../../../events/global_events/ev_update_heart.h"
#include "ev_bot_tutorial2.h"

#include "../msg_events/ev_wasd.h"

static Event ev_LearnBorderLimit(Ev_Learn_Border_Limit, 100);
static GrdCoord dotChase;	// Le player va chase un tit point, ceci sera sa position
static Coord XY;			// À un certain point, il y avoir plusieurs dots, ceci sera leur coord de reférence

static std::string limit = " <- Border Limits";

void Ev_Learn_Border_Limit()// Trace un chemin vers une fausse porte de sortie
{
	if (!ev_LearnBorderLimit.Is_Active())
	{
		ev_LearnBorderLimit.Activate();
		ev_LearnBorderLimit.Start(150);
	}
	else	
	{
		while (ev_LearnBorderLimit.delay.Tick())
		{
			static int step; step = ev_LearnBorderLimit.Get_Current_Step();

			switch (step)	// STEP 20 à +
			{
			case 1:
				MsgQueue::Register(FREE_PLAYER);

				dotChase = { 2, 6 };		// Premier Dot
				if (P1.Get_Grd_Coord().c == 2 || P1.Get_Grd_Coord().r == 6)
					dotChase = { 0, 4 };

				ConsoleRender::Add_Char(linkGrid->link[dotChase.c][dotChase.r].Get_XY(), '?', LIGHT_GREEN);
				ev_LearnBorderLimit.Advance(0);
				ev_LearnBorderLimit.delay.Start_Timer(10000, 1, true);	// va checker à l'infinie pour vérifier si le joueur se trouve sur la position
				break;

			case 2:
				if (Are_Equal(P1.Get_Grd_Coord(), dotChase))	// Si le player se déplace sur le dot
				{
					Draw_Tuto_Progression(1);


					XY = linkGrid->link[linkGrid->Get_Cols() - 6][dotChase.r].Get_XY();
					XY.x += DELTA_X;
					ev_LearnBorderLimit.delay.Stop();	// Stop le infinite check
					ev_LearnBorderLimit.Go_To_Next_Step();
					ev_LearnBorderLimit.delay.Start_Timer(7500, 7);	// Stop le infinite check
				}
				break;

			case 3:
				XY.x += DELTA_X;
				ConsoleRender::Add_Char(XY, 250);
				ev_LearnBorderLimit.Advance(6000, 2);
				break;

			case 4:
				XY.y -= DELTA_Y;
				ConsoleRender::Add_Char(XY, 250);
				ev_LearnBorderLimit.Advance(6000);
				break;

			case 5:
				XY.y -= DELTA_Y;
				ConsoleRender::Add_Char(XY, 250);
				ev_LearnBorderLimit.Advance(6000);
				break;

			case 6:					
				ConsoleRender::Add_Char(XY, '?', LIGHT_GREEN);

				ev_LearnBorderLimit.Advance(0);
				ev_LearnBorderLimit.delay.Start_Timer(50000, 1, true);	// va checker à l'infinie pour vérifier si le joueur se trouve sur la position
				break;

			case 7:
				if (P1.Get_Grd_Coord().c == linkGrid->Get_Cols() - 1)
				{
					clrscr();
					Just_Dr_Map_Borders();
					Just_Dr_Heart();
					Just_Dr_Wasd();
					P1.Dr_Player();

					Draw_Tuto_Progression(1);

					ev_LearnBorderLimit.delay.Stop();	// Stop le infinite check
					ev_LearnBorderLimit.Go_To_Next_Step();
					ev_LearnBorderLimit.delay.Start_Timer(500);	// va checker à l'infinie pour vérifier si le joueur se trouve sur la position
				}
				break;

			case 8:
				ConsoleRender::Add_String(limit, { XY.x - 10, XY.y }, WHITE, TXT_SPD_DR);
				ev_LearnBorderLimit.Advance(300);
				break;

			case 9:
				ConsoleRender::Add_String(limit, { XY.x - 10, XY.y }, WHITE, TXT_SPD_ER, 1);
				Ev_Bot_Tutorial2();

				ev_LearnBorderLimit.Cancel();
				break;
			}

		}
	}
}

