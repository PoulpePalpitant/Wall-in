#include <iostream>
#include <mutex>

#include "basic_output.h"
#include "dsp_string.h"
#include "dsp_char.h"

// AFFICHE UNE STRING SELON UNE VITESSE ET UNE COULEUR
void UI_Dsp_String(Coord crd, std::string txt, Colors clr, time_t time)
{
	static std::mutex mu;			// Va locker UNIQUEMENT cette fonction

	static int size;	// Longueur de la string
	static int loop;	// Variable de loop

	mu.lock();
	size = (int)txt.length();	// Assignation de la longueur de la string 
	
	//AFFICHE LA STRING EN V�RIFIANT LA COULEUR � CHAQUE FOIS, ET EN REPOSITIONNANT DEUX FOIS LE CURSEUR >:(		(quand m�me mieux que d'avoir des erreurs d'affichage � cause des race conditions!!!!)
	for ( loop = 0; loop < size; loop++)
	{		 
		//	T'es mieux d'utiliser qu'une seule fonction d'affichage. *done*
		
		UI_Dsp_Char(crd, txt[loop], clr, time);
		crd.x++;	// Incr�mente x pour le prochain charact�re	


		//gotoxy(crd.x + loop, crd.y);	// Position de d�part
		//	
		//if (Get_Current_Color() != clr)	// Check si on a toujours la bonne couleur
		//	Change_Color(clr);			// Changement de couleur

		//Basic_Output();		// Affiche chaque char de la string, 1 � 1
		//Sleep((int)time);				// Temps d'attente avant le prochain output

	}
	mu.unlock();
}

////  CECI AFFICHE LA STRING D'UNE SHOT

//gotoxy(crd.x, crd.y);	// Position de d�part
//if (Get_Current_Color() != clr)	// Check si on a toujours la bonne couleur
//	Change_Color(clr);			// Changement de couleur

//std::cout << txt;	// Affiche le txt
