
#include "../grid/AllGrids.h"
#include "../UI/console_output/dsp_char.h"
#include "UI_invalid_move.h"


void UI_Invalide_Move(Player& player, GrdCoord &grd)
{
	Coord crd = linkGrid->link[grd.c][grd.r].Get_XY();	// Position XY , // unstatic 
	char sym = player.Get_Sym();

	UI_Dsp_Char(crd, sym, LIGHT_PURPLE);	// Le player va flash pendant une fraction de seconde pour montrer qu'il ne peut se déplacer
	Sleep(90);
	UI_Dsp_Char(crd, sym, player.Get_Clr());// Réaffiche le joueur
}
