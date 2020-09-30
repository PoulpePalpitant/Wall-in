
#include "../UI/map.h"
#include "../UI/console_output/render_list.h"

#include "UI_draw_map.h"

// Affiche les bordures TOP BOT, Ensuite LEFT RIGHT
void UI_Draw_Map_Borders_1()
{
	Coord crd;	// oh yeah
	int length = map.Get_Length();
	int height = map.Get_Height();
	int speedFix = 350;


	// BORDURE TOP	-> coin gauche vers la droite
	crd = { map.Get_Box_Limit(LEFT) - 1 , map.Get_Box_Limit(UP) - 1 };
	ConsoleRender::Create_Animation_Queue(200 + speedFix);

	for (int i = crd.x; i < length; i++)
	{
		ConsoleRender::Add_Char(crd, 179, BRIGHT_WHITE);
		crd.x++;
	}

	ConsoleRender::Add_Char(crd, (unsigned char)191, BRIGHT_WHITE);	// TOP-RIGHT CORNER
	ConsoleRender::Stop_Queue();


	// BORDURE BOT	-> coin droit vers la gauche
	crd = { map.Get_Box_Limit(RIGHT) + 1 , map.Get_Box_Limit(DOWN) + 1 };
	ConsoleRender::Create_Animation_Queue(200 + speedFix);

	for (int i = crd.x; i < length; i++)
	{
		ConsoleRender::Add_Char(crd, 179, BRIGHT_WHITE);
		crd.x--;
	}
	ConsoleRender::Add_Char(crd, (unsigned char)192, BRIGHT_WHITE);	// BOT-LEFT CORNER
	ConsoleRender::Stop_Queue();


	// BORDURE left-> coin geauche-bas vers up
	crd = { map.Get_Box_Limit(LEFT) - 1 , map.Get_Box_Limit(DOWN) + 1 };
	ConsoleRender::Create_Animation_Queue(200 + speedFix);

	for (int i = crd.x; i < height; i++)
	{
		ConsoleRender::Add_Char(crd, 196, BRIGHT_WHITE);
		crd.y--;
	}
	ConsoleRender::Add_Char(crd, (unsigned char)218, BRIGHT_WHITE);	// TOP-LEFT CORNER
	ConsoleRender::Stop_Queue();


	// BORDURE RIGHT-> coin up vers down
	crd = { map.Get_Box_Limit(RIGHT) + 1 , map.Get_Box_Limit(UP) + 1 };
	ConsoleRender::Create_Animation_Queue(200);

	for (int i = crd.x; i < height; i++)
	{
		ConsoleRender::Add_Char(crd, 196, BRIGHT_WHITE);
		crd.y--;
	}
	ConsoleRender::Add_Char(crd, (unsigned char)217, BRIGHT_WHITE);	// BOT-RIGHT CORNER
	ConsoleRender::Stop_Queue();
}


void UI_Erase_Map_Borders_1()
{

}
// Affiche chaque borders a partir du milieu
void UI_Draw_Map_Borders_2()
{
}
void UI_Erase_Map_Borders_2()
{
}
// Affiche somehow somethign else
void UI_Draw_Map_Borders_3()
{
}
void UI_Erase_Map_Borders_3()
{
}