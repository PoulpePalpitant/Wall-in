

#include "grid.h"

// CONSTANTES POUR L'AFFICHAGE SEULEMENT
// *************************************

extern const int START_X = 10;	// Position, sur l'axe des X de la console, du coin supérieur gauche du MAIN grid
extern const int START_Y = 8;	// Position, sur l'axe des Y de la console, du coin supérieur gauche du MAIN grid

extern const int DELTA_X = 5;	// Distance séparant chaque point du du Main Grid en X 
extern const int DELTA_Y = 3;	// Note:  Le joueur peut uniquement se déplacer sur cette distance


// Servira à naviguer dans les tableaux des grids
GrdCoord gGrd;


// LOGIQUES DES GRIDS: MAIN GRID, WALL GRID ET SPAWN GRID
// ------------------------------------------------------

/*	
	Chaque niveau est consitué de plusieurs Grids logiques qui permettent notamment de naviguer l'espace de la console.
	Le terrain de jeu est construit par un Grid (main Grd) sur lequelle le joueur peut se déplacer. Le joueur ne peut sortir
	de Ce Grid, et ne peut pas bouger autrement que par l'intervalle qui sépare chaque point du Grid. Le joueur peut tirer,
	et ces tirs laissent une ligne qu'on appel simplement un Wall. Chaque Walls sont relié par les point du Main Grid comme 
	ça : O----O----O		 Mgrid = O    Walls = ---- 
	
	Pour retracer la localisation de chaque wall, un Grid horizontal[col][lig] et vertical[col][lig] est nécessaire.
	À NOTER: contrairement au main Grid qui est constitué d'unique	Coordonnées XY dans la console, un Wall sur le wall grid
	est constitué de plusieurs charatères sur une suite de case. Pour convertir la position logique en une Coord XY	dans 
	la console on procède avec la logique suivante : le premier char du wall se trouve à +1 case du main grid	 

	 LEGENDE:	M= XY Main Grid			W = XY WallGrid 		Le reste des walls : ---, |||

		HorizontalWall Grid:	MW---	(+1 en X)				Vertical Wall Grid : M	(+1 en Y)
																					 w
																					 |
																					 |
	
	SPAWN GRID: ...

*/

// Méthode de Création de base d'un grid selon les dimensions colonnes et lignes (ici, le grid est de type int, et sera aussi jamais utilisé lol)
void Grid::Create(int col, int row, int** &grid)	 // Ceci entâme la CRÉATION D'UN GRID!
{
	// Le grid va pointer vers la liste de colonnes
	grid = new int * [col];

	// Chaques colonnes aura une liste de lignes(rows) contenant chacun 1 élément du Grid
	for (int i = 0; i < col; ++i) {
		grid[i] = new int[row];

		for (int j = 0; j < row; j++){
			grid[i][j] = {};	// Peut mettre une valeur par défaut
		}
	}
	UpdSize(col, row);	// Update le nb de col et de rows
}

// Détruit tout ce qui se trouvait sur le grid et le redimensionne
void Grid::Resize(int col, int row, int** &grid)
{	
	int maxCol = this->Get_Cols();	// Le nombre max de colonnes

	// DESTRUCTION
	for (int i = 0; i < maxCol; ++i) {
		delete[] grid[i];
	}

	delete[] grid;	// Détruit le tableau de tableaux

	// CRÉATION
	Create(col, row, grid);
}

// Vérification de si le nb de col et de row son valide selon la dimension du Grid
bool Grid::Is_Inbound(GrdCoord crd)
{
	if (crd.c > this->Get_Cols() - 1 || crd.r > this->Get_Rows() - 1)	// Validation d'une coordonnée trop grande
		return false;

	if (crd.c < 0 || crd.r < 0)		// Validation d'une coordonnée dans les négatifs
		return false;

	return true;
}

// Créer une égalité entre deux coordonnées XY.		La première sera égale à la seconde
void Equal_Coordinates(GrdCoord& from, GrdCoord to)
{
	from.c = to.c;
	from.r = to.r;
}

// Permet de comparer deux points ensemble. Si les deux ne sont pas égals, return false
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