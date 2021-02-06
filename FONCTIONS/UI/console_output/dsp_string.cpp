#include <iostream>
//#include <mutex>

#include "basic_output.h"
#include "dsp_string.h"
#include "dsp_char.h"


// CECI EST  OBSELETE


// AFFICHE UNE STRING SELON UNE VITESSE ET UNE COULEUR
void UI_Dsp_String(Coord crd, std::string txt, Colors clr, time_t time)
{
	//static std::mutex mu;			// Va locker UNIQUEMENT cette fonction

	static int size;	// Longueur de la string
	static int loop;	// Variable de loop

	//mu.lock();
	size = (int)txt.length();	// Assignation de la longueur de la string 
	
	//AFFICHE LA STRING EN V�RIFIANT LA COULEUR � CHAQUE FOIS, ET EN REPOSITIONNANT DEUX FOIS LE CURSEUR >:(		(quand m�me mieux que d'avoir des erreurs d'affichage � cause des race conditions!!!!)
	for ( loop = 0; loop < size; loop++)
	{		 
		UI_Dsp_Char(crd, txt[loop], clr);
		crd.x++;	// Incr�mente x pour le prochain charact�re	
	}
	//mu.unlock();
}

// CECI EST  OBSELETE
