#pragma once 

#include "../grid/spawngrid.h"

struct InvalidSpw{
	int spw;
	InvalidSpw* nxt;
};

struct InvalidBorders{	
	InvalidSpw* start[4], *end[4], *it;		// 1 Seul itérateur
	int count[4];	// Permet de vérifier si on à atteint la limite de spawn sur une bordure
};

/* Chaque bordures va contenir une liste de tout les spawns qui seraient potentiellements invalidés durant un cycle de spawn */


class InvalidSpwCrd {
private:
	static InvalidBorders invSpw;	// La liste contenant tout les spawns invalides sur chacunes des bordures


public:
	static bool Is_Full(int border);
	static bool Is_Empty(int border);

	static int Get_Max(int border);	// Donne la dimension max
	static void Add_Invalid_Coord_To_List(SpwCrd spwCrd);// Ajoute une coordonnée Invalide à la liste. 
	static bool Check_Invalid_Coord_Lists(SpwCrd spwCrd);	// Vérifie si le spawn fait partie de la liste
	static void Empty_Invalid_Coord_List();// Cette liste est vidé à la fin des spawns
};

