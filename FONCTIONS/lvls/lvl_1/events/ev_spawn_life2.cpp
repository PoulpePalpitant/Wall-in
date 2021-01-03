
#include "ev_spawn_life2.h"

#include "../../../items/item_list.h"

#include "../../../console/sweet_cmd_console.h"
#include "../../lvl_script.h"
#include "../../../events/events.h"
#include "../../../grid/AllGrids.h"
#include "../../../player/player.h"
#include "../../../UI/console_output/render_list.h"
#include "../../../time/movement_timer.h"
#include "../../../events/msg_dispatcher.h"
#include "../../../events/global_events/ev_update_heart.h"

static Coord pos;		// position en xy
static int itemY;
static Event ev_SpawnMysteriousItem(Ev_Spawn_Mysterious_Item2, 10);
static std::string healthy = "You Seem";
static std::string anything = "Healthy Enough";


void Ev_Spawn_Mysterious_Item2()	// Spawn un item mystérieux! ( version pas de tit points)
{
	static Item item;	// l'item qui va être créé 

	if (!ev_SpawnMysteriousItem.Is_Active())
	{
		if (gCurrentStage == 0)
		{
			pos.x = linkGrid->link[linkGrid->Get_Cols() / 2][0].Get_XY().x;	// Le milieu
			pos.y = linkGrid->link[0][0].Get_XY().y;						// première ligne
			itemY = pos.y;
			
			ev_SpawnMysteriousItem.Activate();
			ev_SpawnMysteriousItem.Start(0);
			ev_SpawnMysteriousItem.delay.Start_Timer(10000, 1, true);// INFINITY
		}
	}
	else	// doin stuff 
	{
		while (ev_SpawnMysteriousItem.delay.Tick())
		{
			switch (ev_SpawnMysteriousItem.Get_Current_Step())
			{
			case 1:
				if (P1.Get_Grd_Coord().r <= linkGrid->Get_Rows() / 2 + 2)	// Attend que le joueur se déplace sur la moitié du field pour spawner l'item
				{
					ConsoleRender::Add_Char(pos, 250, GRAY);	// item1 symbole
					ev_SpawnMysteriousItem.delay.Stop();
					ev_SpawnMysteriousItem.Advance(5000);
				}
				break;

			case 2:
				ConsoleRender::Add_Char({ pos.x, pos.y }, 'o', WHITE);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 1, pos.y - 1 }, '/', GRAY);	// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x + 1, pos.y + 1 }, '\\', GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 1, pos.y - 1 }, '\\', GRAY);// truc diagonal qui splash
				ConsoleRender::Add_Char({ pos.x - 1, pos.y + 1 }, '/', GRAY);	// truc diagonal qui splash
				ev_SpawnMysteriousItem.Advance(7000);
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
				ev_SpawnMysteriousItem.Advance(9000);
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


				// Ajoute l'item dans la liste
				item.Activate();
				item.Set_Coord({ linkGrid->Get_Cols() / 2, 0 });
				item.Set_Type(ItemType::LIFE);
				ItemsOnGrid::Add(item);

				ev_SpawnMysteriousItem.Advance(12000);
				break;

			case 5:
				ConsoleRender::Add_Char({ pos.x - 1, pos.y }, '|', GRAY);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 1, pos.y }, '|', GRAY);	// item3 symbole
				ev_SpawnMysteriousItem.Advance(10000);
				break;

			case 6:
				ConsoleRender::Add_Char({ pos.x + 2, pos.y - 2 }, TXT_CONST.SPACE, WHITE);	// erase
				ConsoleRender::Add_Char({ pos.x + 2, pos.y + 2 }, TXT_CONST.SPACE, WHITE);
				ConsoleRender::Add_Char({ pos.x - 2, pos.y - 2 }, TXT_CONST.SPACE, WHITE);
				ConsoleRender::Add_Char({ pos.x - 2, pos.y + 2 }, TXT_CONST.SPACE, WHITE);
				ConsoleRender::Add_Char({ pos.x - 2, pos.y }, '-', WHITE);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 2, pos.y }, '-', WHITE);	// item3 symbole
				ev_SpawnMysteriousItem.Advance(8000);
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

				ev_SpawnMysteriousItem.Advance(6000);
				break;

			case 8:
				// faut effacer les tites lignes sur les côtés aussi
				ConsoleRender::Add_Char({ pos.x - 1,itemY }, TXT_CONST.SPACE);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 1,itemY }, TXT_CONST.SPACE);	// item3 symbole
				ev_SpawnMysteriousItem.Advance(6000);
				break;

			case 9:
				ConsoleRender::Add_Char({ pos.x - 2,itemY }, TXT_CONST.SPACE);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 2,itemY }, TXT_CONST.SPACE);	// item3 symbole
				ev_SpawnMysteriousItem.Advance(6000);
				break;

			case 10:
				ConsoleRender::Add_Char({ pos.x - 3,itemY }, TXT_CONST.SPACE);	// item2 symbole
				ConsoleRender::Add_Char({ pos.x + 3,itemY }, TXT_CONST.SPACE);	// item3 symbole
				ev_SpawnMysteriousItem.Advance(3000, 15);
				break;
				
			case 11:
				
				break;


			}
		}			
	}
}


static Coord crd;	// NE PAS MÉLANGER POS ET CRD
static Event ev_SpawnLife(Ev_Spawn_Life2, 10);

void Ev_Spawn_Life2()					// Trace un chemin vers le coeur
{
	if (!ev_SpawnLife.Is_Active())
	{
		if (gCurrentStage == 0)
		{
			crd.x = linkGrid->link[linkGrid->Get_Cols() / 2][0].Get_XY().x;	// Le milieu
			crd.y = linkGrid->link[0][0].Get_XY().y + 2;						// première ligne
			ConsoleRender::Add_Char(crd, TXT_CONST.VER_BAR);

			ev_SpawnLife.Activate();
			ev_SpawnLife.Start(15000, 10);// ON EMMERDE L'ÉTAPE 0
		}
	}
	else
		while (ev_SpawnLife.delay.Tick())
		{
			switch (ev_SpawnLife.Get_Current_Step())
			{

			case 1:

				ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
				crd.y++;		// Fait un bond
				ConsoleRender::Add_Char(crd, TXT_CONST.VER_BAR);
				ev_SpawnLife.Advance(15000, 5);
				break;

			case 2:
				ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
				crd.y++;
				ConsoleRender::Add_Char(crd, TXT_CONST.VER_BAR);
				ev_SpawnLife.Advance(20000, 5);
				break;

			case 3:
				ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
				crd.y++;
				ConsoleRender::Add_Char(crd, TXT_CONST.VER_BAR);
				ev_SpawnLife.Advance(40000, 10);
				break;

			case 4:
				ConsoleRender::Add_Char(crd, TXT_CONST.SPACE); 
				crd.y++;
				ConsoleRender::Add_Char(crd, TXT_CONST.VER_BAR);
				ev_SpawnLife.Advance(50000, 10);
				break;

			case 5:
				ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
				crd.y++;
				ConsoleRender::Add_Char(crd, TXT_CONST.VER_BAR);
				ev_SpawnLife.Advance(60000, 7);
				break;

			case 6:
				ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
				crd.y++;
				ConsoleRender::Add_Char(crd, TXT_CONST.VER_BAR);
				ev_SpawnLife.Advance(0);
				break;
			case 7:
				ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
				Start_Ev_Dr_Heart(3, true); // affiche le coeur 	// spawn le coeur
				ev_SpawnLife.Advance(400);
				break;

			case 8:
				
				ConsoleRender::Add_String(healthy, Heart_Txt_Crd_Left (healthy), LIGHT_GREEN, TXT_SPD_DR);
				ev_SpawnLife.Advance(1000);
				break;

			case 9:
				ConsoleRender::Add_String(anything, Heart_Txt_Crd_Right(anything), LIGHT_GREEN, TXT_SPD_DR);
				ev_SpawnLife.Advance(300);
				break;

			case 10:
				ConsoleRender::Add_String(healthy, Heart_Txt_Crd_Left (healthy), WHITE, TXT_SPD_ER, true);
				ConsoleRender::Add_String(anything, Heart_Txt_Crd_Right(anything), WHITE, TXT_SPD_ER, true);
				ev_SpawnLife.Advance(0);
				break;
			}
		}
}