#pragma once

#include "linkgrid.h"
#include "../walls/walls.h"


class WallGrid : public Grid
{
private:
	Axis gridAxis;				// Le sens vertical ou horizontal des walls. Ne doit jamais changer
public:								
	WallGrid(Axis axis) {	
		this->gridAxis = axis;		//Constructor
				wall = NULL;
	}

	Wall** wall;						// Va contenir le Grid contenant les pointeurs vers les arrays de Walls
	void Create(LinkGrid& linkGrid);	// Cr�er le Grid. (Les dimensions d�pendent du LinkGrid) ET Assignent une valeur XY pour chacun des �l�ments du Grid 
	void Resize(LinkGrid& linkGrid);	// Redimensionne.... Mais d�truit aussi le grid...
	void Adapt_To_LinkGrid_Size(int &col, int & row, LinkGrid& linkGrid);	// Calcul les dimensions qu'aura le grid selon celle des Link Grid
	Axis Get_Grid_Axis() { return gridAxis; }				// Acc�s vers l'axe des murs
	bool Is_Wall_here(GrdCoord);		// WHERE IS WALL? I CAN'T FIND IT!
	GrdCoord Find_Wall_Btwn_Links();						// Trouve le wall entre deux Link

};

