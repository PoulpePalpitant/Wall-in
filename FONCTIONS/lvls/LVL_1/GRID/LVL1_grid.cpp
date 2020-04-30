

#include "LVL1_grid.h"
using namespace std;

// INITIALISE LES DIMENSIONS MAXIMALES DU GRID

void INIT_Grids()
{
	static const grdCoord MAXgrdMain = { 15,13 };		// Les dimensions constantes du grid du niveau 1
	static const grdCoord MAXgrdWall = { 15, 13 };

	pMAXgrdMain = &MAXgrdMain;	// Pointe vers les dimensions constantes
	pMAXgrdWall = &MAXgrdWall;


	int grid[10][12];


	// NOTE: J'aimerais pouvoir créer et delete un grid, mais la solution semble plus complexe que anticipé.
	//		 Alors pour l,instant je vais créer un grid qui va juste rester. Je reviendrais plus tard
	//		Voici théoriquement comment ça pourrait se faire selon les internets

	//// Création du array
	//int** ary = new int* [sizeY];
	//for (int i = 0; i < sizeY; ++i) {
	//	ary[i] = new int[sizeX];
	//}
	//
	//// Destruction de l'array
	//for (int i = 0; i < sizeY; ++i) {
	//	delete[] ary[i];
	//}
	//delete[] ary;



	// = new enum de trucs présent dans le grid
	
	
// pour delete un new array					delete[] array;
}

