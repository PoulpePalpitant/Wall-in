
#include "item_spw_drawer.h"

const int MAX_ANIMATIONS = MAX_ITEMS;	// screw it, make this shit laggy if you want

int DrawItemSpawnList::animationSteps = 8;					
ItemDrawer  DrawItemSpawnList::drawer[MAX_ANIMATIONS] = {};	
int DrawItemSpawnList::total;


void DrawItemSpawnList::Remove(int index)	
{
	for (int i = index; i < total; i++)		
	{
		drawer[i] = drawer[i + 1];
	}

	total--;
}


void DrawItemSpawnList::Remove_All()
{
	for (int i = 0; i < MAX_ANIMATIONS; i++)
	{
		drawer[i].cancel = true;
		drawer[i].currStep = 0;
		drawer[i].type = ItemType::REGULAR;
		drawer[i].XY = {};
		drawer[i].timer.Stop();
	}
	
	total = 0;
}
void DrawItemSpawnList::Cancel(Coord XY)
{
	for (int index = 0; index < total; index++)		
	{
		if (Are_Equal(drawer[index].XY, XY))
			drawer[index].cancel = true;
	}
}

bool DrawItemSpawnList::Add(ItemType type, GrdCoord crd)		
{
	if (total < MAX_ANIMATIONS)
	{
		drawer[total].type = type;
		drawer[total].XY = linkGrid->link[crd.c][crd.r].Get_XY();
		drawer[total].timer.Start_Timer(0);		
		drawer[total].cancel = false;

		total++;	
		return true;
	}
	else
		return false;
}


static unsigned char sym;	
static Colors clr;	

void DrawItemSpawnList::Find_Item_Sym(ItemType type)
{
	switch (type)
	{
	case ItemType::REGULAR:			  break;
	case ItemType::BUFFER:		sym = 254;	clr = LIGHT_YELLOW;		  break;
	case ItemType::BLOCKER:		sym = 158; 	clr = LIGHT_RED;		  break;
	case ItemType::CORRUPTED:	sym = 207;	clr = LIGHT_PURPLE;		break;
	case ItemType::COLOR_A:		sym = 176;	clr = LIGHT_YELLOW;	  break;
	case ItemType::COLOR_B: 	sym = 176;	clr = LIGHT_AQUA;	break;
	case ItemType::BLIND_COLOR:	sym = 176;	clr = BRIGHT_WHITE;	  break;
	case ItemType::AMMO:		sym = 245;	clr = LIGHT_GREEN;	  break;
	}
}

void DrawItemSpawnList::Draw_Item(ItemType type, GrdCoord crd)	
{
	Find_Item_Sym(type);
	ConsoleRender::Add_Char(linkGrid->link[crd.c][crd.r].Get_XY(), sym, clr);	
}

void DrawItemSpawnList::Draw_Item_Spawn()
{
	if (!total) return;	

	static ItemDrawer* draw;	
	static int X;				
	static int Y;				
	static const int spd = 7000;

	for (int index = 0; index < total; index++)
	{
		draw = &drawer[index];

		while (draw->timer.Tick())
		{
			X = draw->XY.x;
			Y = draw->XY.y;

			switch (draw->currStep)
			{
			case 0:// emmerde pas l'étape 0, pour cette fois
				if (!draw->cancel)
				{
					Find_Item_Sym(draw->type);
					ConsoleRender::Add_Char({ X,Y }, sym, GRAY);	
				}
				ConsoleRender::Add_Char({ X + 2,Y + 2 }, 250, GRAY);	
				ConsoleRender::Add_Char({ X + 2,Y - 2 }, 250, GRAY);	
				ConsoleRender::Add_Char({ X - 2,Y + 2 }, 250, GRAY);	
				ConsoleRender::Add_Char({ X - 2,Y - 2 }, 250, GRAY);	
				draw->timer.Start_Timer(spd);
				draw->currStep++;
				break;

			case 1:
				ConsoleRender::Add_Char({ X + 2,Y + 2 }, '\\', WHITE);
				ConsoleRender::Add_Char({ X + 2,Y - 2 }, '/',  WHITE);
				ConsoleRender::Add_Char({ X - 2,Y + 2 }, '/',  WHITE);
				ConsoleRender::Add_Char({ X - 2,Y - 2 }, '\\', WHITE);
				ConsoleRender::Add_Char({ X + 1,Y + 1 }, 250, GRAY);
				ConsoleRender::Add_Char({ X + 1,Y - 1 }, 250, GRAY);
				ConsoleRender::Add_Char({ X - 1,Y + 1 }, 250, GRAY);
				ConsoleRender::Add_Char({ X - 1,Y - 1 }, 250, GRAY);
				draw->timer.Start_Timer(spd);
				draw->currStep++;
				break;

			case 2:
				ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', GRAY);
				ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/', GRAY);
				ConsoleRender::Add_Char({ X - 1,Y + 1 }, '/', GRAY);
				ConsoleRender::Add_Char({ X - 1,Y - 1 }, '\\', GRAY);
				ConsoleRender::Add_Char({ X + 2,Y + 2 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X + 2,Y - 2 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X - 2,Y + 2 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X - 2,Y - 2 }, TXT_CONST.SPACE, GRAY);
				draw->timer.Start_Timer(spd + 2000);
				draw->currStep++;
				break;

			case 3:
				ConsoleRender::Add_Char({ X + 1,Y + 1 }, '\\', WHITE);
				ConsoleRender::Add_Char({ X + 1,Y - 1 }, '/',  WHITE);
				ConsoleRender::Add_Char({ X - 1,Y + 1 }, '/',  WHITE);
				ConsoleRender::Add_Char({ X - 1,Y - 1 }, '\\', WHITE);
				draw->timer.Start_Timer(spd + 2000);
				draw->currStep++;
				break;

			case 4:
				if(!draw->cancel)
					ConsoleRender::Add_Char({ X,Y }, 250, GRAY);

				ConsoleRender::Add_Char({ X + 1,Y + 1 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X + 1,Y - 1 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X - 1,Y + 1 }, TXT_CONST.SPACE, GRAY);
				ConsoleRender::Add_Char({ X - 1,Y - 1 }, TXT_CONST.SPACE, GRAY);
				draw->timer.Start_Timer(spd);
				draw->currStep++;
				break;

			case 5:
				if (!draw->cancel)
				{
					ConsoleRender::Add_Char({ X,Y }, '-', WHITE);
				}
				draw->timer.Start_Timer(spd);
				draw->currStep++;
				break;

			case 6:
				if (!draw->cancel)
				{
					Find_Item_Sym(draw->type);
					ConsoleRender::Add_Char({ X,Y }, sym, clr);
				}
				draw->timer.Start_Timer(spd);
				draw->currStep++;
				break;

			case 7:
				draw->timer.Start_Timer(spd);
				draw->currStep++;
				break;

			case 8:
				Remove(index);	// we done here
			}
		}

	}

}
