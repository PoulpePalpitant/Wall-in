#pragma once


#include "../UI/polarisation.h"
#include "grid.h"

class GridIndexIncrementor {	// Permet d'incrémenter une pair d'index [col][row] facilement
	
public:
	GrdCoord index;				// La coordonnée en Col/row
	Polarization polar;			// La polarisation positive ou négative du déplacement. +1 (pos) = Droite/Bas : -1 (neg) = Left/haut
	int* axis;					// Le pointeur vers l'axe à incrémenter
	
	void Initialize_All(GrdCoord crd, Direction dir);
	void Initialize_Axis(Direction direction);
	void Increment_Coord();						
	void Decrement_Coord();						


	// Cette façon de faire est quand même dangerous. J'ai appris à mes dépens que les pointeur et l'opérateur '=' sont sources de bugs assez insidieux
	void operator = (const GridIndexIncrementor& crd) {
		index = crd.index;
		polar = crd.polar;

		if (crd.axis == &crd.index.c)	// Faut changer l'adresse du pointeur 
			axis = &(index.c);
		else
			axis = &(index.r);
	}
	

};
