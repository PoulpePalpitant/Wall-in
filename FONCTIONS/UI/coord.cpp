

#include "../grid/grid.h"
#include "coord.h"
#include "direction.h"

// Permet de comparer deux points ensemble. Si les deux ne sont pas �gals, return false
bool Is_Equal(Coord crd1, Coord crd2)
{
	if (crd1.x == crd2.x)
	{
		if (crd1.y == crd2.y)
			return true;// Les deux sont identiques
		else
			return false;
	}
	else
		return false;
}

// Cr�er une �galit� entre deux coordonn�es XY.		La premi�re sera �gale � la seconde
void Equal_Coordinates(Coord &from, Coord to)
{
	from.x = to.x;
	from.y = to.y;
}

// Augmente de 1 ou -1 une coordonn�e sur les X ou les Y!!
void CoordIncrementor::Increment_Coord()
{
	*axis += polar;
}

// Augmente de 1 ou -1 une coordonn�e sur le grid des link (Col ou Row), mais dans la direction inverse de la polarisation	
void CoordIncrementor::Decrement_Coord()							// D�cr�mente une position XY dans la Console	-BackWard!
{
	*this->axis -= this->polar;
}

// Initialise l'incr�menteur de position de grid � une une position de grid
void CoordIncrementor::Initialize_All(Coord crd, Direction dir)	// Initialize tout 
{
	this->Initialize_Axis(dir);
	Equal_Coordinates(this->coord, crd);	// Permet d'�galiser deux valeurs de coordonn�es de grid [col][row]
}

// Initialise un CoordIncrementor � partir d'une direction d'incr�mentation
void CoordIncrementor::Initialize_Axis(Direction direction)
{
	switch (direction)
	{
	case UP:	axis = &coord.y; polar = NEG;break;	// L'incr�mentation se fera � la vertical, donc sur l'axe des Y, donc vers le haut avec une polarisation de  -1
	case LEFT:	axis = &coord.x; polar = NEG;break;
	case DOWN:	axis = &coord.y; polar = POS;break;
	case RIGHT: axis = &coord.x; polar = POS;break;
	}
}

// Initialise le pointeur vers l'axe de d�placement � partir d'un Axe
void CoordIncrementor::Initialize_Axis(Axis ax)
{
	if (ax == HOR)
	{
		axis = &coord.x;
		axis = &coord.x;
	}
	else
	{
		axis = &coord.y;
		axis = &coord.y;
	}

}

