
#include "../grid/AllGrids.h"
#include "../UI/console_output/render_list.h"



#include "UI_move_player.h"



// Affiche le joueur
void UI_Move_Player( Player& player,const GrdCoord &erase, const GrdCoord &draw)
{
	static Coord crdErase, crdDraw;
	crdErase = linkGrid->link[erase.c][erase.r].Get_XY();	// Position XY
	crdDraw = linkGrid->link[draw.c][draw.r].Get_XY();		// Position XY
	

	if (linkGrid->link[erase.c][erase.r].Get_State() == LinkState::FREE)	
		linkGrid->link[erase.c][erase.r].Dsp_Link();	// Quand le joueur se trouve sur un Link Free, il faut réafficher son symbol dès que le joueur ne s'y trouve plus
	else
		ConsoleRender::Add_Char(crdErase, TXT_CONST.SPACE);	// Erase

	ConsoleRender::Add_Char(crdDraw, player.Get_Sym(), player.Get_Clr());	// draw
}