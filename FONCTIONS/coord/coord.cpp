

#include "../grid/grid.h"
#include "coord.h"





// On obtient la coord X et Y selon la position logique du maingrid
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

void Get_HorWallGrdXY(int& col, int& lig)	
{
	col = Get_GrdX(col) + 1;		// Le COORD XY du wall horizontal se trouvera tjrs une case plus loin en X(+1) que celle du Main Grid
	lig = Get_GrdY(lig);			// Voir grid.h -> WallGrd pour la logique
}

void Get_VerWallGrdXY(int& col, int& lig)
{
	col = Get_GrdX(col);			// Le COORD XY du wall vertical se trouvera tjrs une case plus loin en Y(+1) que celle du Main Grid
	lig = Get_GrdY(lig) + 1;		// Voir grid.h -> WallGrd pour la logique
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