
#include <iostream>
#include <mutex>

#include "basic_output.h"
#include "dsp_char.h"



// Affiche un char � une certaine position dans la console, selon une couleur.
// Pour effacer un char � une position. Remplace le SYM par un charact�re vide , soit Txt_Const.SPACE ' ' 

 void UI_Dsp_Char(Coord crd, char sym, Colors clr)
{
	//static std::mutex mu;			// Va permettre de blocker tout les autres fonctions qui essaient d'afficher du texte dans la console			/**/ remove

	//mu.lock();						// V�rrouille cette region. Personne n'a le droit de changer la position du curseur ou la couleur temps qu'on a pas fini d'afficher ce qu'on voulait!
	gotoxy(crd.x, crd.y);			// Positionnement du curseur
	
	if(Get_Current_Color() != clr)	// Check si on a d�j� la bonne couleur
		Change_Color(clr);			// Changement de couleur
	
	Basic_Output(sym);				// Affichage du char
	//mu.unlock();					// D�v�rouille.

}
