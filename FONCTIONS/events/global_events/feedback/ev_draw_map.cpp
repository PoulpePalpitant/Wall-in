
#include "../../../UI/map.h"
#include "../../../UI/console_output/render_list.h"


#include "../../../lvls/lvl_script.h"
#include "../../msg_dispatcher.h"
#include "../../../player/player.h"
#include "ev_draw_map.h"
//#include "../../../animation/UI_draw_map.h"

#include "../../../lvls/lvl_1/msg_events/ev_waking_up.h"

static Event ev_DrawMap1(Ev_Dr_Map_Borders_1);	// das event

// Affiche les bordures TOP BOT, Ensuite LEFT RIGHT
void Ev_Dr_Map_Borders_1()
 {
	if (!ev_DrawMap1.Is_Ignored())
		if (!ev_DrawMap1.Is_Active())
		{
			if (P1.Get_XY().x == map.Get_Box_Limit(RIGHT))	// D�s que le joueur touche � la bordure droite, on affiche �a		
			{
				ev_DrawMap1.Activate();
				clrscr();	// fuck that screen
			}
		}
		else
		{
			static Coord crd;// crdBot, crdLeft, crdRight;	// oh yeah
			/* Les limites*/
			int right = map.Get_Box_Limit(RIGHT);
			int up = map.Get_Box_Limit(UP);
			int left = map.Get_Box_Limit(LEFT);
			int down = map.Get_Box_Limit(DOWN);


			/*
				Animation va comme suis. Top et bot par et vont en direction oppos�. Les deux atteignent un corner et on passe aux bordures left et right
				->	&&	v	synchro
				<-	&&	^
			*/


			// BORDURE TOP	-> coin gauche vers la droite
			crd = { left, up - 1 };
			//ConsoleRender::Create_Queue(150);

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
			//ConsoleRender::Create_Queue(150);
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
		//	ConsoleRender::Stop_Queue();

			ev_DrawMap1.Deactivate();	// Finis
			ev_DrawMap1.Ignore();
		}

	gBorderShown = true;	// we see them borders now
}

void Erase_Map_Borders_1(int speed)
{
	static Coord crd;// crdBot, crdLeft, crdRight;	// oh yeah
			/* Les limites*/
	int right = map.Get_Box_Limit(RIGHT);
	int up = map.Get_Box_Limit(UP);
	int left = map.Get_Box_Limit(LEFT);
	int down = map.Get_Box_Limit(DOWN);

	if (speed)
		ConsoleRender::Create_Queue(speed);
	
	// BORDURE TOP	-> coin gauche vers la droite
	crd = { left, up - 1 };

	for (int i = crd.x; i <= right; i++)
	{
		ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
		crd.x++;
	}
	ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// TOP-RIGHT CORNER

	// BORDURE RIGHT-> coin up vers down

	for (int i = ++crd.y; i <= down; i++)
	{
		ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
		crd.y++;
	}
	ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// BOT-RIGHT CORNER

	// BORDURE BOT	-> coin droit vers la gauche

	crd = { right , down + 1 };

	for (int i = crd.x; i >= left; i--)
	{
		ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
		crd.x--;
	}
	ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// BOT-LEFT CORNER

	// BORDURE left-> coin geauche-bas vers up

	for (int i = --crd.y; i >= up; i--)
	{
		ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);
		crd.y--;
	}
	ConsoleRender::Add_Char(crd, TXT_CONST.SPACE);	// TOP-LEFT CORNER

	if (speed)
		ConsoleRender::Stop_Queue();

	gBorderShown = false;
} // soon





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