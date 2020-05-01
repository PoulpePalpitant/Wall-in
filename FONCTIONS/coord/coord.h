#pragma once


int Get_GrdX(int col);	//	La conversion d'une position logique en colonne vers la coord X dans la console
int Get_GrdY(int lig);	//	La conversion d'une position logique en ligne vers la coord Y dans la console
void Get_GrdXY(int& col, int& lig);	// La conversion logique d'une coordonnée (col, lig) et un point xy



int Get_WallGrdX(int col);	// 
int Get_WallGrdY(int lig);	//
int Get_HorWallGrdXY(int &col,int& lig);	//
int Get_VerWallGrdXY(int &col,int& lig);	//

int Get_GrdX(int col);	// 
int Get_GrdY(int lig);	//




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