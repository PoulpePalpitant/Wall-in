#pragma once


#include "linkgrid.h"
#include "wallgrid.h"
#include "spawngrid.h"





class AllGrids	// Tout les grids au m�me endroit
{

public:
	LinkGrid linkGrd;
	SpawnGrid spawnGrd;
	WallGrid wallGrdHor;
	WallGrid wallGrdVer;

	// Met tout �a � z�ro
	AllGrids() : wallGrdHor(HOR) , wallGrdVer(VER)	// axe des wallgrid
	{
		linkGrd = {};
		spawnGrd = {};
	}

	WallGrid* Find_Wall_Grid_From_Direction(Direction dir);		// Trouve le grid de wall qui correspond � un axe

	void Activate_Walls_And_Links_From_Blast(Blast* blast);	// record tout les walls et links apr�s un blast
	void Activate_Chain_Of_Walls(GridIndexIncrementor grdCrd, BlastType type, int numWalls);	// Cr�er manuellement une cha�ne de murs et de Links dans une direction
};

// VARIABLEs GLOBALEs

extern AllGrids gGrids;				// Contient tout les grids
extern LinkGrid* const linkGrid;	// Les pointeurs vers chacun des grids
extern WallGrid *const wallGridVer;	
extern WallGrid *const wallGridHor;		
extern SpawnGrid* const spawnGrid;

