#pragma once 

#include "../grid/spawngrid.h"

struct InvalidSpw{
	int spw;
	InvalidSpw* nxt;
};

struct InvalidBorders{	
	InvalidSpw* start[4], *end[4], *it;		// 1 Seul it�rateur
	int count[4];	// Permet de v�rifier si on � atteint la limite de spawn sur une bordure
};

/* Chaque bordures va contenir une liste de tout les spawns qui seraient potentiellements invalid�s durant un cycle de spawn */


class InvalidSpwCrd {
private:
	static InvalidBorders invSpw;	// La liste contenant tout les spawns invalides sur chacunes des bordures


public:
	static bool Is_Full(int border);
	static bool Is_Empty(int border);

	static int Get_Max(int border);	// Donne la dimension max
	static void Add_Invalid_Coord_To_List(SpwCrd spwCrd);// Ajoute une coordonn�e Invalide � la liste. 
	static bool Check_Invalid_Coord_Lists(SpwCrd spwCrd);	// V�rifie si le spawn fait partie de la liste
	static void Empty_Invalid_Coord_List();// Cette liste est vid� � la fin des spawns
};

