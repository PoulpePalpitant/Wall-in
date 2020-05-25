
#include "grd_incrementor.h"

// Initialise l'incrémenteur de position de grid à une une position de grid
void GridIndexIncrementor::Initialize(GrdCoord crd, Direction dir)	// Initialize tout 
{
	this->Init_Axis_Incrementor(dir);		
	Equal_Coordinates(this->index, crd);	// Permet d'égaliser deux valeurs de coordonnées de grid [col][row]
}

// Initialise un CoordIncrementor à partir d'une direction d'incrémentation
 void GridIndexIncrementor::Init_Axis_Incrementor(Direction direction)
{
	switch (direction)
	{
	case UP:	this->axis = &this->index.r;	this->polar = NEG;break;	// L'incrémentation se fera à la vertical, donc sur l'axe des Y, donc vers le haut avec une polarisation de  -1
	case LEFT:	this->axis = &this->index.c;	this->polar = NEG;break;
	case DOWN:	this->axis = &this->index.r;	this->polar = POS;break;
	case RIGHT: this->axis = &this->index.c;	this->polar = POS;break;
	}
}

// Augmente de 1 ou -1 une coordonnée sur le grid des link (Col ou Row)
void GridIndexIncrementor::Increment_Coord()
{
	this->axis += this->polar;
}

// Augmente de 1 ou -1 une coordonnée sur le grid des link (Col ou Row), mais dans la direction inverse de la polarisation	
void GridIndexIncrementor::Décrement_Coord()							// Décrémente une position [col][row] dans le grid	-BackWard!
{
	this->axis -= this->polar;
}

