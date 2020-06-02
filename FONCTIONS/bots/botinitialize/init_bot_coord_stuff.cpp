

#include "../../grid/AllGrids.h"
#include "../bot.h"


// INITIALISATION DES VARIABLES DE POSITIONS
// -----------------------------------------

void Bot::Init_Bot_Coord_Stuff(GrdCoord& spGrdCrd)
{
	static Spawn* spawn;
	spawn = &spawnGrid->border[spGrdCrd.c].spawn[spGrdCrd.r];	// Le spawn du bot en question

	Equal_Coordinates(this->XY, spawn->Get_XY());		// La coordonnée xy du Bot sera égale à celle du spawn sur lequel il se trouve
	dir = Find_Opposite_Dir((Direction)spGrdCrd.c);		// La direction de déplacement sera l'opposé de la direction de son spawn. Si spawn en bas, va se diriger vers le haut Ex: la colonne C représente le numéro de bordure de spawn(0 à 4, pour chaque côté de la console)
	
	nxtWallCrd.Initialize_Axis(dir);				// L'axe d'incrémentation et la polarisation son intialisé. Manque plus que trouvé la coordXY du premier wall			
	Find_First_Wall_Grd_Index((Direction)spGrdCrd.c, spGrdCrd.r, nxtWallCrd);	// Tu dois passer somehow ici, les deux index du spawnborder
}



// Ceci permet de trouver la coord( en col et en row) du premier élément "Wall" se trouvant sur le wallgrid que le bot percutera dans sa folle aventure linéaire
// -------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bot::Find_First_Wall_Grd_Index(Direction indexBoxSide, int indexrow, GridIndexIncrementor& wallcrd)	// ceci doit à tout prix être utilisé à la création du bot
{
	switch (indexBoxSide)
	{
	case UP:case DOWN: wallcrd.index.c = indexrow; break;		// Trouve le numero de colonne selon la bordure
	case LEFT:case RIGHT:wallcrd.index.r = indexrow;			// Trouve le numero de row selon la bordure
	}

	switch (indexBoxSide)	// trouve le reste
	{
	case UP:wallcrd.index.r = 0; break;
	case DOWN: wallcrd.index.r = wallGridHor->Get_Rows() - 1; break;	// La dernière ligne du wallgrid
	case LEFT:wallcrd.index.c = 0; break;
	case RIGHT: wallcrd.index.c = wallGridVer->Get_Cols() - 1;
	}

}
