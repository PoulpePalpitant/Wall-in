#pragma once

#include "linkgrid.h"
#include "../walls/walls.h"


class WallGrid : public Grid
{
private:
	Axis gridAxis;				// Le sens vertical ou horizontal des walls. Ne doit jamais changer
public:								
	WallGrid(Axis axis) {	
		this->gridAxis = axis;		
				wall = NULL;
	}

	Wall** wall;						// Va contenir le Grid contenant les pointeurs vers les arrays de Walls
	void Create(LinkGrid& linkGrid);	
	void Resize(LinkGrid& linkGrid);	
	void Adapt_To_LinkGrid_Size(int &col, int & row, LinkGrid& linkGrid);	
	Axis Get_Grid_Axis() { return gridAxis; }				
	bool Is_Wall_here(GrdCoord);		// WHERE IS WALL? I CAN'T FIND IT!
};

