#pragma once


#include "../grid/AllGrids.h"
#include "../time/movement_timer.h"

// Une item du stack de link à détruire
struct LinkToDestroy
{
	Link* link = NULL; /*data*/
	LinkToDestroy* below = NULL;
};

struct Chain // une pile d'item chainés
{
	LinkToDestroy* top = NULL; // indique le dessus de la pile
	int count = 0;	// don't need
};

class Chain_To_Destroy
{
	friend class DestroyChainOfWalls;

	MovementTimer timer;	// Vitesse à laquelle on détruit les murs
	
	Chain chain;
	Link* toDeactivate = NULL;
	Link *toErase = NULL;	// Le Link à désactiver actuellement, et son parent

	Wall* parentWall;					// Le mur à détruire entre deux Link
	Chain_To_Destroy* nxt = NULL;
	


	bool empty();
	void push(Link* link);	// Ajoute un Link à détruire de la liste
	bool pop(Link*& data);	// Enlève un Link à détruire de la liste
};


class DestroyChainOfWalls {
	friend class StructureManager;
private:
	static Chain_To_Destroy* start;
	static Chain_To_Destroy* end;


	//static void Add_Children_To_List(Link* parent);
	static void Add_Children_To_List(Chain_To_Destroy* chain, Link* parent);
	static void Delete_Parents(Chain_To_Destroy* chain);
	static void Remove_Chain(Chain_To_Destroy* &toRemove, Chain_To_Destroy* &prev);
public:
	// Détruit la chaine de link et de mur dépendant d'un Link
	static void Update_Destruction();
	static void Add_Chain_To_Destroy(GrdCoord crd = {}, Link* link = NULL);
};






