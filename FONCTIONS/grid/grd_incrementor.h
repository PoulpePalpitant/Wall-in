#pragma once


#include "../UI/polarisation.h"
#include "grid.h"

class GridIndexIncrementor {	// Permet d'incr�menter une pair d'index [col][row] facilement
	
public:
	GrdCoord index;				// La coordonn�e en Col/row
	Polarization polar;			// La polarisation positive ou n�gative du d�placement. +1 (pos) = Droite/Bas : -1 (neg) = Left/haut
	int* axis;					// Le pointeur vers l'axe � incr�menter
	
	void Initialize_All(GrdCoord crd, Direction dir);
	void Initialize_Axis(Direction direction);
	void Increment_Coord();						
	void Decrement_Coord();						


	// Cette fa�on de faire est quand m�me dangerous. J'ai appris � mes d�pens que les pointeur et l'op�rateur '=' sont sources de bugs assez insidieux
	void operator = (const GridIndexIncrementor& crd) {
		index = crd.index;
		polar = crd.polar;

		if (crd.axis == &crd.index.c)	// Faut changer l'adresse du pointeur 
			axis = &(index.c);
		else
			axis = &(index.r);
	}
	

};
