

#include "../grid/grid.h"
#include "coord.h"
#include "direction.h"

bool Are_Equal(Coord crd1, Coord crd2)
{
	if (crd1.x == crd2.x)
	{
		if (crd1.y == crd2.y)
			return true;
		else
			return false;
	}
	else
		return false;
}

void Equal_Coordinates(Coord &from, Coord to)
{
	from.x = to.x;
	from.y = to.y;
}

void CoordIncrementor::Increment_Coord()
{
	*axis += polar;
}

void CoordIncrementor::Decrement_Coord()							
{
	*this->axis -= this->polar;
}

void CoordIncrementor::Initialize_All(Coord crd, Direction dir)	
{
	this->Initialize_Axis(dir);
	Equal_Coordinates(this->coord, crd);	
}

void CoordIncrementor::Initialize_Axis(Direction direction)
{
	switch (direction)
	{
	case UP:	axis = &coord.y; polar = NEG;break;	
	case LEFT:	axis = &coord.x; polar = NEG;break;
	case DOWN:	axis = &coord.y; polar = POS;break;
	case RIGHT: axis = &coord.x; polar = POS;break;
	}
}

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
