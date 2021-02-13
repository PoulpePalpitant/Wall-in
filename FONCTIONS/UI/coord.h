#pragma once

#include "console(v1.9).h"
#include "polarisation.h"
#include "direction.h"
#include "axis.h"

using Distance = int;

struct Coord { int x; int y; };	
struct FCoord { float x; float y; };	// Coordonn�e xy dans la console windows en float

class CoordIncrementor {	// Pour une position XY mobile, qui se d�place sur un axe
public:
	Coord coord;			// La coordonn�e en xy ou en Col/row
	Polarization polar;		// La polarisation positive ou n�gative du d�placement. +1 (pos) = Droite/Bas : -1 (neg) = Left/haut
	int* axis;				// Le pointeur vers l'axe � incr�menter

	void Initialize_All(Coord crd, Direction dir);	
	void Initialize_Axis(Direction direction);		
	void Initialize_Axis(Axis ax);					
	void Increment_Coord();							
	void Decrement_Coord();							

	void operator = (const CoordIncrementor& crd) {	
		coord = crd.coord;
		polar = crd.polar;

		if (crd.axis == &crd.coord.x)	// Faut changer l'adresse du pointeur 
			axis = &coord.x;
		else
			axis = &coord.y;
	}
};

bool Are_Equal(Coord crd1, Coord crd2);				
void Equal_Coordinates(Coord &from, Coord to);		


