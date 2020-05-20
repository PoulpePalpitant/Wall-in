
#include <iostream>
#include "dsp_int.h"


void UI_Dsp_Int(Coord crd, int nb, Colors clr, time_t time)	// affiche un int dans la console
{

	gotoxy(crd.x, crd.y);		// Positionnement du curseur

	if (Get_Current_Color() != clr)	// Check si on a déjà la bonne couleur
		Change_Color(clr);			// Changement de couleur

	std::cout << nb;				// Output!
	Sleep(time);					// temps d'attente
	

}