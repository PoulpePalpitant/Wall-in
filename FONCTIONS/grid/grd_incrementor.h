#pragma once


#include "../UI/polarisation.h"

#include "grid.h"

class GridIndexIncrementor {	// Permet d'incr�menter une pair d'index [col][row] facilement
	
public:
	GrdCoord index;				// La coordonn�e en xy ou en Col/row
	Polarization polar;			// La polarisation positive ou n�gative du d�placement. +1 (pos) = Droite/Bas : -1 (neg) = Left/haut
	int* axis;					// Le pointeur vers l'axe � incr�menter
	
	void Initialize(GrdCoord crd, Direction dir);	// Initialize tout 
	void Init_Axis_Incrementor(Direction direction);// Initialise une position			
	void Increment_Coord();							// Incr�mente une position [col][row] dans le grid	-Forward!
	void D�crement_Coord();							// D�cr�mente une position [col][row] dans le grid	-BackWard!

	// Le = est d�j� overload� :( no practice for you

};
