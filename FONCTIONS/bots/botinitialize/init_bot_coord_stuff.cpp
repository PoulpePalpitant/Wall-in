

#include "../../grid/AllGrids.h"
#include "../bot.h"


// INITIALISATION DES VARIABLES DE POSITIONS
// -----------------------------------------

void Bot::Init_Bot_Coord_Stuff(SpwCrd& spGrdCrd)
{
	static BotSpawner* spawn;
	spawn = &spawnGrid->border[spGrdCrd.border].spawn[spGrdCrd.spwNum];	

	Equal_Coordinates(this->XY, spawn->Get_XY());				// La coordonn�e xy du Bot sera �gale � celle du spawn sur lequel il se trouve
	dir = Find_Opposite_Dir((Direction)spGrdCrd.border);		// La direction de d�placement sera l'oppos� de la direction de son spawn. Si spawn en bas, va se diriger vers le haut Ex: la colonne C repr�sente le num�ro de bordure de spawn(0 � 4, pour chaque c�t� de la console)
	
	nxtWallCrd.Initialize_Axis(dir);				// L'axe d'incr�mentation et la polarisation son intialis�. Manque plus que trouv� la coordXY du premier wall			
	Find_First_Wall_Grd_Index((Direction)spGrdCrd.border, spGrdCrd.spwNum, nxtWallCrd);	
	onAWall = {};	
}

// Ceci permet de trouver la coord( en col et en row) du premier �l�ment "Wall" se trouvant sur le wallgrid que le bot percutera dans sa folle aventure lin�aire
// -------------------------------------------------------------------------------------------------------------------------------------------------------------

void Bot::Find_First_Wall_Grd_Index(Direction indexBoxSide, int indexrow, GridIndexIncrementor& wallcrd)	// ceci doit � tout prix �tre utilis� � la cr�ation du bot
{
	switch (indexBoxSide)
	{
	case UP:case DOWN: wallcrd.index.c = indexrow; break;		
	case LEFT:case RIGHT:wallcrd.index.r = indexrow;			
	}

	switch (indexBoxSide)
	{
	case UP:wallcrd.index.r = 0; break;
	case DOWN: wallcrd.index.r = wallGridHor->Get_Rows() - 1; break;	// La derni�re ligne du wallgrid
	case LEFT:wallcrd.index.c = 0; break;
	case RIGHT: wallcrd.index.c = wallGridVer->Get_Cols() - 1;
	}

}
