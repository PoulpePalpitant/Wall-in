
#include "../grid/AllGrids.h"
#include "../UI/console_output/render_list.h"
#include "UI_invalid_move.h"

// DEVRAIT �TRE UN EVENT


void UI_Invalide_Move(Player& player, GrdCoord &grd)
{
	Coord crd = linkGrid->link[grd.c][grd.r].Get_XY();	// Position XY , // unstatic 
	char sym = player.Get_Sym();

	ConsoleRender::Add_Char_To_Render_List(crd, sym, LIGHT_PURPLE);		// Premier affichage est tjrs instantann�!	// Le player va flash pendant une fraction de seconde pour montrer qu'il ne peut se d�placer
	
	// Faudrait time_out le joueur un ti peu pour lui montrer qui peut pas se d�placer l�
	player.Set_Timeout(300);
	
}
