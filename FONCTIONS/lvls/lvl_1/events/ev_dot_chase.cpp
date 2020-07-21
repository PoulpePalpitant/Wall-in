

#include "ev_dot_chase.h"

#include "../../lvl_script.h"
#include "../../../events/events.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../grid/AllGrids.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../player/player.h"
#include "../../../events/global_events/ev_update_heart.h"

static Event ev_DotChaseAdventure_1(Ev_Dot_Chase_Adventure_1, 29);
static GrdCoord dotChase;	// Le player va chase un tit point, ceci sera sa position
static Coord XY;			// Pour tout les XY
static std::string smthing = "Something";
static std::string chasing = "You do enjoy wandering around a lot. Chasing uncatchable things. Thats, ok. If that's want you want to do with your time left. It's all gonna be worth it.";

void Ev_Dot_Chase_Adventure_1()// Trace un chemin vers une fausse porte de sortie
{
	if (!ev_DotChaseAdventure_1.Is_Active())
	{
		dotChase = { 2, 9 };		// Premier Dot
		XY = linkGrid->link[dotChase.c][dotChase.r].Get_XY();
		ConsoleRender::Add_Char(XY, 250);
		ConsoleRender::Add_String(TXT_CONST.R_ARROW, { XY.x - 3, XY.y }, WHITE, 100);	// arorw

		//ConsoleRender::Add_String(smthing, { XY.x - ((int)smthing.size() / 2),XY.y - 2 }, WHITE, 50);	// jeu de mot poche

		ev_DotChaseAdventure_1.Activate();
		ev_DotChaseAdventure_1.Start(600);
		ev_DotChaseAdventure_1.delay.Start_Timer(50000, 1, true);	// va checker à l'infinie pour vérifier si le joueur se trouve sur la position
	}
	else	// doin stuff 
	{
		while (ev_DotChaseAdventure_1.delay.Tick())
		{
			static int step; step = ev_DotChaseAdventure_1.Get_Current_Step();

			if (Are_Equal(P1.Get_Grd_Coord(), dotChase))	// Si le player se déplace sur le dot
			{
				switch (step)	// STEP 1 à 20 -> On troll le joueur en faisant déplacer un tit point
				{
				case 1:
					ConsoleRender::Add_String(TXT_CONST.R_ARROW, { XY.x - 3, XY.y }, LIGHT_GREEN, 100, true);	// arorw
					//ConsoleRender::Add_String(smthing, { XY.x - ((int)smthing.size() / 2),XY.y - 2 }, WHITE, 80, true); // efface le jeu de mot poche
					dotChase = { 5, 4 };
					break;

				case 2:
					dotChase = { 7, 8 };
					break;

				case 3:
					dotChase = { 10, 11 };
					break;

				case 4:
					dotChase.c++;
					break;

				case 5:
					dotChase.r--;
					break;

				case 6:
					dotChase.c--;
					break;

				case 7:
					dotChase.c--;
					break;

				case 8:
					dotChase.c--;
					break;

				case 9:
					dotChase.r--;
					break;

				case 10:
					dotChase.c--;
					break;

				case 11:
					dotChase.r++;
					Ev_Dr_Heart_2();	// Le joueur perd de la vie
					break;

				case 12:
					dotChase.c++;
					break;

				case 13:
					dotChase.r--;
					break;

				case 14:
					dotChase.r++;
					break;

				case 15:
					dotChase.r--;
					break;

				case 16:
					dotChase.r += 2;
					break;

				case 17:
					dotChase.r += 2;
					break;

				case 18:
					dotChase.r -= 3;
					dotChase.c = 0;
					break;

				case 19:
					dotChase.c += 5;
					XY = linkGrid->link[dotChase.c][dotChase.r].Get_XY();
					//ev_DotChaseAdventure_1.delay.Stop();	// Stop le infinite check
					ev_DotChaseAdventure_1.delay.Start_Timer(8000, 5);	// Stop le infinite check
					//ConsoleRender::Add_String(chasing, Up_Txt_2(chasing), WHITE, 150);

					break;

					//case 20:
					//	dotChase.c += 1;
					//	break;

					//case 21:
					//	dotChase.c += 2;
					//	break;

					//case 22:
					//	dotChase.c += 2;
					//	break;

					//case 23:
					//	dotChase.c += 3;
					//	break;

					//case 24:
					//	dotChase.c += 3;
					//	furtherDots = linkGrid->link[linkGrid->Get_Cols() - 1][dotChase.r].Get_XY();
					//	furtherDots.x += DELTA_X * 2;
					//	ev_DotChaseAdventure_1.delay.Stop();	// Stop le infinite check
					//	ev_DotChaseAdventure_1.delay.Start_Timer(0);	// Stop le infinite check
					//	break;
				}

				if (step > 20)
				{
					// gen random crd for next dot
					dotChase.c = rand() % linkGrid->Get_Cols();
					dotChase.r = rand() % linkGrid->Get_Rows();

				}

				ev_DotChaseAdventure_1.Go_To_Next_Step();
				ConsoleRender::Add_Char(linkGrid->link[dotChase.c][dotChase.r].Get_XY(), 250, LIGHT_GREEN);
			}
			else
			{
				switch (step)	// STEP 20 à +
				{
				case 20:
					XY.x += DELTA_X;
					ConsoleRender::Add_Char(XY, 250);
					ev_DotChaseAdventure_1.Advance(8000, 4);
					break;

				case 21:
					XY.y -= DELTA_Y;
					ConsoleRender::Add_Char(XY, 250);
					ev_DotChaseAdventure_1.Advance(8000, 3);
					break;

				case 22:
					//Ev_Dr_Heart_1();	// Le joueur perd de la vie

					XY.x -= DELTA_X;
					ConsoleRender::Add_Char(XY, 250);
					ev_DotChaseAdventure_1.Advance(8000);
					break;

				case 23:
					XY.y += DELTA_Y;
					ConsoleRender::Add_Char(XY, 250);
					ev_DotChaseAdventure_1.Advance(8000, 4);
					break;

				case 24:
					XY.x -= DELTA_X;
					ConsoleRender::Add_Char(XY, 250);
					ev_DotChaseAdventure_1.Advance(8000, 4);
					break;

				case 25:

					XY.y += DELTA_Y;
					ConsoleRender::Add_Char(XY, 250);
					ev_DotChaseAdventure_1.Advance(8000, 4);
					break;

				case 26:
					XY.x -= DELTA_X;
					ConsoleRender::Add_Char(XY, 250);
					ev_DotChaseAdventure_1.Advance(12000, 2);
					break;


				case 27:
					XY.y -= DELTA_Y;
					ConsoleRender::Add_Char(XY, 250);
					ev_DotChaseAdventure_1.Advance(8000);
					break;


				case 28:
					XY.y -= DELTA_Y;
					ConsoleRender::Add_Char(XY, 219, LIGHT_AQUA);
					XY.y -= DELTA_Y;
					XY.x -= 6;
					ConsoleRender::Add_String("Adventure here", XY, WHITE);
					ev_DotChaseAdventure_1.Advance(0);
					ev_DotChaseAdventure_1.delay.Start_Timer(50000, 1, true);	// va checker à l'infinie pour vérifier si le joueur se trouve sur la position
					break;
					// Reveal that there is no exit

				}
			}
		}
	}

}