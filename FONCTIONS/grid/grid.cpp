

#include "grid.h"
#include "../console/sweet_cmd_console.h"


int START_X = 0;	// D�pend de l'�cran du joueur mon gars!!!!
int START_Y = 0;

const int DELTA_X = 5;	
const int DELTA_Y = 3;	// Note:  Le joueur peut uniquement se d�placer sur cette distance


// Servira � naviguer dans les tableaux des grids
GrdCoord gGrd;


// LOGIQUES DES GRIDS: Link GRID, WALL GRID ET SPAWN GRID
// ------------------------------------------------------

/*	
"POST-MORTEM
	Ceci est extr�mement stupide xD"


	Chaque niveau est consitu� de plusieurs Grids logiques qui permettent notamment de naviguer l'espace de la console.
	Le terrain de jeu est construit par un Grid (LinkGrd) sur lequelle le joueur peut se d�placer. Le joueur ne peut sortir
	de Ce Grid, et ne peut pas bouger autrement que par l'intervalle qui s�pare chaque point du Grid. Le joueur peut tirer,
	et ces tirs laissent une ligne qu'on appel simplement un Wall. Chaque Walls sont reli� par les "Link" du LinkGrid comme 
	�a : O----O----O		 Lgrid = O    Walls = ---- 
	
	Pour retracer la localisation de chaque wall, un Grid horizontal[col][lig] et vertical[col][lig] est n�cessaire.
	� NOTER: contrairement au LinkGrid qui est constitu� d'unique coordonn�es XY dans la console, un Wall sur le wall grid
	est constitu� de plusieurs charat�res sur une suite de case. Pour convertir la position logique en une Coord XY	dans 
	la console on proc�de avec la logique suivante : le premier char du wall se trouve � +1 case du main grid	 

	 LEGENDE:	L= XY LinkGrid			W = XY WallGrid 		Le reste des walls : ---, |||

		HorizontalWall Grid:	LW---	(+1 en X)				Vertical Wall Grid : M	(+1 en Y)
																					 w
																					 |
																					 |
	SPAWN GRID: 
	Le spawngrid sert � faire spawner des "bots". Il est constitu� de 4 "bordures" de spawns(1 pour chaque c�t� de la box du jeu,
	 contenants chaucun un certain nombre de spawns (coord XY). Ce "grid"  se situe en � l'ext�rieur du Linkgrid (distance de  map.Get_Limit +/- GAP_BTW_GRID)
	 La position xY suivent la m�me logiques que les wallGrid, c'est � dire un d�calage de 1 case droite, ou en bas de chaque Links

	 Tout ces grids sont contenus dans un objet global nomm� AllGrids.
*/

void Grid::Create(int col, int row, int** &grid)	 // Ceci ent�me la CR�ATION D'UN GRID!
{
	grid = new int * [col];

	// Chaques colonnes aura une liste de lignes(rows) contenant chacun 1 �l�ment du Grid
	for (int i = 0; i < col; ++i) {
		grid[i] = new int[row];

		for (int j = 0; j < row; j++){
			grid[i][j] = {};
		}
	}
	UpdSize(col, row);	
}

// D�truit tout ce qui se trouvait sur le grid et le redimensionne
void Grid::Resize(int col, int row, int** &grid)
{	
	int maxCol = this->Get_Cols();	

	for (int i = 0; i < maxCol; ++i) {
		delete[] grid[i];
	}

	delete[] grid;	

	Create(col, row, grid);
}

bool Grid::Is_Inbound(GrdCoord crd)
{
	if (crd.c > this->Get_Cols() - 1 || crd.r > this->Get_Rows() - 1)	
		return false;

	if (crd.c < 0 || crd.r < 0)		
		return false;

	return true;
}

// Cr�er une �galit� entre deux coordonn�es XY.		La premi�re sera �gale � la seconde
void Equal_Coordinates(GrdCoord& from, GrdCoord to)
{
	from.c = to.c;
	from.r = to.r;
}

bool Are_Equal(const GrdCoord &crd1, const GrdCoord &crd2)
{
	if (crd1.c == crd2.c)
	{
		if (crd1.r != crd2.r)
			return false;
	}
	else
		return false;

	return true;	// Les deux sont identiques
}