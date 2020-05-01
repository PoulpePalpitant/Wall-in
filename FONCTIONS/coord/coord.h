#pragma once


int Get_GrdX(int col);	//	La conversion d'une position logique en colonne du main Grd vers la coord X dans la console
int Get_GrdY(int lig);	//	La conversion d'une position logique en ligne du main Grd vers la coord Y dans la console
void Get_GrdXY(int& col, int& lig);	// La conversion logique d'une coordonnée (col, lig) en un point xy de la console

void Get_HorWallGrdXY(int& col, int& lig);	//	La conversion d'une Coord du Grd de Walls horizontale en coord XY 
void Get_VerWallGrdXY(int& col, int& lig);	//	La conversion d'une Coord du Grd de Walls verticale en coord XY 

int Get_WallGrdX(int col);	// same old shit
int Get_WallGrdY(int lig);	//







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