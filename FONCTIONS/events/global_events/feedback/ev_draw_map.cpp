
#include "../../../UI/map.h"
#include "../../../UI/console_output/render_list.h"


#include "../../../lvls/lvl_script.h"
#include "../../msg_dispatcher.h"
#include "../../../player/player.h"
#include "ev_draw_map.h"
//#include "../../../animation/UI_draw_map.h"

#include "../../../lvls/lvl_1/msg_events/ev_waking_up.h"

static Event ev_DrawMap1(Ev_Dr_Map_Borders_1);	// das event
static Event ev_FlashMapBorder(Ev_Flash_Map_Border, 1);	// das event
static Direction brderToFlash;
static int numOfFlash;

static Coord instXY;// crdBot, crdLeft, crdRight;	// oh yeah

// Affiche les bordures TOP BOT, Ensuite LEFT RIGHT
void Ev_Dr_Map_Borders_1()
 {
	if (!ev_DrawMap1.Is_Ignored())
		if (!ev_DrawMap1.Is_Active())
		{
			if (P1.Get_XY().x == map.Get_Box_Limit(RIGHT))	// Dès que le joueur touche à la bordure droite, on affiche ça		
			{
				ev_DrawMap1.Activate();
				clrscr();	// fuck that screen
			}
		}
		else
		{
			/* Les limites*/
			int right = map.Get_Box_Limit(RIGHT);
			int up = map.Get_Box_Limit(UP);
			int left = map.Get_Box_Limit(LEFT);
			int down = map.Get_Box_Limit(DOWN);


			/*
				Animation va comme suis. Top et bot par et vont en direction opposé. Les deux atteignent un corner et on passe aux bordures left et right
				->	&&	v	synchro
				<-	&&	^
			*/


			// BORDURE TOP	-> coin gauche vers la droite
			instXY = { left, up - 1 };
			//ConsoleRender::Create_Animation_Queue(150);

			for (int i = instXY.x; i <= right; i++)
			{
				ConsoleRender::Add_Char(instXY, 196, BRIGHT_WHITE);
				instXY.x++;
			}
			ConsoleRender::Add_Char(instXY, (unsigned char)191, BRIGHT_WHITE);	// TOP-RIGHT CORNER

			// BORDURE RIGHT-> coin up vers down

			for (int i = ++instXY.y; i <= down; i++)
			{
				ConsoleRender::Add_Char(instXY, 179, BRIGHT_WHITE);
				instXY.y++;
			}
			ConsoleRender::Add_Char(instXY, (unsigned char)217, BRIGHT_WHITE);	// BOT-RIGHT CORNER
			//::Stop_Queue();

			// BORDURE BOT	-> coin droit vers la gauche
			//ConsoleRender::Create_Animation_Queue(150);
			instXY = { right , down + 1 };

			for (int i = instXY.x; i >= left; i--)
			{
				ConsoleRender::Add_Char(instXY, 196, BRIGHT_WHITE);
				instXY.x--;
			}
			ConsoleRender::Add_Char(instXY, (unsigned char)192, BRIGHT_WHITE);	// BOT-LEFT CORNER

			// BORDURE left-> coin geauche-bas vers up

			for (int i = --instXY.y; i >= up; i--)
			{
				ConsoleRender::Add_Char(instXY, 179, BRIGHT_WHITE);
				instXY.y--;
			}
			ConsoleRender::Add_Char(instXY, (unsigned char)218, BRIGHT_WHITE);	// TOP-LEFT CORNER
		//	ConsoleRender::Stop_Queue();

			ev_DrawMap1.Deactivate();	// Finis
			ev_DrawMap1.Ignore();
		}

	gBorderShown = true;	// we see them borders now
}

void Erase_Map_Borders_1(int speed)
{
			/* Les limites*/
	int right = map.Get_Box_Limit(RIGHT);
	int up = map.Get_Box_Limit(UP);
	int left = map.Get_Box_Limit(LEFT);
	int down = map.Get_Box_Limit(DOWN);

	if (speed)
		ConsoleRender::Create_Animation_Queue((float)speed);
	
	// BORDURE TOP	-> coin gauche vers la droite
	instXY = { left, up - 1 };

	for (int i = instXY.x; i <= right; i++)
	{
		ConsoleRender::Add_Char(instXY, TXT_CONST.SPACE);
		instXY.x++;
	}
	ConsoleRender::Add_Char(instXY, TXT_CONST.SPACE);	// TOP-RIGHT CORNER

	// BORDURE RIGHT-> coin up vers down

	for (int i = ++instXY.y; i <= down; i++)
	{
		ConsoleRender::Add_Char(instXY, TXT_CONST.SPACE);
		instXY.y++;
	}
	ConsoleRender::Add_Char(instXY, TXT_CONST.SPACE);	// BOT-RIGHT CORNER

	// BORDURE BOT	-> coin droit vers la gauche

	instXY = { right , down + 1 };

	for (int i = instXY.x; i >= left; i--)
	{
		ConsoleRender::Add_Char(instXY, TXT_CONST.SPACE);
		instXY.x--;
	}
	ConsoleRender::Add_Char(instXY, TXT_CONST.SPACE);	// BOT-LEFT CORNER

	// BORDURE left-> coin geauche-bas vers up

	for (int i = --instXY.y; i >= up; i--)
	{
		ConsoleRender::Add_Char(instXY, TXT_CONST.SPACE);
		instXY.y--;
	}
	ConsoleRender::Add_Char(instXY, TXT_CONST.SPACE);	// TOP-LEFT CORNER

	if (speed)
		ConsoleRender::Stop_Queue();

	gBorderShown = false;
} // soon



void Set_Flashy_Border(Direction border, int numFlash)
{
	if (!ev_FlashMapBorder.Is_Active())
	{
		brderToFlash = border;
		numOfFlash = numFlash;
	}
}


static void Draw_Or_Erase_Border(bool erase = false)	// Pour faire flasher une bordure, j'ai besoin de ^ca
{
	unsigned char sym;
	if (erase)
		sym = TXT_CONST.SPACE;
	else
		switch (brderToFlash)
		{
		case UP: case DOWN: sym = 196; break;
		case RIGHT: case LEFT: sym = 179; break;
		}

	switch (brderToFlash)
	{
	case UP:
		instXY = { map.Get_Box_Limit(LEFT), map.Get_Box_Limit(UP) - 1 };
		for (int i = instXY.x; i <= map.Get_Box_Limit(RIGHT); i++)
		{
			ConsoleRender::Add_Char(instXY, sym, BRIGHT_WHITE);
			instXY.x++;
		}
		break;

	case RIGHT:
		instXY = { map.Get_Box_Limit(RIGHT) + 1, map.Get_Box_Limit(UP) /*- 2*/ };
		for (int i = instXY.y; i <= map.Get_Box_Limit(DOWN); i++)
		{
			ConsoleRender::Add_Char(instXY, sym, BRIGHT_WHITE);
			instXY.y++;
		}
		break;

	case DOWN:
		instXY = { map.Get_Box_Limit(RIGHT), map.Get_Box_Limit(DOWN) + 1 };
		for (int i = instXY.x; i >= map.Get_Box_Limit(LEFT); i--)
		{
			ConsoleRender::Add_Char(instXY, sym, BRIGHT_WHITE);
			instXY.x--;
		}
		break;

	case LEFT:
		instXY = { map.Get_Box_Limit(LEFT) - 1, map.Get_Box_Limit(DOWN) };
		for (int i = --instXY.y; i >= map.Get_Box_Limit(UP); i--)
		{
			ConsoleRender::Add_Char(instXY, sym, BRIGHT_WHITE);
			instXY.y--;
		}
		break;
	}
}

void Ev_Flash_Map_Border()		 // Affiche instantannément
{
	if (!ev_FlashMapBorder.Is_Active())
	{
		ev_FlashMapBorder.Activate();
		ev_FlashMapBorder.Start(2000, numOfFlash);	// Met un nombre impair si tu veux que ça disparaisse
	}
	else
		while (ev_FlashMapBorder.delay.Tick())
		{			
			if (ev_FlashMapBorder.delay.Get_Moves_Left() % 2 == 0)
				Draw_Or_Erase_Border();
			else
				Draw_Or_Erase_Border(true);
		}

	if (!ev_FlashMapBorder.delay.Is_On())
		ev_FlashMapBorder.Cancel();	// we done
}



//
//
//void UI_Erase_Map_Borders_1()
//{
//
//}
//// Affiche chaque borders a partir du milieu
//void UI_Draw_Map_Borders_2()
//{
//}
//void UI_Erase_Map_Borders_2()
//{
//}
//// Affiche somehow somethign else
//void UI_Draw_Map_Borders_3()
//{
//}
//void UI_Erase_Map_Borders_3()
//{
//}


void Just_Dr_Map_Borders()
{
	/* Les limites*/
	int right = map.Get_Box_Limit(RIGHT);
	int up = map.Get_Box_Limit(UP);
	int left = map.Get_Box_Limit(LEFT);
	int down = map.Get_Box_Limit(DOWN);
	/*
		Animation va comme suis. Top et bot par et vont en direction opposé. Les deux atteignent un corner et on passe aux bordures left et right
		->	&&	v	synchro
		<-	&&	^
	*/

	// BORDURE TOP	-> coin gauche vers la droite
	instXY = { left, up - 1 };

	for (int i = instXY.x; i <= right; i++)
	{
		ConsoleRender::Add_Char(instXY, 196, BRIGHT_WHITE);
		instXY.x++;
	}
	ConsoleRender::Add_Char(instXY, (unsigned char)191, BRIGHT_WHITE);	// TOP-RIGHT CORNER

	// BORDURE RIGHT-> coin up vers down

	for (int i = ++instXY.y; i <= down; i++)
	{
		ConsoleRender::Add_Char(instXY, 179, BRIGHT_WHITE);
		instXY.y++;
	}
	ConsoleRender::Add_Char(instXY, (unsigned char)217, BRIGHT_WHITE);	// BOT-RIGHT CORNER
	//::Stop_Queue();

	// BORDURE BOT	-> coin droit vers la gauche
	instXY = { right , down + 1 };

	for (int i = instXY.x; i >= left; i--)
	{
		ConsoleRender::Add_Char(instXY, 196, BRIGHT_WHITE);
		instXY.x--;
	}
	ConsoleRender::Add_Char(instXY, (unsigned char)192, BRIGHT_WHITE);	// BOT-LEFT CORNER

	// BORDURE left-> coin geauche-bas vers up

	for (int i = --instXY.y; i >= up; i--)
	{
		ConsoleRender::Add_Char(instXY, 179, BRIGHT_WHITE);
		instXY.y--;
	}
	ConsoleRender::Add_Char(instXY, (unsigned char)218, BRIGHT_WHITE);	// TOP-LEFT CORNER
}