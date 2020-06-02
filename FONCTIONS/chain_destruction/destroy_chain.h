#pragma once


#include "../grid/AllGrids.h"


// Liste de Link � d�truire

bool empty();			
void push(Link* link);	// Ajoute un Link � d�truire de la liste
bool pop(Link* &data);	// Enl�ve un Link � d�truire de la liste


class DestroyChainOfWalls {

	void Add_Children_To_List(Link* parent);

	void Destroy_Chain_Of_Walls(GrdCoord linkCrd);							// D�truit la chaine de link et de mur d�pendant d'un Link


};






