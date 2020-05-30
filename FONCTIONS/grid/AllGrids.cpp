
#include "../player/player.h"

#include "AllGrids.h"


extern AllGrids gGrids = {};	//	 La variable globale contenant tout les grids

// POINTEURS GLOBAux

extern LinkGrid *const linkGrid = &gGrids.linkGrd;			// Pour all�ger l'utilisation des grids.	Pointera toujours vers le m�me LinkGrid 
extern WallGrid* const wallGridHor = &gGrids.wallGrdHor;
extern WallGrid* const wallGridVer = &gGrids.wallGrdVer;
extern SpawnGrid* const spawnGrid = &gGrids.spawnGrd;				// LE GRID DE SPAWNBORDERS


// Trouve quel wallgrid correspond � une direction 
WallGrid* AllGrids::Find_Wall_Grid_From_Direction(Direction dir)
{
	if (dir == UP || dir == DOWN)
		return wallGridVer;			// WallGrid vertical
	else
		return wallGridHor;			// Wallgrid horizontal
}

// Activation d'�l�ments sur les grids:
// ***********************************

void AllGrids::Activate_Walls_And_Links_From_Blast(Blast* blast)
{
	static bool drawPlayer;														// Affiche le joueur, si le dernier Link se retrouve sur la m�me position		//DONT TRY TO UNDESTAND, KEEP GOING, WE DOIN THIS
	blast->length >= blast->nbSteps ? drawPlayer = true : drawPlayer = false;	// Le dernier Link sera certainemennt sur la m�me position que le joueur
	P1.Upd_Sym_From_Direction(blast->dir);	P1.Dis_Player_Sym();				// Affiche le joueur

	linkGrid->Activate_Links_From_Blast(blast, drawPlayer);	
	// bound Link to wall?
	Find_Wall_Grid_From_Direction(blast->dir)->Activate_Walls_From_Blast(blast);	// Active les murs sur le bon grid de wall
}

