
#include "grd_incrementor.h"

void GridIndexIncrementor::Initialize_All(GrdCoord crd, Direction dir)	
{
	this->Initialize_Axis(dir);		
	Equal_Coordinates(this->index, crd);	
}

 void GridIndexIncrementor::Initialize_Axis(Direction direction)
{
	switch (direction)
	{
	case UP:	this->axis = &this->index.r;	this->polar = NEG;break;	
	case LEFT:	this->axis = &this->index.c;	this->polar = NEG;break;
	case DOWN:	this->axis = &this->index.r;	this->polar = POS;break;
	case RIGHT: this->axis = &this->index.c;	this->polar = POS;break;
	}
}

void GridIndexIncrementor::Increment_Coord()
{
	*this->axis += this->polar;
}

void GridIndexIncrementor::Decrement_Coord()							
{
	*this->axis -= this->polar;
}

