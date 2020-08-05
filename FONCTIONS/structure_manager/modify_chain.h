#pragma once


#include "../grid/AllGrids.h"
#include "../time/movement_timer.h"

// Les trois actions possibles pour la gestion des chaines de murs
enum ModifyChain
{
	DESTROY, BUFF, CORRUPT
};

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

class ChainToModify
{
	friend class ListsOfChainToModify;

	SpeedTimer timer;	// Vitesse � laquelle on d�truit les murs
	
	Chain chain;
	Link* selectedLink = NULL;
	Link *toErase = NULL;		// Le Link � effacer quand tu d�truit une cha�ne de mur. On l'efface APR�S que le mur soit effac�
	ModifyChain modification;	// L'action qui sera faite sur les �l�ments de la cha�ne

	Wall* parentWall;					// Le mur � d�truire entre deux Link
	ChainToModify* nxt = NULL;
	


	bool empty();
	void push(Link* link);	// Ajoute un Link � d�truire de la liste
	bool pop(Link*& data);	// Enl�ve un Link � d�truire de la liste
};


class ListsOfChainToModify {
	friend class StructureManager;
private:
	static ChainToModify* start;
	static ChainToModify* end;


	static void Add_Children_To_List(ChainToModify* chain, Link* parent);

	static void Modify_Element(ChainToModify* chain);	// D�truit un �l�ment de la cha�ne
	
	static void Select_Modification(ChainToModify* chain);
	static void Delete_Parents(ChainToModify* chain);	// D�truit un �l�ment de la cha�ne ainsi que son parent wall
	static void Corrupt(ChainToModify* chain);			// Change le modifier de u link en Corrupted, et de ce fait, le wall aussi
	static void Buff_Walls(ChainToModify* chain);		// Buff les walls 

	static void Remove_Chain(ChainToModify* &toRemove, ChainToModify* &prev);
public:
	// D�truit la chaine de link et de mur d�pendant d'un Link
	static void Annihilate_All_Links();	// Efface tout les murs et les links sur tout les grids
	static void Update_Chain_Modification();
	static void Add_Chain_To_Modify(GrdCoord crd = {}, Link* link = NULL, bool excludeParent = false, ModifyChain theModif = DESTROY);
};






