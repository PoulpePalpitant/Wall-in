#include "spawngrid.h"

// LE GRID DE SPAWNBORDERS

extern Spawn_Grid spawnGrid = {};


void Spawn_Grid::Resize(LinkGrid& linkGrid)		// Redimensionne.... Mais détruit aussi le grid...
{
	// DESTRUCTION
	for (int i = 0; i < 4; ++i) {
		delete[]  this->border[i].spawn;	// Spawn est un tableau de spawns, contenu dans une tableau de spawnborder nommé border
		//delete[] this->border				// Supprime le tableaux de borders = not what i want here
	}

	Create(linkGrid);	// Création de tous les éléments spawns sur chacunes des bordures	
}
void Spawn_Grid::Create(LinkGrid& linkGrid)	// Création de tous les éléments spawns sur chacunes des bordures	
{
	// CRÉATION
	for (int boxSide = 0; boxSide < 4; boxSide++)
		this->border[boxSide].Create_Border(linkGrid, (Direction)boxSide);
}

