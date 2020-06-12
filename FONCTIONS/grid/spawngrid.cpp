
#include "../spawns/valid_spwn_intervals.h"
#include "spawngrid.h"


 int SpawnGrid::maxSpwnCrdX;		// Nombre de COORD de spawn Maximum sur les bordures horizontales UP(0) et DOWN(2)
 int SpawnGrid::maxSpwnCrdY;		// Nombre de COORD de spawn Maximum sur les bordures verticales LEFT(1) et RIGHT(3)


void SpawnGrid::Resize(LinkGrid& linkGrid)		// Redimensionne.... Mais d�truit aussi le grid...
{
	// DESTRUCTION
	for (int i = 0; i < 4; ++i) {
		delete[]  this->border[i].spawn;	// Spawn est un tableau de spawns, contenu dans une tableau de spawnborder nomm� border
		//delete[] this->border				// Supprime le tableaux de borders = not what i want here
	}

	Create(linkGrid);	// Cr�ation de tous les �l�ments spawns sur chacunes des bordures	
}

void SpawnGrid::Create(LinkGrid& linkGrid)	// Cr�ation de tous les �l�ments spawns sur chacunes des bordures	
{
	// CR�ATION
	for (int boxSide = 0; boxSide < 4; boxSide++)
		this->border[boxSide].Create_Border(linkGrid, (Direction)boxSide);

	maxSpwnCrdX = this->border[UP].Get_Num_Spawns();		// Nombre de COORD de spawn Maximum sur les bordures horizontales UP(0) et DOWN(2)
	maxSpwnCrdY = this->border[LEFT].Get_Num_Spawns();		// Nombre de COORD de spawn Maximum sur les bordures verticales LEFT(1) et RIGHT(3)
	
	ValidSpwnIntervals::Set_Maximums(maxSpwnCrdX, maxSpwnCrdY);	// shhhhhh, st'un secret

}


// V�rification de si le nb de col et de row son valide selon chacune des bordures du spawn
bool SpawnGrid::Is_Inbound_Everywhere(GrdCoord spwnCrd)
{
	if (spwnCrd.c > 4 - 1)	// Ya juste 4 bordures
		return false;

	for (int i = 0; i < 4; i++)
		if (spwnCrd.r > border[i].Get_Num_Spawns() - 1)	// nombre de spawn max
			return false;

	if (spwnCrd.c < 0 || spwnCrd.r < 0)		// Validation d'une coordonn�e dans les n�gatifs
		return false;

	return true;
}

// V�rification de si le nb de col et de row son valide selon la dimension du Grid
bool SpawnGrid::Is_Inbound(int boxSide, int spwNum)
{
	if (boxSide > 4 - 1)	// Ya juste 4 bordures
		return false;

	if (spwNum > this->border[boxSide].Get_Num_Spawns() - 1)	// nombre de spawn max
		return false;

	if (boxSide < 0 || spwNum < 0)		// Validation d'une coordonn�e dans les n�gatifs
		return false;

	return true;
}