
#include <iostream>   // pour le cout

#include "../../../../MAIN/console(v1.9).h"
#include "../../../grid/grid.h"


#include "LVL1_grid.h"
using namespace std;




void INIT_Grids()
{
	// Ce que j'essaie de faire /,:
	//static const GrdCoord const  MAXgrdMain = { 15,13 };		// Les dimensions constantes du grid du niveau 1
	//static const GrdCoord MAXgrdWall = { 15, 13 };		
	//pMaxGrdMain = &MAXgrdMain;	// Pointe vers les dimensions constantes du Main grid
	//pMaxGrdWall = &MAXgrdWall;	// Pointe vers les dimensions constantes du Wall grid


	
	// Dimensions des Main grids de chacun des niveaux
	static const int LVL1_GRDMAIN_MAX_C = 15; // Les dimensions constantes du grid du niveau 1
	static const int LVL1_GRDMAIN_MAX_L = 13; // Les dimensions constantes du grid du niveau 1
	Grid MainGrd1[LVL1_GRDMAIN_MAX_C][LVL1_GRDMAIN_MAX_L] = {};		// Le grid du Level 1!


	
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




	// = new enum de trucs présent dans le grid
	
	
// pour delete un new array					delete[] array;
}

