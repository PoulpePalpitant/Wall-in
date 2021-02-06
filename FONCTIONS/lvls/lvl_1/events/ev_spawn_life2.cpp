
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

void Ev_Spawn_Mysterious_Item2()	
{
	static Item item;	

	if (!ev_SpawnMysteriousItem.Is_Active())
	{
		if (gCurrentStage == 0)
		{
			pos.x = linkGrid->link[linkGrid->Get_Cols() / 2][0].Get_XY().x;	
			pos.y = linkGrid->link[0][0].Get_XY().y;						
			itemY = pos.y;
			
			ev_SpawnMysteriousItem.Activate();
			ev_SpawnMysteriousItem.Start(0);
			ev_SpawnMysteriousItem.delay.Start_Timer(10000, 1, true);
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
					ConsoleRender::Add_Char(pos, 250, GRAY);	
					ev_SpawnMysteriousItem.delay.Stop();
					ev_SpawnMysteriousItem.Advance(5000);
				}
				break;

			case 2:
				ConsoleRender::Add_Char({ pos.x, pos.y }, 'o', WHITE);			
				ConsoleRender::Add_Char({ pos.x + 1, pos.y - 1 }, '/', GRAY);
				ConsoleRender::Add_Char({ pos.x + 1, pos.y + 1 }, '\\', GRAY);
				ConsoleRender::Add_Char({ pos.x - 1, pos.y - 1 }, '\\', GRAY);
				ConsoleRender::Add_Char({ pos.x - 1, pos.y + 1 }, '/', GRAY); 
				ev_SpawnMysteriousItem.Advance(7000);
				break;

			case 3:
				ConsoleRender::Add_Char(pos, 'O', BRIGHT_WHITE);	
				ConsoleRender::Add_Char({ pos.x + 1, pos.y - 1 }, '/', WHITE); 
				ConsoleRender::Add_Char({ pos.x + 1, pos.y + 1 }, '\\', WHITE);
				ConsoleRender::Add_Char({ pos.x - 1, pos.y - 1 }, '\\', WHITE);
				ConsoleRender::Add_Char({ pos.x - 1, pos.y + 1 }, '/', WHITE);	

				ConsoleRender::Add_Char({ pos.x + 2, pos.y - 2 }, 250, GRAY);	
				ConsoleRender::Add_Char({ pos.x + 2, pos.y + 2 }, 250, GRAY);
				ConsoleRender::Add_Char({ pos.x - 2, pos.y - 2 }, 250, GRAY);
				ConsoleRender::Add_Char({ pos.x - 2, pos.y + 2 }, 250, GRAY);	
				ev_SpawnMysteriousItem.Advance(9000);
				break;

			case 4:
				ConsoleRender::Add_Char({ pos.x + 1, pos.y - 1 }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ pos.x + 1, pos.y + 1 }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ pos.x - 1, pos.y - 1 }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ pos.x - 1, pos.y + 1 }, TXT_CONST.SPACE);

				ConsoleRender::Add_Char({ pos.x, pos.y }, '?', LIGHT_GREEN);  
				ConsoleRender::Add_Char({ pos.x + 2, pos.y - 2 }, '+', WHITE);
				ConsoleRender::Add_Char({ pos.x + 2, pos.y + 2 }, '+', WHITE);
				ConsoleRender::Add_Char({ pos.x - 2, pos.y - 2 }, '+', WHITE);
				ConsoleRender::Add_Char({ pos.x - 2, pos.y + 2 }, '+', WHITE);
				ConsoleRender::Add_Char({ pos.x - 1, pos.y }, 250, GRAY);	
				ConsoleRender::Add_Char({ pos.x + 1, pos.y }, 250, GRAY);	

				// Ajoute l'item dans la liste
				item.Activate();
				item.Set_Coord({ linkGrid->Get_Cols() / 2, 0 });
				item.Set_Type(ItemType::LIFE);
				ItemsOnGrid::Add(item);

				ev_SpawnMysteriousItem.Advance(12000);
				break;

			case 5:
				ConsoleRender::Add_Char({ pos.x - 1, pos.y }, '|', GRAY);
				ConsoleRender::Add_Char({ pos.x + 1, pos.y }, '|', GRAY);
				ev_SpawnMysteriousItem.Advance(10000);
				break;

			case 6:
				ConsoleRender::Add_Char({ pos.x + 2, pos.y - 2 }, TXT_CONST.SPACE, WHITE);	
				ConsoleRender::Add_Char({ pos.x + 2, pos.y + 2 }, TXT_CONST.SPACE, WHITE);
				ConsoleRender::Add_Char({ pos.x - 2, pos.y - 2 }, TXT_CONST.SPACE, WHITE);
				ConsoleRender::Add_Char({ pos.x - 2, pos.y + 2 }, TXT_CONST.SPACE, WHITE);
				ConsoleRender::Add_Char({ pos.x - 2, pos.y }, '-', WHITE);
				ConsoleRender::Add_Char({ pos.x + 2, pos.y }, '-', WHITE);
				ev_SpawnMysteriousItem.Advance(8000);
				break;
			case 7:
				ConsoleRender::Add_Char({ pos.x - 1, pos.y }, TXT_CONST.SPACE, GRAY);	
				ConsoleRender::Add_Char({ pos.x + 1, pos.y }, TXT_CONST.SPACE, GRAY);	
				ConsoleRender::Add_Char({ pos.x - 1, pos.y }, '|', WHITE);	
				ConsoleRender::Add_Char({ pos.x + 1, pos.y }, '|', WHITE);	
				ConsoleRender::Add_Char({ pos.x - 2, pos.y }, '-', GRAY);	
				ConsoleRender::Add_Char({ pos.x + 2, pos.y }, '-', GRAY);	
				ConsoleRender::Add_Char({ pos.x - 3, pos.y }, '-', GRAY);	
				ConsoleRender::Add_Char({ pos.x + 3, pos.y }, '-', GRAY);	

				ev_SpawnMysteriousItem.Advance(6000);
				break;

			case 8:
				ConsoleRender::Add_Char({ pos.x - 1,itemY }, TXT_CONST.SPACE);
				ConsoleRender::Add_Char({ pos.x + 1,itemY }, TXT_CONST.SPACE);
				ev_SpawnMysteriousItem.Advance(6000);
				break;

			case 9:
				ConsoleRender::Add_Char({ pos.x - 2,itemY }, TXT_CONST.SPACE);	
				ConsoleRender::Add_Char({ pos.x + 2,itemY }, TXT_CONST.SPACE);	
				ev_SpawnMysteriousItem.Advance(6000);
				break;

			case 10:
				ConsoleRender::Add_Char({ pos.x - 3,itemY }, TXT_CONST.SPACE);	
				ConsoleRender::Add_Char({ pos.x + 3,itemY }, TXT_CONST.SPACE);	
				ev_SpawnMysteriousItem.Advance(3000, 15);
				break;
				
			case 11:
				
				break;


			}
		}			
	}
}

