#pragma once


#include "../grid/AllGrids.h"


// Liste de Link � d�truire

bool empty();			
void push(Link* link);	// Ajoute un Link � d�truire de la liste
bool pop(Link* &data);	// Enl�ve un Link � d�truire de la liste


class DestroyChainOfWalls {
	friend class StructureManager;

	static void Add_Children_To_List(Link* parent);
public:
	// D�truit la chaine de link et de mur d�pendant d'un Link
	static void Destroy_Chain_Of_Walls(GrdCoord linkCrd = {}, Link* link = NULL);	// Tu peux soit avoir la coord du LINK, soit l'adresse pour le d�truire :)
	static bool LameStaticFunction(bool, GrdCoord&, GrdCoord = {2,2});
};






