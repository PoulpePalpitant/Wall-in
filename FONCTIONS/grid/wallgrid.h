#pragma once

#include "linkgrid.h"
#include "../walls/walls.h"
#include "../blast/blast.h"

class WallGrid : public Grid
{
private:
	int Nb_Of_Walls_Per_Blast(Blast* blast);		// Calcul le nombre de walls à enregistrer après un blast.

public:
	Axis gridAxis;				// Le sens vertical ou horizontal des walls. Ne doit jamais changer
	
								//Constructor
	WallGrid(Axis axis) { this->gridAxis = axis; wall = NULL; }

	Wall** wall;						// Va contenir le Grid contenant les pointeurs vers les arrays de Walls
	void Create(LinkGrid& linkGrid);	// Créer le Grid. (Les dimensions dépendent du LinkGrid) ET Assignent une valeur XY pour chacun des éléments du Grid 
	void Resize(LinkGrid& linkGrid);	// Redimensionne.... Mais détruit aussi le grid...
	void Adapt_To_LinkGrid_Size(int &col, int & row, LinkGrid& linkGrid);	// Calcul les dimensions qu'aura le grid selon celle des Link Grid
	Axis Get_Grid_Axis() { return gridAxis; }	// Accès vers l'axe des murs
	GrdCoord Find_Wall_Btwn_Links();		// Trouve le wall entre deux Link
	GridIndexIncrementor Find_Wall_With_LinkDir();		// Trouve le wall avec la coord d'un Link et une direction


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

	void Activate_Walls_From_Blast(Blast* blast);	// Créer des murs(modifie leur valeurs) d'après un certains blast . Quand le joueur tir, ça laisse un mur, et il faut le record dans le grid
	WallGrid* Find_Grid_From_Direction(Direction dir);
};

/*

	quoi mettre dans allwallgrids et dans wallgrids pour record le blast


	transformer allwAllGrids en AllGrids



*/



// VARIABLES GLOBAL des Grids(déclaration)

extern AllWallGrids wallGrids;	 
extern WallGrid wallGridHor;
extern WallGrid wallGridVer;