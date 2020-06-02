#pragma once


#include "../UI/polarisation.h"

#include "grid.h"

class GridIndexIncrementor {	// Permet d'incrémenter une pair d'index [col][row] facilement
	
public:
	GrdCoord index;				// La coordonnée en Col/row
	Polarization polar;			// La polarisation positive ou négative du déplacement. +1 (pos) = Droite/Bas : -1 (neg) = Left/haut
	int* axis;					// Le pointeur vers l'axe à incrémenter
	
	void Initialize_All(GrdCoord crd, Direction dir);	// Initialize tout 
	void Initialize_Axis(Direction direction);// Initialise une position			
	void Increment_Coord();							// Incrémente une position [col][row] dans le grid	-Forward!
	void Decrement_Coord();							// Décrémente une position [col][row] dans le grid	-BackWard!

	void operator = (const GridIndexIncrementor& crd) {	// Peremet d'égaliser deux objets comme ça
		index = crd.index;
		polar = crd.polar;

		if (crd.axis == &crd.index.c)	// Faut changer l'adresse du pointeur 
			axis = &index.c;
		else
			axis = &index.r;
	}
	

};
