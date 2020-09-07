
#include "../UI/map.h"
#include "managegrids.h"
#include "../events/msg_dispatcher.h"
#include "../console/sweet_cmd_console.h"
#include "../structure_manager/modify_chain.h"

// G�n�re les Grids pour la premi�re fois
void Create_All_Grids(AllGrids& grid, int col, int row)
{
	grid.linkGrd.Create(col, row);	// Initialisation du Grid principal du jeu: le LinkGrid
	map.Resize(grid.linkGrd);		// Les dimensions de la map en x et y sont updat�s .	** SpawnGrid en a besoin pour s'initialiser**
	grid.wallGrdHor.Create(grid.linkGrd);	// Initialisation du grid des Walls horizontaux
	grid.wallGrdVer.Create(grid.linkGrd);	// Initialisation du grid des Walls verticaux
	grid.spawnGrd.Create(grid.linkGrd);	// Initialisation du Grid de bordures de spawns Up down Left Right
	grid.areCreated = true;
}

// Resize les grids
void Resize_All_Grids(AllGrids& grid, int col, int row)
{
	grid.linkGrd.Resize(col, row);	// Initialisation du Grid principal du jeu: le LinkGrid
	map.Resize(grid.linkGrd);		// Les dimensions de la map en x et y sont updat�s .	** SpawnGrid en a besoin pour s'initialiser**
	grid.wallGrdHor.Resize(grid.linkGrd);	// R�-Initialisation du grid des Walls horizontaux		c'�tait � "create" avant, dois v�rifier si je faisais une memory leak
	grid.wallGrdVer.Resize(grid.linkGrd);	// R�-Initialisation du grid des Walls verticaux
	grid.spawnGrd.Resize(grid.linkGrd);	// R�-Initialisation du Grid de bordures de spawns Up down Left Right
}


bool Resize_Grids_To_Level(AllGrids& grid, int lvl, int stage) {
	
	// NE JAMAIS resizer le grid quand tu fais encore des affichages des links et de walls and stuff
	if (!DrawWalls::Is_Empty() || !ListsOfChainToModify::Is_Empty())
		return false;

	int col = 14, row = 14;	// dimension par d�faut au premier niveau
	
	int gridLength; // pour calculer un start_x Centr�
	int gridHeight; // pour calculer un start_y Centr�


	switch (lvl)
	{
	case 0:	col = 14, row = 14;	break;		
	case 1:	col = 13, row = 15;	break; // col = 13	row = 15
	case 2:
		switch (stage)
		{
		default:	col = 13, row = 15; break;	// dimension du Level
		case 2:	col = 17, row = 5; break;		// dimension des training stages
		case 3:	col = 3, row = 3; break;	// c= 21 r= 3 V1 du tutorial #3	
		case 4:	col = 7, row = 14; break;		
		}
		break;

	case 3:
	col = 14, row = 15;	break;
	case 4:
	col = 14, row = 15;	break;
	case 5:
	col = 14, row = 15;	break;
	case 6:
	col = 14, row = 15;	break;
	case 7:
	col = 14, row = 15;	break;
	}

	gridLength = DELTA_X * col;
	START_X = (gConWidth - gridLength) / 2;
	gridHeight = DELTA_Y * row;
	START_Y = (gConHeight - gridHeight) / 2;

	if (grid.areCreated)
		Resize_All_Grids(grid, col, row); // UNE SEULE CR�ATION
	else
		Create_All_Grids(grid, col, row);

	MsgQueue::Register(GRIDS_RESIZED);
	return true;
}
