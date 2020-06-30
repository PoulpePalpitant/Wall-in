
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
static Event ev_SpawnLife(Ev_Spawn_Life, 9);

void Ev_Spawn_Life()// Trace un chemin vers une fausse porte de sortie
{
	if (!ev_SpawnLife.Is_Active())
	{
		if (gCurrentStage == 0)
		{
			pos.x = linkGrid->link[linkGrid->Get_Cols() / 2][0].Get_XY().x;	// Le milieu
			pos.y = linkGrid->link[0][0].Get_XY().y;						// première ligne
			//pos = P1.Get_XY(); 
			//pos.y -= DELTA_Y * 6;		// Position de l'item
			
			ev_SpawnLife.Activate();
			ev_SpawnLife.Start(90);// ON EMMERDE L'ÉTAPE 0
		}
	}
	else	// doin stuff 
	{
		while (ev_SpawnLife.delay.Tick())
		{
			switch (ev_SpawnLife.Get_Current_Step())
			{
			
			case 1:
				ConsoleRender::Add_Char(pos, 250, GRAY);	// item1 symbole
				ev_SpawnLife.Advance(5000);
				break;

			case 2:
				ConsoleRender::Add_Char({pos.x, pos.y}, 'o', WHITE);	// truc diagonal qui splash
				ConsoleRender::Add_Char({pos.x + 1, pos.y - 1}, '/', GRAY);	// truc diagonal qui splash
				ConsoleRender::Add_Char({pos.x + 1, pos.y + 1}, '\\', GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char({pos.x - 1, pos.y - 1}, '\\', GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char({pos.x - 1, pos.y + 1}, '/', GRAY);	// truc diagonal qui splash
				ev_SpawnLife.Advance(7000);
				break;

			case 3:
				ConsoleRender::Add_Char(pos, 'O', BRIGHT_WHITE);	// item1 symbole
				ConsoleRender::Add_Char({ pos.x + 1, pos.y - 1 }, '/', WHITE);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 1, pos.y + 1 }, '\\', WHITE);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 1, pos.y - 1 }, '\\', WHITE);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 1, pos.y + 1 }, '/', WHITE);	// truc diagonal qui splash

				ConsoleRender::Add_Char({ pos.x + 2, pos.y - 2 }, 250, GRAY);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 2, pos.y + 2 }, 250, GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 2, pos.y - 2 }, 250, GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 2, pos.y + 2 }, 250, GRAY);	// truc diagonal qui splash
				ev_SpawnLife.Advance(9000);
				break;

			case 4:
				ConsoleRender::Add_Char({ pos.x + 1, pos.y - 1 }, TXT_CONST.SPACE);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 1, pos.y + 1 }, TXT_CONST.SPACE);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 1, pos.y - 1 }, TXT_CONST.SPACE);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 1, pos.y + 1 }, TXT_CONST.SPACE);	// truc diagonal qui splash

				ConsoleRender::Add_Char({ pos.x, pos.y }, '0', LIGHT_GREEN);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 2, pos.y - 2 },'+', WHITE);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 2, pos.y + 2 },'+', WHITE);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 2, pos.y - 2 },'+', WHITE);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 2, pos.y + 2 },'+', WHITE);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 1, pos.y }, 250, GRAY);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 1, pos.y }, 250, GRAY);	// item3 symbole
				ev_SpawnLife.Advance(12000);
				break;

			case 5:
				ConsoleRender::Add_Char({ pos.x - 1, pos.y }, '|', GRAY);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 1, pos.y }, '|', GRAY);	// item3 symbole
				ev_SpawnLife.Advance(10000);
				break;

			case 6: 
				ConsoleRender::Add_Char({ pos.x + 2, pos.y - 2 }, TXT_CONST.SPACE, WHITE);	// erase
				ConsoleRender::Add_Char({ pos.x + 2, pos.y + 2 }, TXT_CONST.SPACE, WHITE);	
				ConsoleRender::Add_Char({ pos.x - 2, pos.y - 2 }, TXT_CONST.SPACE, WHITE);	
				ConsoleRender::Add_Char({ pos.x - 2, pos.y + 2 }, TXT_CONST.SPACE, WHITE);	
				ConsoleRender::Add_Char({ pos.x - 2, pos.y }, '-', WHITE);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 2, pos.y }, '-', WHITE);	// item3 symbole
				ev_SpawnLife.Advance(8000);
				break;

			case 7: 
				ConsoleRender::Add_Char({ pos.x - 1, pos.y }, TXT_CONST.SPACE, GRAY);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 1, pos.y }, TXT_CONST.SPACE, GRAY);	// item3 symbole
				ConsoleRender::Add_Char({ pos.x - 1, pos.y }, '|', WHITE);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 1, pos.y }, '|', WHITE);	// item3 symbole
				ConsoleRender::Add_Char({ pos.x - 2, pos.y }, '-', GRAY);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 2, pos.y }, '-', GRAY);	// item3 symbole
				ConsoleRender::Add_Char({ pos.x - 3, pos.y }, '-', GRAY);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 3, pos.y }, '-', GRAY);	// item3 symbole
				ev_SpawnLife.Advance(6000);
				break;

			case 8: 
				//ConsoleRender::Add_Char({ pos.x - 2, pos.y }, TXT_CONST.SPACE);	// item2 symbole
				//ConsoleRender::Add_Char({ pos.x + 2, pos.y }, TXT_CONST.SPACE);	// item3 symbole
				ev_SpawnLife.Advance(3000,15);
				break;

			case 9:
				pos.y += DELTA_Y;		// Fait un bond sur le grid :)
				
				if (P1.Get_XY().y - DELTA_Y > pos.y)	// Fait un point vers le joueur
					ConsoleRender::Add_Char(pos, 250);
				else
				{
					ev_SpawnLife.Cancel();						// terminate l'event
					//MsgQueue::Register(START_BOTS);				// Here they come baby
				}
				break;
			}
		}			
	}
}

