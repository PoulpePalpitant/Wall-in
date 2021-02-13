

#include "basic_output.h"
#include "dsp_char.h"



// Affiche un char à une certaine position dans la console, selon une couleur.
// Pour effacer un char à une position. Remplace le SYM par un charactère vide , soit Txt_Const.SPACE ' ' 

 void UI_Dsp_Char(Coord crd, char sym, Colors clr)
{
	gotoxy(crd.x, crd.y);			// Positionnement du curseur
	
	if(Get_Current_Color() != clr)	// Check si on a déjà la bonne couleur
		Change_Color(clr);			
	
	Basic_Output(sym);				// Affichage du char
}
