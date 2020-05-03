
#include <iostream>   // pour le cout

#include "../../../../MAIN/console(v1.9).h"
#include "LVL1_grid.h"

using namespace std;

// INITIALISE LES DIMENSIONS MAXIMALES DU GRID

void INIT_Grids()
{
	// Ce que j'essaie de faire /,:
	static const GrdCoord MAXgrdMain = { 15,13 };		// Les dimensions constantes du grid du niveau 1
	static const GrdCoord MAXgrdWall = { 15, 13 };		
	pMaxGrdMain = &MAXgrdMain;	// Pointe vers les dimensions constantes du Main grid
	pMaxGrdWall = &MAXgrdWall;	// Pointe vers les dimensions constantes du Wall grid


	static const int MaxGrdMainC = 15;		// Les dimensions constantes du grid du niveau 1
	static const int MaxGrdMainL = 13;		// Les dimensions constantes du grid du niveau 1




	CaseMainGrd MainGrd1[10][12] = {};		// Le grid du Level 1!
	
	// le grid est bien là
	for (int l = 0; l < pMaxGrdMain->l; l++)
	{
		for (int c = 0; c < pMaxGrdMain->c; c++)
		{
			gotoxy(START_X + c * DELTA_X, START_Y + l * DELTA_Y); cout << ".";
		}
	}



	// NOTE: J'aimerais pouvoir créer et delete un grid, mais la solution semble plus complexe que anticipé.
	//		 Alors pour l,instant je vais créer un grid qui va juste rester. Je reviendrais plus tard
	//		Voici théoriquement comment ça pourrait se faire selon les internets

	//// Création du array qui pointe vers un tableau de pointer qui pointe sur un tableau de int :O
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

