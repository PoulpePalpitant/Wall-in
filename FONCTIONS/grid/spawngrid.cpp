
#include "../spawns/valid_spwn_intervals.h"
#include "spawngrid.h"


 int SpawnGrid::maxSpwnCrdX;		// Nombre de COORD de spawn Maximum sur les bordures horizontales UP(0) et DOWN(2)
 int SpawnGrid::maxSpwnCrdY;		// Nombre de COORD de spawn Maximum sur les bordures verticales LEFT(1) et RIGHT(3)


void SpawnGrid::Resize(LinkGrid& linkGrid)		// Redimensionne.... Mais détruit aussi le grid...
{
	for (int i = 0; i < 4; ++i) {
		delete[]  this->border[i].spawn;	// Spawn est un tableau de spawns, contenu dans une tableau de spawnborder nommé border
	}

	Create(linkGrid);	
}

void SpawnGrid::Create(LinkGrid& linkGrid)	
{
	// CRÉATION
	for (int boxSide = 0; boxSide < 4; boxSide++)
		this->border[boxSide].Create_Border(linkGrid, (Direction)boxSide);

	maxSpwnCrdX = this->border[UP].Get_Num_Spawns();
	maxSpwnCrdY = this->border[LEFT].Get_Num_Spawns();
	
	ValidSpwnIntervals::Set_Maximums(maxSpwnCrdX, maxSpwnCrdY);	// shhhhhh, st'un secret
}

bool SpawnGrid::Is_Inbound_Everywhere(GrdCoord spwnCrd)
{
	if (spwnCrd.c > 4 - 1)	// Ya juste 4 bordures
		return false;

	for (int i = 0; i < 4; i++)
		if (spwnCrd.r > border[i].Get_Num_Spawns() - 1)	// nombre de spawn max
			return false;

	if (spwnCrd.c < 0 || spwnCrd.r < 0)		// Validation d'une coordonnée dans les négatifs
		return false;

	return true;
}

bool SpawnGrid::Is_Inbound(int boxSide, int spwNum)
{
	if (boxSide > 4 - 1 || boxSide < 0)
		return false;

	if (spwNum > this->border[boxSide].Get_Num_Spawns() - 1)	
		return false;

	if (boxSide < 0 || spwNum < 0)	
		return false;

	return true;
}