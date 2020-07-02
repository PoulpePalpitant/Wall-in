#pragma once


#include "../grid/AllGrids.h"
#include "../time/movement_timer.h"

// Une item du stack de link � d�truire
struct LinkToDestroy
{
	Link* link = NULL; /*data*/
	LinkToDestroy* below = NULL;
};

struct Chain // une pile d'item chain�s
{
	LinkToDestroy* top = NULL; // indique le dessus de la pile
	int count = 0;	// don't need
};

class Chain_To_Destroy
{
	friend class DestroyChainOfWalls;

	MovementTimer timer;	// Vitesse � laquelle on d�truit les murs
	
	Chain chain;
	Link* toDeactivate = NULL;
	Link *toErase = NULL;	// Le Link � d�sactiver actuellement, et son parent

	Wall* parentWall;					// Le mur � d�truire entre deux Link
	Chain_To_Destroy* nxt = NULL;
	


	bool empty();
	void push(Link* link);	// Ajoute un Link � d�truire de la liste
	bool pop(Link*& data);	// Enl�ve un Link � d�truire de la liste
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
	// D�truit la chaine de link et de mur d�pendant d'un Link
	static void Update_Destruction();
	static void Add_Chain_To_Destroy(GrdCoord crd = {}, Link* link = NULL);
};






