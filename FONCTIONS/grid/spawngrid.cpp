#include "spawngrid.h"

// LE GRID DE SPAWNBORDERS

extern Spawn_Grid spawnGrid = {};


void Spawn_Grid::Resize(LinkGrid& linkGrid)		// Redimensionne.... Mais d�truit aussi le grid...
{
	// DESTRUCTION
	for (int i = 0; i < 4; ++i) {
		delete[]  this->border[i].spawn;	// Spawn est un tableau de spawns, contenu dans une tableau de spawnborder nomm� border
		//delete[] this->border				// Supprime le tableaux de borders = not what i want here
	}

	Create(linkGrid);	// Cr�ation de tous les �l�ments spawns sur chacunes des bordures	
}
void Spawn_Grid::Create(LinkGrid& linkGrid)	// Cr�ation de tous les �l�ments spawns sur chacunes des bordures	
{
	// CR�ATION
	for (int boxSide = 0; boxSide < 4; boxSide++)
		this->border[boxSide].Create_Border(linkGrid, (Direction)boxSide);
}

