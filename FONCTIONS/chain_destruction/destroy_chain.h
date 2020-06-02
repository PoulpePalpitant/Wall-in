#pragma once


#include "../grid/AllGrids.h"


// Liste de Link à détruire

bool empty();			
void push(Link* link);	// Ajoute un Link à détruire de la liste
bool pop(Link* &data);	// Enlève un Link à détruire de la liste


class DestroyChainOfWalls {

	void Add_Children_To_List(Link* parent);

	void Destroy_Chain_Of_Walls(GrdCoord linkCrd);							// Détruit la chaine de link et de mur dépendant d'un Link


};






