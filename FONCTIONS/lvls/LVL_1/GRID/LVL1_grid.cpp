

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


	// NOTE: J'aimerais pouvoir cr�er et delete un grid, mais la solution semble plus complexe que anticip�.
	//		 Alors pour l,instant je vais cr�er un grid qui va juste rester. Je reviendrais plus tard
	//		Voici th�oriquement comment �a pourrait se faire selon les internets

	//// Cr�ation du array
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



	// = new enum de trucs pr�sent dans le grid
	
	
// pour delete un new array					delete[] array;
}

