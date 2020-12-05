#pragma once

#include "coord.h"
#include "../grid/linkgrid.h"
#include "direction.h"


// MAP
// La map est l'air du jeu. La dimension de celle-ci est donnée en x et y et dépend de la dimension du grid prinicpal(LinkGrid). Sert principalement pour l'affichage

extern const Distance GAP_BTW_GRID;	// La distance qui sépare l'air du jeu définis par les Limit de la map des spawns
extern bool gBorderShown;

class Map
{
private:
	Distance length;		// La largeur de la map en X
	Distance height;		// La hauteur de la map en Y
	Distance limit[4];	// La bordure de la map ou le joueur peut se déplacer. Représente un point dans la console, mais avec une seule valeur, en x ou y
	
public:
	Distance Get_Length() { return length; }
	Distance Get_Height() { return height; }
	Distance Get_Box_Limit(Direction boxSide) { return limit[boxSide]; }	// Cahcune des Bordures de la map
	Distance Get_Ctr_X() { return ((limit[RIGHT] - limit[LEFT]) / 2); }	// Point central en X
	Distance Get_Ctr_Y();// Point central en Y


	void Resize(LinkGrid& linkGrid);	// Resize selon la dimension du Grid principal(LinkGrid)

public:
	void UI_Draw_Map_Corners();			// Affiche des tit symboles pour montrer la dimension de la map
	void UI_Erase_Map_Corners();		// efface les tits coins

};

extern Map map;	// Déclaration de la map. Sera définis ailleurs, à genre SpawnBorder


// DON'T PUT ; AFTER dans une méthode de class{					
//						}