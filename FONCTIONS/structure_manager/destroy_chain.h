#pragma once


#include "../grid/AllGrids.h"


// Liste de Link à détruire

bool empty();			
void push(Link* link);	// Ajoute un Link à détruire de la liste
bool pop(Link* &data);	// Enlève un Link à détruire de la liste


class DestroyChainOfWalls {
	friend class StructureManager;

	static void Add_Children_To_List(Link* parent);
public:
	// Détruit la chaine de link et de mur dépendant d'un Link
	static void Destroy_Chain_Of_Walls(GrdCoord linkCrd = {}, Link* link = NULL);	// Tu peux soit avoir la coord du LINK, soit l'adresse pour le détruire :)
	static bool LameStaticFunction(bool, GrdCoord&, GrdCoord = {2,2});
};






