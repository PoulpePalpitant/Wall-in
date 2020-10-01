#pragma once


#include "linkgrid.h"
#include "wallgrid.h"
#include "spawngrid.h"
#include "../blast/blast.h"

class AllGrids	// Tout les grids au même endroit
{

public:
	LinkGrid linkGrd;
	SpawnGrid spawnGrd;
	WallGrid wallGrdHor;
	WallGrid wallGrdVer;

	bool areCreated = false;

	// Met tout ça à zéro
	AllGrids() : wallGrdHor(HOR) , wallGrdVer(VER)	// axe des wallgrid
	{
		linkGrd = {};
		spawnGrd = {};
	}

	WallGrid* Find_Wall_Grid_From_Axis(Axis ax);								// Trouve le grid de wall qui correspond à un axe
	WallGrid* Find_Wall_Grid_From_Direction(Direction dir);						// Trouve le grid de wall qui correspond à une direction
	WallGrid* Find_Wall_Grid_From_Crd_Incrementor(const GridIndexIncrementor &crd);	// Trouve le grid de wall qui correspond à un axe	
	GrdCoord Convert_LinkCrd_To_WallCrd(GrdCoord linkCrd, Direction dir);		// Trouve un wall qui possède la même position qu'un Link avec la direction
	GrdCoord Convert_LinkCrd_To_WallCrd(const GridIndexIncrementor &linkCrd);	// Trouve un wall qui possède la même position qu'un Link avec la polarisation et l'axe
	void Remove_All_Bots_From_Grid();	// Si tu élimine les bots artificiellement, tu dois aussi les removes du grid

	bool Activate_Walls_And_Links_From_Blast(Blast* blast);	// record tout les walls et links après un blast
	// Créer manuellement une chaîne de murs et de Links dans une direction
	// Par défaut, chaque chaines de murs ne peuvent avoir deux origines, mais tu peux mettre la valeur multipleRoot true  pour que ce soit true... Nope, it odenst work sry
	void Make_Chain_Of_Walls(GrdCoord grdCrd, Direction dir, int numWalls, WallStrength strength = WallStrength::REGULAR, Modifier mod = Modifier::REGULAR, bool multipleRoot = false);

	bool Deal_With_Modifier_Combinations(GrdCoord linkCrd, Modifier blastMod, bool &eraseBlast);
	void Activate_Blocker(GrdCoord crd, bool deactivate = false);	// Active un blocker sans child
	void Corrupt_All_Children();
	void Buff_All_Child_Walls();
}; 

// VARIABLEs GLOBALEs

extern AllGrids gGrids;				// Contient tout les grids
extern LinkGrid* const linkGrid;	// Les pointeurs vers chacun des grids
extern WallGrid *const wallGridVer;	
extern WallGrid *const wallGridHor;		
extern SpawnGrid* const spawnGrid;


// test the all grids
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//char UI; int maxC, maxR;

//// AFFICHE TOUS LES GRIDS 
//maxC = gGrids.linkGrd.Get_Cols();
//maxR = gGrids.linkGrd.Get_Rows();
//UI = LinkSym::PARENT;

//for (int i = 0; i < maxC; i++)	// Affiche Le Link grid
//{
//	for (int j = 0; j < maxR; j++)
//	{
//		crd = gGrids.linkGrd.link[i][j].Get_XY(); gotoxy(crd.x, crd.y); cout << UI;
//	}
//}

//maxC = gGrids.wallGrdHor.Get_Cols();
//maxR = gGrids.wallGrdVer.Get_Cols();

//for (int i = 0; i < maxC; i++)	// Affiche le wall Grid
//{
//	for (int j = 0; j < maxR; j++)
//	{
//		UI = gGrids.wallGrdHor.wall[i][j].Get_Sym();crd = gGrids.wallGrdHor.wall[i][j].Get_XY();

//		UI_Dsp_Char(crd, UI, (Colors)j);


//	}
//}

//maxC = gGrids.wallGrdVer.Get_Cols();
//maxR = gGrids.wallGrdVer.Get_Rows();

//for (int i = 0; i < maxC; i++)	// Affiche le wall Grid
//{
//	for (int j = 0; j < maxR; j++)
//	{
//		UI = gGrids.wallGrdVer.wall[i][j].Get_Sym();crd = gGrids.wallGrdVer.wall[i][j].Get_XY();	UI_Dsp_Char(crd, UI, (Colors)i);

//	}
//}

//for (int i = 0; i < 4; i++)	// Affiche Le spawn Grid
//{
//	for (int j = 0; j < gGrids.spawnGrd.border[i].Get_Num_Spawns(); j++)
//	{
//		//spawnGrid->border[i].spawn[j]->GetSpawnXY(crd); 
//		crd = gGrids.spawnGrd.border[i].spawn[j].Get_XY();
//		ConsoleRender::Add_String(std::to_string(j),crd,(Colors)j);


//	}
//}

//Coord XYCOLOR = { 0,0 };
//for (int i = 0; i < 500; i++)
//{
//	Change_Color(i);
//	XYCOLOR.x++;

//	cout << i;

//	if (XYCOLOR.x == 20)
//	{
//		XYCOLOR.x = 0;
//		XYCOLOR.y++;
//	}
//}
