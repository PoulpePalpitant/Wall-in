
#include "../bot.h"

// Initialise la distance qui sépare chacun des walls que le Bot va devoir traverser dans son épopée
void Bot::Init_Dist_Btw_Walls()																	
{
	switch (dir)
	{
	case UP:
	case DOWN: btwWalls = DELTA_Y; break;
	case LEFT:
	case RIGHT: btwWalls = DELTA_X; break;
	}

}