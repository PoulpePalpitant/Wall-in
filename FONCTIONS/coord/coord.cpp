

#include "../grid/grid.h"
#include "coord.h"





// On obtient la coord X selon la position logique du maingrid
// --------------------------------------------------------

int Get_GrdX(int col)
{
	return START_X + DELTA_X * col;
}

// On obtient la coord Y selon la position logique du maingrd
// ---------------------------------------------------------

int Get_GrdY(int lig)
{
	return START_Y + DELTA_Y * lig;
}


// On obtient la coord X et Y selon la position logique du maingrd
// ---------------------------------------------------------
void Get_GrdXY(int &col, int &lig)	// WATCHOUT :Passage par référence
{
	col = Get_GrdX(col);
	lig = Get_GrdY(lig);
}



// On obtient la coord X selon la position logique du maingrid
// --------------------------------------------------------

int Get_GrdX(int col)
{
	return START_X + DELTA_X * col;
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