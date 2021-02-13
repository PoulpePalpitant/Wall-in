#pragma once

#include "coord.h"
#include "../grid/linkgrid.h"
#include "direction.h"


// MAP
// La map est l'air du jeu. La dimension de celle-ci est donnée en x et y et dépend de la dimension du grid prinicpal(LinkGrid). Sert principalement pour l'affichage

extern const Distance GAP_BTW_GRID;	
extern bool gBorderShown;

class Map
{
private:
	Distance length;	
	Distance height;	
	Distance limit[4];	
	
public:
	Distance Get_Length() { return length; }
	Distance Get_Height() { return height; }
	Distance Get_Limit(Direction boxSide) { return limit[boxSide]; }	
	Distance Get_Ctr_X() { return ((limit[RIGHT] - limit[LEFT]) / 2); }	
	Distance Get_Ctr_Y();

	void Resize(LinkGrid& linkGrid);	
};

extern Map map;	


// DON'T PUT ; AFTER dans une méthode de class{					
//						}