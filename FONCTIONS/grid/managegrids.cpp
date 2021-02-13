
#include "../UI/map.h"
#include "managegrids.h"
#include "../events/msg_dispatcher.h"
#include "../console/sweet_cmd_console.h"
#include "../structure_manager/modify_chain.h"
#include "../events/global_events/ev_resize_from_grids.h"

// Génère les Grids pour la première fois
void Create_All_Grids(AllGrids& grid, int col, int row)
{
	grid.linkGrd.Create(col, row);	// Initialisation du Grid principal du jeu: le LinkGrid
	map.Resize(grid.linkGrd);		// Les dimensions de la map en x et y sont updatés .	** SpawnGrid en a besoin pour s'initialiser**
	grid.wallGrdHor.Create(grid.linkGrd);	
	grid.wallGrdVer.Create(grid.linkGrd);	
	grid.spawnGrd.Create(grid.linkGrd);		
	grid.areCreated = true;
}

// Resize les grids
void Resize_All_Grids(AllGrids& grid, int col, int row)
{
	grid.linkGrd.Resize(col, row);	
	map.Resize(grid.linkGrd);		
	grid.wallGrdHor.Resize(grid.linkGrd);	
	grid.wallGrdVer.Resize(grid.linkGrd);	
	grid.spawnGrd.Resize(grid.linkGrd);		
}


bool Resize_Grids_To_Level(AllGrids& grid, int lvl, bool finalPuzzle) {
	
	// NE JAMAIS resizer le grid quand tu fais encore des affichages des links et de walls and stuff
	if (!DrawWalls::Is_Empty() || !ListsOfChainToModify::Is_Empty())
		return false;

	int col = 14, row = 14;	
	
	int gridLength;
	int gridHeight;

	switch (lvl)
	{
	case 0:	col = 14, row = 14;	break;		
	case 1:	col = 13, row = 15;	break; 
	case 2: col = 13, row = 15; break;	
	case 3:	col = 27, row = 15;	break;
	}


	gridLength = DELTA_X * col;
	START_X = (gConWidth - gridLength) / 2;
	gridHeight = DELTA_Y * row;
	START_Y = (gConHeight - gridHeight + 6) / 2 ;

	if (grid.areCreated)
		Resize_All_Grids(grid, col, row); // UNE SEULE CRÉATION
	else
		Create_All_Grids(grid, col, row);

	Ev_Resize_From_Grids();
	return true;
}
