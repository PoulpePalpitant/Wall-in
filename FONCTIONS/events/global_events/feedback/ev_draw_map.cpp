
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


static Coord crd;
static int drSpeed;
static int erase;

			/*
				Animation va comme suis. Top et bot par et vont en direction opposé. Les deux atteignent un corner et on passe aux bordures left et right
				->	&&	v	synchro
				<-	&&	^
			*/

// Affiche les bordures TOP BOT, Ensuite LEFT RIGHT
void Ev_Dr_Map_Borders_1()
{
	static int numCharsTot;		// Le nombre de char à draw ou erase au total 
	static int numCharsDrawn;	// Le nombre de char drawn
	static char sym;
	static int right, up, left, down; 	/* Les limites*/
	static Coord crd;
	if (!ev_DrawMap1.Is_Active())
	{
		numCharsTot = map.Get_Height() * 2 + map.Get_Length() * 2;

		if (erase)
			sym = TXT_CONST.SPACE;

		/* Les limites*/
		right = map.Get_Box_Limit(RIGHT) + 1;
		up = map.Get_Box_Limit(UP) - 1;
		left = map.Get_Box_Limit(LEFT) - 1;
		down = map.Get_Box_Limit(DOWN) + 1;
		crd = { left + 1, up };

		if (erase)
			crd.x--;	// Erase le premier coin d'abord


		ev_DrawMap1.Activate();
		ev_DrawMap1.Start(0, 0);
		ev_DrawMap1.delay.Start_Timer(drSpeed, numCharsTot,true);
	}
	else
	{
		while (ev_DrawMap1.delay.Tick())
		{
			if (crd.y == up && crd.x < right) 			// BORDURE TOP	-> coin gauche vers la droite
			{
				if (!erase)
					sym = 196;

				ConsoleRender::Add_Char(crd, sym);
				crd.x++;
			}
			else
				if (crd.x == right && crd.y < down)	// BORDURE RIGHT-> coin up vers down
				{
					if (!erase)
						if (crd.y == up)	 // TOP-RIGHT CORNER
							sym = 191;
						else
							sym = 179;


					ConsoleRender::Add_Char(crd, sym);
					crd.y++;
				}
				else
					if (crd.y == down && crd.x > left)	// BORDURE RIGHT-> coin right vers left
					{
						if (!erase)
							if (crd.x == right)	 // BOTTOM-RIGHT CORNER
								sym = 217;
							else
								sym = 196;

						ConsoleRender::Add_Char(crd, sym);
						crd.x--;
					}
					else
						if (crd.x == left && crd.y > up)	// BORDURE LEFT-> coin down vers up
						{
							if (crd.y == 8)
								int coord = 2  +3;
							if (!erase)
							{
							
								if (crd.y == down)	 // BOTTOM-LEFT CORNER
									sym = 192;
								else
									sym = 179;
							}

							ConsoleRender::Add_Char(crd, sym);
							crd.y--;

							// Le dernier output sera affiché instant pour couvrir un bug logique de paresse
							if (crd.y == up)	 // TOP-LEFT CORNER
							{


								if (erase)
									gBorderShown = false;
								else
								{
									sym = 218;
									gBorderShown = true;	// we see them borders now
								}

								ConsoleRender::Add_Char(crd, sym);
								ev_DrawMap1.Cancel();	// Désactive l'event ici
								return;
							}
						}
		}
	}
}

void Set_Dr_Map_1(int speed, bool er)
{
	drSpeed = speed;
	erase = er;
	Ev_Dr_Map_Borders_1();
}



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
		crd = { map.Get_Box_Limit(LEFT), map.Get_Box_Limit(UP) - 1 };
		for (int i = crd.x; i <= map.Get_Box_Limit(RIGHT); i++)
		{
			ConsoleRender::Add_Char(crd, sym, BRIGHT_WHITE);
			crd.x++;
		}
		break;

	case RIGHT:
		crd = { map.Get_Box_Limit(RIGHT) + 1, map.Get_Box_Limit(UP) /*- 2*/ };
		for (int i = crd.y; i <= map.Get_Box_Limit(DOWN); i++)
		{
			ConsoleRender::Add_Char(crd, sym, BRIGHT_WHITE);
			crd.y++;
		}
		break;

	case DOWN:
		crd = { map.Get_Box_Limit(RIGHT), map.Get_Box_Limit(DOWN) + 1 };
		for (int i = crd.x; i >= map.Get_Box_Limit(LEFT); i--)
		{
			ConsoleRender::Add_Char(crd, sym, BRIGHT_WHITE);
			crd.x--;
		}
		break;

	case LEFT:
		crd = { map.Get_Box_Limit(LEFT) - 1, map.Get_Box_Limit(DOWN) };
		for (int i = --crd.y; i >= map.Get_Box_Limit(UP); i--)
		{
			ConsoleRender::Add_Char(crd, sym, BRIGHT_WHITE);
			crd.y--;
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
	crd = { left, up - 1 };

	for (int i = crd.x; i <= right; i++)
	{
		ConsoleRender::Add_Char(crd, 196, BRIGHT_WHITE);
		crd.x++;
	}
	ConsoleRender::Add_Char(crd, (unsigned char)191, BRIGHT_WHITE);	// TOP-RIGHT CORNER

	// BORDURE RIGHT-> coin up vers down

	for (int i = ++crd.y; i <= down; i++)
	{
		ConsoleRender::Add_Char(crd, 179, BRIGHT_WHITE);
		crd.y++;
	}
	ConsoleRender::Add_Char(crd, (unsigned char)217, BRIGHT_WHITE);	// BOT-RIGHT CORNER
	//::Stop_Queue();

	// BORDURE BOT	-> coin droit vers la gauche
	crd = { right , down + 1 };

	for (int i = crd.x; i >= left; i--)
	{
		ConsoleRender::Add_Char(crd, 196, BRIGHT_WHITE);
		crd.x--;
	}
	ConsoleRender::Add_Char(crd, (unsigned char)192, BRIGHT_WHITE);	// BOT-LEFT CORNER

	// BORDURE left-> coin geauche-bas vers up

	for (int i = --crd.y; i >= up; i--)
	{
		ConsoleRender::Add_Char(crd, 179, BRIGHT_WHITE);
		crd.y--;
	}
	ConsoleRender::Add_Char(crd, (unsigned char)218, BRIGHT_WHITE);	// TOP-LEFT CORNER
}