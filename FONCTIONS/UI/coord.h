#pragma once

#include "console(v1.9).h"
#include "polarisation.h"
#include "direction.h"

using Distance = int;	// Les distances






struct Coord { int x; int y; };	// Coordonn�e xy dans la console windows

struct CoordIncrementor {
	Coord coord;			// La coordonn�e en xy ou en Col/row
	Polarization polar;		// La polarisation positive ou n�gative du d�placement. +1 (pos) = Droite/Bas : -1 (neg) = Left/haut
	int* axis;				// Le pointeur vers l'axe � incr�menter
};

extern Coord gFrom;				// position de d�part 
extern Coord gTo;				// position d'arriv�e


int Get_GrdX(int col);	//	La conversion d'une position logique en colonne du main Grd vers la coord X dans la console
int Get_GrdY(int lig);	//	La conversion d'une position logique en ligne du main Grd vers la coord Y dans la console
void Get_GrdXY(int& col, int& lig);	// La conversion logique d'une coordonn�e (col, lig) en un point xy de la console

void Set_WallGrdXY(int& col, int& lig);	//	La conversion d'une Coord du Grd de Walls horizontale en coord XY 
void Get_VerWallGrdXY(int& col, int& lig);	//	La conversion d'une Coord du Grd de Walls verticale en coord XY 

int Get_WallGrdX(int col);	// same old shit
int Get_WallGrdY(int lig);	//
bool Is_Equal(Coord crd1, Coord crd2);				// V�rification d'une �galit� entre deux coordonn�es XY
void Equal_Coordinates(Coord &from, Coord to);					// Cr�er une �galit� entre deux coordonn�es XY
void Increment_Coordinates(CoordIncrementor& coord);			// Augmente de 1 ou -1 une coordonn�e sur les X ou les Y!!
void Init_Axis_Incrementor(Direction direction, CoordIncrementor& incre);	// Initialise une variable de type CoordIncrementor � l'aide d'une direction pour dirig� l'incr�mentation








//
//
//
//Main axe
//
//main axe ++ ou --
//
//
//gotoxy(int main axe,)
//
//ifmainaxe = x
//gotoxy(mainaxe,y)
//else
//gotoxy(x, mainaxe)