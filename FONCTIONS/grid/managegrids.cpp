
#include "../UI/map.h"
#include "managegrids.h"


// Génère les Grids pour la première fois
void Create_All_Grids(AllGrids& grid, int col, int row)
{
	grid.linkGrd.Create(col, row);	// Initialisation du Grid principal du jeu: le LinkGrid
	map.Resize(grid.linkGrd);		// Les dimensions de la map en x et y sont updatés .	** SpawnGrid en a besoin pour s'initialiser**
	grid.wallGrdHor.Create(grid.linkGrd);	// Initialisation du grid des Walls horizontaux
	grid.wallGrdVer.Create(grid.linkGrd);	// Initialisation du grid des Walls verticaux
	grid.spawnGrd.Create(grid.linkGrd);	// Initialisation du Grid de bordures de spawns Up down Left Right
}

// Resize les grids
void Resize_All_Grids(AllGrids& grid, int col, int row)
{
	grid.linkGrd.Resize(col, row);	// Initialisation du Grid principal du jeu: le LinkGrid
	map.Resize(grid.linkGrd);		// Les dimensions de la map en x et y sont updatés .	** SpawnGrid en a besoin pour s'initialiser**
	grid.wallGrdHor.Resize(grid.linkGrd);	// Ré-Initialisation du grid des Walls horizontaux		c'était à "create" avant, dois vérifier si je faisais une memory leak
	grid.wallGrdVer.Resize(grid.linkGrd);	// Ré-Initialisation du grid des Walls verticaux
	grid.spawnGrd.Resize(grid.linkGrd);	// Ré-Initialisation du Grid de bordures de spawns Up down Left Right

	// Resize Window to map?
}


void Resize_Grids_To_Level(AllGrids& grid, int lvl) {	
	
	int col = 13, row = 15;	// dimension par défaut au premier niveau

	switch (lvl)
	{
	case 0:	Create_All_Grids(grid, col, row);	break;		// UNE SEULE CRÉATION
	case 1:	Resize_All_Grids(grid, col, row);	break;
	case 2:	Resize_All_Grids(grid, col, row);	break;
	case 3:	Resize_All_Grids(grid, col, row);	break;
	case 4:	Resize_All_Grids(grid, col, row);	break;
	case 5:	Resize_All_Grids(grid, col, row);	break;
	case 6:	Resize_All_Grids(grid, col, row);	break;
	case 7:	Resize_All_Grids(grid, col, row);	break;
	}
	
}