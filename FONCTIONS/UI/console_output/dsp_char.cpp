
#include <iostream>
#include <mutex>

#include "basic_output.h"
#include "dsp_char.h"



// Affiche un char à une certaine position dans la console, selon une couleur.

 void UI_Dsp_Char(Coord crd, char sym, Colors clr, time_t time)
{
	static std::mutex mu;			// Va permettre de blocker tout les autres fonctions qui essaient d'afficher du texte dans la console

	mu.lock();						// Vérrouille cette region. Personne n'a le droit de changer la position du curseur ou la couleur temps qu'on a pas fini d'afficher ce qu'on voulait!
	gotoxy(crd.x, crd.y);			// Positionnement du curseur
	
	if(Get_Current_Color() != clr)	// Check si on a déjà la bonne couleur
		Change_Color(clr);			// Changement de couleur
	
	Basic_Output(sym);				// Affichage du char
	mu.unlock();					// Dévérouille.

	Sleep((int)time);				// temps d'attente, si la fonction est utilisé en rafale
	//unlock()
}
