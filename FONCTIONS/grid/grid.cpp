

#include "grid.h"

// CONSTANTES POUR L'AFFICHAGE SEULEMENT
// *************************************

extern const int START_X = 10;	// Position, sur l'axe des X de la console, du coin sup�rieur gauche du MAIN grid
extern const int START_Y = 8;	// Position, sur l'axe des Y de la console, du coin sup�rieur gauche du MAIN grid

extern const int DELTA_X = 5;	// Distance s�parant chaque point du du Main Grid en X 
extern const int DELTA_Y = 3;	// Note:  Le joueur peut uniquement se d�placer sur cette distance


// Servira � naviguer dans les tableaux des grids
GrdCoord gGrd;


// LOGIQUES DES GRIDS: MAIN GRID, WALL GRID ET SPAWN GRID
// ------------------------------------------------------

/*	
	Chaque niveau est consitu� de plusieurs Grids logiques qui permettent notamment de naviguer l'espace de la console.
	Le terrain de jeu est construit par un Grid (main Grd) sur lequelle le joueur peut se d�placer. Le joueur ne peut sortir
	de Ce Grid, et ne peut pas bouger autrement que par l'intervalle qui s�pare chaque point du Grid. Le joueur peut tirer,
	et ces tirs laissent une ligne qu'on appel simplement un Wall. Chaque Walls sont reli� par les point du Main Grid comme 
	�a : O----O----O		 Mgrid = O    Walls = ---- 
	
	Pour retracer la localisation de chaque wall, un Grid horizontal[col][lig] et vertical[col][lig] est n�cessaire.
	� NOTER: contrairement au main Grid qui est constitu� d'unique	Coordonn�es XY dans la console, un Wall sur le wall grid
	est constitu� de plusieurs charat�res sur une suite de case. Pour convertir la position logique en une Coord XY	dans 
	la console on proc�de avec la logique suivante : le premier char du wall se trouve � +1 case du main grid	 

	 LEGENDE:	M= XY Main Grid			W = XY WallGrid 		Le reste des walls : ---, |||

		HorizontalWall Grid:	MW---	(+1 en X)				Vertical Wall Grid : M	(+1 en Y)
																					 w
																					 |
																					 |
	
	SPAWN GRID: ...

*/

// M�thode de Cr�ation de base d'un grid selon les dimensions colonnes et lignes (ici, le grid est de type int, et sera aussi jamais utilis� lol)
void Grid::Create(int col, int row, int** &grid)	 // Ceci ent�me la CR�ATION D'UN GRID!
{
	// Le grid va pointer vers la liste de colonnes
	grid = new int * [col];

	// Chaques colonnes aura une liste de lignes(rows) contenant chacun 1 �l�ment du Grid
	for (int i = 0; i < col; ++i) {
		grid[i] = new int[row];

		for (int j = 0; j < row; j++){
			grid[i][j] = {};	// Peut mettre une valeur par d�faut
		}
	}
	UpdSize(col, row);	// Update le nb de col et de rows
}

// D�truit tout ce qui se trouvait sur le grid et le redimensionne
void Grid::Resize(int col, int row, int** &grid)
{	
	int maxCol = this->Get_Cols();	// Le nombre max de colonnes

	// DESTRUCTION
	for (int i = 0; i < maxCol; ++i) {
		delete[] grid[i];
	}

	delete[] grid;	// D�truit le tableau de tableaux

	// CR�ATION
	Create(col, row, grid);
}

// V�rification de si le nb de col et de row son valide selon la dimension du Grid
bool Grid::Is_Inbound(GrdCoord crd)
{
	if (crd.c > this->Get_Cols() - 1 || crd.r > this->Get_Rows() - 1)	// Validation d'une coordonn�e trop grande
		return false;

	if (crd.c < 0 || crd.r < 0)		// Validation d'une coordonn�e dans les n�gatifs
		return false;

	return true;
}

// Cr�er une �galit� entre deux coordonn�es XY.		La premi�re sera �gale � la seconde
void Equal_Coordinates(GrdCoord& from, GrdCoord to)
{
	from.c = to.c;
	from.r = to.r;
}

// Permet de comparer deux points ensemble. Si les deux ne sont pas �gals, return false
bool Is_Equal(const GrdCoord &crd1, const GrdCoord &crd2)
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