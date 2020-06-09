

#include "../grid/AllGrids.h"

#include "invalid_spwns.h"


 InvalidBorders InvalidSpwCrd::invSpw = {};	// La liste contenant tout les spawns invalides sur chacunes des bordures


 // Nombre de spw max sur une bordure
int InvalidSpwCrd::Get_Max(int border)
{
	if (border == LEFT || border == RIGHT)			// Les bordures LEFT et RIGHT sont verticaux
		return spawnGrid->Get_MaxSpwnCrdY();
	else
		return spawnGrid->Get_MaxSpwnCrdX();
}

bool InvalidSpwCrd::Is_Full(int border)
{
	if (invSpw.count[border] == Get_Max(border))	// le max doit être à moins 1???? pt pas
		return true;		// la border doit être entre 0-3
	else
		return false;
}

bool InvalidSpwCrd::Is_Empty(int border)
{
	return invSpw.count[border] ? false : true;	// Si = 0, alors Empty it is
}

void InvalidSpwCrd::Add_Invalid_Coord_To_List(SpwCrd spwCrd)	// crd 
{
	int border = spwCrd.border;	// Pour alléger la lisibilité... I hope

	if (Is_Empty(border))	// list vide
		invSpw.start[border] = invSpw.end[border] = new InvalidSpw;
	else
		invSpw.end[border] = invSpw.end[border]->nxt = new InvalidSpw;	// ajout d'un élément

	invSpw.end[border]->spw = spwCrd.spwNum;	// Le num du spawn
	invSpw.end[border]->nxt = NULL;	// Bonne pratique
	invSpw.count[spwCrd.border]++;	// Ajout d'un élément à la liste
}


bool InvalidSpwCrd::Check_Invalid_Coord_Lists(SpwCrd spwCrd)	// 4 listes pour chaques boxside
{
	if (Is_Empty(spwCrd.border))	// N'est pas dans la liste
		return false;


	if (Is_Full(spwCrd.border))	// est dans la liste
		return true;
	else
	{
		invSpw.it = invSpw.start[spwCrd.border];	// Premier élément de la liste à vérifier

		while (invSpw.it != NULL)	// Pas atteint la fin
		{			
			if (invSpw.it->spw == spwCrd.spwNum)
				return true;

			invSpw.it = invSpw.it->nxt;		// Prochain élément		
		}
	}
	return false;
}

void InvalidSpwCrd::Empty_Invalid_Coord_List()// Cette liste est vidé à la fin des spawns
{
	for (int i = 0; i < 4; i++)	// # bordures			BORUDRE!
	{
		if (Is_Empty(i))
			continue;
		else {
			if (invSpw.it = invSpw.start[i]) {
				invSpw.start[i] = invSpw.start[i]->nxt;
				delete invSpw.it;
			}

			invSpw.it = invSpw.start[i] = invSpw.end[i] = NULL;	// bonne pratique
		}
	}
}
