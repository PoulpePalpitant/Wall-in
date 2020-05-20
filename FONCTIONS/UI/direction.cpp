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
