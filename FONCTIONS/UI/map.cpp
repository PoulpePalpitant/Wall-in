#include "console_output/render_list.h"
#include "map.h"


extern const Distance GAP_BTW_GRID = 2;	// Les Spawns se retrouvent 2 case plus loin que le grid de Links

extern bool gBorderShown = false;		// Les bordures de la map sont visibles

extern Map map = {};	

Distance Map::Get_Ctr_Y()
{
	return height / 2 + limit[UP];
}		

void Map::Resize(LinkGrid& linkGrid)	// Resize les dimensions selon la nouvelle dimension du Grid principal(LinkGrid)
{
	limit[LEFT] = START_X;	
	limit[RIGHT] = START_X + DELTA_X * (linkGrid.Get_Cols() - 1);
	length = limit[RIGHT] - limit[LEFT];	

	limit[UP] = START_Y;	
	limit[DOWN] = START_Y + DELTA_Y * (linkGrid.Get_Rows() - 1);
	height = limit[DOWN] - limit[UP];	
}

