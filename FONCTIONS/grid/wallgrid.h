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
	GrdCoord Find_Wall_Btwn_Links();						// Trouve le wall entre deux Link
	//GridIndexIncrementor Find_Wall_From_Link_Dir(GrdCoord crd, Direction dir);	// Trouve le wall avec la coord d'un Link et une direction

	//void Activate_Walls_From_Blast(Blast* blast);		// Cr�er des murs(modifie leur valeurs) d'apr�s un certains blast . Quand le joueur tir, �a laisse un mur, et il faut le record dans le grid
	//void UI_Draw_Wall(GridIndexIncrementor crd);	// Affiche un MUR		
};

/*

	quoi mettre dans allwallgrids et dans wallgrids pour record le blast


	transformer allwAllGrids en AllGrids



*/

