#pragma once


#include "../grid/AllGrids.h"
#include "../time/movement_timer.h"

// Liste de Link à détruire

bool empty();			
void push(Link* link);	// Ajoute un Link à détruire de la liste
bool pop(Link* &data);	// Enlève un Link à détruire de la liste


// Une item du stack de link à détruire
static struct LinkToDestroy
{
	Link* link = NULL; /*data*/
	LinkToDestroy* below = NULL;
};

static struct Chain // une pile d'item chainés
{
	LinkToDestroy* top; // indique le dessus de la pile
	int count;	// don't need
};

class Chains_To_Destroy
{
	MovementTimer timer;	// Vitesse à laquelle on détruit les murs
	Chain chain;
	bool empty();
	void push(Link* link);	// Ajoute un Link à détruire de la liste
	bool pop(Link*& data);	// Enlève un Link à détruire de la liste
};


class DestroyChainOfWalls {
	friend class StructureManager;
private:
	Chains_To_Destroy* start = NULL;
	Chains_To_Destroy* end = NULL;


	static void Add_Children_To_List(Link* parent);
public:
	// Détruit la chaine de link et de mur dépendant d'un Link
	static void Destroy_Chain_Of_Walls(GrdCoord linkCrd = {}, Link* link = NULL);	// Tu peux soit avoir la coord du LINK, soit l'adresse pour le détruire :)
	static bool Add_Chain_ToDestroy(GrdCoord crd, Link* link);
	static bool Update_Destruction();
};






