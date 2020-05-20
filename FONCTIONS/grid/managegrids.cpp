
#include "managegrids.h"
#include "../UI/map.h"


// G�n�re les Grids pour la premi�re fois
void Create_All_Grids(LinkGrid &linkGrid, AllWallGrids& wallGrid, Spawn_Grid& spwnGrid, int col, int row)
{
	linkGrid.Create(col, row);	// Initialisation du Grid principal du jeu: le LinkGrid
	map.Resize(linkGrid);		// Les dimensions de la map en x et y sont updat�s .	** SpawnGrid en a besoin pour s'initialiser**
	wallGrid.hor->Create(linkGrid);	// Initialisation du grid des Walls horizontaux
	wallGrid.ver->Create(linkGrid);	// Initialisation du grid des Walls verticaux
	spwnGrid.Create(linkGrid);	// Initialisation du Grid de bordures de spawns Up down Left Right
	
}

// Resize les Grids une fois qu'ils ont tous �t� cr��s( ppour les niveaux suivant)
void Resize_All_Grids(LinkGrid& linkGrid, AllWallGrids& wallGrid, Spawn_Grid& spwnGrid, int col, int row)
{
	linkGrid.Resize(col, row);
	map.Resize(linkGrid);		// Les dimensions de la map en x et y sont updat�s .	** SpawnGrid en a besoin pour s'initialiser**
	wallGrid.hor->Create(linkGrid);	// R�-Initialisation du grid des Walls horizontaux
	wallGrid.ver->Create(linkGrid);	// R�-Initialisation du grid des Walls verticaux
	spwnGrid.Resize(linkGrid);	// R�-Initialisation du Grid de bordures de spawns Up down Left Right
}

void Resize_Grids_To_Level(LinkGrid& linkGrid, AllWallGrids& wallGrid, Spawn_Grid& spwnGrid, int lvl) {
	
	int col = 13, row = 15;	// dimension par d�faut au premier niveau

	switch (lvl)
	{
	case 1:	Create_All_Grids(linkGrid, wallGrid, spwnGrid, col, row);	break;
	case 2:	Resize_All_Grids(linkGrid, wallGrid, spwnGrid, col, row);	break;
	case 3:	Resize_All_Grids(linkGrid, wallGrid, spwnGrid, col, row);	break;
	case 4:	Resize_All_Grids(linkGrid, wallGrid, spwnGrid, col, row);	break;
	case 5:	Resize_All_Grids(linkGrid, wallGrid, spwnGrid, col, row);	break;
	case 6:	Resize_All_Grids(linkGrid, wallGrid, spwnGrid, col, row);	break;
	case 7:	Resize_All_Grids(linkGrid, wallGrid, spwnGrid, col, row);	break;
	}
	
}