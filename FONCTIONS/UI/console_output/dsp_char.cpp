
#include <iostream>

#include "basic_output.h"
#include "dsp_char.h"


// Affiche un char à une certaine position dans la console, selon une couleur.

 void UI_Dsp_Char(Coord crd, char sym, Colors clr, time_t time)
{
	gotoxy(crd.x, crd.y);			// Positionnement du curseur
	
	if(Get_Current_Color() != clr)	// Check si on a déjà la bonne couleur
		Change_Color(clr);			// Changement de couleur
	
	Basic_Output(sym);				// Affichage du char
	Sleep(time);					// temps d'attente, si la fonction est utilisé en rafale
}
