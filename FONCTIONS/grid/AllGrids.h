#pragma once


#include "linkgrid.h"
#include "wallgrid.h"
#include "spawngrid.h"
#include "../blast/blast.h"

class AllGrids	
{

public:
	LinkGrid linkGrd;
	SpawnGrid spawnGrd;
	WallGrid wallGrdHor;
	WallGrid wallGrdVer;

	bool areCreated = false;

	AllGrids() : wallGrdHor(HOR), wallGrdVer(VER)	// axe des wallgrid
	{
		linkGrd = {};
		spawnGrd = {};
	}

	Wall* Find_Wall_From_Link_Coord_Incrementor(GridIndexIncrementor &incre, Direction dir);					
	WallGrid* Find_Wall_Grid_From_Axis(Axis ax);								
	WallGrid* Find_Wall_Grid_From_Direction(Direction dir);						
	WallGrid* Find_Wall_Grid_From_Crd_Incrementor(const GridIndexIncrementor& crd);
	GrdCoord Convert_LinkCrd_To_WallCrd(GrdCoord linkCrd, Direction dir);		
	GrdCoord Convert_LinkCrd_To_WallCrd(const GridIndexIncrementor& linkCrd);	
	void Remove_All_Bots_From_Grid();	// Si tu élimine les bots artificiellement, tu dois aussi les removes du grid
	void Dr_Spawngrid();
	bool Activate_Walls_And_Links_From_Blast(Blast* blast);	

	// Par défaut, chaque chaines de murs ne peuvent avoir deux origines, mais tu peux mettre la valeur multipleRoot true  pour que ce soit true... Nope, it odenst work sry
	void Make_Chain_Of_Walls(GrdCoord grdCrd, Direction dir, int numWalls, WallType wallType = WallType::REGULAR, Modifier mod = Modifier::REGULAR, GrdCoord movePlayer = {-1,-1});
	void Make_Box_Of_Blockers(GrdCoord start, GrdCoord end, bool erase = false);
	void Make_Box_Around(GrdCoord crd, Distance distance = 1, Modifier mod = Modifier::REGULAR, bool erase = false);	

	void Extremely_Dumb_Fix_To_Redraw_Walls();	// Ceci redraw tout les walls, parce que ça arrive que les walls sont pas bien affichés
	void Activate_Link(GrdCoord crd, Modifier mod = Modifier::REGULAR, bool deactivate = false);	
	bool Deal_With_Modifier_Combinations(GrdCoord linkCrd, Modifier blastMod, bool &eraseBlast);
	void Activate_Blocker(GrdCoord crd, bool deactivate = false);	
}; 

// VARIABLEs GLOBALEs

extern AllGrids gGrids;				
extern LinkGrid* const linkGrid;	
extern WallGrid *const wallGridVer;	
extern WallGrid *const wallGridHor;		
extern SpawnGrid* const spawnGrid;

