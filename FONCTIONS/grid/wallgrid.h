#pragma once

#include "linkgrid.h"
#include "../walls/walls.h"

class WallGrid : public Grid
{
private:
public:
	Axis gridAxis;				// Le sens vertical ou horizontal des walls. Ne doit jamais changer
	//Constructor
	WallGrid(Axis axis) { this->gridAxis = axis; wall = NULL; }

	Wall** wall;						// Va contenir le Grid contenant les pointeurs vers les arrays de Walls
	void Create(LinkGrid& linkGrid);	// Cr�er le Grid. (Les dimensions d�pendent du LinkGrid) ET Assignent une valeur XY pour chacun des �l�ments du Grid 
	void Resize(LinkGrid& linkGrid);	// Redimensionne.... Mais d�truit aussi le grid...
	void Adapt_To_LinkGrid_Size(int &col, int & row, LinkGrid& linkGrid);	// Calcul les dimensions qu'aura le grid selon celle des Link Grid
	Axis Get_Grid_Axis() { return gridAxis; }	// Acc�s vers l'axe des murs

	// Set X and Y on Grid element?
};

// Ceci va contenir les deux wallGrids (horizontal et vertical)
class AllWallGrids {
public:
	WallGrid* hor;
	WallGrid* ver;
	AllWallGrids(WallGrid &horizontal, WallGrid &vertical)
	{
		hor = &horizontal;
		ver = &vertical;
	}
};

// VARIABLES GLOBAL des Grids(d�claration)

extern AllWallGrids wallGrids;	 
extern WallGrid wallGridHor;
extern WallGrid wallGridVer;