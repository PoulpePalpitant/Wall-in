#pragma once


#include "../UI/polarisation.h"

#include "grid.h"

class GridIndexIncrementor {	// Permet d'incrémenter une pair d'index [col][row] facilement
	
public:
	GrdCoord index;				// La coordonnée en xy ou en Col/row
	Polarization polar;			// La polarisation positive ou négative du déplacement. +1 (pos) = Droite/Bas : -1 (neg) = Left/haut
	int* axis;					// Le pointeur vers l'axe à incrémenter
	
	void Initialize(GrdCoord crd, Direction dir);	// Initialize tout 
	void Init_Axis_Incrementor(Direction direction);// Initialise une position			
	void Increment_Coord();							// Incrémente une position [col][row] dans le grid	-Forward!
	void Décrement_Coord();							// Décrémente une position [col][row] dans le grid	-BackWard!

	// Le = est déjà overloadé :( no practice for you

};
