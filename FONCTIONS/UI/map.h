#pragma once

#include "coord.h"
#include "../grid/linkgrid.h"
#include "direction.h"


// MAP
// La map est l'air du jeu. La dimension de celle-ci est donn�e en x et y et d�pend de la dimension du grid prinicpal(LinkGrid). Sert principalement pour l'affichage

extern const Distance GAP_BTW_GRID;	// La distance qui s�pare l'air du jeu d�finis par les Limit de la map des spawns

class Map
{
private:
	Distance length;		// La largeur de la map en X
	Distance height;		// La hauteur de la map en Y
	Distance limit[4];	// La bordure de la map ou le joueur peut se d�placer. Repr�sente un point dans la console, mais avec une seule valeur, en x ou y
	public:
	Distance Get_Length() { return length; };
	Distance Get_Height() { return height; };
	Distance Get_Box_Limit(Direction boxSide) { return limit[boxSide]; };	// Cahcune des Bordures de la map
	void Resize(LinkGrid& linkGrid);	// Resize selon la dimension du Grid principal(LinkGrid)
};

extern Map map;	// D�claration de la map. Sera d�finis ailleurs, � genre SpawnBorder