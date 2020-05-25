#include <iostream>

#include "basic_output.h"
#include "dsp_string.h"
#include "dsp_char.h"

// AFFICHE UNE STRING SELON UNE VITESSE ET UNE COULEUR
void UI_Dsp_String(Coord crd, std::string txt, Colors clr, time_t time)
{
	static int size;	// Longueur de la string
	static int loop;	// Variable de loop

	size = (int)txt.length();	// Assignation de la longueur de la string 

	//AFFICHE LA STRING EN VÉRIFIANT LA COULEUR À CHAQUE FOIS, ET EN REPOSITIONNANT DEUX FOIS LE CURSEUR >:(		(quand même mieux que d'avoir des erreurs d'affichage à cause des race conditions!!!!)
	for ( loop = 0; loop < size; loop++)
	{		 
		//	T'es mieux d'utiliser qu'une seule fonction d'affichage. *done*
		
		crd.x++;	// Incrémente x pour le prochain charactère	
		UI_Dsp_Char(crd, txt[loop], clr, time);


		//gotoxy(crd.x + loop, crd.y);	// Position de départ
		//	
		//if (Get_Current_Color() != clr)	// Check si on a toujours la bonne couleur
		//	Change_Color(clr);			// Changement de couleur

		//Basic_Output();		// Affiche chaque char de la string, 1 à 1
		//Sleep((int)time);				// Temps d'attente avant le prochain output

	}
}

////  CECI AFFICHE LA STRING D'UNE SHOT

//gotoxy(crd.x, crd.y);	// Position de départ
//if (Get_Current_Color() != clr)	// Check si on a toujours la bonne couleur
//	Change_Color(clr);			// Changement de couleur

//std::cout << txt;	// Affiche le txt
