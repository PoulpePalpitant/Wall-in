#include <iostream>

#include "basic_output.h"
#include "dsp_string.h"
#include "dsp_char.h"

// AFFICHE UNE STRING SELON UNE VITESSE ET UNE COULEUR
void UI_Dsp_String(Coord crd, std::string txt, Colors clr, time_t time)
{
	static int size;	// Longueur de la string
	static int loop;	// Variable de loop

	size = txt.length();	// Assignation de la longueur de la string 

	//AFFICHE LA STRING EN VÉRIFIANT LA COULEUR À CHAQUE FOIS, ET EN REPOSITIONNANT DEUX FOIS LE CURSEUR >:(
	for ( loop = 0; loop < size; loop++)
	{		 
		gotoxy(crd.x + loop, crd.y);	// Position de départ
			
		if (Get_Current_Color() != clr)	// Check si on a toujours la bonne couleur
			Change_Color(clr);			// Changement de couleur

		Basic_Output(txt[loop]);		// Affiche chaque char de la string, 1 à 1
		Sleep(time);					// Temps d'attente avant le prochain output
	}
}

////  CECI AFFICHE LA STRING D'UNE SHOT

//gotoxy(crd.x, crd.y);	// Position de départ
//if (Get_Current_Color() != clr)	// Check si on a toujours la bonne couleur
//	Change_Color(clr);			// Changement de couleur

//std::cout << txt;	// Affiche le txt
