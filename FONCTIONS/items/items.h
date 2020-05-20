#pragma once

#include "../grid/grid.h"
#include "../UI/txtstyle.h"


class Items {

private:

	/*
		IDEAS:
		Chaque Objet items aurait un impact unique sur le jeu. Je devrais cr�er donc un classe diff�rente pour chacuns si jamais j'en fais
		Un Item pourrait appara�tre randomly sur le grid en utilisant un random position generator et un random item generator			
		Une fois apparu, un item pourrait avoir une dur�e de vie limit�. Le joueur devra donc se d�p�cher pour le ramasser				requesite: item timer
		Pour ramasser l'item, le joueur pourrait se d�placer par dessus, ou simplement tirer dessus
		Une fois ramass� l'item pourrait avoir un Effet Limit�, ou permanent? (permanent serait int�ressant) L'effet pourrait m�me rest� si le joueur quitte le jeu		Why?: Les actions ont des cons�quences? Pas tellement un them du jeu, sauf si j'instaure une narrative avec des choix
		
		ID�ES D'ITEMS:
		- Health
		- Shooting speed
		- Pause

		Id�es Out There: 
		Si je fais un jeu punitifs, les items pourrait �tre des debuffs?  : Difficile � faire comprendre au joueur MM kinda bad
	*/																																	

	// UI
	Colors clr = Colors::LIGHT_GREEN;		// Sa couleur
	char sym;								// Le symbole le repr�sentant 

	// POSITION
	GrdCoord grdCrd;						// On utilise le syst�me de coordonn�es des grids pour changer la position du joueur

public:
	// GETS
	char Get_Sym() { return sym; }				// Le symbole pour l'affichage
	GrdCoord Get_Grd_Coord() { return grdCrd; }	// Sa position dans le grid

	// SETS
	void Set_Position(GrdCoord newPos) { grdCrd = newPos; }			// Change sa position sur le Grid
	void Set_Sym(char newSym) { sym = newSym; }						// Change le symbole 
	void Set_Color(Colors newColor) { clr = newColor; }				// Change la couleur 

	// UPDATES


};


