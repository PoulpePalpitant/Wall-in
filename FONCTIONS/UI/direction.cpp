#pragma once

#include "direction.h"




// Trouve la direction opposée d'une direction
// ---------------------------

Direction Find_Opposite_Dir(Direction direction)	
{
	switch (direction)
	{
	case UP: direction = DOWN;
		break;
	case LEFT: direction = RIGHT;
		break;
	case DOWN: direction = UP;
		break;
	case RIGHT: direction = LEFT;
		break;
	}
	return direction;

	
}

Direction Create_Direction(Axis ax, Polarization plr) // transforme un Axe et une polarisation en une direction
{
	Direction dir;
	if (ax == HOR)
	{
		if (plr == POS)
			dir = RIGHT;
		else
			dir = LEFT;
	}
	else
	{
		if (plr == POS)
			dir = DOWN;
		else
			dir = UP;
	}

	return dir;
}

bool Is_Same_Direction(Direction dir, Axis ax, Polarization plr)	// Compare une direction avec un Axe et une Polarization
{
	Direction dir2 = Create_Direction(ax, plr);
	
	if (dir == dir2)
		return true;
	else
		return false;
}