
#include "ev_spawn_life.h"

#include "../../../items/item_list.h"

#include "../../lvl_script.h"
#include "../../../events/events.h"
#include "../../../grid/AllGrids.h"
#include "../../../player/player.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../time/movement_timer.h"
#include "../../../events/msg_dispatcher.h"

static CDTimer timer;	// Pour délay l'event and shit
static Coord pos;		// position en xy
static int itemY;
static Event ev_SpawnLife(Ev_Spawn_Mysterious_Item, 11);

void Ev_Spawn_Mysterious_Item()// Trace un chemin vers une fausse porte de sortie
{
	static Item item;	// l'item qui va être créé 

	// si au stage 1
	if (!ev_SpawnLife.Is_Active())
	{
		if (gCurrentStage == 0)
		{
			pos.x = linkGrid->link[linkGrid->Get_Cols() / 2][0].Get_XY().x;	// Le milieu
			pos.y = linkGrid->link[0][0].Get_XY().y;						// première ligne
			itemY = pos.y;
			//pos = P1.Get_XY(); 
			//pos.y -= DELTA_Y * 6;		// Position de l'item
			
			ev_SpawnLife.Activate();
			ev_SpawnLife.Start(/*90*/0);// ON EMMERDE L'ÉTAPE 0
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
				ConsoleRender::Add_Char({ pos.x, pos.y }, 'o', WHITE);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 1, pos.y - 1 }, '/', GRAY);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 1, pos.y + 1 }, '\\', GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 1, pos.y - 1 }, '\\', GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 1, pos.y + 1 }, '/', GRAY);	// truc diagonal qui splash
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

				ConsoleRender::Add_Char({ pos.x, pos.y }, '?', LIGHT_GREEN);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 2, pos.y - 2 }, '+', WHITE);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 2, pos.y + 2 }, '+', WHITE);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 2, pos.y - 2 }, '+', WHITE);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 2, pos.y + 2 }, '+', WHITE);	// truc diagonal qui splash
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

				// Ajoute l'item dans la liste
				item.Activate();
				item.Set_Coord({ linkGrid->Get_Cols() / 2, 0 });
				item.Set_Type(ItemType::LIFE);
				ItemsOnGrid::Add(item);
				ev_SpawnLife.Advance(6000);
				break;

			case 8:
				// faut effacer les tites lignes sur les côtés aussi
				ConsoleRender::Add_Char({ pos.x - 1,itemY }, TXT_CONST.SPACE);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 1,itemY }, TXT_CONST.SPACE);	// item3 symbole
				ev_SpawnLife.Advance(6000);
				break;

			case 9:
				ConsoleRender::Add_Char({ pos.x - 2,itemY }, TXT_CONST.SPACE);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 2,itemY }, TXT_CONST.SPACE);	// item3 symbole
				ev_SpawnLife.Advance(6000);
				break;

			case 10:
				ConsoleRender::Add_Char({ pos.x - 3,itemY }, TXT_CONST.SPACE);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 3,itemY }, TXT_CONST.SPACE);	// item3 symbole
				ev_SpawnLife.Advance(3000, 15);
				break;
				
			case 11:
				pos.y += DELTA_Y;		// Fait un bond sur le grid :)

				if (P1.Get_XY().y - DELTA_Y > pos.y)	// Fait un point vers le joueur
					ConsoleRender::Add_Char(pos, 250);
				else
				{
					ev_SpawnLife.delay.Stop();
					ev_SpawnLife.Advance(0);						// terminate l'event
				}
				break;


			}
		}			
	}
}

//
//
//void Ev_Spawn_Life()					// Trace un chemin vers le coeur
//{
//	case 11:
//		pos.y = DELTA_Y + 1;
//		ConsoleRender::Add_Char(pos, TXT_CONST.VER_BAR);
//		ConsoleRender::Add_Char(pos, TXT_CONST.SPACE);
//
//		pos.y++;		// Fait un bond sur le grid :)
//		ConsoleRender::Add_Char(pos, TXT_CONST.VER_BAR);
//		ev_SpawnLife.Advance(15000, 10);
//
//		/*
//
//		Cmt je fais pour faire plusieurs step dans un même step?
//
//		*/
//		//if(pos.y == DELTA_Y + 10)
//
//
//		break;
//	case 12:
//		ConsoleRender::Add_Char(pos, TXT_CONST.SPACE);
//		pos.y++;
//		ConsoleRender::Add_Char(pos, TXT_CONST.VER_BAR);
//		ev_SpawnLife.Advance(20000, 10);
//		// fait afficher une ligne qui va faire appara^tre le coeur
//		break;
//
//	case 13:
//		ConsoleRender::Add_Char(pos, TXT_CONST.SPACE);
//		pos.y++;
//		ConsoleRender::Add_Char(pos, TXT_CONST.VER_BAR);
//		ev_SpawnLife.Advance(40000, 10);
//		break;
//}