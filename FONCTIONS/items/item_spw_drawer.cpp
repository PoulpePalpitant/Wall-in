
#include "item_spw_drawer.h"

const int MAX_ANIMATIONS = MAX_ITEMS;	// screw it, make this shit laggy if you want

int DrawItemSpawnList::animationSteps = 8;			// Nombre de steps dans cet animation
ItemDrawer  DrawItemSpawnList::drawer[MAX_ANIMATIONS] = {};		// why not 20?
int DrawItemSpawnList::total;


void DrawItemSpawnList::Remove(int index)	// On delete rien au final
{
	// ITS GRID TIME MOTHERFUCKER

	for (int i = index; i < total; i++)		// Décale tout
		drawer[i] = drawer[i + 1];

	total--;
}


void DrawItemSpawnList::Remove_All()
{
	for (int i = 0; i < MAX_ANIMATIONS; i++)		// ALL SHALL BE DELETED
	{
		drawer[i].timer.~SpeedTimer();	// we shall see if it works
		drawer[i] = {};
	}
	
	total = 0;
}
void DrawItemSpawnList::Cancel(Coord XY)	// Stop l'animation de l'item sur cette position
{
	for (int index = 0; index < total; index++)		
	{
		if (Are_Equal(drawer[index].XY, XY))
			drawer[index].cancel = true;
	}
}

bool DrawItemSpawnList::Add(ItemType type, GrdCoord crd)		// Ajoute l'item à draw dans la list
{
	static ItemDrawer tempDrawer = {};

	if (total < MAX_ANIMATIONS)
	{
		tempDrawer.type = type;
		tempDrawer.XY = linkGrid->link[crd.c][crd.r].Get_XY();
		tempDrawer.timer.Start_Timer(0);		// First step de l'animation

		drawer[total] = tempDrawer;
		total++;	
		return true;
	}
	else
		return false;
}


static unsigned char sym;	// le sym de l'item
static Colors clr;	// le sym de l'item

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
	case ItemType::HEALTH:		sym = 245;	clr = LIGHT_GREEN;	  break;
	case ItemType::AMMO:		sym = TXT_CONST.PLUS;	clr = BRIGHT_WHITE;	  break;
	}
}

void DrawItemSpawnList::Draw_Item(ItemType type, GrdCoord crd)	// sans aucune animations
{
	Find_Item_Sym(type);
	ConsoleRender::Add_Char(linkGrid->link[crd.c][crd.r].Get_XY(), sym, clr);	// Pour l'instant, tout les items sont verts
}

void DrawItemSpawnList::Draw_Item_Spawn()
{
	if (!total) return;	// Liste vide

	static ItemDrawer* draw;	/// my pencil	
	static int X;				// facilite l'affichage
	static int Y;				// facilite l'affichage
	static const int spd = 7000;// vitesse constante

	for (int index = 0; index < total; index++)
	{
		draw = &drawer[index];

		while (draw->timer.Tick())
		{
			X = draw->XY.x;	//yep
			Y = draw->XY.y;	//xep

			// ANIMATION TIME
			switch (draw->currStep)
			{
			case 0:// emmerde pas l'étape 0, pour cette fois
				if (!draw->cancel)
				{
					//sym = ITEM_SYM[(int)draw->type];
					Find_Item_Sym(draw->type);
					ConsoleRender::Add_Char({ X,Y }, sym, GRAY);	// Pour l'instant, tout les items sont verts
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
					//ConsoleRender::Add_Char({ X - 1,Y }, 250, GRAY);
					//ConsoleRender::Add_Char({ X + 1,Y }, 250, GRAY);
				}
				draw->timer.Start_Timer(spd);
				draw->currStep++;
				break;

			case 6:
				if (!draw->cancel)
				{
					Find_Item_Sym(draw->type);
					ConsoleRender::Add_Char({ X,Y }, sym, clr);
					//ConsoleRender::Add_Char({ X - 2,Y }, 250, GRAY);
					//ConsoleRender::Add_Char({ X + 2,Y }, 250, GRAY);
					//ConsoleRender::Add_Char({ X - 1,Y }, '-', WHITE);
					//ConsoleRender::Add_Char({ X + 1,Y }, '-', WHITE);
				}
				draw->timer.Start_Timer(spd);
				draw->currStep++;
				break;

			case 7:
				if (!draw->cancel)
				{
					//ConsoleRender::Add_Char({ X - 1,Y }, TXT_CONST.SPACE);
					//ConsoleRender::Add_Char({ X + 1,Y }, TXT_CONST.SPACE);
					//ConsoleRender::Add_Char({ X - 2,Y }, '-', GRAY);
					//ConsoleRender::Add_Char({ X + 2,Y }, '-', GRAY);
				}
				draw->timer.Start_Timer(spd);
				draw->currStep++;
				break;

			case 8:
				if (!draw->cancel)
				{
					//ConsoleRender::Add_Char({ X - 2,Y }, TXT_CONST.SPACE);
					//ConsoleRender::Add_Char({ X + 2,Y }, TXT_CONST.SPACE);
				}
				Remove(index);	// we done here
			}
		}

	}

}
