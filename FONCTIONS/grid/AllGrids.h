#pragma once


#include "linkgrid.h"
#include "wallgrid.h"
#include "spawngrid.h"
#include "../blast/blast.h"

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

	WallGrid* Find_Wall_Grid_From_Axis(Axis ax);								// Trouve le grid de wall qui correspond � un axe
	WallGrid* Find_Wall_Grid_From_Direction(Direction dir);						// Trouve le grid de wall qui correspond � une direction
	WallGrid* Find_Wall_Grid_From_Crd_Incrementor(const GridIndexIncrementor &crd);	// Trouve le grid de wall qui correspond � un axe	
	GrdCoord Convert_LinkCrd_To_WallCrd(GrdCoord linkCrd, Direction dir);		// Trouve un wall qui poss�de la m�me position qu'un Link avec la direction
	GrdCoord Convert_LinkCrd_To_WallCrd(const GridIndexIncrementor &linkCrd);	// Trouve un wall qui poss�de la m�me position qu'un Link avec la polarisation et l'axe
	
	void Activate_Walls_And_Links_From_Blast(Blast* blast);	// record tout les walls et links apr�s un blast
	// Cr�er manuellement une cha�ne de murs et de Links dans une direction
	void Activate_Chain_Of_Walls(GrdCoord grdCrd, Direction dir, int numWalls, WallStrength strength = WallStrength::REGULAR, LinkType type = LinkType::REGULAR);
};

// VARIABLEs GLOBALEs

extern AllGrids gGrids;				// Contient tout les grids
extern LinkGrid* const linkGrid;	// Les pointeurs vers chacun des grids
extern WallGrid *const wallGridVer;	
extern WallGrid *const wallGridHor;		
extern SpawnGrid* const spawnGrid;

