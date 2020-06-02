#pragma once

#include "console(v1.9).h"
#include "polarisation.h"
#include "direction.h"
#include "axis.h"

using Distance = int;	// Les distances

struct Coord { int x; int y; };	// Coordonnée xy dans la console windows

class CoordIncrementor {	// Pour une position XY mobile, qui se déplace sur un axe
public:
	Coord coord;			// La coordonnée en xy ou en Col/row
	Polarization polar;		// La polarisation positive ou négative du déplacement. +1 (pos) = Droite/Bas : -1 (neg) = Left/haut
	int* axis;				// Le pointeur vers l'axe à incrémenter

	void Initialize_All(Coord crd, Direction dir);	// Initialize tout 
	void Initialize_Axis(Direction direction);		// Initialise une position			
	void Initialize_Axis(Axis ax);				// Initialise un Axe			
	void Increment_Coord();							// Incrémente une position [col][row] dans le grid	-Forward!
	void Decrement_Coord();							// Décrémente une position [col][row] dans le grid	-BackWard!

	void operator = (const CoordIncrementor& crd) {	// Peremet d'égaliser deux objets comme ça
		coord = crd.coord;
		polar = crd.polar;

		if (crd.axis == &crd.coord.x)	// Faut changer l'adresse du pointeur 
			axis = &coord.x;
		else
			axis = &coord.y;
	}
};

bool Is_Equal(Coord crd1, Coord crd2);				// Vérification d'une égalité entre deux coordonnées XY
void Equal_Coordinates(Coord &from, Coord to);					// Créer une égalité entre deux coordonnées XY

