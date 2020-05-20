
#include "link.h"
#include "../grid/grid.h"


// La position x et y du Link dans la console, par rapport à son propre LinkGrid
void Link::Set_LinkXY(int col, int row)
{
	this->coord.x = START_X + DELTA_X * col;			
	this->coord.y = START_Y + DELTA_Y * row;
}