

#include "ev_spawn_life.h"

#include "../../lvl_script.h"
#include "../../../events/events.h"
#include "../../../grid/AllGrids.h"
#include "../../../player/player.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../time/movement_timer.h"
#include "../../../events/msg_dispatcher.h"

static CDTimer timer;	// Pour délay l'event and shit
static Coord pos;		// position en xy
static Event Ev_SpawnLife(Ev_Spawn_Life, 6);

// Vitesse d'affichage and shit
MovementTimer drawer;

//
//void Ev_Spawn_Life()// Trace un chemin vers une fausse porte de sortie
//{
//	if (!Ev_SpawnLife.Is_Active())
//	{
//		if (gCurrentStage == 0)
//		{
//			Ev_SpawnLife.Activate();
//			timer.Set_Cd_Duration(300);
//			timer.Start_CountDown(5);	// 5 fois!
//			pos = P1.Get_XY();
//		
//		}
//	}
//	else	// doin stuff 
//	{
//		if (timer.Get_Time_Left() <= 0)
//		{
//			switch (Ev_SpawnLife.Get_Current_Step())
//			{
//			case 0:
//				pos.y -= DELTA_Y;	// Fait un bond sur le grid :)
//				ConsoleRender::Add_Char_To_Render_List(pos, 250);
//				
//				if (!timer.Is_Finished())	// finis le nombre de cycles
//					Ev_SpawnLife.Advance();
//				
//				timer.Start_CountDown();
//				break;
//
//			case 1:
//				pos.y -= DELTA_Y;		// Position de l'item
//				ConsoleRender::Create_Queue(50);
//				ConsoleRender::Add_Char_To_Render_List(pos, 250, GRAY);	// item1 symbole
//				ConsoleRender::Add_Char_To_Render_List(pos, 'o', WHITE);	// item1 symbole
//				ConsoleRender::Add_Char_To_Render_List({ pos.x -1, pos.y }, '[', WHITE);	// item2 symbole
//				ConsoleRender::Add_Char_To_Render_List(pos, 'O', BRIGHT_WHITE);	// item1 symbole
//				ConsoleRender::Add_Char_To_Render_List({ pos.x + 1, pos.y }, ']', WHITE);	// item3 symbole
//				ConsoleRender::Stop_Queue();
//				/*
//
//				
//				
//				
//				*/
//				Ev_SpawnLife.Advance();
//				break;
//			}
//
//				pos.y -= 2;
//				ConsoleRender::Add_String_To_Render_List("Exit", pos, LIGHT_YELLOW, 70);
//
//				Ev_SpawnLife.Advance();
//				timer.Set_Cd_Duration(1000);	// Délay séparant le prochain step
//
//		}
//		else
//			timer.Tick_Timer_With_Speed();
//
//		// Reveal that there is no exit
//		Ev_SpawnLife.Stop_If_No_More_Steps();
//
//	}
//}
//

void Ev_Spawn_Life()// Trace un chemin vers une fausse porte de sortie
{
	if (!Ev_SpawnLife.Is_Active())
	{
		if (gCurrentStage == 0)
		{
			Ev_SpawnLife.Activate();
			pos = P1.Get_XY(); pos.y -= DELTA_Y * 2;		// Position de l'item
			drawer.Start_Timer(5, 5, DELTA_Y);
		}
	}
	else	// doin stuff 
	{
		if (drawer.Move_Tick())
		{
			switch (Ev_SpawnLife.Get_Current_Step())
			{
			case 0:
				pos.y -= drawer.Get_Move_Distance();	// Fait un bond sur le grid :)
				ConsoleRender::Add_Char_To_Render_List(pos, 250);

				if (!drawer.Is_Moving())	// finis le nombre de cycles
				{
					Ev_SpawnLife.Advance();
					drawer.Start_Timer(10);
				}

				break;

			case 1:
				
				pos.y -= DELTA_Y * 2;		// Position de l'item
				ConsoleRender::Add_Char_To_Render_List(pos, 250, GRAY);	// item1 symbole
				
				if (!drawer.Is_Moving())	// finis le nombre de cycles
				{
					Ev_SpawnLife.Advance();
					drawer.Start_Timer(15);
				}
				break;
			case 2:
				ConsoleRender::Add_Char_To_Render_List({pos.x, pos.y}, 'o', WHITE);	// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({pos.x + 1, pos.y - 1}, '/', GRAY);	// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({pos.x + 1, pos.y + 1}, '\\', GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({pos.x - 1, pos.y - 1}, '\\', GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({pos.x - 1, pos.y + 1}, '/', GRAY);	// truc diagonal qui splash
				
				if (!drawer.Is_Moving())	// finis le nombre de cycles
				{
					Ev_SpawnLife.Advance();
					drawer.Start_Timer(20);
				}
				break;

			case 3:
				ConsoleRender::Add_Char_To_Render_List(pos, 'O', BRIGHT_WHITE);	// item1 symbole
				ConsoleRender::Add_Char_To_Render_List({ pos.x + 1, pos.y - 1 }, '/', WHITE);	// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x + 1, pos.y + 1 }, '\\', WHITE);// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x - 1, pos.y - 1 }, '\\', WHITE);// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x - 1, pos.y + 1 }, '/', WHITE);	// truc diagonal qui splash

				ConsoleRender::Add_Char_To_Render_List({ pos.x + 2, pos.y - 2 }, 250, GRAY);	// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x + 2, pos.y + 2 }, 250, GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x - 2, pos.y - 2 }, 250, GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x - 2, pos.y + 2 }, 250, GRAY);	// truc diagonal qui splash

				if (!drawer.Is_Moving())	// finis le nombre de cycles
				{
					Ev_SpawnLife.Advance();
					drawer.Start_Timer(5);
				}
				break;
			case 4:
				ConsoleRender::Add_Char_To_Render_List({ pos.x, pos.y }, '0', LIGHT_GREEN);	// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x + 1, pos.y - 1 }, TXT_CONST.SPACE);	// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x + 1, pos.y + 1 }, TXT_CONST.SPACE);// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x - 1, pos.y - 1 }, TXT_CONST.SPACE);// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x - 1, pos.y + 1 }, TXT_CONST.SPACE);	// truc diagonal qui splash

				ConsoleRender::Add_Char_To_Render_List({ pos.x + 2, pos.y - 2 },'+', WHITE);	// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x + 2, pos.y + 2 },'+', WHITE);// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x - 2, pos.y - 2 },'+', WHITE);// truc diagonal qui splash
				ConsoleRender::Add_Char_To_Render_List({ pos.x - 2, pos.y + 2 },'+', WHITE);	// truc diagonal qui splash

				if (!drawer.Is_Moving())	// finis le nombre de cycles
				{
					Ev_SpawnLife.Advance();
					drawer.Start_Timer(5);
				}
				break;

				/*
				COMBINE ADVANCE AVER LE DRAWER!

				
				
				*/

				// 	Ev_SpawnLife.Advance(5, 5, DELTA_Y)


			case 5: //LAST STEP!

				ConsoleRender::Add_Char_To_Render_List({ pos.x - 1, pos.y }, '|', GRAY);	// item2 symbole
				ConsoleRender::Add_Char_To_Render_List({ pos.x + 1, pos.y }, '|', GRAY);	// item3 symbole

				Ev_SpawnLife.Advance();
				break;

			}

		}

		// Reveal that there is no exit
		if (Ev_SpawnLife.Stop_If_No_More_Steps())
			MsgQueue::Register(START_BOTS);				// Here they come baby
	}
}

