
#include "../grid/AllGrids.h"
#include "../UI/console_output/render_list.h"
#include "UI_invalid_move.h"

// DEVRAIT ÊTRE UN EVENT


void UI_Invalide_Action()
{
	Coord crd = P1.Get_XY();	// Position XY , // unstatic 
	char sym = P1.Get_Sym();

	ConsoleRender::Add_Char(crd, sym, LIGHT_PURPLE);		// Premier affichage est tjrs instantanné!	// Le player va flash pendant une fraction de seconde pour montrer qu'il ne peut se déplacer
	
	// Faudrait time_out le joueur un ti peu pour lui montrer qui peut pas se déplacer là
	P1.Set_Timeout(300);
	
}
