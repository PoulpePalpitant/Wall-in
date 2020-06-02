#pragma once


#include "../UI/polarisation.h"

#include "grid.h"

class GridIndexIncrementor {	// Permet d'incr�menter une pair d'index [col][row] facilement
	
public:
	GrdCoord index;				// La coordonn�e en Col/row
	Polarization polar;			// La polarisation positive ou n�gative du d�placement. +1 (pos) = Droite/Bas : -1 (neg) = Left/haut
	int* axis;					// Le pointeur vers l'axe � incr�menter
	
	void Initialize_All(GrdCoord crd, Direction dir);	// Initialize tout 
	void Initialize_Axis(Direction direction);// Initialise une position			
	void Increment_Coord();							// Incr�mente une position [col][row] dans le grid	-Forward!
	void Decrement_Coord();							// D�cr�mente une position [col][row] dans le grid	-BackWard!

	void operator = (const GridIndexIncrementor& crd) {	// Peremet d'�galiser deux objets comme �a
		index = crd.index;
		polar = crd.polar;

		if (crd.axis == &crd.index.c)	// Faut changer l'adresse du pointeur 
			axis = &index.c;
		else
			axis = &index.r;
	}
	

};
