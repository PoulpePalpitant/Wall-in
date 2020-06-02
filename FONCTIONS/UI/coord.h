#pragma once

#include "console(v1.9).h"
#include "polarisation.h"
#include "direction.h"
#include "axis.h"

using Distance = int;	// Les distances

struct Coord { int x; int y; };	// Coordonn�e xy dans la console windows

class CoordIncrementor {	// Pour une position XY mobile, qui se d�place sur un axe
public:
	Coord coord;			// La coordonn�e en xy ou en Col/row
	Polarization polar;		// La polarisation positive ou n�gative du d�placement. +1 (pos) = Droite/Bas : -1 (neg) = Left/haut
	int* axis;				// Le pointeur vers l'axe � incr�menter

	void Initialize_All(Coord crd, Direction dir);	// Initialize tout 
	void Initialize_Axis(Direction direction);		// Initialise une position			
	void Initialize_Axis(Axis ax);				// Initialise un Axe			
	void Increment_Coord();							// Incr�mente une position [col][row] dans le grid	-Forward!
	void Decrement_Coord();							// D�cr�mente une position [col][row] dans le grid	-BackWard!

	void operator = (const CoordIncrementor& crd) {	// Peremet d'�galiser deux objets comme �a
		coord = crd.coord;
		polar = crd.polar;

		if (crd.axis == &crd.coord.x)	// Faut changer l'adresse du pointeur 
			axis = &coord.x;
		else
			axis = &coord.y;
	}
};

bool Is_Equal(Coord crd1, Coord crd2);				// V�rification d'une �galit� entre deux coordonn�es XY
void Equal_Coordinates(Coord &from, Coord to);					// Cr�er une �galit� entre deux coordonn�es XY

