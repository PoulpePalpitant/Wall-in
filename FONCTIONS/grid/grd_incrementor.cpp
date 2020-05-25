
#include "grd_incrementor.h"

// Initialise l'incr�menteur de position de grid � une une position de grid
void GridIndexIncrementor::Initialize(GrdCoord crd, Direction dir)	// Initialize tout 
{
	this->Init_Axis_Incrementor(dir);		
	Equal_Coordinates(this->index, crd);	// Permet d'�galiser deux valeurs de coordonn�es de grid [col][row]
}

// Initialise un CoordIncrementor � partir d'une direction d'incr�mentation
 void GridIndexIncrementor::Init_Axis_Incrementor(Direction direction)
{
	switch (direction)
	{
	case UP:	this->axis = &this->index.r;	this->polar = NEG;break;	// L'incr�mentation se fera � la vertical, donc sur l'axe des Y, donc vers le haut avec une polarisation de  -1
	case LEFT:	this->axis = &this->index.c;	this->polar = NEG;break;
	case DOWN:	this->axis = &this->index.r;	this->polar = POS;break;
	case RIGHT: this->axis = &this->index.c;	this->polar = POS;break;
	}
}

// Augmente de 1 ou -1 une coordonn�e sur le grid des link (Col ou Row)
void GridIndexIncrementor::Increment_Coord()
{
	this->axis += this->polar;
}

// Augmente de 1 ou -1 une coordonn�e sur le grid des link (Col ou Row), mais dans la direction inverse de la polarisation	
void GridIndexIncrementor::D�crement_Coord()							// D�cr�mente une position [col][row] dans le grid	-BackWard!
{
	this->axis -= this->polar;
}

