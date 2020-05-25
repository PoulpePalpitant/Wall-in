

#include "../grid/grid.h"
#include "coord.h"
#include "direction.h"


// On obtient la coord X et Y selon la position logique du maingrid ()obselete
// --------------------------------------------------------

int Get_GrdX(int col)
{
	return START_X + DELTA_X * col;
}
int Get_GrdY(int lig)
{
	return START_Y + DELTA_Y * lig;
}
void Get_GrdXY(int &col, int &lig)	// WATCHOUT :Passage par référence
{
	col = Get_GrdX(col);
	lig = Get_GrdY(lig);
}

// On obtient la coord X et Y selon la position logique des WallGrid horizontale et vertical
// -----------------------------------------------------------------------------------------

void Get_VerWallGrdXY(int& col, int& lig)
{
	col = Get_GrdX(col);			// Le COORD XY du wall vertical se trouvera tjrs une case plus loin en Y(+1) que celle du Main Grid
	lig = Get_GrdY(lig) + 1;		// Voir grid.h -> WallGrd pour la logique
}

// Permet de comparer deux points ensemble. Si les deux ne sont pas égals, return false
bool Is_Equal(Coord crd1, Coord crd2)
{
	if (crd1.x == crd2.x)
	{
		if (crd1.y == crd2.y)
			return false;
	}
	else
		return false;

	return true;	// Les deux sont identiques
}

// Créer une égalité entre deux coordonnées XY.		La première sera égale à la seconde
void Equal_Coordinates(Coord &from, Coord to)
{
	from.x = to.x;
	from.y = to.y;
}


// Augmente de 1 ou -1 une coordonnée sur les X ou les Y!!
void Increment_Coordinates(CoordIncrementor& coord)		
{
	*coord.axis += coord.polar;
}

// Initialise un CoordIncrementor à partir d'une direction d'incrémentation
void Init_Axis_Incrementor(Direction direction, CoordIncrementor & incre)
{
	switch (direction)
	{
	case UP:	incre.axis = &incre.coord.y;	incre.polar = NEG;break;	// L'incrémentation se fera à la vertical, donc sur l'axe des Y, donc vers le haut avec une polarisation de  -1
	case LEFT:	incre.axis = &incre.coord.x;	incre.polar = NEG;break;
	case DOWN:	incre.axis = &incre.coord.y;	incre.polar = POS;break;
	case RIGHT: incre.axis = &incre.coord.x;	incre.polar = POS;break;
	}
}



//
//
//int Get_WallGrdX(int col)
//{
//
//	Get_GrdX(col) + 1;
//
//}
//
//
//int Get_WallGrdY(int lig)
//{
//	Get_GrdY(lig) + 1;
//
//}